#pragma once

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
            __int128 t = (__int128)a * b;
            t = (t >> 61) + (t & MOD);
            if (t >= MOD) t -= MOD;
            return (ull)t;
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
    
        // 同じ文字列の中で部分文字列が等しいか
        bool equals(int l1, int r1, int l2, int r2) const {
            if (r1 - l1 != r2 - l2) return false;
            return get(l1, r1) == get(l2, r2);
        }
    };
    
}
