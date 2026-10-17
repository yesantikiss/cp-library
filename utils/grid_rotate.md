---
title: 二次元配列の回転
documentation_of: ./grid_rotate.hpp
---

## 概要

二次元配列を時計回りに 90°・180°・270° 回転した新しい配列を返します。
`std::vector<std::vector<T>>` と `std::vector<std::string>` のどちらにも使えます。

```text
a = abc    rotate90(a) = da    rotate180(a) = fed    rotate270(a) = cf
    def                  eb                   cba                   be
                         fc                                         ad
```

## API

- `rotate90(a)`: 時計回りに 90° 回転します。`H x W` が `W x H` になります。
- `rotate180(a)`: 180° 回転します。
- `rotate270(a)`: 時計回りに 270°（反時計回りに 90°）回転します。
- `rotate(a, k)`: 時計回りに `90k°` 回転します。`k` は負でも構いません。

## 要件・注意

- すべての行の長さが等しい必要があります。
- 元の配列は変更せず、新しい配列を返します。
- 行の型は `Row(n, value)` での構築と添字アクセスができる必要があります。

## 計算量

`O(HW)` です。
