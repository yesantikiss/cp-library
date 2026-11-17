---
title: ロールバック付き Union-Find
documentation_of: ./rollback_dsu.hpp
---

## 概要

`yesantikiss::rollback_dsu` は、直前の `merge` を取り消せる Union-Find です。
経路圧縮をせず union by size だけで併合するので、`merge` を新しい順に
`O(1)` で取り消せます。オフラインの動的連結性や、DFS しながら状態を巻き戻す
処理に使えます。

## API

- `rollback_dsu(n)`: `n` 頂点で初期化します。
- `merge(a, b)`: `a` と `b` の成分を併合し、併合後の leader を返します。
- `undo()`: 直前の `merge` を 1 回取り消します。
- `snapshot()`: 取り消されずに残っている `merge` の回数を返します。
- `rollback(state)`: `snapshot()` が `state` を返した時点まで戻します。
- `count()`: 連結成分の個数を返します。
- `leader(a)`, `same(a, b)`, `size(a)`, `groups()`: 通常の DSU 操作です。

```cpp
yesantikiss::rollback_dsu dsu(4);
dsu.merge(0, 1);
int state = dsu.snapshot();
dsu.merge(1, 2);
dsu.merge(0, 2);      // 同じ成分どうしでも履歴を積む
dsu.undo();           // merge(0, 2) を取り消す
dsu.rollback(state);  // merge(1, 2) も取り消す
```

## 要件・注意

- 頂点番号は `0 <= v < n` です。
- すでに同じ成分にある頂点どうしの `merge` も履歴を 1 件積みます。そのため
  `merge` 1 回と `undo` 1 回が必ず対応します。
- `undo()` は取り消せる `merge` が残っているときだけ呼んでください。
- `rollback(state)` の `state` は `0 <= state <= snapshot()` です。いったん
  `state` より前まで戻したあとに再び `merge` した場合、古い `state` は別の
  状態を指すので注意してください。
- `leader` などの参照系の関数は状態を書き換えず、`const` で呼べます。

## 計算量

`leader(a)`, `same(a, b)`, `size(a)`, `merge(a, b)` は `O(log N)`、`undo()` と
`count()`, `snapshot()` は `O(1)` です。`rollback(state)` は取り消す `merge`
1 回あたり `O(1)` です。`groups()` は各頂点の leader を一時配列にメモしながら
求めるので `O(N)` で、本体の配列は書き換えません。メモリは `O(N + M)`
（`M` は履歴の長さ）です。
