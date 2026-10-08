#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include <iostream>
#include <string>

#include "string/rolling_hash.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;
    const int n = (int)s.size();

    yesantikiss::RollingHash hash(s);
    for (int i = 0; i < n; ++i) {
        if (i != 0) std::cout << ' ';
        std::cout << hash.lcp(0, n, i, n);
    }
    std::cout << '\n';
}
