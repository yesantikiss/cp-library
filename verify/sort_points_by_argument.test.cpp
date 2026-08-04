#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include <algorithm>
#include <iostream>
#include <vector>

#include "geometry/argument_sort.hpp"

int main() {
    using namespace yesantikiss;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<Point> points(n);
    for (Point& point : points) std::cin >> point;

    std::sort(points.begin(), points.end(), ArgumentLess{});

    for (const Point& point : points) {
        std::cout << static_cast<long long>(point.x) << ' '
                  << static_cast<long long>(point.y) << '\n';
    }
}
