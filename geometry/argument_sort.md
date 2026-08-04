---
title: 偏角ソート
documentation_of: ./argument_sort.hpp
---

## 概要

`yesantikiss::ArgumentLess` は、原点から見た `Point` の偏角を `(-pi, pi]` の
順に並べる比較関数です。

```cpp
std::sort(points.begin(), points.end(), yesantikiss::ArgumentLess{});
```

## 要件・注意

- 偏角が同じ点同士の順序は未規定です。
- 原点 `(0, 0)` の偏角は `0` として扱います。
- 狭義弱順序を保つため比較に `EPS` は使いません。入力値に丸め誤差がある場合、
  幾何判定用の誤差付き順序とは一致しないことがあります。

## 計算量

比較一回は `O(1)`、`N` 点の `std::sort` は `O(N log N)` です。
