---
title: 直線と点の位置関係
documentation_of: ./line.hpp
---

## 概要

`yesantikiss::Line` は異なる二点 `a`, `b` を通る直線を表します。点の射影、
鏡映、有向直線に対する位置分類を提供します。

## API

- `projection(line, point)`: 点から直線への正射影を返します。
- `reflection(line, point)`: 直線に関する点の鏡映を返します。
- `point_position(a, b, point)`, `point_position(line, point)`: 点の位置を
  `PointPosition` で返します。

`PointPosition` の値は次のとおりです。

- `counter_clockwise`: 有向直線 `a -> b` の左側
- `clockwise`: 右側
- `online_back`: 同一直線上で `a` より後方
- `online_front`: 同一直線上で `b` より前方
- `on_segment`: 線分 `ab` 上

## 要件・注意

- `projection` と `reflection` では `line.a != line.b`、より正確には
  `norm_squared(line.b - line.a) > 0` が必要です。
- 位置分類には `EPS` を用います。入力のスケールに応じた誤差を考慮してください。

## 計算量

すべて `O(1)` です。
