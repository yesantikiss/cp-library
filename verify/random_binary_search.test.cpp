// 素朴な実装と突き合わせるランダムテストを通してから A + B を解く。
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <limits>
#include <random>

#include "algo/binary_search.hpp"

int main() {
    using yesantikiss::binary_search_max_right;
    using yesantikiss::binary_search_min_left;

    // 小さい範囲では、番兵と境界の組をすべて試す。
    for (int left = -6; left <= 6; ++left) {
        for (int right = left + 1; right <= left + 12; ++right) {
            // f(x) = (x >= border)。left は false、right は true の番兵
            for (int border = left + 1; border <= right; ++border) {
                int calls = 0;
                int found = binary_search_min_left(left, right, [&](int x) {
                    assert(left < x && x < right);  // 番兵は評価しない
                    ++calls;
                    return x >= border;
                });
                assert(found == border);
                assert(calls <= 5);
            }
            // f(x) = (x <= border)。left は true、right は false の番兵
            for (int border = left; border < right; ++border) {
                int found = binary_search_max_right(left, right, [&](int x) {
                    assert(left < x && x < right);
                    return x <= border;
                });
                assert(found == border);
            }
        }
    }

    // 大きい範囲でも、途中の計算があふれない。
    std::mt19937_64 random(20261110);
    const long long max = std::numeric_limits<long long>::max();
    for (int trial = 0; trial < 20000; ++trial) {
        long long left = static_cast<long long>(random() >> 2);
        long long right = left + 1 + static_cast<long long>(random() >> 2);
        if (trial % 3 == 0) right = max;
        // 番兵として -1 を渡す形 (right - left があふれない範囲で)
        if (trial % 3 != 0 && trial % 7 == 0) left = -1;
        unsigned long long width =
            static_cast<unsigned long long>(right - left);
        long long border = left + 1 +
                           static_cast<long long>(random() % width);
        assert(binary_search_min_left(left, right, [&](long long x) {
                   return x >= border;
               }) == border);
        assert(binary_search_max_right(left, right, [&](long long x) {
                   return x < border;
               }) == border - 1);
    }

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
