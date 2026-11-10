#pragma once

#include <initializer_list>
#include <vector>

#include "tree/tree_diameter.hpp"

namespace yesantikiss {
    // 木を中心で根付けする。中心が2点なら、その間に仮想頂点 n を置いて根にする。
    // dist2[x] は中心点からの距離の2倍で、頂点倍した木での深さと一致する。
    struct CenteredTree {
        int n = 0;
        int root = -1;
        int diameter = 0;
        std::vector<int> parent;
        std::vector<int> order;
        std::vector<int> dist2;

        CenteredTree() = default;

        explicit CenteredTree(const std::vector<std::vector<int>>& graph) {
            build(graph);
        }

        void build(const std::vector<std::vector<int>>& graph) {
            n = static_cast<int>(graph.size());
            root = -1;
            diameter = 0;
            parent.assign(n + 1, -1);
            dist2.assign(n + 1, -1);
            order.clear();
            if (n == 0) return;

            TreeDiameter tree_diameter(graph);
            diameter = tree_diameter.length;
            const std::vector<int>& path = tree_diameter.path;

            if (diameter % 2 == 0) {
                root = path[diameter / 2];
                dist2[root] = 0;
                order.push_back(root);
            } else {
                root = n;
                dist2[root] = 0;
                order.push_back(root);
                for (int v : {path[diameter / 2], path[diameter / 2 + 1]}) {
                    parent[v] = root;
                    dist2[v] = 1;
                    order.push_back(v);
                }
            }

            for (int i = 0; i < static_cast<int>(order.size()); ++i) {
                int v = order[i];
                if (v == n) continue;
                for (int to : graph[v]) {
                    if (dist2[to] != -1) continue;
                    parent[to] = v;
                    dist2[to] = dist2[v] + 2;
                    order.push_back(to);
                }
            }
        }

        bool is_virtual(int v) const { return v == n; }

        bool has_virtual_root() const { return root == n; }

        int radius() const { return (diameter + 1) / 2; }

        bool is_diameter_endpoint(int v) const {
            return !is_virtual(v) && dist2[v] == diameter;
        }

        // 元の木で v から最も遠い頂点までの距離。
        int eccentricity(int v) const { return (dist2[v] + diameter) / 2; }
    };
}
