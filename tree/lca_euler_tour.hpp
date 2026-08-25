#pragma once

#include <algorithm>
#include <vector>

namespace yesantikiss {
    struct EulerTourLCA {
        int n = 0;
        std::vector<int> depth;
        std::vector<int> parent;
        std::vector<int> component;
        std::vector<int> tin;
        std::vector<int> tout;

        EulerTourLCA() = default;

        explicit EulerTourLCA(const std::vector<std::vector<int>>& graph,
                              int root = 0) {
            build(graph, root);
        }

        void build(const std::vector<std::vector<int>>& graph, int root = 0) {
            init(static_cast<int>(graph.size()));
            if (n == 0) return;

            euler.reserve(2 * n - 1);
            build_component(graph, root, 0);
            build_sparse_table();
        }

        void build_forest(const std::vector<std::vector<int>>& graph) {
            init(static_cast<int>(graph.size()));
            euler.reserve(n == 0 ? 0 : 2 * n - 1);

            int component_id = 0;
            for (int root = 0; root < n; ++root) {
                if (parent[root] == -1) {
                    build_component(graph, root, component_id++);
                }
            }
            build_sparse_table();
        }

        int lca(int a, int b) const {
            if (!same_component(a, b)) return -1;
            int left = first[a];
            int right = first[b];
            if (left > right) std::swap(left, right);

            int length = right - left + 1;
            int level = lg[length];
            return better(st_at(level, left),
                          st_at(level, right - (1 << level) + 1));
        }

        int dist(int a, int b) const {
            int ancestor = lca(a, b);
            if (ancestor == -1) return -1;
            return depth[a] + depth[b] - 2 * depth[ancestor];
        }

        bool is_ancestor(int ancestor, int v) const {
            return same_component(ancestor, v) && tin[ancestor] <= tin[v] &&
                   tout[v] <= tout[ancestor];
        }

    private:
        int timer = 0;
        int euler_size = 0;
        int levels = 0;
        std::vector<int> first;
        std::vector<int> euler;
        std::vector<int> lg;
        std::vector<int> sparse_table;

        struct Frame {
            int v;
            int next_edge;
        };

        void init(int size) {
            n = size;
            timer = 0;
            euler_size = 0;
            levels = 0;
            depth.assign(n, 0);
            parent.assign(n, -1);
            component.assign(n, -1);
            tin.assign(n, -1);
            tout.assign(n, -1);
            first.assign(n, -1);
            euler.clear();
            lg.clear();
            sparse_table.clear();
        }

        bool contains(int v) const { return 0 <= v && v < n; }

        bool same_component(int a, int b) const {
            return contains(a) && contains(b) && component[a] != -1 &&
                   component[a] == component[b];
        }

        int& st_at(int level, int index) {
            return sparse_table[level * euler_size + index];
        }

        int st_at(int level, int index) const {
            return sparse_table[level * euler_size + index];
        }

        int better(int a, int b) const {
            return depth[a] <= depth[b] ? a : b;
        }

        void enter(int v, int p, int component_id) {
            parent[v] = p;
            component[v] = component_id;
            tin[v] = timer++;
            first[v] = static_cast<int>(euler.size());
            euler.push_back(v);
        }

        void build_component(const std::vector<std::vector<int>>& graph,
                             int root, int component_id) {
            depth[root] = 0;
            enter(root, root, component_id);
            std::vector<Frame> stack{{root, 0}};

            while (!stack.empty()) {
                Frame& frame = stack.back();
                int v = frame.v;
                if (frame.next_edge == static_cast<int>(graph[v].size())) {
                    tout[v] = timer;
                    stack.pop_back();
                    if (!stack.empty()) euler.push_back(stack.back().v);
                    continue;
                }

                int to = graph[v][frame.next_edge++];
                if (parent[to] != -1) continue;
                depth[to] = depth[v] + 1;
                enter(to, v, component_id);
                stack.push_back({to, 0});
            }
        }

        void build_sparse_table() {
            euler_size = static_cast<int>(euler.size());
            if (euler_size == 0) return;

            lg.assign(euler_size + 1, 0);
            for (int i = 2; i <= euler_size; ++i) lg[i] = lg[i / 2] + 1;

            levels = lg[euler_size] + 1;
            sparse_table.assign(levels * euler_size, 0);
            for (int i = 0; i < euler_size; ++i) st_at(0, i) = euler[i];

            for (int level = 1; level < levels; ++level) {
                int length = 1 << level;
                int half = length / 2;
                for (int i = 0; i + length <= euler_size; ++i) {
                    st_at(level, i) =
                        better(st_at(level - 1, i),
                               st_at(level - 1, i + half));
                }
            }
        }
    };
}
