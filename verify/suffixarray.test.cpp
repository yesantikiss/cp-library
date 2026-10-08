#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "string/rolling_hash.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;
    const int n = (int)s.size();

    yesantikiss::RollingHash hash(s);
    std::vector<int> order(n);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(),
              [&](int i, int j) { return hash.compare(i, n, j, n) < 0; });

    for (int i = 0; i < n; ++i) {
        if (i != 0) std::cout << ' ';
        std::cout << order[i];
    }
    std::cout << '\n';
}
