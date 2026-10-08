#pragma once

#include <algorithm>
#include <cassert>
#include <random>
#include <string>
#include <vector>

namespace yesantikiss {
    struct RollingHash {
        using ull = unsigned long long;
        static constexpr ull MOD = (1ULL << 61) - 1;
    
        // 共有資源（全インスタンスで共通）
        inline static ull base = 0;
        inline static std::vector<ull> pow_base;
    
        std::vector<ull> hash;  // hash[i] = S[0..i) のハッシュ
        int n = 0;
    
        // 2^61-1 用の演算
        static inline ull add(ull a, ull b) {
            ull c = a + b;
            if (c >= MOD) c -= MOD;
            return c;
        }
        static inline ull mul(ull a, ull b) {
            unsigned __int128 t = (unsigned __int128)a * b;
            ull res = (ull)(t >> 61) + ((ull)t & MOD);
            if (res >= MOD) res -= MOD;
            return res;
        }
    
        static void init_base() {
            if (base != 0) return;
            std::mt19937_64 rng(std::random_device{}());
            std::uniform_int_distribution<ull> dist(1ULL, MOD - 1);
            base = dist(rng);
            pow_base = {1};  // pow_base[0] = 1
        }
    
        static void ensure_pow(int len) {
            if ((int)pow_base.size() >= len + 1) return;
            int cur = (int)pow_base.size();
            pow_base.resize(len + 1);
            for (int i = cur; i <= len; ++i) {
                pow_base[i] = mul(pow_base[i - 1], base);
            }
        }
    
        // hash(A + B) を hash(A), hash(B), |B| から求める
        static ull concat(ull h1, ull h2, int len2) {
            assert(len2 >= 0);
            init_base();
            ensure_pow(len2);
            return add(mul(h1, pow_base[len2]), h2);
        }

        // 長さ付きのハッシュ値。+ で文字列の連結に対応するハッシュが得られる
        // 既定値は空文字列（+ の単位元）
        struct Hash {
            ull val = 0;
            int len = 0;

            Hash() = default;
            Hash(ull val, int len) : val(val), len(len) {}
            // 1 文字 / 文字列全体のハッシュ（prefix hash を持たずに求める）
            explicit Hash(char c) : val((ull)(unsigned char)c + 1), len(1) { init_base(); }
            explicit Hash(const std::string &s) : len((int)s.size()) {
                init_base();
                for (char c : s) val = add(mul(val, base), (ull)(unsigned char)c + 1);
            }

            friend Hash operator+(const Hash &a, const Hash &b) {
                return {concat(a.val, b.val, b.len), a.len + b.len};
            }
            Hash &operator+=(const Hash &o) { return *this = *this + o; }
            friend bool operator==(const Hash &a, const Hash &b) {
                return a.val == b.val && a.len == b.len;
            }
            friend bool operator!=(const Hash &a, const Hash &b) { return !(a == b); }
        };

        RollingHash() : n(0) {}
    
        RollingHash(const std::string &s) {
            build(s);
        }
    
        void build(const std::string &s) {
            init_base();
            n = (int)s.size();
            ensure_pow(n);
            hash.assign(n + 1, 0);
            for (int i = 0; i < n; ++i) {
                hash[i + 1] = add(mul(hash[i], base), (ull)(unsigned char)s[i] + 1);
            }
        }
    
        // S[l..r) のハッシュを取得
        ull get(int l, int r) const {
            assert(0 <= l && l <= r && r <= n);
            ull res = hash[r] + MOD - mul(hash[l], pow_base[r - l]);
            if (res >= MOD) res -= MOD;
            return res;
        }
    
        // S[l..r) の長さ付きハッシュを取得（+ で連結できる）
        Hash slice(int l, int r) const {
            return {get(l, r), r - l};
        }

        // 同じ文字列の中で部分文字列が等しいか
        bool equals(int l1, int r1, int l2, int r2) const {
            if (r1 - l1 != r2 - l2) return false;
            return get(l1, r1) == get(l2, r2);
        }

        // a の [l1, r1) と b の [l2, r2) の最長共通接頭辞の長さ  O(log N)
        static int lcp(const RollingHash &a, int l1, int r1, const RollingHash &b, int l2, int r2) {
            assert(0 <= l1 && l1 <= r1 && r1 <= a.n);
            assert(0 <= l2 && l2 <= r2 && r2 <= b.n);
            // get(l1, l1 + len) == get(l2, l2 + len) を乗算 1 回で判定する
            const ull diff = add(a.hash[l1], MOD - b.hash[l2]);
            auto same = [&](int len) {
                return add(a.hash[l1 + len], MOD - b.hash[l2 + len]) == mul(diff, pow_base[len]);
            };
            const int limit = std::min(r1 - l1, r2 - l2);
            // 答えが短い場合に速いよう、長さ 32 までは倍々で確かめてから二分探索する
            int ok = 0, ng = 1;
            while (true) {
                if (ng > limit || !same(ng)) break;
                ok = ng;
                if (ng >= 32) {
                    ng = limit + 1;
                    break;
                }
                ng *= 2;
            }
            if (ng > limit + 1) ng = limit + 1;
            while (ng - ok > 1) {
                int mid = ok + (ng - ok) / 2;
                if (same(mid)) ok = mid;
                else ng = mid;
            }
            return ok;
        }
        int lcp(int l1, int r1, int l2, int r2) const {
            return lcp(*this, l1, r1, *this, l2, r2);
        }

        // a の [l1, r1) と b の [l2, r2) を辞書順で比較  O(log N)
        // 負: a 側が小さい、0: 等しい、正: a 側が大きい（std::string::compare と同じ順序）
        static int compare(const RollingHash &a, int l1, int r1, const RollingHash &b, int l2, int r2) {
            int len1 = r1 - l1, len2 = r2 - l2;
            int k = lcp(a, l1, r1, b, l2, r2);
            if (k == len1 || k == len2) return (len1 > len2) - (len1 < len2);
            // 長さ 1 のハッシュは 文字 + 1 そのもの
            ull c1 = a.get(l1 + k, l1 + k + 1), c2 = b.get(l2 + k, l2 + k + 1);
            return (c1 > c2) - (c1 < c2);
        }
        int compare(int l1, int r1, int l2, int r2) const {
            return compare(*this, l1, r1, *this, l2, r2);
        }
    };
    
}
