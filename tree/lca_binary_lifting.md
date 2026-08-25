---
title: LCA (Binary Lifting)
documentation_of: ./lca_binary_lifting.hpp
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
