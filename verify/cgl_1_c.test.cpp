#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_1_C"

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

    while (q--) {
        Point point;
        std::cin >> point;

        switch (point_position(line, point)) {
            case PointPosition::counter_clockwise:
                std::cout << "COUNTER_CLOCKWISE\n";
                break;
            case PointPosition::clockwise:
                std::cout << "CLOCKWISE\n";
                break;
            case PointPosition::online_back:
                std::cout << "ONLINE_BACK\n";
                break;
            case PointPosition::online_front:
                std::cout << "ONLINE_FRONT\n";
                break;
            case PointPosition::on_segment:
                std::cout << "ON_SEGMENT\n";
                break;
        }
    }
}
