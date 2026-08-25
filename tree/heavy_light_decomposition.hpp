#pragma once

#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

namespace yesantikiss {
    struct HeavyLightDecomposition {
        int n = 0;
        int root = -1;
        std::vector<int> parent;
        std::vector<int> depth;
        std::vector<int> size;
        std::vector<int> in;
        std::vector<int> out;
        std::vector<int> head;
        std::vector<int> heavy;
        std::vector<int> vertex;

        HeavyLightDecomposition() = default;

        explicit HeavyLightDecomposition(
            const std::vector<std::vector<int>>& graph, int root_ = 0) {
            build(graph, root_);
        }

        void build(const std::vector<std::vector<int>>& graph, int root_ = 0) {
            init(static_cast<int>(graph.size()));
            if (n == 0) return;
            root = root_;

            std::vector<int> order{root};
            parent[root] = root;
            for (int i = 0; i < static_cast<int>(order.size()); ++i) {
                int v = order[i];
                for (int to : graph[v]) {
                    if (parent[to] != -1) continue;
                    parent[to] = v;
                    depth[to] = depth[v] + 1;
                    order.push_back(to);
                }
            }

            for (int i = static_cast<int>(order.size()) - 1; i >= 0; --i) {
                int v = order[i];
                int largest_size = 0;
                for (int to : graph[v]) {
                    if (parent[to] != v) continue;
                    size[v] += size[to];
                    if (size[to] > largest_size) {
                        largest_size = size[to];
                        heavy[v] = to;
                    }
                }
            }

            int timer = 0;
            std::vector<std::pair<int, int>> pending{{root, root}};
            while (!pending.empty()) {
                auto [v, chain_head] = pending.back();
                pending.pop_back();

                for (; v != -1; v = heavy[v]) {
                    head[v] = chain_head;
                    in[v] = timer;
                    vertex[timer++] = v;

                    for (int to : graph[v]) {
                        if (parent[to] == v && to != heavy[v]) {
                            pending.emplace_back(to, to);
                        }
                    }
                }
            }

            for (int v = 0; v < n; ++v) {
                if (in[v] != -1) out[v] = in[v] + size[v];
            }
        }

        int edge_vertex(int u, int v) const {
            return depth[u] > depth[v] ? u : v;
        }

        int lca(int u, int v) const {
            while (head[u] != head[v]) {
                if (depth[head[u]] > depth[head[v]]) {
                    u = parent[head[u]];
                } else {
                    v = parent[head[v]];
                }
            }
            return depth[u] < depth[v] ? u : v;
        }

        int dist(int u, int v) const {
            int ancestor = lca(u, v);
            return depth[u] + depth[v] - 2 * depth[ancestor];
        }

        bool is_ancestor(int ancestor, int v) const {
            return in[ancestor] <= in[v] && out[v] <= out[ancestor];
        }

        std::pair<int, int> subtree_vertex(int v) const {
            return {in[v], out[v]};
        }

        // 各辺を深い方の頂点に対応させたときの部分木内の辺。
        std::pair<int, int> subtree_edge(int v) const {
            return {in[v] + 1, out[v]};
        }

        // u -> v の順に、パスを半開区間へ分解する。
        // reverse=true の区間は r-1, ..., l の順に読む。
        template <class F>
        void path_query(int u, int v, bool edge, F&& callback) const {
            std::vector<std::tuple<int, int, bool>> right;

            while (head[u] != head[v]) {
                if (depth[head[u]] > depth[head[v]]) {
                    callback(in[head[u]], in[u] + 1, true);
                    u = parent[head[u]];
                } else {
                    right.emplace_back(in[head[v]], in[v] + 1, false);
                    v = parent[head[v]];
                }
            }

            if (depth[u] > depth[v]) {
                int left = in[v] + (edge ? 1 : 0);
                int right_end = in[u] + 1;
                if (left < right_end) callback(left, right_end, true);
            } else {
                int left = in[u] + (edge ? 1 : 0);
                int right_end = in[v] + 1;
                if (left < right_end) callback(left, right_end, false);
            }

            std::reverse(right.begin(), right.end());
            for (auto [left, right_end, reverse] : right) {
                callback(left, right_end, reverse);
            }
        }

        template <class S, class Op, class Get>
        S path_fold(int u, int v, bool edge, Op op, S identity,
                    Get get) const {
            S result = identity;
            path_query(u, v, edge,
                       [&](int left, int right, bool reverse) {
                           result = op(result, get(left, right, reverse));
                       });
            return result;
        }

    private:
        void init(int size_) {
            n = size_;
            root = -1;
            parent.assign(n, -1);
            depth.assign(n, 0);
            size.assign(n, 1);
            in.assign(n, -1);
            out.assign(n, -1);
            head.assign(n, -1);
            heavy.assign(n, -1);
            vertex.assign(n, -1);
        }
    };
}
