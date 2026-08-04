---
title: Cartesian Tree
documentation_of: ./cartesian_tree.hpp
---

## 概要

配列から `yesantikiss::CartesianTree<T, Compare>` を構築します。中順巡回が
元の配列順になり、比較関数によるヒープ条件を満たす二分木です。

## API

- `CartesianTree(a, comp)`: 配列 `a` から木を構築します。
- `root`: 根の添字です。空配列では `-1` です。
- `par[i]`, `left[i]`, `right[i]`: 親・左の子・右の子の添字です。
  存在しない場合は `-1` です。

既定の `std::less<T>` では min Cartesian Tree、`std::greater<T>` では
max Cartesian Tree になります。

## 要件・注意

- `Compare` は狭義弱順序を満たす必要があります。
- 同値な要素はスタックから取り除かれないため、同値要素間では先に現れた
  要素が上側になります。
- 頂点番号は元配列の添字と同じです。

## 計算量

構築は `O(N)` 時間、`O(N)` メモリです。
