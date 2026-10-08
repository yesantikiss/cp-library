---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: tests/test.cpp
    title: tests/test.cpp
  - icon: ':warning:'
    path: tests/tree_randomized.cpp
    title: tests/tree_randomized.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/vertex_add_path_sum.test.cpp
    title: verify/vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/vertex_set_path_composite.test.cpp
    title: verify/vertex_set_path_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"tree/heavy_light_decomposition.hpp\"\n\n#include <algorithm>\n\
    #include <tuple>\n#include <utility>\n#include <vector>\n\nnamespace yesantikiss\
    \ {\n    struct HeavyLightDecomposition {\n        int n = 0;\n        int root\
    \ = -1;\n        std::vector<int> parent;\n        std::vector<int> depth;\n \
    \       std::vector<int> size;\n        std::vector<int> in;\n        std::vector<int>\
    \ out;\n        std::vector<int> head;\n        std::vector<int> heavy;\n    \
    \    std::vector<int> vertex;\n\n        HeavyLightDecomposition() = default;\n\
    \n        explicit HeavyLightDecomposition(\n            const std::vector<std::vector<int>>&\
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
    \ -1);\n            vertex.assign(n, -1);\n        }\n    };\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\nnamespace yesantikiss {\n    struct HeavyLightDecomposition\
    \ {\n        int n = 0;\n        int root = -1;\n        std::vector<int> parent;\n\
    \        std::vector<int> depth;\n        std::vector<int> size;\n        std::vector<int>\
    \ in;\n        std::vector<int> out;\n        std::vector<int> head;\n       \
    \ std::vector<int> heavy;\n        std::vector<int> vertex;\n\n        HeavyLightDecomposition()\
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
    \ -1);\n            vertex.assign(n, -1);\n        }\n    };\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/heavy_light_decomposition.hpp
  requiredBy:
  - tests/tree_randomized.cpp
  - tests/test.cpp
  timestamp: '2026-10-08 13:39:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/vertex_add_path_sum.test.cpp
  - verify/vertex_set_path_composite.test.cpp
documentation_of: tree/heavy_light_decomposition.hpp
layout: document
title: Heavy-Light Decomposition
---

## 概要

木のパスを `O(log N)` 個の半開区間へ分解します。各頂点 `v` は配列上の
`in[v]` に対応し、`vertex[in[v]] == v` です。同じ部分木の頂点は連続する
区間に配置されます。

## パスの分解

```cpp
yesantikiss::HeavyLightDecomposition hld(graph, root);
hld.path_query(u, v, false, [&](int l, int r, bool reverse) {
    // reverse == false: l, l+1, ..., r-1
    // reverse == true : r-1, r-2, ..., l
});
```

コールバックは `u` から `v` へ進む順に呼ばれるため、文字列合成などの
非可換な演算にも利用できます。`edge == false` では頂点パス、`true` では
各辺を深い方の頂点へ対応させた辺パスを分解します。

`path_fold(u, v, edge, op, identity, get)` は、各区間について
`get(l, r, reverse)` が返した値を順に `op` で畳み込みます。

## その他のAPI

- `subtree_vertex(v)`: 頂点部分木に対応する `[in[v], out[v])`
- `subtree_edge(v)`: 部分木内の辺に対応する `[in[v] + 1, out[v])`
- `edge_vertex(u, v)`: 辺 `u-v` に対応する深い方の頂点
- `lca(u, v)`, `dist(u, v)`, `is_ancestor(u, v)`

## 要件・計算量

入力は連結な無向木で、頂点番号は `0` 以上 `N` 未満とします。構築は
`O(N)` 時間・メモリ、LCAとパス分解は `O(log N)` 時間です。構築処理は
再帰を使用しません。
