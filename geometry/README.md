# Geometry

[トップへ戻る](../README.md)

二次元幾何を扱うライブラリです。座標計算には
`yesantikiss::Real` (`long double`) を使用します。

## `core.hpp`

- `EPS`: 幾何判定に使用する許容誤差
- `sign(x)`: `x` を誤差込みで `-1`, `0`, `1` に分類
- `almost_equal(a, b)`: 誤差込みの一致判定

## `point.hpp`

二次元の点・ベクトルを表す `yesantikiss::Point` です。

- 四則演算、入力、出力
- `dot(a, b)`: 内積
- `cross(a, b)`: 外積
- `norm_squared(p)`, `norm(p)`: ノルムの二乗、ノルム
- `distance(a, b)`: 二点間距離

`Point::operator==` は厳密比較です。幾何的な一致判定には
`almost_equal(a, b)` を使用します。

## `line.hpp`

異なる二点を通る直線 `yesantikiss::Line` を扱います。

- `projection(line, point)`: 点の直線への正射影
- `reflection(line, point)`: 直線に関する点の鏡映
- `point_position(a, b, point)`: 有向直線 `a -> b` に対する点の位置

`point_position` は `PointPosition` を返します。

- `counter_clockwise`: 左側
- `clockwise`: 右側
- `online_back`: 同一直線上で `a` より後方
- `online_front`: 同一直線上で `b` より前方
- `on_segment`: 線分 `ab` 上

## `argument_sort.hpp`

`ArgumentLess` は原点から見た偏角を `(-π, π]` の順に比較する
`Point` 用コンパレータです。

```cpp
std::sort(points.begin(), points.end(), ArgumentLess{});
```

偏角が同じ点同士の順序は未規定です。原点 `(0, 0)` の偏角は `0` として
扱います。ソート条件の狭義弱順序を保つため、比較には `EPS` を使用しません。
