---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: tree/centered_tree.hpp
    title: "\u6728\u306E\u4E2D\u5FC3\u3067\u6839\u4ED8\u3051"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/random_centered_tree.test.cpp
    title: verify/random_centered_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"tree/tree_diameter.hpp\"\n\n#include <algorithm>\n#include\
    \ <vector>\n\nnamespace yesantikiss {\n    struct TreeDiameter {\n        int\
    \ length = 0;\n        std::vector<int> path;\n\n        TreeDiameter() = default;\n\
    \n        explicit TreeDiameter(const std::vector<std::vector<int>>& graph) {\n\
    \            build(graph);\n        }\n\n        void build(const std::vector<std::vector<int>>&\
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
    \    };\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <vector>\n\nnamespace yesantikiss\
    \ {\n    struct TreeDiameter {\n        int length = 0;\n        std::vector<int>\
    \ path;\n\n        TreeDiameter() = default;\n\n        explicit TreeDiameter(const\
    \ std::vector<std::vector<int>>& graph) {\n            build(graph);\n       \
    \ }\n\n        void build(const std::vector<std::vector<int>>& graph) {\n    \
    \        length = 0;\n            path.clear();\n            int n = static_cast<int>(graph.size());\n\
    \            if (n == 0) return;\n\n            std::vector<int> dist, parent;\n\
    \            int a = farthest(graph, 0, dist, parent);\n            int b = farthest(graph,\
    \ a, dist, parent);\n\n            length = dist[b];\n            for (int v =\
    \ b; v != -1; v = parent[v]) path.push_back(v);\n            std::reverse(path.begin(),\
    \ path.end());\n        }\n\n    private:\n        static int farthest(const std::vector<std::vector<int>>&\
    \ graph,\n                            int source, std::vector<int>& dist,\n  \
    \                          std::vector<int>& parent) {\n            int n = static_cast<int>(graph.size());\n\
    \            dist.assign(n, -1);\n            parent.assign(n, -1);\n        \
    \    std::vector<int> queue{source};\n            dist[source] = 0;\n        \
    \    for (int i = 0; i < static_cast<int>(queue.size()); ++i) {\n            \
    \    int v = queue[i];\n                for (int to : graph[v]) {\n          \
    \          if (dist[to] != -1) continue;\n                    dist[to] = dist[v]\
    \ + 1;\n                    parent[to] = v;\n                    queue.push_back(to);\n\
    \                }\n            }\n            return queue.back();\n        }\n\
    \    };\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/tree_diameter.hpp
  requiredBy:
  - tree/centered_tree.hpp
  timestamp: '2026-11-12 13:13:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/random_centered_tree.test.cpp
documentation_of: tree/tree_diameter.hpp
layout: document
title: "\u6728\u306E\u76F4\u5F84"
---

## 概要

重みなしの木の直径と、直径パスを求めます。

```cpp
yesantikiss::TreeDiameter diameter(graph);
int d = diameter.length;               // 直径 (辺数)
const std::vector<int>& path = diameter.path;  // path[0..d]
```

## API

- `TreeDiameter(graph)`: 構築します。
- `build(graph)`: 同じインスタンスを再構築します。
- `length`: 直径の辺数です。
- `path`: 直径の一方の端点からもう一方の端点までの頂点列で、長さは
  `length + 1` です。

## 要件・計算量

入力は重みなしの無向の木で、頂点番号は `0` 以上 `N` 未満とします。
`N = 0` のときは `length = 0` で `path` は空です。BFS を2回行うので
`O(N)` 時間です。
