#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_1_A"
#define ERROR "1e-8"

#include <iomanip>
#include <iostream>

#include "geometry/line.hpp"

int main() {
    using namespace yesantikiss;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Line line;
    std::cin >> line.a >> line.b;

    int q;
    std::cin >> q;

    std::cout << std::fixed << std::setprecision(15);
    while (q--) {
        Point point;
        std::cin >> point;
        std::cout << projection(line, point) << '\n';
    }
}
