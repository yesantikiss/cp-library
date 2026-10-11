#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/5/DSL_5_B"

#include <algorithm>
#include <iostream>

#include "ds/2d_prefixsum.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    constexpr int MAX = 1000;
    int n;
    std::cin >> n;

    yesantikiss::PS2D<int> imos(MAX, MAX);
    while (n--) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        imos.add_rect(y1, x1, y2, x2, 1);
    }
    imos.build();

    int answer = 0;
    for (int y = 0; y < MAX; ++y) {
        for (int x = 0; x < MAX; ++x) answer = std::max(answer, imos.get(y, x));
    }
    std::cout << answer << '\n';
}
