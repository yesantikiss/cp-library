---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/centered_tree.hpp
    title: "\u6728\u306E\u4E2D\u5FC3\u3067\u6839\u4ED8\u3051"
  - icon: ':heavy_check_mark:'
    path: tree/tree_diameter.hpp
    title: "\u6728\u306E\u76F4\u5F84"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/random_centered_tree.test.cpp\"\n// \u7D20\u6734\u306A\
    \u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\u30E9\u30F3\u30C0\u30E0\
    \u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089 A + B \u3092\u89E3\u304F\
    \u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <iostream>\n#include <random>\n#include\
    \ <vector>\n\n#line 2 \"tree/centered_tree.hpp\"\n\n#include <initializer_list>\n\
    #line 5 \"tree/centered_tree.hpp\"\n\n#line 2 \"tree/tree_diameter.hpp\"\n\n#line\
    \ 5 \"tree/tree_diameter.hpp\"\n\nnamespace yesantikiss {\n    struct TreeDiameter\
    \ {\n        int length = 0;\n        std::vector<int> path;\n\n        TreeDiameter()\
    \ = default;\n\n        explicit TreeDiameter(const std::vector<std::vector<int>>&\
    \ graph) {\n            build(graph);\n        }\n\n        void build(const std::vector<std::vector<int>>&\
    \ graph) {\n            length = 0;\n            path.clear();\n            int\
    \ n = static_cast<int>(graph.size());\n            if (n == 0) return;\n\n   \
    \         std::vector<int> dist, parent;\n            int a = farthest(graph,\
    \ 0, dist, parent);\n            int b = farthest(graph, a, dist, parent);\n\n\
    \            length = dist[b];\n            for (int v = b; v != -1; v = parent[v])\
    \ path.push_back(v);\n            std::reverse(path.begin(), path.end());\n  \
    \      }\n\n    private:\n        static int farthest(const std::vector<std::vector<int>>&\
    \ graph,\n                            int source, std::vector<int>& dist,\n  \
    \                          std::vector<int>& parent) {\n            int n = static_cast<int>(graph.size());\n\
    \            dist.assign(n, -1);\n            parent.assign(n, -1);\n        \
    \    std::vector<int> queue{source};\n            dist[source] = 0;\n        \
    \    for (int i = 0; i < static_cast<int>(queue.size()); ++i) {\n            \
    \    int v = queue[i];\n                for (int to : graph[v]) {\n          \
    \          if (dist[to] != -1) continue;\n                    dist[to] = dist[v]\
    \ + 1;\n                    parent[to] = v;\n                    queue.push_back(to);\n\
    \                }\n            }\n            return queue.back();\n        }\n\
    \    };\n}\n#line 7 \"tree/centered_tree.hpp\"\n\nnamespace yesantikiss {\n  \
    \  // \u6728\u3092\u4E2D\u5FC3\u3067\u6839\u4ED8\u3051\u3059\u308B\u3002\u4E2D\
    \u5FC3\u304C2\u70B9\u306A\u3089\u3001\u305D\u306E\u9593\u306B\u4EEE\u60F3\u9802\
    \u70B9 n \u3092\u7F6E\u3044\u3066\u6839\u306B\u3059\u308B\u3002\n    // dist2[x]\
    \ \u306F\u4E2D\u5FC3\u70B9\u304B\u3089\u306E\u8DDD\u96E2\u306E2\u500D\u3067\u3001\
    \u9802\u70B9\u500D\u3057\u305F\u6728\u3067\u306E\u6DF1\u3055\u3068\u4E00\u81F4\
    \u3059\u308B\u3002\n    // \u4E2D\u5FC3\u306E2\u70B9\u306F\u5143\u306E\u30B0\u30E9\
    \u30D5\u3067\u96A3\u308A\u5408\u3046\u304C\u3001\u6839\u4ED8\u304D\u6728\u3067\
    \u306F\u89AA\u5B50\u3067\u306F\u306A\u3044\u3002\n    // \u5B50\u306F graph[v]\
    \ \u3067\u306F\u306A\u304F children[v] \u3067\u305F\u3069\u308B\u3053\u3068\u3002\
    \n    struct CenteredTree {\n        int n = 0;\n        int root = -1;\n    \
    \    int diameter = 0;\n        std::vector<int> parent;\n        std::vector<int>\
    \ order;\n        std::vector<int> dist2;\n        std::vector<std::vector<int>>\
    \ children;\n\n        CenteredTree() = default;\n\n        explicit CenteredTree(const\
    \ std::vector<std::vector<int>>& graph) {\n            build(graph);\n       \
    \ }\n\n        void build(const std::vector<std::vector<int>>& graph) {\n    \
    \        n = static_cast<int>(graph.size());\n            root = -1;\n       \
    \     diameter = 0;\n            parent.assign(n + 1, -1);\n            dist2.assign(n\
    \ + 1, -1);\n            children.assign(n + 1, std::vector<int>());\n       \
    \     order.clear();\n            if (n == 0) return;\n\n            TreeDiameter\
    \ tree_diameter(graph);\n            diameter = tree_diameter.length;\n      \
    \      const std::vector<int>& path = tree_diameter.path;\n\n            if (diameter\
    \ % 2 == 0) {\n                root = path[diameter / 2];\n                dist2[root]\
    \ = 0;\n                order.push_back(root);\n            } else {\n       \
    \         root = n;\n                dist2[root] = 0;\n                order.push_back(root);\n\
    \                for (int v : {path[diameter / 2], path[diameter / 2 + 1]}) {\n\
    \                    parent[v] = root;\n                    dist2[v] = 1;\n  \
    \                  children[root].push_back(v);\n                    order.push_back(v);\n\
    \                }\n            }\n\n            for (int i = 0; i < static_cast<int>(order.size());\
    \ ++i) {\n                int v = order[i];\n                if (v == n) continue;\n\
    \                for (int to : graph[v]) {\n                    if (dist2[to]\
    \ != -1) continue;\n                    parent[to] = v;\n                    dist2[to]\
    \ = dist2[v] + 2;\n                    children[v].push_back(to);\n          \
    \          order.push_back(to);\n                }\n            }\n        }\n\
    \n        bool is_virtual(int v) const { return v == n; }\n\n        bool has_virtual_root()\
    \ const { return root == n; }\n\n        int radius() const { return (diameter\
    \ + 1) / 2; }\n\n        bool is_diameter_endpoint(int v) const {\n          \
    \  return !is_virtual(v) && dist2[v] == diameter;\n        }\n\n        // \u5143\
    \u306E\u6728\u3067 v \u304B\u3089\u6700\u3082\u9060\u3044\u9802\u70B9\u307E\u3067\
    \u306E\u8DDD\u96E2\u3002\n        int eccentricity(int v) const { return (dist2[v]\
    \ + diameter) / 2; }\n    };\n}\n#line 12 \"verify/random_centered_tree.test.cpp\"\
    \n\nnamespace {\n    std::vector<int> bfs(const std::vector<std::vector<int>>&\
    \ graph,\n                         int source) {\n        std::vector<int> dist(graph.size(),\
    \ -1);\n        std::vector<int> queue{source};\n        dist[source] = 0;\n \
    \       for (int i = 0; i < static_cast<int>(queue.size()); ++i) {\n         \
    \   int v = queue[i];\n            for (int to : graph[v]) {\n               \
    \ if (dist[to] != -1) continue;\n                dist[to] = dist[v] + 1;\n   \
    \             queue.push_back(to);\n            }\n        }\n        return dist;\n\
    \    }\n\n    std::vector<std::vector<int>> random_tree(int n, std::mt19937& random)\
    \ {\n        std::vector<std::vector<int>> graph(n);\n        std::vector<int>\
    \ label(n);\n        for (int i = 0; i < n; ++i) label[i] = i;\n        std::shuffle(label.begin(),\
    \ label.end(), random);\n        int mode = static_cast<int>(random() % 3);\n\
    \        for (int v = 1; v < n; ++v) {\n            int p = mode == 0   ? static_cast<int>(random()\
    \ % v)\n                    : mode == 1 ? v - 1\n                            \
    \    : std::max(0, v - 1 - static_cast<int>(random() % 3));\n            graph[label[p]].push_back(label[v]);\n\
    \            graph[label[v]].push_back(label[p]);\n        }\n        return graph;\n\
    \    }\n\n    // \u5404\u8FBA\u306B\u9802\u70B9\u3092\u306F\u3055\u3093\u3060\u6728\
    \u3067\u3001\u4E2D\u5FC3\u304B\u3089\u306E\u8DDD\u96E2\u3092\u7D20\u6734\u306B\
    \u6C42\u3081\u308B\u3002\n    std::vector<int> naive_dist2(const std::vector<std::vector<int>>&\
    \ graph) {\n        int n = static_cast<int>(graph.size());\n        std::vector<std::vector<int>>\
    \ doubled(2 * n - 1);\n        int next = n;\n        for (int v = 0; v < n; ++v)\
    \ {\n            for (int to : graph[v]) {\n                if (v > to) continue;\n\
    \                doubled[v].push_back(next);\n                doubled[next].push_back(v);\n\
    \                doubled[to].push_back(next);\n                doubled[next].push_back(to);\n\
    \                ++next;\n            }\n        }\n        int size = static_cast<int>(doubled.size());\n\
    \        int center = -1, best = size;\n        for (int v = 0; v < size; ++v)\
    \ {\n            std::vector<int> dist = bfs(doubled, v);\n            int ecc\
    \ = *std::max_element(dist.begin(), dist.end());\n            if (ecc < best)\
    \ {\n                best = ecc;\n                center = v;\n            }\n\
    \        }\n        std::vector<int> dist = bfs(doubled, center);\n        dist.resize(n);\n\
    \        return dist;\n    }\n}\n\nint main() {\n    std::mt19937 random(987654321);\n\
    \n    {\n        std::vector<std::vector<int>> empty;\n        yesantikiss::TreeDiameter\
    \ diameter(empty);\n        yesantikiss::CenteredTree centered(empty);\n     \
    \   assert(diameter.length == 0 && diameter.path.empty());\n        assert(centered.root\
    \ == -1 && centered.order.empty());\n    }\n\n    for (int trial = 0; trial <\
    \ 500; ++trial) {\n        int n = trial < 100 ? 1 + trial % 8\n             \
    \               : 1 + static_cast<int>(random() % 60);\n        std::vector<std::vector<int>>\
    \ graph = random_tree(n, random);\n\n        std::vector<std::vector<int>> dist(n);\n\
    \        int expected_diameter = 0;\n        for (int v = 0; v < n; ++v) {\n \
    \           dist[v] = bfs(graph, v);\n            expected_diameter = std::max(\n\
    \                expected_diameter, *std::max_element(dist[v].begin(),\n     \
    \                                                dist[v].end()));\n        }\n\
    \n        yesantikiss::TreeDiameter diameter(graph);\n        assert(diameter.length\
    \ == expected_diameter);\n        assert(static_cast<int>(diameter.path.size())\
    \ == diameter.length + 1);\n        for (int i = 0; i + 1 < static_cast<int>(diameter.path.size());\
    \ ++i) {\n            int u = diameter.path[i], v = diameter.path[i + 1];\n  \
    \          assert(std::count(graph[u].begin(), graph[u].end(), v) == 1);\n   \
    \     }\n        assert(dist[diameter.path.front()][diameter.path.back()] ==\n\
    \               diameter.length);\n\n        yesantikiss::CenteredTree centered(graph);\n\
    \        assert(centered.n == n);\n        assert(centered.diameter == expected_diameter);\n\
    \        assert(centered.radius() == (expected_diameter + 1) / 2);\n        assert(centered.has_virtual_root()\
    \ == (expected_diameter % 2 == 1));\n\n        std::vector<int> expected_dist2\
    \ = naive_dist2(graph);\n        for (int v = 0; v < n; ++v) {\n            assert(centered.dist2[v]\
    \ == expected_dist2[v]);\n            int ecc = *std::max_element(dist[v].begin(),\
    \ dist[v].end());\n            assert(centered.eccentricity(v) == ecc);\n    \
    \        assert(centered.is_diameter_endpoint(v) ==\n                   (ecc ==\
    \ expected_diameter));\n        }\n\n        // children \u3060\u3051\u3092\u4F7F\
    \u3046\u6728DP\u3067\u76F4\u5F84\u306E\u672C\u6570\u3092\u6570\u3048\u3001\u5168\
    \u9802\u70B9\u5BFE\u306E\u8DDD\u96E2\u3068\u6BD4\u3079\u308B\u3002\n        {\n\
    \            long long expected_count = 0;\n            for (int u = 0; u < n;\
    \ ++u) {\n                for (int v = u + 1; v < n; ++v) {\n                \
    \    if (dist[u][v] == expected_diameter) ++expected_count;\n                }\n\
    \            }\n            std::vector<long long> endpoints(n + 1);\n       \
    \     long long count = 0;\n            for (int i = static_cast<int>(centered.order.size())\
    \ - 1; i >= 0;\n                 --i) {\n                int v = centered.order[i];\n\
    \                if (centered.is_diameter_endpoint(v)) endpoints[v] = 1;\n   \
    \             for (int to : centered.children[v]) {\n                    if (v\
    \ == centered.root) {\n                        count += endpoints[v] * endpoints[to];\n\
    \                    }\n                    endpoints[v] += endpoints[to];\n \
    \               }\n            }\n            assert(count == expected_count);\n\
    \        }\n\n        int vertices = n + (centered.has_virtual_root() ? 1 : 0);\n\
    \        assert(static_cast<int>(centered.order.size()) == vertices);\n      \
    \  assert(centered.order[0] == centered.root);\n        assert(centered.parent[centered.root]\
    \ == -1);\n        std::vector<int> position(n + 1, -1);\n        for (int i =\
    \ 0; i < vertices; ++i) {\n            int v = centered.order[i];\n          \
    \  assert(position[v] == -1);\n            position[v] = i;\n        }\n     \
    \   assert(static_cast<int>(centered.children.size()) == n + 1);\n        int\
    \ child_count = 0;\n        for (int v = 0; v <= n; ++v) {\n            for (int\
    \ to : centered.children[v]) {\n                assert(centered.parent[to] ==\
    \ v);\n                ++child_count;\n            }\n        }\n        assert(child_count\
    \ == vertices - 1);\n        if (centered.has_virtual_root()) {\n            assert(centered.children[n].size()\
    \ == 2);\n        } else {\n            assert(centered.children[n].empty());\n\
    \        }\n        for (int v = 0; v < n; ++v) {\n            if (v == centered.root)\
    \ continue;\n            int p = centered.parent[v];\n            assert(position[p]\
    \ < position[v]);\n            if (centered.is_virtual(p)) {\n               \
    \ assert(centered.dist2[v] == 1);\n            } else {\n                assert(std::count(graph[v].begin(),\
    \ graph[v].end(), p) == 1);\n                assert(centered.dist2[v] == centered.dist2[p]\
    \ + 2);\n            }\n        }\n    }\n\n    long long a, b;\n    std::cin\
    \ >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "// \u7D20\u6734\u306A\u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\
    \u30E9\u30F3\u30C0\u30E0\u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089\
    \ A + B \u3092\u89E3\u304F\u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <random>\n\
    #include <vector>\n\n#include \"tree/centered_tree.hpp\"\n#include \"tree/tree_diameter.hpp\"\
    \n\nnamespace {\n    std::vector<int> bfs(const std::vector<std::vector<int>>&\
    \ graph,\n                         int source) {\n        std::vector<int> dist(graph.size(),\
    \ -1);\n        std::vector<int> queue{source};\n        dist[source] = 0;\n \
    \       for (int i = 0; i < static_cast<int>(queue.size()); ++i) {\n         \
    \   int v = queue[i];\n            for (int to : graph[v]) {\n               \
    \ if (dist[to] != -1) continue;\n                dist[to] = dist[v] + 1;\n   \
    \             queue.push_back(to);\n            }\n        }\n        return dist;\n\
    \    }\n\n    std::vector<std::vector<int>> random_tree(int n, std::mt19937& random)\
    \ {\n        std::vector<std::vector<int>> graph(n);\n        std::vector<int>\
    \ label(n);\n        for (int i = 0; i < n; ++i) label[i] = i;\n        std::shuffle(label.begin(),\
    \ label.end(), random);\n        int mode = static_cast<int>(random() % 3);\n\
    \        for (int v = 1; v < n; ++v) {\n            int p = mode == 0   ? static_cast<int>(random()\
    \ % v)\n                    : mode == 1 ? v - 1\n                            \
    \    : std::max(0, v - 1 - static_cast<int>(random() % 3));\n            graph[label[p]].push_back(label[v]);\n\
    \            graph[label[v]].push_back(label[p]);\n        }\n        return graph;\n\
    \    }\n\n    // \u5404\u8FBA\u306B\u9802\u70B9\u3092\u306F\u3055\u3093\u3060\u6728\
    \u3067\u3001\u4E2D\u5FC3\u304B\u3089\u306E\u8DDD\u96E2\u3092\u7D20\u6734\u306B\
    \u6C42\u3081\u308B\u3002\n    std::vector<int> naive_dist2(const std::vector<std::vector<int>>&\
    \ graph) {\n        int n = static_cast<int>(graph.size());\n        std::vector<std::vector<int>>\
    \ doubled(2 * n - 1);\n        int next = n;\n        for (int v = 0; v < n; ++v)\
    \ {\n            for (int to : graph[v]) {\n                if (v > to) continue;\n\
    \                doubled[v].push_back(next);\n                doubled[next].push_back(v);\n\
    \                doubled[to].push_back(next);\n                doubled[next].push_back(to);\n\
    \                ++next;\n            }\n        }\n        int size = static_cast<int>(doubled.size());\n\
    \        int center = -1, best = size;\n        for (int v = 0; v < size; ++v)\
    \ {\n            std::vector<int> dist = bfs(doubled, v);\n            int ecc\
    \ = *std::max_element(dist.begin(), dist.end());\n            if (ecc < best)\
    \ {\n                best = ecc;\n                center = v;\n            }\n\
    \        }\n        std::vector<int> dist = bfs(doubled, center);\n        dist.resize(n);\n\
    \        return dist;\n    }\n}\n\nint main() {\n    std::mt19937 random(987654321);\n\
    \n    {\n        std::vector<std::vector<int>> empty;\n        yesantikiss::TreeDiameter\
    \ diameter(empty);\n        yesantikiss::CenteredTree centered(empty);\n     \
    \   assert(diameter.length == 0 && diameter.path.empty());\n        assert(centered.root\
    \ == -1 && centered.order.empty());\n    }\n\n    for (int trial = 0; trial <\
    \ 500; ++trial) {\n        int n = trial < 100 ? 1 + trial % 8\n             \
    \               : 1 + static_cast<int>(random() % 60);\n        std::vector<std::vector<int>>\
    \ graph = random_tree(n, random);\n\n        std::vector<std::vector<int>> dist(n);\n\
    \        int expected_diameter = 0;\n        for (int v = 0; v < n; ++v) {\n \
    \           dist[v] = bfs(graph, v);\n            expected_diameter = std::max(\n\
    \                expected_diameter, *std::max_element(dist[v].begin(),\n     \
    \                                                dist[v].end()));\n        }\n\
    \n        yesantikiss::TreeDiameter diameter(graph);\n        assert(diameter.length\
    \ == expected_diameter);\n        assert(static_cast<int>(diameter.path.size())\
    \ == diameter.length + 1);\n        for (int i = 0; i + 1 < static_cast<int>(diameter.path.size());\
    \ ++i) {\n            int u = diameter.path[i], v = diameter.path[i + 1];\n  \
    \          assert(std::count(graph[u].begin(), graph[u].end(), v) == 1);\n   \
    \     }\n        assert(dist[diameter.path.front()][diameter.path.back()] ==\n\
    \               diameter.length);\n\n        yesantikiss::CenteredTree centered(graph);\n\
    \        assert(centered.n == n);\n        assert(centered.diameter == expected_diameter);\n\
    \        assert(centered.radius() == (expected_diameter + 1) / 2);\n        assert(centered.has_virtual_root()\
    \ == (expected_diameter % 2 == 1));\n\n        std::vector<int> expected_dist2\
    \ = naive_dist2(graph);\n        for (int v = 0; v < n; ++v) {\n            assert(centered.dist2[v]\
    \ == expected_dist2[v]);\n            int ecc = *std::max_element(dist[v].begin(),\
    \ dist[v].end());\n            assert(centered.eccentricity(v) == ecc);\n    \
    \        assert(centered.is_diameter_endpoint(v) ==\n                   (ecc ==\
    \ expected_diameter));\n        }\n\n        // children \u3060\u3051\u3092\u4F7F\
    \u3046\u6728DP\u3067\u76F4\u5F84\u306E\u672C\u6570\u3092\u6570\u3048\u3001\u5168\
    \u9802\u70B9\u5BFE\u306E\u8DDD\u96E2\u3068\u6BD4\u3079\u308B\u3002\n        {\n\
    \            long long expected_count = 0;\n            for (int u = 0; u < n;\
    \ ++u) {\n                for (int v = u + 1; v < n; ++v) {\n                \
    \    if (dist[u][v] == expected_diameter) ++expected_count;\n                }\n\
    \            }\n            std::vector<long long> endpoints(n + 1);\n       \
    \     long long count = 0;\n            for (int i = static_cast<int>(centered.order.size())\
    \ - 1; i >= 0;\n                 --i) {\n                int v = centered.order[i];\n\
    \                if (centered.is_diameter_endpoint(v)) endpoints[v] = 1;\n   \
    \             for (int to : centered.children[v]) {\n                    if (v\
    \ == centered.root) {\n                        count += endpoints[v] * endpoints[to];\n\
    \                    }\n                    endpoints[v] += endpoints[to];\n \
    \               }\n            }\n            assert(count == expected_count);\n\
    \        }\n\n        int vertices = n + (centered.has_virtual_root() ? 1 : 0);\n\
    \        assert(static_cast<int>(centered.order.size()) == vertices);\n      \
    \  assert(centered.order[0] == centered.root);\n        assert(centered.parent[centered.root]\
    \ == -1);\n        std::vector<int> position(n + 1, -1);\n        for (int i =\
    \ 0; i < vertices; ++i) {\n            int v = centered.order[i];\n          \
    \  assert(position[v] == -1);\n            position[v] = i;\n        }\n     \
    \   assert(static_cast<int>(centered.children.size()) == n + 1);\n        int\
    \ child_count = 0;\n        for (int v = 0; v <= n; ++v) {\n            for (int\
    \ to : centered.children[v]) {\n                assert(centered.parent[to] ==\
    \ v);\n                ++child_count;\n            }\n        }\n        assert(child_count\
    \ == vertices - 1);\n        if (centered.has_virtual_root()) {\n            assert(centered.children[n].size()\
    \ == 2);\n        } else {\n            assert(centered.children[n].empty());\n\
    \        }\n        for (int v = 0; v < n; ++v) {\n            if (v == centered.root)\
    \ continue;\n            int p = centered.parent[v];\n            assert(position[p]\
    \ < position[v]);\n            if (centered.is_virtual(p)) {\n               \
    \ assert(centered.dist2[v] == 1);\n            } else {\n                assert(std::count(graph[v].begin(),\
    \ graph[v].end(), p) == 1);\n                assert(centered.dist2[v] == centered.dist2[p]\
    \ + 2);\n            }\n        }\n    }\n\n    long long a, b;\n    std::cin\
    \ >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - tree/centered_tree.hpp
  - tree/tree_diameter.hpp
  isVerificationFile: true
  path: verify/random_centered_tree.test.cpp
  requiredBy: []
  timestamp: '2026-11-12 13:12:40+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/random_centered_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/random_centered_tree.test.cpp
- /verify/verify/random_centered_tree.test.cpp.html
title: verify/random_centered_tree.test.cpp
---
