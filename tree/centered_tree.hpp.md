---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/tree_diameter.hpp
    title: "\u6728\u306E\u76F4\u5F84"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/random_centered_tree.test.cpp
    title: verify/random_centered_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"tree/centered_tree.hpp\"\n\n#include <initializer_list>\n\
    #include <vector>\n\n#line 2 \"tree/tree_diameter.hpp\"\n\n#include <algorithm>\n\
    #line 5 \"tree/tree_diameter.hpp\"\n\nnamespace yesantikiss {\n    struct TreeDiameter\
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
    \ + diameter) / 2; }\n    };\n}\n"
  code: "#pragma once\n\n#include <initializer_list>\n#include <vector>\n\n#include\
    \ \"tree/tree_diameter.hpp\"\n\nnamespace yesantikiss {\n    // \u6728\u3092\u4E2D\
    \u5FC3\u3067\u6839\u4ED8\u3051\u3059\u308B\u3002\u4E2D\u5FC3\u304C2\u70B9\u306A\
    \u3089\u3001\u305D\u306E\u9593\u306B\u4EEE\u60F3\u9802\u70B9 n \u3092\u7F6E\u3044\
    \u3066\u6839\u306B\u3059\u308B\u3002\n    // dist2[x] \u306F\u4E2D\u5FC3\u70B9\
    \u304B\u3089\u306E\u8DDD\u96E2\u306E2\u500D\u3067\u3001\u9802\u70B9\u500D\u3057\
    \u305F\u6728\u3067\u306E\u6DF1\u3055\u3068\u4E00\u81F4\u3059\u308B\u3002\n   \
    \ // \u4E2D\u5FC3\u306E2\u70B9\u306F\u5143\u306E\u30B0\u30E9\u30D5\u3067\u96A3\
    \u308A\u5408\u3046\u304C\u3001\u6839\u4ED8\u304D\u6728\u3067\u306F\u89AA\u5B50\
    \u3067\u306F\u306A\u3044\u3002\n    // \u5B50\u306F graph[v] \u3067\u306F\u306A\
    \u304F children[v] \u3067\u305F\u3069\u308B\u3053\u3068\u3002\n    struct CenteredTree\
    \ {\n        int n = 0;\n        int root = -1;\n        int diameter = 0;\n \
    \       std::vector<int> parent;\n        std::vector<int> order;\n        std::vector<int>\
    \ dist2;\n        std::vector<std::vector<int>> children;\n\n        CenteredTree()\
    \ = default;\n\n        explicit CenteredTree(const std::vector<std::vector<int>>&\
    \ graph) {\n            build(graph);\n        }\n\n        void build(const std::vector<std::vector<int>>&\
    \ graph) {\n            n = static_cast<int>(graph.size());\n            root\
    \ = -1;\n            diameter = 0;\n            parent.assign(n + 1, -1);\n  \
    \          dist2.assign(n + 1, -1);\n            children.assign(n + 1, std::vector<int>());\n\
    \            order.clear();\n            if (n == 0) return;\n\n            TreeDiameter\
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
    \ + diameter) / 2; }\n    };\n}\n"
  dependsOn:
  - tree/tree_diameter.hpp
  isVerificationFile: false
  path: tree/centered_tree.hpp
  requiredBy: []
  timestamp: '2026-11-14 15:53:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/random_centered_tree.test.cpp
documentation_of: tree/centered_tree.hpp
layout: document
title: "\u6728\u306E\u4E2D\u5FC3\u3067\u6839\u4ED8\u3051"
---

## 概要

木を中心で根付けします。中心が2点 `u, v` のときは、その間に仮想頂点 `N`
を置いて根にします。`dist2[x]` は中心点からの距離の2倍で、各辺に頂点を
はさんだ木で中心から測った深さと一致します。頂点を倍にしなくても、
中心が1点か2点かで場合分けせずに木DPが書けます。

```cpp
// 直径の本数 (距離が直径に等しい頂点対の数) を数える例
yesantikiss::CenteredTree tree(graph);
std::vector<long long> endpoints(tree.n + 1);
long long answer = 0;
// 葉から根へ
for (int i = static_cast<int>(tree.order.size()) - 1; i >= 0; --i) {
    int v = tree.order[i];
    if (tree.is_diameter_endpoint(v)) endpoints[v] = 1;
    for (int to : tree.children[v]) {
        // 根では、別々の子の部分木にある端点どうしが直径になる
        if (v == tree.root) answer += endpoints[v] * endpoints[to];
        endpoints[v] += endpoints[to];
    }
}
```

中心が2点 `u, v` のとき、`u` と `v` は元の `graph` では隣り合っていますが、
根付き木ではどちらも仮想頂点 `N` の子です。`graph[v]` を
`to != parent[v]` で絞ると `u` の子に `v` が入ってしまうので、子は必ず
`children[v]` でたどってください。

## API

- `CenteredTree(graph)`: 構築します。
- `build(graph)`: 同じインスタンスを再構築します。
- `n`: 元の木の頂点数です。仮想頂点の番号は `n` です。
- `root`: 根です。中心が1点ならその頂点、2点なら `n` です。
- `diameter`: 直径の辺数です。
- `parent[v]`: 根付き木での親です。`parent[root] = -1` です。
- `order`: 根からの BFS 順です。中心が1点のときは `n` を含みません。
- `children[v]`: 根付き木での子です。仮想頂点が根のとき、
  `children[n]` は中心の2点です。
- `dist2[v]`: 中心点からの距離の2倍です。根では `0`、使わない仮想頂点では
  `-1` です。
- `is_virtual(v)`: `v` が仮想頂点か判定します。
- `has_virtual_root()`: 中心が2点 (直径が奇数) か判定します。
- `radius()`: 半径 `(diameter + 1) / 2` を返します。
- `is_diameter_endpoint(v)`: `v` がある直径の端点か判定します。
  `dist2[v] == diameter` と同じです。
- `eccentricity(v)`: 元の木で `v` から最も遠い頂点までの距離
  `(dist2[v] + diameter) / 2` を返します。

`parent`, `dist2`, `children` のサイズは常に `n + 1` です。

## 要件・計算量

入力は重みなしの無向の木で、頂点番号は `0` 以上 `N` 未満とします。
`N = 0` のときは `root = -1` で `order` は空です。BFS を3回行うので
`O(N)` 時間です。
