#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <iostream>
#include <vector>

#include "tree/lca_euler_tour.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<std::vector<int>> graph(n);
    for (int v = 1; v < n; ++v) {
        int parent;
        std::cin >> parent;
        graph[parent].push_back(v);
        graph[v].push_back(parent);
    }

    yesantikiss::EulerTourLCA lca(graph);
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        std::cout << lca.lca(u, v) << '\n';
    }
}
