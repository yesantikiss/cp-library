#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

#include "tree/heavy_light_decomposition.hpp"
#include "tree/lca_binary_lifting.hpp"
#include "tree/lca_euler_tour.hpp"

int main() {
    std::mt19937 random(123456789);

    for (int trial = 0; trial < 100; ++trial) {
        int n = 1 + static_cast<int>(random() % 100);
        std::vector<std::vector<int>> graph(n);
        std::vector<int> parent(n), depth(n);
        for (int v = 1; v < n; ++v) {
            parent[v] = static_cast<int>(random() % v);
            depth[v] = depth[parent[v]] + 1;
            graph[parent[v]].push_back(v);
            graph[v].push_back(parent[v]);
        }

        yesantikiss::BinaryLiftingLCA doubling(graph);
        yesantikiss::EulerTourLCA sparse(graph);
        yesantikiss::HeavyLightDecomposition hld(graph);

        auto naive_lca = [&](int u, int v) {
            while (depth[u] > depth[v]) u = parent[u];
            while (depth[v] > depth[u]) v = parent[v];
            while (u != v) {
                u = parent[u];
                v = parent[v];
            }
            return u;
        };

        for (int query = 0; query < 200; ++query) {
            int u = static_cast<int>(random() % n);
            int v = static_cast<int>(random() % n);
            int ancestor = naive_lca(u, v);

            assert(doubling.lca(u, v) == ancestor);
            assert(sparse.lca(u, v) == ancestor);
            assert(hld.lca(u, v) == ancestor);

            std::vector<int> expected;
            for (int x = u; x != ancestor; x = parent[x]) expected.push_back(x);
            expected.push_back(ancestor);
            std::vector<int> suffix;
            for (int x = v; x != ancestor; x = parent[x]) suffix.push_back(x);
            std::reverse(suffix.begin(), suffix.end());
            expected.insert(expected.end(), suffix.begin(), suffix.end());

            assert(doubling.dist(u, v) == static_cast<int>(expected.size()) - 1);
            assert(sparse.dist(u, v) == static_cast<int>(expected.size()) - 1);
            assert(hld.dist(u, v) == static_cast<int>(expected.size()) - 1);
            for (int k = 0; k < static_cast<int>(expected.size()); ++k) {
                assert(doubling.jump(u, v, k) == expected[k]);
            }
            assert(doubling.jump(u, v, static_cast<int>(expected.size())) == -1);

            std::vector<int> actual;
            hld.path_query(u, v, false,
                           [&](int left, int right, bool reverse) {
                               if (reverse) {
                                   for (int i = right - 1; i >= left; --i) {
                                       actual.push_back(hld.vertex[i]);
                                   }
                               } else {
                                   for (int i = left; i < right; ++i) {
                                       actual.push_back(hld.vertex[i]);
                                   }
                               }
                           });
            assert(actual == expected);

            actual.clear();
            hld.path_query(u, v, true,
                           [&](int left, int right, bool reverse) {
                               if (reverse) {
                                   for (int i = right - 1; i >= left; --i) {
                                       actual.push_back(hld.vertex[i]);
                                   }
                               } else {
                                   for (int i = left; i < right; ++i) {
                                       actual.push_back(hld.vertex[i]);
                                   }
                               }
                           });
            expected.erase(std::find(expected.begin(), expected.end(), ancestor));
            assert(actual == expected);
        }

        for (int ancestor = 0; ancestor < n; ++ancestor) {
            for (int v = 0; v < n; ++v) {
                bool expected = naive_lca(ancestor, v) == ancestor;
                assert(doubling.is_ancestor(ancestor, v) == expected);
                assert(sparse.is_ancestor(ancestor, v) == expected);
                assert(hld.is_ancestor(ancestor, v) == expected);
            }
        }
    }
}
