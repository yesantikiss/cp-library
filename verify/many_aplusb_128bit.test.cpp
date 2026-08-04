#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb_128bit"

#include <iostream>

#include "utils/int128.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        yesantikiss::i128 a = 0, b = 0;
        std::cin >> a >> b;
        std::cout << a + b << '\n';
    }
}
