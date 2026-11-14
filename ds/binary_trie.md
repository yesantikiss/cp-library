---
title: Binary Trie
documentation_of: ./binary_trie.hpp
---

## 概要

`yesantikiss::BinaryTrie<B>` は、`B` ビット非負整数の多重集合です。
全要素に XOR を適用したとみなした順序統計も取得できます。

## API

- `insert(x)`: `x` を一つ追加します。
- `erase(x)`: `x` を一つ削除し、存在したかを返します。
- `count(v, T)`, `contains(v, T)`: 多重集合 `{x xor T}` に含まれる
  `v` の個数・有無を返します。`T` の既定値は `0` です。
- `kth(k, T)`: `{x xor T}` を昇順に並べた 0-indexed の `k` 番目を返します。
- `count_less(r, T)`: `{x xor T}` のうち `r` 未満の要素数を返します。
  `r >= 2^B` のときは `size()` を返します。
- `count_range(l, r, T)`: `{x xor T}` のうち半開区間 `[l, r)` に入る要素数を
  返します。`l >= r` のときは `0` です。
- `min_element(T)`, `max_element(T)`: 変換後の最小値・最大値を返します。
- `size()`, `empty()`: 重複を含む要素数・空判定です。

## 要件・注意

- `1 <= B <= 63` が必要です。
- `count_less`, `count_range` の `l`, `r` は `2^B` 以上でも構いません。
- 格納する値と XOR マスクは `B` ビット以内、すなわち
  `0 <= x, T < 2^B` としてください。上位ビットは区別されません。
- `kth` は `0 <= k < size()`、最小値・最大値の取得は非空の場合に限ります。
- 削除後も内部ノードは解放されません。

## 計算量

各更新・検索・順序統計は `O(B)`、メモリは追加した相異なるビット列の
Trie ノード数に比例します。
