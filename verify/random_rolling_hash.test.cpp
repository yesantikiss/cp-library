// 素朴な実装と突き合わせるランダムテストを通してから A + B を解く。
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
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
}  // namespace

int main() {
    test_pow_of();
    test_concat_matches_string();
    test_long_concat_memory();
    test_huge_repeat();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
