#pragma once

#include <algorithm>
#include <vector>

namespace yesantikiss {
    struct TreeDiameter {
        int length = 0;
        std::vector<int> path;

        TreeDiameter() = default;

        explicit TreeDiameter(const std::vector<std::vector<int>>& graph) {
            build(graph);
        }

        void build(const std::vector<std::vector<int>>& graph) {
            length = 0;
            path.clear();
            int n = static_cast<int>(graph.size());
            if (n == 0) return;

            std::vector<int> dist, parent;
            int a = farthest(graph, 0, dist, parent);
            int b = farthest(graph, a, dist, parent);

            length = dist[b];
            for (int v = b; v != -1; v = parent[v]) path.push_back(v);
            std::reverse(path.begin(), path.end());
        }

    private:
        static int farthest(const std::vector<std::vector<int>>& graph,
                            int source, std::vector<int>& dist,
                            std::vector<int>& parent) {
            int n = static_cast<int>(graph.size());
            dist.assign(n, -1);
            parent.assign(n, -1);
            std::vector<int> queue{source};
            dist[source] = 0;
            for (int i = 0; i < static_cast<int>(queue.size()); ++i) {
                int v = queue[i];
                for (int to : graph[v]) {
                    if (dist[to] != -1) continue;
                    dist[to] = dist[v] + 1;
                    parent[to] = v;
                    queue.push_back(to);
                }
            }
            return queue.back();
        }
    };
}
