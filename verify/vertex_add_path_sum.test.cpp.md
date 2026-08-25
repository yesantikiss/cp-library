---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/heavy_light_decomposition.hpp
    title: Heavy-Light Decomposition
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_path_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_path_sum
  bundledCode: "#line 1 \"verify/vertex_add_path_sum.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/vertex_add_path_sum\"\n\n#include <iostream>\n\
    #include <vector>\n\n#line 2 \"tree/heavy_light_decomposition.hpp\"\n\n#include\
    \ <algorithm>\n#include <tuple>\n#include <utility>\n#line 7 \"tree/heavy_light_decomposition.hpp\"\
    \n\nnamespace yesantikiss {\n    struct HeavyLightDecomposition {\n        int\
    \ n = 0;\n        int root = -1;\n        std::vector<int> parent;\n        std::vector<int>\
    \ depth;\n        std::vector<int> size;\n        std::vector<int> in;\n     \
    \   std::vector<int> out;\n        std::vector<int> head;\n        std::vector<int>\
    \ heavy;\n        std::vector<int> vertex;\n\n        HeavyLightDecomposition()\
    \ = default;\n\n        explicit HeavyLightDecomposition(\n            const std::vector<std::vector<int>>&\
    \ graph, int root_ = 0) {\n            build(graph, root_);\n        }\n\n   \
    \     void build(const std::vector<std::vector<int>>& graph, int root_ = 0) {\n\
    \            init(static_cast<int>(graph.size()));\n            if (n == 0) return;\n\
    \            root = root_;\n\n            std::vector<int> order{root};\n    \
    \        parent[root] = root;\n            for (int i = 0; i < static_cast<int>(order.size());\
    \ ++i) {\n                int v = order[i];\n                for (int to : graph[v])\
    \ {\n                    if (parent[to] != -1) continue;\n                   \
    \ parent[to] = v;\n                    depth[to] = depth[v] + 1;\n           \
    \         order.push_back(to);\n                }\n            }\n\n         \
    \   for (int i = static_cast<int>(order.size()) - 1; i >= 0; --i) {\n        \
    \        int v = order[i];\n                int largest_size = 0;\n          \
    \      for (int to : graph[v]) {\n                    if (parent[to] != v) continue;\n\
    \                    size[v] += size[to];\n                    if (size[to] >\
    \ largest_size) {\n                        largest_size = size[to];\n        \
    \                heavy[v] = to;\n                    }\n                }\n  \
    \          }\n\n            int timer = 0;\n            std::vector<std::pair<int,\
    \ int>> pending{{root, root}};\n            while (!pending.empty()) {\n     \
    \           auto [v, chain_head] = pending.back();\n                pending.pop_back();\n\
    \n                for (; v != -1; v = heavy[v]) {\n                    head[v]\
    \ = chain_head;\n                    in[v] = timer;\n                    vertex[timer++]\
    \ = v;\n\n                    for (int to : graph[v]) {\n                    \
    \    if (parent[to] == v && to != heavy[v]) {\n                            pending.emplace_back(to,\
    \ to);\n                        }\n                    }\n                }\n\
    \            }\n\n            for (int v = 0; v < n; ++v) {\n                if\
    \ (in[v] != -1) out[v] = in[v] + size[v];\n            }\n        }\n\n      \
    \  int edge_vertex(int u, int v) const {\n            return depth[u] > depth[v]\
    \ ? u : v;\n        }\n\n        int lca(int u, int v) const {\n            while\
    \ (head[u] != head[v]) {\n                if (depth[head[u]] > depth[head[v]])\
    \ {\n                    u = parent[head[u]];\n                } else {\n    \
    \                v = parent[head[v]];\n                }\n            }\n    \
    \        return depth[u] < depth[v] ? u : v;\n        }\n\n        int dist(int\
    \ u, int v) const {\n            int ancestor = lca(u, v);\n            return\
    \ depth[u] + depth[v] - 2 * depth[ancestor];\n        }\n\n        bool is_ancestor(int\
    \ ancestor, int v) const {\n            return in[ancestor] <= in[v] && out[v]\
    \ <= out[ancestor];\n        }\n\n        std::pair<int, int> subtree_vertex(int\
    \ v) const {\n            return {in[v], out[v]};\n        }\n\n        // \u5404\
    \u8FBA\u3092\u6DF1\u3044\u65B9\u306E\u9802\u70B9\u306B\u5BFE\u5FDC\u3055\u305B\
    \u305F\u3068\u304D\u306E\u90E8\u5206\u6728\u5185\u306E\u8FBA\u3002\n        std::pair<int,\
    \ int> subtree_edge(int v) const {\n            return {in[v] + 1, out[v]};\n\
    \        }\n\n        // u -> v \u306E\u9806\u306B\u3001\u30D1\u30B9\u3092\u534A\
    \u958B\u533A\u9593\u3078\u5206\u89E3\u3059\u308B\u3002\n        // reverse=true\
    \ \u306E\u533A\u9593\u306F r-1, ..., l \u306E\u9806\u306B\u8AAD\u3080\u3002\n\
    \        template <class F>\n        void path_query(int u, int v, bool edge,\
    \ F&& callback) const {\n            std::vector<std::tuple<int, int, bool>> right;\n\
    \n            while (head[u] != head[v]) {\n                if (depth[head[u]]\
    \ > depth[head[v]]) {\n                    callback(in[head[u]], in[u] + 1, true);\n\
    \                    u = parent[head[u]];\n                } else {\n        \
    \            right.emplace_back(in[head[v]], in[v] + 1, false);\n            \
    \        v = parent[head[v]];\n                }\n            }\n\n          \
    \  if (depth[u] > depth[v]) {\n                int left = in[v] + (edge ? 1 :\
    \ 0);\n                int right_end = in[u] + 1;\n                if (left <\
    \ right_end) callback(left, right_end, true);\n            } else {\n        \
    \        int left = in[u] + (edge ? 1 : 0);\n                int right_end = in[v]\
    \ + 1;\n                if (left < right_end) callback(left, right_end, false);\n\
    \            }\n\n            std::reverse(right.begin(), right.end());\n    \
    \        for (auto [left, right_end, reverse] : right) {\n                callback(left,\
    \ right_end, reverse);\n            }\n        }\n\n        template <class S,\
    \ class Op, class Get>\n        S path_fold(int u, int v, bool edge, Op op, S\
    \ identity,\n                    Get get) const {\n            S result = identity;\n\
    \            path_query(u, v, edge,\n                       [&](int left, int\
    \ right, bool reverse) {\n                           result = op(result, get(left,\
    \ right, reverse));\n                       });\n            return result;\n\
    \        }\n\n    private:\n        void init(int size_) {\n            n = size_;\n\
    \            root = -1;\n            parent.assign(n, -1);\n            depth.assign(n,\
    \ 0);\n            size.assign(n, 1);\n            in.assign(n, -1);\n       \
    \     out.assign(n, -1);\n            head.assign(n, -1);\n            heavy.assign(n,\
    \ -1);\n            vertex.assign(n, -1);\n        }\n    };\n}\n#line 7 \"verify/vertex_add_path_sum.test.cpp\"\
    \n\nstruct FenwickTree {\n    std::vector<long long> data;\n\n    explicit FenwickTree(int\
    \ n) : data(n + 1) {}\n\n    void add(int index, long long value) {\n        for\
    \ (++index; index < static_cast<int>(data.size());\n             index += index\
    \ & -index) {\n            data[index] += value;\n        }\n    }\n\n    long\
    \ long prefix_sum(int right) const {\n        long long result = 0;\n        for\
    \ (; right > 0; right -= right & -right) result += data[right];\n        return\
    \ result;\n    }\n\n    long long sum(int left, int right) const {\n        return\
    \ prefix_sum(right) - prefix_sum(left);\n    }\n};\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<int>\
    \ value(n);\n    for (int& x : value) std::cin >> x;\n\n    std::vector<std::vector<int>>\
    \ graph(n);\n    for (int i = 0; i + 1 < n; ++i) {\n        int u, v;\n      \
    \  std::cin >> u >> v;\n        graph[u].push_back(v);\n        graph[v].push_back(u);\n\
    \    }\n\n    yesantikiss::HeavyLightDecomposition hld(graph);\n    FenwickTree\
    \ fenwick(n);\n    for (int v = 0; v < n; ++v) fenwick.add(hld.in[v], value[v]);\n\
    \n    while (q--) {\n        int type;\n        std::cin >> type;\n        if\
    \ (type == 0) {\n            int v, x;\n            std::cin >> v >> x;\n    \
    \        fenwick.add(hld.in[v], x);\n        } else {\n            int u, v;\n\
    \            std::cin >> u >> v;\n            long long answer = 0;\n        \
    \    hld.path_query(u, v, false, [&](int left, int right, bool) {\n          \
    \      answer += fenwick.sum(left, right);\n            });\n            std::cout\
    \ << answer << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_path_sum\"\n\
    \n#include <iostream>\n#include <vector>\n\n#include \"tree/heavy_light_decomposition.hpp\"\
    \n\nstruct FenwickTree {\n    std::vector<long long> data;\n\n    explicit FenwickTree(int\
    \ n) : data(n + 1) {}\n\n    void add(int index, long long value) {\n        for\
    \ (++index; index < static_cast<int>(data.size());\n             index += index\
    \ & -index) {\n            data[index] += value;\n        }\n    }\n\n    long\
    \ long prefix_sum(int right) const {\n        long long result = 0;\n        for\
    \ (; right > 0; right -= right & -right) result += data[right];\n        return\
    \ result;\n    }\n\n    long long sum(int left, int right) const {\n        return\
    \ prefix_sum(right) - prefix_sum(left);\n    }\n};\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<int>\
    \ value(n);\n    for (int& x : value) std::cin >> x;\n\n    std::vector<std::vector<int>>\
    \ graph(n);\n    for (int i = 0; i + 1 < n; ++i) {\n        int u, v;\n      \
    \  std::cin >> u >> v;\n        graph[u].push_back(v);\n        graph[v].push_back(u);\n\
    \    }\n\n    yesantikiss::HeavyLightDecomposition hld(graph);\n    FenwickTree\
    \ fenwick(n);\n    for (int v = 0; v < n; ++v) fenwick.add(hld.in[v], value[v]);\n\
    \n    while (q--) {\n        int type;\n        std::cin >> type;\n        if\
    \ (type == 0) {\n            int v, x;\n            std::cin >> v >> x;\n    \
    \        fenwick.add(hld.in[v], x);\n        } else {\n            int u, v;\n\
    \            std::cin >> u >> v;\n            long long answer = 0;\n        \
    \    hld.path_query(u, v, false, [&](int left, int right, bool) {\n          \
    \      answer += fenwick.sum(left, right);\n            });\n            std::cout\
    \ << answer << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - tree/heavy_light_decomposition.hpp
  isVerificationFile: true
  path: verify/vertex_add_path_sum.test.cpp
  requiredBy: []
  timestamp: '2026-08-25 15:58:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/vertex_add_path_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/vertex_add_path_sum.test.cpp
- /verify/verify/vertex_add_path_sum.test.cpp.html
title: verify/vertex_add_path_sum.test.cpp
---
