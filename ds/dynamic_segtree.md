---
title: 動的セグメント木
documentation_of: ./dynamic_segtree.hpp
---

## 概要

`yesantikiss::dynamic_segtree<S, op, e>` は、更新された点へ至る経路だけを
生成する動的（implicit）セグメント木です。巨大で疎な添字範囲 `[0, n)` を
扱えます。

## API

- `dynamic_segtree(n)`, `init(n)`: 長さ `n` で初期化します。全要素は `e()` です。
- `reserve_nodes(m)`: 内部ノード領域を予約します。
- `set(p, x)`: 点 `p` を `x` に置き換えます。
- `apply_point(p, x)`: 点 `p` を `op(get(p), x)` に更新します。
- `get(p)`, `prod(l, r)`, `all_prod()`: 点、半開区間、全体の積を返します。
- `max_right(l, f)`, `min_left(r, f)`: ACL の `segtree` と同様の境界探索です。

## 要件・注意

- `op` は結合的で、`e()` はその単位元である必要があります。
- `0 <= p < n`、区間は `0 <= l <= r <= n` を満たしてください。
- 境界探索では `f(e()) == true` が必要です。また、正しい境界を得るには
  `f` が探索方向に対して単調で、副作用を持たない必要があります。
- 未更新の点は `e()` として扱われます。

## 計算量

点操作・区間積・境界探索は `O(log n)` です。点更新一回につき最大
`O(log n)` 個のノードを追加します。
