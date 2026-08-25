---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/core.hpp
    title: "\u5E7E\u4F55\u306E\u57FA\u672C\u578B\u3068\u8AA4\u5DEE\u5224\u5B9A"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/argument_sort.hpp
    title: "\u504F\u89D2\u30BD\u30FC\u30C8"
  - icon: ':heavy_check_mark:'
    path: geometry/line.hpp
    title: "\u76F4\u7DDA\u3068\u70B9\u306E\u4F4D\u7F6E\u95A2\u4FC2"
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
  bundledCode: "#line 2 \"geometry/point.hpp\"\n\n#include <istream>\n#include <ostream>\n\
    \n#line 2 \"geometry/core.hpp\"\n\n#include <cmath>\n\nnamespace yesantikiss {\n\
    \    using Real = long double;\n\n    inline constexpr Real EPS = 1e-10L;\n\n\
    \    inline int sign(Real x) {\n        if (x > EPS) return 1;\n        if (x\
    \ < -EPS) return -1;\n        return 0;\n    }\n\n    inline bool almost_equal(Real\
    \ a, Real b) {\n        return sign(a - b) == 0;\n    }\n}\n#line 7 \"geometry/point.hpp\"\
    \n\nnamespace yesantikiss {\n    struct Point {\n        Real x = 0;\n       \
    \ Real y = 0;\n\n        Point() = default;\n        Point(Real x, Real y) : x(x),\
    \ y(y) {}\n\n        Point& operator+=(const Point& other) {\n            x +=\
    \ other.x;\n            y += other.y;\n            return *this;\n        }\n\n\
    \        Point& operator-=(const Point& other) {\n            x -= other.x;\n\
    \            y -= other.y;\n            return *this;\n        }\n\n        Point&\
    \ operator*=(Real scalar) {\n            x *= scalar;\n            y *= scalar;\n\
    \            return *this;\n        }\n\n        Point& operator/=(Real scalar)\
    \ {\n            x /= scalar;\n            y /= scalar;\n            return *this;\n\
    \        }\n\n        Point operator+() const {\n            return *this;\n \
    \       }\n\n        Point operator-() const {\n            return {-x, -y};\n\
    \        }\n\n        friend Point operator+(Point lhs, const Point& rhs) {\n\
    \            lhs += rhs;\n            return lhs;\n        }\n\n        friend\
    \ Point operator-(Point lhs, const Point& rhs) {\n            lhs -= rhs;\n  \
    \          return lhs;\n        }\n\n        friend Point operator*(Point point,\
    \ Real scalar) {\n            point *= scalar;\n            return point;\n  \
    \      }\n\n        friend Point operator*(Real scalar, Point point) {\n     \
    \       point *= scalar;\n            return point;\n        }\n\n        friend\
    \ Point operator/(Point point, Real scalar) {\n            point /= scalar;\n\
    \            return point;\n        }\n\n        friend bool operator==(const\
    \ Point& lhs, const Point& rhs) {\n            return lhs.x == rhs.x && lhs.y\
    \ == rhs.y;\n        }\n\n        friend bool operator!=(const Point& lhs, const\
    \ Point& rhs) {\n            return !(lhs == rhs);\n        }\n\n        friend\
    \ std::istream& operator>>(std::istream& input, Point& point) {\n            return\
    \ input >> point.x >> point.y;\n        }\n\n        friend std::ostream& operator<<(std::ostream&\
    \ output, const Point& point) {\n            return output << point.x << ' ' <<\
    \ point.y;\n        }\n    };\n\n    inline Real dot(const Point& a, const Point&\
    \ b) {\n        return a.x * b.x + a.y * b.y;\n    }\n\n    inline Real cross(const\
    \ Point& a, const Point& b) {\n        return a.x * b.y - a.y * b.x;\n    }\n\n\
    \    inline Real norm_squared(const Point& point) {\n        return dot(point,\
    \ point);\n    }\n\n    inline Real norm(const Point& point) {\n        return\
    \ std::sqrt(norm_squared(point));\n    }\n\n    inline Real distance(const Point&\
    \ a, const Point& b) {\n        return norm(a - b);\n    }\n\n    inline bool\
    \ almost_equal(const Point& a, const Point& b) {\n        return almost_equal(a.x,\
    \ b.x) && almost_equal(a.y, b.y);\n    }\n}\n"
  code: "#pragma once\n\n#include <istream>\n#include <ostream>\n\n#include \"geometry/core.hpp\"\
    \n\nnamespace yesantikiss {\n    struct Point {\n        Real x = 0;\n       \
    \ Real y = 0;\n\n        Point() = default;\n        Point(Real x, Real y) : x(x),\
    \ y(y) {}\n\n        Point& operator+=(const Point& other) {\n            x +=\
    \ other.x;\n            y += other.y;\n            return *this;\n        }\n\n\
    \        Point& operator-=(const Point& other) {\n            x -= other.x;\n\
    \            y -= other.y;\n            return *this;\n        }\n\n        Point&\
    \ operator*=(Real scalar) {\n            x *= scalar;\n            y *= scalar;\n\
    \            return *this;\n        }\n\n        Point& operator/=(Real scalar)\
    \ {\n            x /= scalar;\n            y /= scalar;\n            return *this;\n\
    \        }\n\n        Point operator+() const {\n            return *this;\n \
    \       }\n\n        Point operator-() const {\n            return {-x, -y};\n\
    \        }\n\n        friend Point operator+(Point lhs, const Point& rhs) {\n\
    \            lhs += rhs;\n            return lhs;\n        }\n\n        friend\
    \ Point operator-(Point lhs, const Point& rhs) {\n            lhs -= rhs;\n  \
    \          return lhs;\n        }\n\n        friend Point operator*(Point point,\
    \ Real scalar) {\n            point *= scalar;\n            return point;\n  \
    \      }\n\n        friend Point operator*(Real scalar, Point point) {\n     \
    \       point *= scalar;\n            return point;\n        }\n\n        friend\
    \ Point operator/(Point point, Real scalar) {\n            point /= scalar;\n\
    \            return point;\n        }\n\n        friend bool operator==(const\
    \ Point& lhs, const Point& rhs) {\n            return lhs.x == rhs.x && lhs.y\
    \ == rhs.y;\n        }\n\n        friend bool operator!=(const Point& lhs, const\
    \ Point& rhs) {\n            return !(lhs == rhs);\n        }\n\n        friend\
    \ std::istream& operator>>(std::istream& input, Point& point) {\n            return\
    \ input >> point.x >> point.y;\n        }\n\n        friend std::ostream& operator<<(std::ostream&\
    \ output, const Point& point) {\n            return output << point.x << ' ' <<\
    \ point.y;\n        }\n    };\n\n    inline Real dot(const Point& a, const Point&\
    \ b) {\n        return a.x * b.x + a.y * b.y;\n    }\n\n    inline Real cross(const\
    \ Point& a, const Point& b) {\n        return a.x * b.y - a.y * b.x;\n    }\n\n\
    \    inline Real norm_squared(const Point& point) {\n        return dot(point,\
    \ point);\n    }\n\n    inline Real norm(const Point& point) {\n        return\
    \ std::sqrt(norm_squared(point));\n    }\n\n    inline Real distance(const Point&\
    \ a, const Point& b) {\n        return norm(a - b);\n    }\n\n    inline bool\
    \ almost_equal(const Point& a, const Point& b) {\n        return almost_equal(a.x,\
    \ b.x) && almost_equal(a.y, b.y);\n    }\n}\n"
  dependsOn:
  - geometry/core.hpp
  isVerificationFile: false
  path: geometry/point.hpp
  requiredBy:
  - geometry/argument_sort.hpp
  - geometry/line.hpp
  timestamp: '2026-08-25 15:58:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/sort_points_by_argument.test.cpp
  - verify/cgl_1_a.test.cpp
  - verify/cgl_1_c.test.cpp
  - verify/cgl_1_b.test.cpp
documentation_of: geometry/point.hpp
layout: document
title: "\u4E8C\u6B21\u5143\u306E\u70B9\u30FB\u30D9\u30AF\u30C8\u30EB"
---

## 概要

`yesantikiss::Point` は `Real` 座標を持つ二次元の点・ベクトルです。

## API

- `+`, `-`, `*`, `/`: ベクトルの加減算とスカラー倍・除算です。
- `dot(a, b)`, `cross(a, b)`: 内積・外積を返します。
- `norm_squared(p)`, `norm(p)`: ノルムの二乗・ノルムを返します。
- `distance(a, b)`: 二点間距離を返します。
- `almost_equal(a, b)`: 各座標を `EPS` 込みで比較します。
- 入出力は `x y` の順です。

## 要件・注意

- `operator==` は座標の厳密比較です。幾何的な一致には `almost_equal` を
  使ってください。
- 除算ではスカラーが `0` でないことを呼び出し側で保証してください。
- 浮動小数点演算の丸め誤差が発生します。

## 計算量

すべて `O(1)` です。
