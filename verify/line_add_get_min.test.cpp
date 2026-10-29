#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

#include <iostream>

#include "ds/dynamic_li_chao_tree.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    yesantikiss::DynamicLiChaoTree<long long> lines(-1000000000, 1000000001);
    for (int i = 0; i < n; ++i) {
        long long a, b;
        std::cin >> a >> b;
        lines.add_line(a, b);
    }
    while (q--) {
        int type;
        std::cin >> type;
        if (type == 0) {
            long long a, b;
            std::cin >> a >> b;
            lines.add_line(a, b);
        } else {
            long long p;
            std::cin >> p;
            std::cout << lines.get(p) << '\n';
        }
    }
}
