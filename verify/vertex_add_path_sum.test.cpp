#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include <iostream>
#include <vector>

#include "tree/heavy_light_decomposition.hpp"

struct FenwickTree {
    std::vector<long long> data;

    explicit FenwickTree(int n) : data(n + 1) {}

    void add(int index, long long value) {
        for (++index; index < static_cast<int>(data.size());
             index += index & -index) {
            data[index] += value;
        }
    }

    long long prefix_sum(int right) const {
        long long result = 0;
        for (; right > 0; right -= right & -right) result += data[right];
        return result;
    }

    long long sum(int left, int right) const {
        return prefix_sum(right) - prefix_sum(left);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<int> value(n);
    for (int& x : value) std::cin >> x;

    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i + 1 < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    yesantikiss::HeavyLightDecomposition hld(graph);
    FenwickTree fenwick(n);
    for (int v = 0; v < n; ++v) fenwick.add(hld.in[v], value[v]);

    while (q--) {
        int type;
        std::cin >> type;
        if (type == 0) {
            int v, x;
            std::cin >> v >> x;
            fenwick.add(hld.in[v], x);
        } else {
            int u, v;
            std::cin >> u >> v;
            long long answer = 0;
            hld.path_query(u, v, false, [&](int left, int right, bool) {
                answer += fenwick.sum(left, right);
            });
            std::cout << answer << '\n';
        }
    }
}
