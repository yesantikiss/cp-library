#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"

#include <iostream>

#include "ds/dynamic_li_chao_tree.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    yesantikiss::DynamicLiChaoTree<long long> lines(-1000000000, 1000000001);
    lines.reserve_nodes(12000000);
    for (int i = 0; i < n; ++i) {
        long long l, r, a, b;
        std::cin >> l >> r >> a >> b;
        lines.add_segment(a, b, l, r);
    }
    while (q--) {
        int type;
        std::cin >> type;
        if (type == 0) {
            long long l, r, a, b;
            std::cin >> l >> r >> a >> b;
            lines.add_segment(a, b, l, r);
        } else {
            long long p;
            std::cin >> p;
            if (lines.has_line(p)) {
                std::cout << lines.get(p) << '\n';
            } else {
                std::cout << "INFINITY\n";
            }
        }
    }
}
