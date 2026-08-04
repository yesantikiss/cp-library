---
title: 二次元累積和・二次元いもす法
documentation_of: ./2d_prefixsum.hpp
---

## 概要

`yesantikiss::PS2D<T>` は、点を設定して長方形和を求める二次元累積和と、
長方形加算後のグリッドを求める二次元いもす法を提供します。座標は
0-indexed、長方形は半開区間 `[y1, y2) x [x1, x2)` です。

## API

- `PS2D(H, W)`: `H x W` のグリッドを作ります。
- `set_point(y, x, v)`: 点の値を設定します（SET モード）。
- `add_rect_imos(y1, x1, y2, x2, v)`: 長方形に `v` を加えます
  （IMOS モード）。
- `add_point_imos(y, x, v)`: 一点への加算を登録します。
- `build()`: 完成グリッドと累積和を構築します。
- `at(y, x)`, `operator()(y, x)`, `operator[](y)[x]`: 構築後の点を取得します。
- `sum(y1, x1, y2, x2)`, `sum_all()`: 構築後の和を取得します。
- `clear_all()`: 登録内容を消去して EMPTY モードへ戻します。

## 要件・注意

- `set_point` と `add_rect_imos` は同じ構築サイクル内で併用できません。
- 取得系 API を呼ぶ前に `build()` が必要です。
- 更新を追加した後は、再び `build()` してください。
- `T` は既定構築、加算、減算に対応する必要があります。

## 計算量

`build()` は `O(HW)`、更新登録と構築後の取得は `O(1)`、使用メモリは
`O(HW)` です。
