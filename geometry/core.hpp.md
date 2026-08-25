---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/argument_sort.hpp
    title: "\u504F\u89D2\u30BD\u30FC\u30C8"
  - icon: ':heavy_check_mark:'
    path: geometry/line.hpp
    title: "\u76F4\u7DDA\u3068\u70B9\u306E\u4F4D\u7F6E\u95A2\u4FC2"
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: "\u4E8C\u6B21\u5143\u306E\u70B9\u30FB\u30D9\u30AF\u30C8\u30EB"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/cgl_1_a.test.cpp
    title: verify/cgl_1_a.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/cgl_1_b.test.cpp
    title: verify/cgl_1_b.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/cgl_1_c.test.cpp
    title: verify/cgl_1_c.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/sort_points_by_argument.test.cpp
    title: verify/sort_points_by_argument.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"geometry/core.hpp\"\n\n#include <cmath>\n\nnamespace yesantikiss\
    \ {\n    using Real = long double;\n\n    inline constexpr Real EPS = 1e-10L;\n\
    \n    inline int sign(Real x) {\n        if (x > EPS) return 1;\n        if (x\
    \ < -EPS) return -1;\n        return 0;\n    }\n\n    inline bool almost_equal(Real\
    \ a, Real b) {\n        return sign(a - b) == 0;\n    }\n}\n"
  code: "#pragma once\n\n#include <cmath>\n\nnamespace yesantikiss {\n    using Real\
    \ = long double;\n\n    inline constexpr Real EPS = 1e-10L;\n\n    inline int\
    \ sign(Real x) {\n        if (x > EPS) return 1;\n        if (x < -EPS) return\
    \ -1;\n        return 0;\n    }\n\n    inline bool almost_equal(Real a, Real b)\
    \ {\n        return sign(a - b) == 0;\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: geometry/core.hpp
  requiredBy:
  - geometry/argument_sort.hpp
  - geometry/point.hpp
  - geometry/line.hpp
  timestamp: '2026-08-25 15:58:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/sort_points_by_argument.test.cpp
  - verify/cgl_1_a.test.cpp
  - verify/cgl_1_c.test.cpp
  - verify/cgl_1_b.test.cpp
documentation_of: geometry/core.hpp
layout: document
title: "\u5E7E\u4F55\u306E\u57FA\u672C\u578B\u3068\u8AA4\u5DEE\u5224\u5B9A"
---

## 概要

二次元幾何ライブラリで共通に使う実数型と誤差付き比較を定義します。

## API

- `Real`: `long double` の別名です。
- `EPS`: 誤差判定の閾値 `1e-10L` です。
- `sign(x)`: `x > EPS` なら `1`、`x < -EPS` なら `-1`、それ以外は `0` を返します。
- `almost_equal(a, b)`: `|a - b| <= EPS` に相当する一致判定です。

## 要件・注意

- `EPS` は絶対誤差として使われます。値のスケールが大きい場合の相対誤差は
  呼び出し側で考慮してください。
- 誤差付き比較は推移律を満たさない場合があるため、`std::sort` の比較関数や
  順序付きコンテナのキー比較には使わないでください。

## 計算量

すべて `O(1)` です。
