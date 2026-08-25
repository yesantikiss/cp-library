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
    path: verify/jump_on_tree.test.cpp
    title: verify/jump_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/lca_binary_lifting.test.cpp
    title: verify/lca_binary_lifting.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"tree/lca_binary_lifting.hpp\"\n\n#include <algorithm>\n\
    #include <vector>\n\nnamespace yesantikiss {\n    struct BinaryLiftingLCA {\n\
    \        int n = 0;\n        int log = 1;\n        std::vector<int> depth;\n \
    \       std::vector<int> parent;\n        std::vector<int> component;\n\n    \
    \    BinaryLiftingLCA() = default;\n\n        explicit BinaryLiftingLCA(\n   \
    \         const std::vector<std::vector<int>>& graph, int root = 0) {\n      \
    \      build(graph, root);\n        }\n\n        void build(const std::vector<std::vector<int>>&\
    \ graph, int root = 0) {\n            init(static_cast<int>(graph.size()));\n\
    \            if (n == 0) return;\n\n            build_component(graph, root, 0);\n\
    \            build_table();\n        }\n\n        void build_forest(const std::vector<std::vector<int>>&\
    \ graph) {\n            init(static_cast<int>(graph.size()));\n\n            int\
    \ component_id = 0;\n            for (int root = 0; root < n; ++root) {\n    \
    \            if (parent[root] == -1) {\n                    build_component(graph,\
    \ root, component_id++);\n                }\n            }\n            build_table();\n\
    \        }\n\n        int kth_ancestor(int v, int k) const {\n            if (!contains(v)\
    \ || k < 0 || parent[v] == -1) return -1;\n            k = std::min(k, depth[v]);\n\
    \            for (int bit = 0; bit < log; ++bit) {\n                if ((k >>\
    \ bit) & 1) v = up_at(bit, v);\n            }\n            return v;\n       \
    \ }\n\n        int lca(int a, int b) const {\n            if (!same_component(a,\
    \ b)) return -1;\n            if (depth[a] < depth[b]) std::swap(a, b);\n\n  \
    \          a = kth_ancestor(a, depth[a] - depth[b]);\n            if (a == b)\
    \ return a;\n\n            for (int bit = log - 1; bit >= 0; --bit) {\n      \
    \          if (up_at(bit, a) != up_at(bit, b)) {\n                    a = up_at(bit,\
    \ a);\n                    b = up_at(bit, b);\n                }\n           \
    \ }\n            return parent[a];\n        }\n\n        int dist(int a, int b)\
    \ const {\n            int ancestor = lca(a, b);\n            if (ancestor ==\
    \ -1) return -1;\n            return depth[a] + depth[b] - 2 * depth[ancestor];\n\
    \        }\n\n        bool is_ancestor(int ancestor, int v) const {\n        \
    \    return same_component(ancestor, v) && lca(ancestor, v) == ancestor;\n   \
    \     }\n\n        // a -> b \u30D1\u30B9\u4E0A\u3067 a \u3092 0 \u756A\u76EE\u3068\
    \u3059\u308B k \u756A\u76EE\u306E\u9802\u70B9\u3092\u8FD4\u3059\u3002\n      \
    \  int jump(int a, int b, int k) const {\n            int ancestor = lca(a, b);\n\
    \            if (ancestor == -1 || k < 0) return -1;\n\n            int up_length\
    \ = depth[a] - depth[ancestor];\n            int down_length = depth[b] - depth[ancestor];\n\
    \            if (k > up_length + down_length) return -1;\n            if (k <=\
    \ up_length) return kth_ancestor(a, k);\n            return kth_ancestor(b, up_length\
    \ + down_length - k);\n        }\n\n    private:\n        std::vector<int> up;\n\
    \n        void init(int size) {\n            n = size;\n            log = 1;\n\
    \            while ((1LL << log) <= std::max(1, n)) ++log;\n            depth.assign(n,\
    \ 0);\n            parent.assign(n, -1);\n            component.assign(n, -1);\n\
    \            up.assign(log * n, 0);\n        }\n\n        bool contains(int v)\
    \ const { return 0 <= v && v < n; }\n\n        bool same_component(int a, int\
    \ b) const {\n            return contains(a) && contains(b) && component[a] !=\
    \ -1 &&\n                   component[a] == component[b];\n        }\n\n     \
    \   int& up_at(int bit, int v) { return up[bit * n + v]; }\n        int up_at(int\
    \ bit, int v) const { return up[bit * n + v]; }\n\n        void build_component(const\
    \ std::vector<std::vector<int>>& graph,\n                             int root,\
    \ int component_id) {\n            parent[root] = root;\n            depth[root]\
    \ = 0;\n            component[root] = component_id;\n\n            std::vector<int>\
    \ order{root};\n            for (int i = 0; i < static_cast<int>(order.size());\
    \ ++i) {\n                int v = order[i];\n                for (int to : graph[v])\
    \ {\n                    if (parent[to] != -1) continue;\n                   \
    \ parent[to] = v;\n                    depth[to] = depth[v] + 1;\n           \
    \         component[to] = component_id;\n                    order.push_back(to);\n\
    \                }\n            }\n        }\n\n        void build_table() {\n\
    \            for (int v = 0; v < n; ++v) {\n                if (parent[v] != -1)\
    \ up_at(0, v) = parent[v];\n            }\n            for (int bit = 1; bit <\
    \ log; ++bit) {\n                for (int v = 0; v < n; ++v) {\n             \
    \       if (parent[v] != -1) {\n                        up_at(bit, v) = up_at(bit\
    \ - 1, up_at(bit - 1, v));\n                    }\n                }\n       \
    \     }\n        }\n    };\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <vector>\n\nnamespace yesantikiss\
    \ {\n    struct BinaryLiftingLCA {\n        int n = 0;\n        int log = 1;\n\
    \        std::vector<int> depth;\n        std::vector<int> parent;\n        std::vector<int>\
    \ component;\n\n        BinaryLiftingLCA() = default;\n\n        explicit BinaryLiftingLCA(\n\
    \            const std::vector<std::vector<int>>& graph, int root = 0) {\n   \
    \         build(graph, root);\n        }\n\n        void build(const std::vector<std::vector<int>>&\
    \ graph, int root = 0) {\n            init(static_cast<int>(graph.size()));\n\
    \            if (n == 0) return;\n\n            build_component(graph, root, 0);\n\
    \            build_table();\n        }\n\n        void build_forest(const std::vector<std::vector<int>>&\
    \ graph) {\n            init(static_cast<int>(graph.size()));\n\n            int\
    \ component_id = 0;\n            for (int root = 0; root < n; ++root) {\n    \
    \            if (parent[root] == -1) {\n                    build_component(graph,\
    \ root, component_id++);\n                }\n            }\n            build_table();\n\
    \        }\n\n        int kth_ancestor(int v, int k) const {\n            if (!contains(v)\
    \ || k < 0 || parent[v] == -1) return -1;\n            k = std::min(k, depth[v]);\n\
    \            for (int bit = 0; bit < log; ++bit) {\n                if ((k >>\
    \ bit) & 1) v = up_at(bit, v);\n            }\n            return v;\n       \
    \ }\n\n        int lca(int a, int b) const {\n            if (!same_component(a,\
    \ b)) return -1;\n            if (depth[a] < depth[b]) std::swap(a, b);\n\n  \
    \          a = kth_ancestor(a, depth[a] - depth[b]);\n            if (a == b)\
    \ return a;\n\n            for (int bit = log - 1; bit >= 0; --bit) {\n      \
    \          if (up_at(bit, a) != up_at(bit, b)) {\n                    a = up_at(bit,\
    \ a);\n                    b = up_at(bit, b);\n                }\n           \
    \ }\n            return parent[a];\n        }\n\n        int dist(int a, int b)\
    \ const {\n            int ancestor = lca(a, b);\n            if (ancestor ==\
    \ -1) return -1;\n            return depth[a] + depth[b] - 2 * depth[ancestor];\n\
    \        }\n\n        bool is_ancestor(int ancestor, int v) const {\n        \
    \    return same_component(ancestor, v) && lca(ancestor, v) == ancestor;\n   \
    \     }\n\n        // a -> b \u30D1\u30B9\u4E0A\u3067 a \u3092 0 \u756A\u76EE\u3068\
    \u3059\u308B k \u756A\u76EE\u306E\u9802\u70B9\u3092\u8FD4\u3059\u3002\n      \
    \  int jump(int a, int b, int k) const {\n            int ancestor = lca(a, b);\n\
    \            if (ancestor == -1 || k < 0) return -1;\n\n            int up_length\
    \ = depth[a] - depth[ancestor];\n            int down_length = depth[b] - depth[ancestor];\n\
    \            if (k > up_length + down_length) return -1;\n            if (k <=\
    \ up_length) return kth_ancestor(a, k);\n            return kth_ancestor(b, up_length\
    \ + down_length - k);\n        }\n\n    private:\n        std::vector<int> up;\n\
    \n        void init(int size) {\n            n = size;\n            log = 1;\n\
    \            while ((1LL << log) <= std::max(1, n)) ++log;\n            depth.assign(n,\
    \ 0);\n            parent.assign(n, -1);\n            component.assign(n, -1);\n\
    \            up.assign(log * n, 0);\n        }\n\n        bool contains(int v)\
    \ const { return 0 <= v && v < n; }\n\n        bool same_component(int a, int\
    \ b) const {\n            return contains(a) && contains(b) && component[a] !=\
    \ -1 &&\n                   component[a] == component[b];\n        }\n\n     \
    \   int& up_at(int bit, int v) { return up[bit * n + v]; }\n        int up_at(int\
    \ bit, int v) const { return up[bit * n + v]; }\n\n        void build_component(const\
    \ std::vector<std::vector<int>>& graph,\n                             int root,\
    \ int component_id) {\n            parent[root] = root;\n            depth[root]\
    \ = 0;\n            component[root] = component_id;\n\n            std::vector<int>\
    \ order{root};\n            for (int i = 0; i < static_cast<int>(order.size());\
    \ ++i) {\n                int v = order[i];\n                for (int to : graph[v])\
    \ {\n                    if (parent[to] != -1) continue;\n                   \
    \ parent[to] = v;\n                    depth[to] = depth[v] + 1;\n           \
    \         component[to] = component_id;\n                    order.push_back(to);\n\
    \                }\n            }\n        }\n\n        void build_table() {\n\
    \            for (int v = 0; v < n; ++v) {\n                if (parent[v] != -1)\
    \ up_at(0, v) = parent[v];\n            }\n            for (int bit = 1; bit <\
    \ log; ++bit) {\n                for (int v = 0; v < n; ++v) {\n             \
    \       if (parent[v] != -1) {\n                        up_at(bit, v) = up_at(bit\
    \ - 1, up_at(bit - 1, v));\n                    }\n                }\n       \
    \     }\n        }\n    };\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/lca_binary_lifting.hpp
  requiredBy:
  - tests/test.cpp
  - tests/tree_randomized.cpp
  timestamp: '2026-08-25 15:58:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/lca_binary_lifting.test.cpp
  - verify/jump_on_tree.test.cpp
documentation_of: tree/lca_binary_lifting.hpp
layout: document
title: LCA (Binary Lifting)
---

## 概要

ダブリングで最小共通祖先を求めます。LCAに加えて、祖先への移動とパス上の
頂点への移動が必要な場合に向いています。

```cpp
yesantikiss::BinaryLiftingLCA tree(graph, root);
int ancestor = tree.lca(u, v);
int vertex = tree.jump(u, v, k);  // u を0番目とする
```

## API

- `BinaryLiftingLCA(graph, root)`: `root` を根として構築します。
- `build(graph, root)`: 同じインスタンスを再構築します。
- `build_forest(graph)`: 各連結成分の最小頂点を根として森を構築します。
- `kth_ancestor(v, k)`: `v` の `k` 個上を返します。根を越える場合は根を
  返します。
- `lca(u, v)`: 最小共通祖先を返します。
- `dist(u, v)`: `u-v` パスの辺数を返します。
- `is_ancestor(u, v)`: `u` が `v` の祖先か判定します。
- `jump(u, v, k)`: `u` を0番目としたパス上の頂点を返します。範囲外では
  `-1` を返します。

森に対する異なる連結成分間の問い合わせは、整数を返す関数では `-1`、
`is_ancestor` では `false` になります。

## 要件・計算量

入力は無向の木または森で、頂点番号は `0` 以上 `N` 未満とします。構築は
`O(N log N)` 時間・メモリ、各問い合わせは `O(log N)` 時間です。
