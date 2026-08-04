#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential"

#include <iostream>

#include "ds/potential_dsu.hpp"

namespace {
    constexpr long long mod = 998244353;

    long long normalize(long long value) {
        value %= mod;
        if (value < 0) value += mod;
        return value;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    yesantikiss::potential_dsu<long long> dsu(n);
    while (q--) {
        int type, u, v;
        std::cin >> type >> u >> v;

        if (type == 0) {
            long long x;
            std::cin >> x;

            bool connected = dsu.same(u, v);
            bool valid = !connected || normalize(dsu.diff(v, u)) == x;
            std::cout << valid << '\n';
            if (!connected) dsu.merge(v, u, x);
        } else if (!dsu.same(u, v)) {
            std::cout << -1 << '\n';
        } else {
            std::cout << normalize(dsu.diff(v, u)) << '\n';
        }
    }
}
