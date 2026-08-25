#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

#include <iostream>
#include <vector>

#include "tree/lca_binary_lifting.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i + 1 < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    yesantikiss::BinaryLiftingLCA lca(graph);
    while (q--) {
        int u, v, k;
        std::cin >> u >> v >> k;
        std::cout << lca.jump(u, v, k) << '\n';
    }
}
