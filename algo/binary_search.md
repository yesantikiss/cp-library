---
title: 二分探索
documentation_of: ./binary_search.hpp
---

## 概要

整数区間上の単調な述語に対して、境界を二分探索します。

## API

- `binary_search_min_left(left, right, f)`: `false ... false, true ... true`
  となる述語について、`f(x)` が真となる最小の `x` を返します。
- `binary_search_max_right(left, right, f)`: `true ... true, false ... false`
  となる述語について、`f(x)` が真となる最大の `x` を返します。

## 要件・注意

- `binary_search_min_left` では `left`, `right` を `f(left) == false`、
  `f(right) == true` とみなす番兵として扱い、`(left, right]` から探します。
  `f(left)`, `f(right)` は評価しません。`f(x)` が真となる `x` がなければ
  `right` を返します。
- `binary_search_max_right` では `left`, `right` を `f(left) == true`、
  `f(right) == false` とみなす番兵として扱い、`[left, right)` から探します。
  `f(left)`, `f(right)` は評価しません。`f(x)` が真となる `x` がなければ
  `left` を返します。
- `T` は差・加算・`2` による除算と比較ができる整数型を想定しています。

## 計算量

述語 `f` の評価を `O(F)` とすると `O(F log(right - left))` です。
