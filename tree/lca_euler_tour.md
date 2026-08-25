---
title: LCA (Euler Tour + Sparse Table)
documentation_of: ./lca_euler_tour.hpp
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
