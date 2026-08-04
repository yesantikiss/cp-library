---
title: 永続セグメント木
documentation_of: ./persistent_segtree.hpp
---

## 概要

`yesantikiss::persistent_segtree<S, op, e>` は、一点更新のたびに新しい版を作る
完全永続セグメント木です。古い版への参照と、古い版からの分岐更新ができます。

## API

- `persistent_segtree(a)`: 配列 `a` を version `0` として構築します。
- `persistent_segtree(n)`: `e()` が `n` 個並んだ version `0` を構築します。
- `set(p, x, ver)`: `ver` の点 `p` を更新した版を末尾に追加し、版番号を返します。
- `get(p, ver)`, `prod(l, r, ver)`, `all_prod(ver)`: 指定版を参照します。
- `versions()`, `latest_version()`: 版数・最新版の番号を返します。

`ver = -1` は最新版を表します。

## 要件・注意

- `op` は結合的で、`e()` はその単位元である必要があります。
- `0 <= p < n`、区間は 0-indexed の `0 <= l <= r <= n` です。
- 版番号は `0 <= ver < versions()` または `-1` を指定してください。
- 空配列でも version `0` は存在し、区間積と全体積は `e()` です。点操作は
  できません。

## 計算量

初期構築は `O(N)` 時間・メモリ、一点更新と区間積は `O(log N)` です。
一点更新ごとに `O(log N)` 個のノードを追加します。
