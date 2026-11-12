---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/random_binary_search.test.cpp
    title: verify/random_binary_search.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"algo/binary_search.hpp\"\n\nnamespace yesantikiss {\n  \
    \  // (left, right] \u306E\u7BC4\u56F2\u3067 f(x) \u304C true \u306B\u306A\u308B\
    \u6700\u5C0F\u306E x \u3092\u8FD4\u3059\n    // \u5358\u8ABF\u6027: false...false,true...true\n\
    \    // left \u3068 right \u306F\u756A\u5175\u3067\u3001f(left) == false, f(right)\
    \ == true \u3068\u307F\u306A\u3059\n    // (f(left), f(right) \u306F\u8A55\u4FA1\
    \u3057\u306A\u3044\u3002true \u304C\u306A\u3051\u308C\u3070 right \u3092\u8FD4\
    \u3059)\n    template<class F, class T>\n    T binary_search_min_left(T left,\
    \ T right, F f){\n        while (right - left > 1){\n            T mid = left\
    \ + (right - left) / 2;\n            if(f(mid)) right = mid;\n            else\
    \ left = mid;\n        }\n        return right;\n    }\n\n    // [left, right)\
    \ \u306E\u7BC4\u56F2\u3067 f(x) \u304C true \u306B\u306A\u308B\u6700\u5927\u306E\
    \ x \u3092\u8FD4\u3059\n    // \u5358\u8ABF\u6027: true...true,false...false\n\
    \    // left \u3068 right \u306F\u756A\u5175\u3067\u3001f(left) == true, f(right)\
    \ == false \u3068\u307F\u306A\u3059\n    // (f(left), f(right) \u306F\u8A55\u4FA1\
    \u3057\u306A\u3044\u3002true \u304C\u306A\u3051\u308C\u3070 left \u3092\u8FD4\u3059\
    )\n    template<class F, class T>\n    T binary_search_max_right(T left, T right,\
    \ F f){\n        while (right - left > 1){\n            T mid = left + (right\
    \ - left) / 2;\n            if(f(mid)) left = mid;\n            else right = mid;\n\
    \        }\n        return left;\n    }\n}\n"
  code: "#pragma once\n\nnamespace yesantikiss {\n    // (left, right] \u306E\u7BC4\
    \u56F2\u3067 f(x) \u304C true \u306B\u306A\u308B\u6700\u5C0F\u306E x \u3092\u8FD4\
    \u3059\n    // \u5358\u8ABF\u6027: false...false,true...true\n    // left \u3068\
    \ right \u306F\u756A\u5175\u3067\u3001f(left) == false, f(right) == true \u3068\
    \u307F\u306A\u3059\n    // (f(left), f(right) \u306F\u8A55\u4FA1\u3057\u306A\u3044\
    \u3002true \u304C\u306A\u3051\u308C\u3070 right \u3092\u8FD4\u3059)\n    template<class\
    \ F, class T>\n    T binary_search_min_left(T left, T right, F f){\n        while\
    \ (right - left > 1){\n            T mid = left + (right - left) / 2;\n      \
    \      if(f(mid)) right = mid;\n            else left = mid;\n        }\n    \
    \    return right;\n    }\n\n    // [left, right) \u306E\u7BC4\u56F2\u3067 f(x)\
    \ \u304C true \u306B\u306A\u308B\u6700\u5927\u306E x \u3092\u8FD4\u3059\n    //\
    \ \u5358\u8ABF\u6027: true...true,false...false\n    // left \u3068 right \u306F\
    \u756A\u5175\u3067\u3001f(left) == true, f(right) == false \u3068\u307F\u306A\u3059\
    \n    // (f(left), f(right) \u306F\u8A55\u4FA1\u3057\u306A\u3044\u3002true \u304C\
    \u306A\u3051\u308C\u3070 left \u3092\u8FD4\u3059)\n    template<class F, class\
    \ T>\n    T binary_search_max_right(T left, T right, F f){\n        while (right\
    \ - left > 1){\n            T mid = left + (right - left) / 2;\n            if(f(mid))\
    \ left = mid;\n            else right = mid;\n        }\n        return left;\n\
    \    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/binary_search.hpp
  requiredBy: []
  timestamp: '2026-11-12 13:12:40+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/random_binary_search.test.cpp
documentation_of: algo/binary_search.hpp
layout: document
title: "\u4E8C\u5206\u63A2\u7D22"
---

## 概要

整数区間上の単調な述語に対して、境界を二分探索します。

## API

- `binary_search_min_left(left, right, f)`: `false ... false, true ... true`
  となる述語について、`f(x)` が真となる最小の `x` を返します。
- `binary_search_max_right(left, right, f)`: `true ... true, false ... false`
  となる述語について、`f(x)` が真となる最大の `x` を返します。

## 要件・注意

- `binary_search_min_left` では `f(left) == false`、`f(right) == true` を満たす
  番兵を渡してください。
- `binary_search_max_right` では `f(left) == true`、`f(right) == false` を満たす
  番兵を渡してください。
- `T` は差・加算・`2` による除算と比較ができる整数型を想定しています。

## 計算量

述語 `f` の評価を `O(F)` とすると `O(F log(right - left))` です。
