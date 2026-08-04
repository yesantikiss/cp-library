---
title: 区間 map
documentation_of: ./interval_map.hpp
---

## 概要

`yesantikiss::IntervalMap<T, V>` は `[L, R)` を値付き半開区間の集合として
管理します。管理区間を常に完全被覆し、隣接する同値区間を自動で併合します。

## API

- `IntervalMap(L, R, init)`: 全区間を値 `init` で初期化します。
- `locate(x)`: `x` を含む区間の iterator を返します。
- `get_val(x)`: 点 `x` の値を返します。
- `assign(l, r, v)`: `[l, r)` を `v` に置き換えます。
- `apply(l, r, f)`: 各交差区間の値を `f` で変換します。`f(v)` と
  `f(l, r, v)` の両形式を利用できます。
- `enumerate_cut(l, r, f)`: `[l, r)` の端で切り揃えて各区間を列挙します。
- `segments_cut(l, r)`: 列挙結果を `std::vector<Node>` で返します。

`assign`、`apply`、`enumerate_cut` には `add(l, r, v)` と `del(l, r, v)` を
受け取る版もあり、区間ごとの外部集計を同期できます。

## 要件・注意

- 構築時に `L < R` が必要です。`locate` と `get_val` は `L <= x < R` に限ります。
- 更新・列挙の区間は `[L, R)` との共通部分へ自動的に切り詰められます。
- `T` は順序付けと区間端の比較、`V` は等値比較に対応する必要があります。
- 更新により iterator が無効になるため、更新後は `locate` などで取り直してください。
- コールバック版の構築時には初期区間への `add` は呼ばれません。外部集計には
  初期区間の寄与をあらかじめ入れてください。
- `enumerate_cut` も内部では一時的に分割・併合するため、コールバックが
  呼ばれることがあります。

## 計算量

現在の区間数を `M`、処理対象の区間数を `K` とすると、代表的な操作は
`O(log M + K log M)` 程度です。保持メモリは `O(M)` です。
