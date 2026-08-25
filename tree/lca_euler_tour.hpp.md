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
    path: verify/lca_euler_tour.test.cpp
    title: verify/lca_euler_tour.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"tree/lca_euler_tour.hpp\"\n\n#include <algorithm>\n#include\
    \ <vector>\n\nnamespace yesantikiss {\n    struct EulerTourLCA {\n        int\
    \ n = 0;\n        std::vector<int> depth;\n        std::vector<int> parent;\n\
    \        std::vector<int> component;\n        std::vector<int> tin;\n        std::vector<int>\
    \ tout;\n\n        EulerTourLCA() = default;\n\n        explicit EulerTourLCA(const\
    \ std::vector<std::vector<int>>& graph,\n                              int root\
    \ = 0) {\n            build(graph, root);\n        }\n\n        void build(const\
    \ std::vector<std::vector<int>>& graph, int root = 0) {\n            init(static_cast<int>(graph.size()));\n\
    \            if (n == 0) return;\n\n            euler.reserve(2 * n - 1);\n  \
    \          build_component(graph, root, 0);\n            build_sparse_table();\n\
    \        }\n\n        void build_forest(const std::vector<std::vector<int>>& graph)\
    \ {\n            init(static_cast<int>(graph.size()));\n            euler.reserve(n\
    \ == 0 ? 0 : 2 * n - 1);\n\n            int component_id = 0;\n            for\
    \ (int root = 0; root < n; ++root) {\n                if (parent[root] == -1)\
    \ {\n                    build_component(graph, root, component_id++);\n     \
    \           }\n            }\n            build_sparse_table();\n        }\n\n\
    \        int lca(int a, int b) const {\n            if (!same_component(a, b))\
    \ return -1;\n            int left = first[a];\n            int right = first[b];\n\
    \            if (left > right) std::swap(left, right);\n\n            int length\
    \ = right - left + 1;\n            int level = lg[length];\n            return\
    \ better(st_at(level, left),\n                          st_at(level, right - (1\
    \ << level) + 1));\n        }\n\n        int dist(int a, int b) const {\n    \
    \        int ancestor = lca(a, b);\n            if (ancestor == -1) return -1;\n\
    \            return depth[a] + depth[b] - 2 * depth[ancestor];\n        }\n\n\
    \        bool is_ancestor(int ancestor, int v) const {\n            return same_component(ancestor,\
    \ v) && tin[ancestor] <= tin[v] &&\n                   tout[v] <= tout[ancestor];\n\
    \        }\n\n    private:\n        int timer = 0;\n        int euler_size = 0;\n\
    \        int levels = 0;\n        std::vector<int> first;\n        std::vector<int>\
    \ euler;\n        std::vector<int> lg;\n        std::vector<int> sparse_table;\n\
    \n        struct Frame {\n            int v;\n            int next_edge;\n   \
    \     };\n\n        void init(int size) {\n            n = size;\n           \
    \ timer = 0;\n            euler_size = 0;\n            levels = 0;\n         \
    \   depth.assign(n, 0);\n            parent.assign(n, -1);\n            component.assign(n,\
    \ -1);\n            tin.assign(n, -1);\n            tout.assign(n, -1);\n    \
    \        first.assign(n, -1);\n            euler.clear();\n            lg.clear();\n\
    \            sparse_table.clear();\n        }\n\n        bool contains(int v)\
    \ const { return 0 <= v && v < n; }\n\n        bool same_component(int a, int\
    \ b) const {\n            return contains(a) && contains(b) && component[a] !=\
    \ -1 &&\n                   component[a] == component[b];\n        }\n\n     \
    \   int& st_at(int level, int index) {\n            return sparse_table[level\
    \ * euler_size + index];\n        }\n\n        int st_at(int level, int index)\
    \ const {\n            return sparse_table[level * euler_size + index];\n    \
    \    }\n\n        int better(int a, int b) const {\n            return depth[a]\
    \ <= depth[b] ? a : b;\n        }\n\n        void enter(int v, int p, int component_id)\
    \ {\n            parent[v] = p;\n            component[v] = component_id;\n  \
    \          tin[v] = timer++;\n            first[v] = static_cast<int>(euler.size());\n\
    \            euler.push_back(v);\n        }\n\n        void build_component(const\
    \ std::vector<std::vector<int>>& graph,\n                             int root,\
    \ int component_id) {\n            depth[root] = 0;\n            enter(root, root,\
    \ component_id);\n            std::vector<Frame> stack{{root, 0}};\n\n       \
    \     while (!stack.empty()) {\n                Frame& frame = stack.back();\n\
    \                int v = frame.v;\n                if (frame.next_edge == static_cast<int>(graph[v].size()))\
    \ {\n                    tout[v] = timer;\n                    stack.pop_back();\n\
    \                    if (!stack.empty()) euler.push_back(stack.back().v);\n  \
    \                  continue;\n                }\n\n                int to = graph[v][frame.next_edge++];\n\
    \                if (parent[to] != -1) continue;\n                depth[to] =\
    \ depth[v] + 1;\n                enter(to, v, component_id);\n               \
    \ stack.push_back({to, 0});\n            }\n        }\n\n        void build_sparse_table()\
    \ {\n            euler_size = static_cast<int>(euler.size());\n            if\
    \ (euler_size == 0) return;\n\n            lg.assign(euler_size + 1, 0);\n   \
    \         for (int i = 2; i <= euler_size; ++i) lg[i] = lg[i / 2] + 1;\n\n   \
    \         levels = lg[euler_size] + 1;\n            sparse_table.assign(levels\
    \ * euler_size, 0);\n            for (int i = 0; i < euler_size; ++i) st_at(0,\
    \ i) = euler[i];\n\n            for (int level = 1; level < levels; ++level) {\n\
    \                int length = 1 << level;\n                int half = length /\
    \ 2;\n                for (int i = 0; i + length <= euler_size; ++i) {\n     \
    \               st_at(level, i) =\n                        better(st_at(level\
    \ - 1, i),\n                               st_at(level - 1, i + half));\n    \
    \            }\n            }\n        }\n    };\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <vector>\n\nnamespace yesantikiss\
    \ {\n    struct EulerTourLCA {\n        int n = 0;\n        std::vector<int> depth;\n\
    \        std::vector<int> parent;\n        std::vector<int> component;\n     \
    \   std::vector<int> tin;\n        std::vector<int> tout;\n\n        EulerTourLCA()\
    \ = default;\n\n        explicit EulerTourLCA(const std::vector<std::vector<int>>&\
    \ graph,\n                              int root = 0) {\n            build(graph,\
    \ root);\n        }\n\n        void build(const std::vector<std::vector<int>>&\
    \ graph, int root = 0) {\n            init(static_cast<int>(graph.size()));\n\
    \            if (n == 0) return;\n\n            euler.reserve(2 * n - 1);\n  \
    \          build_component(graph, root, 0);\n            build_sparse_table();\n\
    \        }\n\n        void build_forest(const std::vector<std::vector<int>>& graph)\
    \ {\n            init(static_cast<int>(graph.size()));\n            euler.reserve(n\
    \ == 0 ? 0 : 2 * n - 1);\n\n            int component_id = 0;\n            for\
    \ (int root = 0; root < n; ++root) {\n                if (parent[root] == -1)\
    \ {\n                    build_component(graph, root, component_id++);\n     \
    \           }\n            }\n            build_sparse_table();\n        }\n\n\
    \        int lca(int a, int b) const {\n            if (!same_component(a, b))\
    \ return -1;\n            int left = first[a];\n            int right = first[b];\n\
    \            if (left > right) std::swap(left, right);\n\n            int length\
    \ = right - left + 1;\n            int level = lg[length];\n            return\
    \ better(st_at(level, left),\n                          st_at(level, right - (1\
    \ << level) + 1));\n        }\n\n        int dist(int a, int b) const {\n    \
    \        int ancestor = lca(a, b);\n            if (ancestor == -1) return -1;\n\
    \            return depth[a] + depth[b] - 2 * depth[ancestor];\n        }\n\n\
    \        bool is_ancestor(int ancestor, int v) const {\n            return same_component(ancestor,\
    \ v) && tin[ancestor] <= tin[v] &&\n                   tout[v] <= tout[ancestor];\n\
    \        }\n\n    private:\n        int timer = 0;\n        int euler_size = 0;\n\
    \        int levels = 0;\n        std::vector<int> first;\n        std::vector<int>\
    \ euler;\n        std::vector<int> lg;\n        std::vector<int> sparse_table;\n\
    \n        struct Frame {\n            int v;\n            int next_edge;\n   \
    \     };\n\n        void init(int size) {\n            n = size;\n           \
    \ timer = 0;\n            euler_size = 0;\n            levels = 0;\n         \
    \   depth.assign(n, 0);\n            parent.assign(n, -1);\n            component.assign(n,\
    \ -1);\n            tin.assign(n, -1);\n            tout.assign(n, -1);\n    \
    \        first.assign(n, -1);\n            euler.clear();\n            lg.clear();\n\
    \            sparse_table.clear();\n        }\n\n        bool contains(int v)\
    \ const { return 0 <= v && v < n; }\n\n        bool same_component(int a, int\
    \ b) const {\n            return contains(a) && contains(b) && component[a] !=\
    \ -1 &&\n                   component[a] == component[b];\n        }\n\n     \
    \   int& st_at(int level, int index) {\n            return sparse_table[level\
    \ * euler_size + index];\n        }\n\n        int st_at(int level, int index)\
    \ const {\n            return sparse_table[level * euler_size + index];\n    \
    \    }\n\n        int better(int a, int b) const {\n            return depth[a]\
    \ <= depth[b] ? a : b;\n        }\n\n        void enter(int v, int p, int component_id)\
    \ {\n            parent[v] = p;\n            component[v] = component_id;\n  \
    \          tin[v] = timer++;\n            first[v] = static_cast<int>(euler.size());\n\
    \            euler.push_back(v);\n        }\n\n        void build_component(const\
    \ std::vector<std::vector<int>>& graph,\n                             int root,\
    \ int component_id) {\n            depth[root] = 0;\n            enter(root, root,\
    \ component_id);\n            std::vector<Frame> stack{{root, 0}};\n\n       \
    \     while (!stack.empty()) {\n                Frame& frame = stack.back();\n\
    \                int v = frame.v;\n                if (frame.next_edge == static_cast<int>(graph[v].size()))\
    \ {\n                    tout[v] = timer;\n                    stack.pop_back();\n\
    \                    if (!stack.empty()) euler.push_back(stack.back().v);\n  \
    \                  continue;\n                }\n\n                int to = graph[v][frame.next_edge++];\n\
    \                if (parent[to] != -1) continue;\n                depth[to] =\
    \ depth[v] + 1;\n                enter(to, v, component_id);\n               \
    \ stack.push_back({to, 0});\n            }\n        }\n\n        void build_sparse_table()\
    \ {\n            euler_size = static_cast<int>(euler.size());\n            if\
    \ (euler_size == 0) return;\n\n            lg.assign(euler_size + 1, 0);\n   \
    \         for (int i = 2; i <= euler_size; ++i) lg[i] = lg[i / 2] + 1;\n\n   \
    \         levels = lg[euler_size] + 1;\n            sparse_table.assign(levels\
    \ * euler_size, 0);\n            for (int i = 0; i < euler_size; ++i) st_at(0,\
    \ i) = euler[i];\n\n            for (int level = 1; level < levels; ++level) {\n\
    \                int length = 1 << level;\n                int half = length /\
    \ 2;\n                for (int i = 0; i + length <= euler_size; ++i) {\n     \
    \               st_at(level, i) =\n                        better(st_at(level\
    \ - 1, i),\n                               st_at(level - 1, i + half));\n    \
    \            }\n            }\n        }\n    };\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/lca_euler_tour.hpp
  requiredBy:
  - tests/test.cpp
  - tests/tree_randomized.cpp
  timestamp: '2026-08-25 15:58:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/lca_euler_tour.test.cpp
documentation_of: tree/lca_euler_tour.hpp
layout: document
title: LCA (Euler Tour + Sparse Table)
---

## 概要

Euler Tour上の深さ最小値をSparse Tableで求めることで、最小共通祖先へ
定数時間で回答します。LCAの問い合わせ回数が多い場合に向いています。

```cpp
yesantikiss::EulerTourLCA tree(graph, root);
int ancestor = tree.lca(u, v);
```

## API

- `EulerTourLCA(graph, root)`: `root` を根として構築します。
- `build(graph, root)`: 同じインスタンスを再構築します。
- `build_forest(graph)`: 各連結成分の最小頂点を根として森を構築します。
- `lca(u, v)`: 最小共通祖先を返します。
- `dist(u, v)`: `u-v` パスの辺数を返します。
- `is_ancestor(u, v)`: `u` が `v` の祖先か判定します。

森に対する異なる連結成分間の問い合わせは、整数を返す関数では `-1`、
`is_ancestor` では `false` になります。

## 要件・計算量

入力は無向の木または森で、頂点番号は `0` 以上 `N` 未満とします。構築は
`O(N log N)` 時間・メモリ、各問い合わせは `O(1)` 時間です。
