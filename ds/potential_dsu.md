---
title: ポテンシャル付き Union-Find
documentation_of: ./potential_dsu.hpp
---

## 概要

`yesantikiss::potential_dsu<T>` は、連結成分と頂点間のポテンシャル差を管理する
Union-Find です。

## API

- `potential_dsu(n)`, `init(n)`: `n` 頂点で初期化します。
- `merge(a, b, w)`: 制約 `pot[b] - pot[a] = w` として成分を併合し、leader を返します。
- `diff(a, b)`: `pot[b] - pot[a]` を返します。
- `potential(a)`: `pot[a] - pot[leader(a)]` を返します。
- `leader(a)`, `same(a, b)`, `size(a)`, `groups()`: 通常の DSU 操作です。

## 要件・注意

- 頂点番号は `0 <= v < n` です。
- `diff(a, b)` は `same(a, b)` が真の場合だけ呼んでください。
- すでに同じ成分にある頂点へ `merge` しても、渡した制約の整合性は検査しません。
  必要なら事前に `diff(a, b) == w` を確認してください。
- `T` は零初期化、加算、減算、単項マイナスに対応する必要があります。

## 計算量

`groups()` 以外は償却 `O(alpha(N))`、`groups()` は `O(N)` です。メモリは
`O(N)` です。
