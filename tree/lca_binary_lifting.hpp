#pragma once

#include <algorithm>
#include <vector>

namespace yesantikiss {
    struct BinaryLiftingLCA {
        int n = 0;
        int log = 1;
        std::vector<int> depth;
        std::vector<int> parent;
        std::vector<int> component;

        BinaryLiftingLCA() = default;

        explicit BinaryLiftingLCA(
            const std::vector<std::vector<int>>& graph, int root = 0) {
            build(graph, root);
        }

        void build(const std::vector<std::vector<int>>& graph, int root = 0) {
            init(static_cast<int>(graph.size()));
            if (n == 0) return;

            build_component(graph, root, 0);
            build_table();
        }

        void build_forest(const std::vector<std::vector<int>>& graph) {
            init(static_cast<int>(graph.size()));

            int component_id = 0;
            for (int root = 0; root < n; ++root) {
                if (parent[root] == -1) {
                    build_component(graph, root, component_id++);
                }
            }
            build_table();
        }

        int kth_ancestor(int v, int k) const {
            if (!contains(v) || k < 0 || parent[v] == -1) return -1;
            k = std::min(k, depth[v]);
            for (int bit = 0; bit < log; ++bit) {
                if ((k >> bit) & 1) v = up_at(bit, v);
            }
            return v;
        }

        int lca(int a, int b) const {
            if (!same_component(a, b)) return -1;
            if (depth[a] < depth[b]) std::swap(a, b);

            a = kth_ancestor(a, depth[a] - depth[b]);
            if (a == b) return a;

            for (int bit = log - 1; bit >= 0; --bit) {
                if (up_at(bit, a) != up_at(bit, b)) {
                    a = up_at(bit, a);
                    b = up_at(bit, b);
                }
            }
            return parent[a];
        }

        int dist(int a, int b) const {
            int ancestor = lca(a, b);
            if (ancestor == -1) return -1;
            return depth[a] + depth[b] - 2 * depth[ancestor];
        }

        bool is_ancestor(int ancestor, int v) const {
            return same_component(ancestor, v) && lca(ancestor, v) == ancestor;
        }

        // a -> b パス上で a を 0 番目とする k 番目の頂点を返す。
        int jump(int a, int b, int k) const {
            int ancestor = lca(a, b);
            if (ancestor == -1 || k < 0) return -1;

            int up_length = depth[a] - depth[ancestor];
            int down_length = depth[b] - depth[ancestor];
            if (k > up_length + down_length) return -1;
            if (k <= up_length) return kth_ancestor(a, k);
            return kth_ancestor(b, up_length + down_length - k);
        }

    private:
        std::vector<int> up;

        void init(int size) {
            n = size;
            log = 1;
            while ((1LL << log) <= std::max(1, n)) ++log;
            depth.assign(n, 0);
            parent.assign(n, -1);
            component.assign(n, -1);
            up.assign(log * n, 0);
        }

        bool contains(int v) const { return 0 <= v && v < n; }

        bool same_component(int a, int b) const {
            return contains(a) && contains(b) && component[a] != -1 &&
                   component[a] == component[b];
        }

        int& up_at(int bit, int v) { return up[bit * n + v]; }
        int up_at(int bit, int v) const { return up[bit * n + v]; }

        void build_component(const std::vector<std::vector<int>>& graph,
                             int root, int component_id) {
            parent[root] = root;
            depth[root] = 0;
            component[root] = component_id;

            std::vector<int> order{root};
            for (int i = 0; i < static_cast<int>(order.size()); ++i) {
                int v = order[i];
                for (int to : graph[v]) {
                    if (parent[to] != -1) continue;
                    parent[to] = v;
                    depth[to] = depth[v] + 1;
                    component[to] = component_id;
                    order.push_back(to);
                }
            }
        }

        void build_table() {
            for (int v = 0; v < n; ++v) {
                if (parent[v] != -1) up_at(0, v) = parent[v];
            }
            for (int bit = 1; bit < log; ++bit) {
                for (int v = 0; v < n; ++v) {
                    if (parent[v] != -1) {
                        up_at(bit, v) = up_at(bit - 1, up_at(bit - 1, v));
                    }
                }
            }
        }
    };
}
