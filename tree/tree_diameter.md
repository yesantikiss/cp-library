---
title: 木の直径
documentation_of: ./tree_diameter.hpp
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
