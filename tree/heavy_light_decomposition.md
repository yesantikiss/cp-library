---
title: Heavy-Light Decomposition
documentation_of: ./heavy_light_decomposition.hpp
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
