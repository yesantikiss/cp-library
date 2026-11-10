// 素朴な実装と突き合わせるランダムテストを通してから A + B を解く。
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "tree/centered_tree.hpp"
#include "tree/tree_diameter.hpp"

namespace {
    std::vector<int> bfs(const std::vector<std::vector<int>>& graph,
                         int source) {
        std::vector<int> dist(graph.size(), -1);
        std::vector<int> queue{source};
        dist[source] = 0;
        for (int i = 0; i < static_cast<int>(queue.size()); ++i) {
            int v = queue[i];
            for (int to : graph[v]) {
                if (dist[to] != -1) continue;
                dist[to] = dist[v] + 1;
                queue.push_back(to);
            }
        }
        return dist;
    }

    std::vector<std::vector<int>> random_tree(int n, std::mt19937& random) {
        std::vector<std::vector<int>> graph(n);
        std::vector<int> label(n);
        for (int i = 0; i < n; ++i) label[i] = i;
        std::shuffle(label.begin(), label.end(), random);
        int mode = static_cast<int>(random() % 3);
        for (int v = 1; v < n; ++v) {
            int p = mode == 0   ? static_cast<int>(random() % v)
                    : mode == 1 ? v - 1
                                : std::max(0, v - 1 - static_cast<int>(random() % 3));
            graph[label[p]].push_back(label[v]);
            graph[label[v]].push_back(label[p]);
        }
        return graph;
    }

    // 各辺に頂点をはさんだ木で、中心からの距離を素朴に求める。
    std::vector<int> naive_dist2(const std::vector<std::vector<int>>& graph) {
        int n = static_cast<int>(graph.size());
        std::vector<std::vector<int>> doubled(2 * n - 1);
        int next = n;
        for (int v = 0; v < n; ++v) {
            for (int to : graph[v]) {
                if (v > to) continue;
                doubled[v].push_back(next);
                doubled[next].push_back(v);
                doubled[to].push_back(next);
                doubled[next].push_back(to);
                ++next;
            }
        }
        int size = static_cast<int>(doubled.size());
        int center = -1, best = size;
        for (int v = 0; v < size; ++v) {
            std::vector<int> dist = bfs(doubled, v);
            int ecc = *std::max_element(dist.begin(), dist.end());
            if (ecc < best) {
                best = ecc;
                center = v;
            }
        }
        std::vector<int> dist = bfs(doubled, center);
        dist.resize(n);
        return dist;
    }
}

int main() {
    std::mt19937 random(987654321);

    {
        std::vector<std::vector<int>> empty;
        yesantikiss::TreeDiameter diameter(empty);
        yesantikiss::CenteredTree centered(empty);
        assert(diameter.length == 0 && diameter.path.empty());
        assert(centered.root == -1 && centered.order.empty());
    }

    for (int trial = 0; trial < 500; ++trial) {
        int n = trial < 100 ? 1 + trial % 8
                            : 1 + static_cast<int>(random() % 60);
        std::vector<std::vector<int>> graph = random_tree(n, random);

        std::vector<std::vector<int>> dist(n);
        int expected_diameter = 0;
        for (int v = 0; v < n; ++v) {
            dist[v] = bfs(graph, v);
            expected_diameter = std::max(
                expected_diameter, *std::max_element(dist[v].begin(),
                                                     dist[v].end()));
        }

        yesantikiss::TreeDiameter diameter(graph);
        assert(diameter.length == expected_diameter);
        assert(static_cast<int>(diameter.path.size()) == diameter.length + 1);
        for (int i = 0; i + 1 < static_cast<int>(diameter.path.size()); ++i) {
            int u = diameter.path[i], v = diameter.path[i + 1];
            assert(std::count(graph[u].begin(), graph[u].end(), v) == 1);
        }
        assert(dist[diameter.path.front()][diameter.path.back()] ==
               diameter.length);

        yesantikiss::CenteredTree centered(graph);
        assert(centered.n == n);
        assert(centered.diameter == expected_diameter);
        assert(centered.radius() == (expected_diameter + 1) / 2);
        assert(centered.has_virtual_root() == (expected_diameter % 2 == 1));

        std::vector<int> expected_dist2 = naive_dist2(graph);
        for (int v = 0; v < n; ++v) {
            assert(centered.dist2[v] == expected_dist2[v]);
            int ecc = *std::max_element(dist[v].begin(), dist[v].end());
            assert(centered.eccentricity(v) == ecc);
            assert(centered.is_diameter_endpoint(v) ==
                   (ecc == expected_diameter));
        }

        // children だけを使う木DPで直径の本数を数え、全頂点対の距離と比べる。
        {
            long long expected_count = 0;
            for (int u = 0; u < n; ++u) {
                for (int v = u + 1; v < n; ++v) {
                    if (dist[u][v] == expected_diameter) ++expected_count;
                }
            }
            std::vector<long long> endpoints(n + 1);
            long long count = 0;
            for (int i = static_cast<int>(centered.order.size()) - 1; i >= 0;
                 --i) {
                int v = centered.order[i];
                if (centered.is_diameter_endpoint(v)) endpoints[v] = 1;
                for (int to : centered.children[v]) {
                    if (v == centered.root) {
                        count += endpoints[v] * endpoints[to];
                    }
                    endpoints[v] += endpoints[to];
                }
            }
            assert(count == expected_count);
        }

        int vertices = n + (centered.has_virtual_root() ? 1 : 0);
        assert(static_cast<int>(centered.order.size()) == vertices);
        assert(centered.order[0] == centered.root);
        assert(centered.parent[centered.root] == -1);
        std::vector<int> position(n + 1, -1);
        for (int i = 0; i < vertices; ++i) {
            int v = centered.order[i];
            assert(position[v] == -1);
            position[v] = i;
        }
        assert(static_cast<int>(centered.children.size()) == n + 1);
        int child_count = 0;
        for (int v = 0; v <= n; ++v) {
            for (int to : centered.children[v]) {
                assert(centered.parent[to] == v);
                ++child_count;
            }
        }
        assert(child_count == vertices - 1);
        if (centered.has_virtual_root()) {
            assert(centered.children[n].size() == 2);
        } else {
            assert(centered.children[n].empty());
        }
        for (int v = 0; v < n; ++v) {
            if (v == centered.root) continue;
            int p = centered.parent[v];
            assert(position[p] < position[v]);
            if (centered.is_virtual(p)) {
                assert(centered.dist2[v] == 1);
            } else {
                assert(std::count(graph[v].begin(), graph[v].end(), p) == 1);
                assert(centered.dist2[v] == centered.dist2[p] + 2);
            }
        }
    }

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
