// 素朴な実装と突き合わせるランダムテストを通してから A + B を解く。
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "string/rolling_hash.hpp"

namespace {
    using yesantikiss::RollingHash;
    using Hash = RollingHash::Hash;
    using ull = RollingHash::ull;

    std::mt19937_64 random_engine(20261112);

    int random_int(int lo, int hi) {
        return std::uniform_int_distribution<int>(lo, hi)(random_engine);
    }

    long long random_ll(long long lo, long long hi) {
        return std::uniform_int_distribution<long long>(lo, hi)(random_engine);
    }

    // h を k 回繰り返したハッシュ（繰り返し二乗法で連結する）
    Hash repeat(Hash h, long long k) {
        Hash res;
        for (; k > 0; k >>= 1, h = h + h) {
            if (k & 1) res = res + h;
        }
        return res;
    }

    std::string random_string(int n, int sigma) {
        std::string s(n, 'a');
        for (char &c : s) c = char('a' + random_int(0, sigma - 1));
        return s;
    }

    ull naive_pow(int len) {
        ull res = 1;
        for (int i = 0; i < len; ++i) res = RollingHash::mul(res, RollingHash::base);
        return res;
    }

    // テーブル外の累乗は素朴な掛け算と一致する
    void test_pow_of() {
        RollingHash::init_base();
        for (int len = 0; len <= 3000; ++len) assert(RollingHash::pow_of(len) == naive_pow(len));
        for (int iter = 0; iter < 200; ++iter) {
            long long a = random_ll(0, 1LL << 61), b = random_ll(0, 1LL << 61);
            assert(RollingHash::pow_of(a + b) ==
                   RollingHash::mul(RollingHash::pow_of(a), RollingHash::pow_of(b)));
        }
    }

    // 実際の文字列を連結したハッシュと一致する（テーブルより長い右側を含む）
    void test_concat_matches_string() {
        for (int iter = 0; iter < 300; ++iter) {
            int k = random_int(1, 6);
            std::vector<std::string> parts(k);
            Hash acc;
            std::string whole;
            for (auto &p : parts) {
                p = random_string(random_int(0, 2000), random_int(1, 3));
                acc += Hash(p);
                whole += p;
            }
            assert(acc == Hash(whole));
            RollingHash rh(whole);
            assert(acc == rh.slice(0, (int)whole.size()));
            // build 済みのテーブルを使う slice との連結も一致する
            int l = random_int(0, (int)whole.size()), r = random_int(l, (int)whole.size());
            int m = random_int(l, r);
            assert(rh.slice(l, m) + rh.slice(m, r) == rh.slice(l, r));
            assert(rh.slice(l, m) + Hash(whole.substr(m, r - m)) == rh.slice(l, r));
        }
    }

    // 長いハッシュの組み立てでテーブルが伸びず、結合法則が成り立つ
    void test_long_concat_memory() {
        RollingHash rh(random_string(100, 26));
        const size_t table = RollingHash::pow_base.size();
        Hash h('a');
        for (int i = 0; i < 29; ++i) h = h + h;  // 長さ 2^29
        assert(h.len == 1 << 29);
        assert(RollingHash::pow_base.size() == table);

        std::vector<Hash> pieces = {Hash('x'), h, Hash(std::string("abc")), rh.slice(3, 50)};
        for (int i = 0; i < 6; ++i) pieces.push_back(pieces[random_int(0, (int)pieces.size() - 1)] + Hash('q'));
        for (int iter = 0; iter < 2000; ++iter) {
            const Hash &a = pieces[random_int(0, (int)pieces.size() - 1)];
            const Hash &b = pieces[random_int(0, (int)pieces.size() - 1)];
            const Hash &c = pieces[random_int(0, (int)pieces.size() - 1)];
            if ((long long)a.len + b.len + c.len > (1 << 30)) continue;
            assert((a + b) + c == a + (b + c));
        }
        // 2^29 個の 'a' を 2 進数の各桁の長さに分けて作っても一致する
        Hash g, p('a');
        for (int bit = 0; bit < 30; ++bit, p = p + p) {
            if (((1 << 29) - 1) >> bit & 1) g = g + p;
        }
        assert(g + Hash('a') == h);
        // 文字列から作った長さ 2^20 のハッシュとも一致する
        Hash x('a');
        for (int i = 0; i < 20; ++i) x = x + x;
        assert(x == Hash(std::string(1 << 20, 'a')));
        assert(RollingHash::pow_base.size() == table);
    }

    // 10^18 近くの長さでも連結が整合し、テーブルは伸びない
    void test_huge_repeat() {
        const size_t table = RollingHash::pow_base.size();
        for (int iter = 0; iter < 300; ++iter) {
            std::string s = random_string(random_int(1, 5), random_int(1, 2));
            Hash hs(s);
            long long a = random_ll(0, 100000000000000000LL), b = random_ll(0, 100000000000000000LL);
            Hash ra = repeat(hs, a), rb = repeat(hs, b);
            assert(ra.len == a * (long long)s.size());
            assert(ra + rb == repeat(hs, a + b));
            assert(ra + rb == rb + ra);
            // (s を 2 回並べたもの) を k 回 == s を 2k 回
            long long k = random_ll(0, 100000000000000000LL);
            assert(repeat(Hash(s + s), k) == repeat(hs, 2 * k));
            // 短い場合は実際の文字列と一致する
            int c = random_int(0, 300);
            std::string rep;
            for (int i = 0; i < c; ++i) rep += s;
            assert(repeat(hs, c) == Hash(rep));
            // 1 文字違いの文字列を繰り返すと一致しない
            std::string t = s;
            t[random_int(0, (int)t.size() - 1)] ^= 1;
            long long m = random_ll(1, 100000000000000000LL);
            assert(repeat(hs, m) != repeat(Hash(t), m));
        }
        assert(RollingHash::pow_base.size() == table);
    }

    constexpr long long LIM = RollingHash::INT_LIMIT;

    // 値の種類が少ない列と、境界付近の値を含む列を作る
    std::vector<long long> random_ll_vector(int n) {
        std::vector<long long> pool;
        int kind = random_int(0, 3);
        if (kind == 0) pool = {0};
        else if (kind == 1) pool = {-1, 0, 7};  // 素朴に ull にすると衝突する組
        else if (kind == 2) pool = {-LIM, -LIM + 1, LIM - 1, LIM, 0};
        else for (int i = 0; i < 3; ++i) pool.push_back(random_ll(-LIM, LIM));
        std::vector<long long> a(n);
        for (auto &x : a) x = pool[random_int(0, (int)pool.size() - 1)];
        return a;
    }

    int naive_compare(const std::vector<long long> &x, const std::vector<long long> &y) {
        return (y < x) - (x < y);
    }

    // 整数列の一致・lcp・辞書順比較が素朴な比較と一致する
    void test_vector_matches_naive() {
        for (int iter = 0; iter < 300; ++iter) {
            std::vector<long long> a = random_ll_vector(random_int(0, 30));
            std::vector<long long> b = random_int(0, 1) ? a : random_ll_vector(random_int(0, 30));
            if (!b.empty() && random_int(0, 1)) b[random_int(0, (int)b.size() - 1)] = random_ll(-LIM, LIM);
            RollingHash ra(a), rb(b);
            const int n = (int)a.size(), m = (int)b.size();
            for (int q = 0; q < 300; ++q) {
                int l1 = random_int(0, n), r1 = random_int(l1, n);
                int l2 = random_int(0, m), r2 = random_int(l2, m);
                std::vector<long long> x(a.begin() + l1, a.begin() + r1), y(b.begin() + l2, b.begin() + r2);
                int k = 0;
                while (k < (int)x.size() && k < (int)y.size() && x[k] == y[k]) ++k;
                assert(RollingHash::lcp(ra, l1, r1, rb, l2, r2) == k);
                assert(RollingHash::compare(ra, l1, r1, rb, l2, r2) == naive_compare(x, y));
                assert((ra.slice(l1, r1) == rb.slice(l2, r2)) == (x == y));
                assert(ra.slice(l1, r1) == Hash(x));
                int l3 = random_int(0, n), r3 = random_int(l3, n);
                std::vector<long long> z(a.begin() + l3, a.begin() + r3);
                assert(ra.equals(l1, r1, l3, r3) == (x == z));
            }
            Hash acc;
            for (long long x : a) acc += Hash(x);
            assert(acc == Hash(a) && acc == ra.slice(0, n));
        }
    }

    // 0 だけの列は長さで区別でき、型が違っても同じ値なら同じハッシュになる
    void test_vector_types() {
        for (int len = 0; len <= 50; ++len) {
            RollingHash z(std::vector<int>(len, 0));
            for (int len2 = 0; len2 < len; ++len2) {
                assert(z.get(0, len) != z.get(0, len2));
                assert(Hash(std::vector<int>(len, 0)) != Hash(std::vector<int>(len2, 0)));
            }
        }
        for (int iter = 0; iter < 300; ++iter) {
            int n = random_int(0, 20);
            std::vector<int> vi(n);
            for (int &x : vi) x = random_int(-1000000000, 1000000000);
            std::vector<long long> vl(vi.begin(), vi.end());
            std::vector<short> vs(n);
            for (int i = 0; i < n; ++i) vs[i] = (short)(vi[i] % 30000);
            std::vector<long long> vsl(vs.begin(), vs.end());
            assert(Hash(vi) == Hash(vl));
            assert(RollingHash(vi).get(0, n) == RollingHash(vl).get(0, n));
            assert(Hash(vs) == Hash(vsl));
            std::vector<unsigned> vu(n);
            for (int i = 0; i < n; ++i) vu[i] = (unsigned)std::abs(vi[i]);
            std::vector<long long> vul(vu.begin(), vu.end());
            assert(Hash(vu) == Hash(vul));
            std::vector<unsigned long long> vull(vu.begin(), vu.end());
            assert(RollingHash(vull).get(0, n) == RollingHash(vul).get(0, n));
            std::vector<bool> vb(n);
            std::vector<int> vbi(n);
            for (int i = 0; i < n; ++i) vbi[i] = vb[i] = random_int(0, 1);
            assert(Hash(vb) == Hash(vbi) && RollingHash(vb).slice(0, n) == Hash(vbi));
            // vector<char> は string と同じ
            std::string s = random_string(n, 26);
            std::vector<char> vc(s.begin(), s.end());
            assert(Hash(vc) == Hash(s) && RollingHash(vc).get(0, n) == RollingHash(s).get(0, n));
        }
        // 境界の値と、素朴に ull にすると衝突する組
        std::vector<long long> v = {-LIM, -LIM + 1, -1, 0, 7, LIM - 1, LIM};
        RollingHash rv(v);
        for (int i = 0; i < (int)v.size(); ++i) {
            for (int j = 0; j < (int)v.size(); ++j) {
                assert((rv.get(i, i + 1) == rv.get(j, j + 1)) == (i == j));
                assert(rv.compare(i, i + 1, j, j + 1) == (i > j) - (i < j));
            }
        }
    }
}  // namespace

int main() {
    test_pow_of();
    test_concat_matches_string();
    test_long_concat_memory();
    test_huge_repeat();
    test_vector_matches_naive();
    test_vector_types();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
