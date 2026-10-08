---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: tests/test.cpp
    title: tests/test.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/static_range_count_distinct.test.cpp
    title: verify/static_range_count_distinct.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"ds/compressor.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <vector>\n\nnamespace yesantikiss {\n    template <class T>\n    struct\
    \ Compressor {\n        std::vector<T> xs;   // \u8FFD\u52A0\u3055\u308C\u305F\
    \u5024\uFF08\u91CD\u8907\u3042\u308A\uFF09\n        std::vector<T> v;    // \u30BD\
    \u30FC\u30C8\u6E08\u307F\u30E6\u30CB\u30FC\u30AF\u5217\n        bool built = false;\n\
    \    \n        // \u5024\u3092\u8FFD\u52A0: \u5E73\u5747 O(1)\n        void add(const\
    \ T& x) {\n            xs.push_back(x);\n        }\n    \n        // \u7BC4\u56F2\
    \u8FFD\u52A0: O(k)\n        template <class It>\n        void add_range(It first,\
    \ It last) {\n            xs.insert(xs.end(), first, last);\n        }\n    \n\
    \        // \u69CB\u7BC9: O(n log n)  n = add \u3055\u308C\u305F\u7DCF\u6570\n\
    \        void build() {\n            v = xs;\n            std::sort(v.begin(),\
    \ v.end());\n            v.erase(std::unique(v.begin(), v.end()), v.end());\n\
    \            built = true;\n        }\n    \n        // \u5727\u7E2E\u5F8C\u306E\
    \u8981\u7D20\u6570: O(1)\n        int size() const {\n            return (int)v.size();\n\
    \        }\n    \n        // x \u306E\u5727\u7E2E\u5F8C\u30A4\u30F3\u30C7\u30C3\
    \u30AF\u30B9\u3092\u8FD4\u3059\u3002\u5B58\u5728\u3057\u306A\u3051\u308C\u3070\
    \ -1: O(log n)\n        int get(const T& x) const {\n            assert(built);\n\
    \            auto it = std::lower_bound(v.begin(), v.end(), x);\n            if\
    \ (it == v.end() || *it != x) return -1;\n            return (int)(it - v.begin());\n\
    \        }\n    \n        // x \u304C\u5B58\u5728\u3059\u308B\u304B: O(log n)\n\
    \        bool has(const T& x) const {\n            return get(x) != -1;\n    \
    \    }\n    \n        // v[i] >= x \u3068\u306A\u308B\u6700\u5C0F i \u3092\u8FD4\
    \u3059\u3002\u5168\u3066 < x \u306A\u3089 size(): O(log n)\n        int lower_bound(const\
    \ T& x) const {\n            assert(built);\n            return (int)(std::lower_bound(v.begin(),\
    \ v.end(), x) - v.begin());\n        }\n    \n        // v[i] > x \u3068\u306A\
    \u308B\u6700\u5C0F i \u3092\u8FD4\u3059\u3002\u5168\u3066 <= x \u306A\u3089 size():\
    \ O(log n)\n        int upper_bound(const T& x) const {\n            assert(built);\n\
    \            return (int)(std::upper_bound(v.begin(), v.end(), x) - v.begin());\n\
    \        }\n    \n        // \u5727\u7E2E\u5024 \u2192 \u5143\u306E\u5024: O(1)\n\
    \        const T& value(int idx) const {\n            assert(built);\n       \
    \     return v[idx];\n        }\n    \n        // \u914D\u5217\u3092\u5727\u7E2E\
    \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\u5217\u306B\u5909\u63DB\u3057\u3066\u8FD4\
    \u3059\uFF08\u5B58\u5728\u3057\u306A\u3044\u5024\u306F -1\uFF09: O(k log n)\n\
    \        std::vector<int> map(const std::vector<T>& a) const {\n            assert(built);\n\
    \            std::vector<int> res; res.reserve(a.size());\n            for (auto&\
    \ x : a) res.push_back(get(x));\n            return res;\n        }\n    };\n\
    }\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\
    \nnamespace yesantikiss {\n    template <class T>\n    struct Compressor {\n \
    \       std::vector<T> xs;   // \u8FFD\u52A0\u3055\u308C\u305F\u5024\uFF08\u91CD\
    \u8907\u3042\u308A\uFF09\n        std::vector<T> v;    // \u30BD\u30FC\u30C8\u6E08\
    \u307F\u30E6\u30CB\u30FC\u30AF\u5217\n        bool built = false;\n    \n    \
    \    // \u5024\u3092\u8FFD\u52A0: \u5E73\u5747 O(1)\n        void add(const T&\
    \ x) {\n            xs.push_back(x);\n        }\n    \n        // \u7BC4\u56F2\
    \u8FFD\u52A0: O(k)\n        template <class It>\n        void add_range(It first,\
    \ It last) {\n            xs.insert(xs.end(), first, last);\n        }\n    \n\
    \        // \u69CB\u7BC9: O(n log n)  n = add \u3055\u308C\u305F\u7DCF\u6570\n\
    \        void build() {\n            v = xs;\n            std::sort(v.begin(),\
    \ v.end());\n            v.erase(std::unique(v.begin(), v.end()), v.end());\n\
    \            built = true;\n        }\n    \n        // \u5727\u7E2E\u5F8C\u306E\
    \u8981\u7D20\u6570: O(1)\n        int size() const {\n            return (int)v.size();\n\
    \        }\n    \n        // x \u306E\u5727\u7E2E\u5F8C\u30A4\u30F3\u30C7\u30C3\
    \u30AF\u30B9\u3092\u8FD4\u3059\u3002\u5B58\u5728\u3057\u306A\u3051\u308C\u3070\
    \ -1: O(log n)\n        int get(const T& x) const {\n            assert(built);\n\
    \            auto it = std::lower_bound(v.begin(), v.end(), x);\n            if\
    \ (it == v.end() || *it != x) return -1;\n            return (int)(it - v.begin());\n\
    \        }\n    \n        // x \u304C\u5B58\u5728\u3059\u308B\u304B: O(log n)\n\
    \        bool has(const T& x) const {\n            return get(x) != -1;\n    \
    \    }\n    \n        // v[i] >= x \u3068\u306A\u308B\u6700\u5C0F i \u3092\u8FD4\
    \u3059\u3002\u5168\u3066 < x \u306A\u3089 size(): O(log n)\n        int lower_bound(const\
    \ T& x) const {\n            assert(built);\n            return (int)(std::lower_bound(v.begin(),\
    \ v.end(), x) - v.begin());\n        }\n    \n        // v[i] > x \u3068\u306A\
    \u308B\u6700\u5C0F i \u3092\u8FD4\u3059\u3002\u5168\u3066 <= x \u306A\u3089 size():\
    \ O(log n)\n        int upper_bound(const T& x) const {\n            assert(built);\n\
    \            return (int)(std::upper_bound(v.begin(), v.end(), x) - v.begin());\n\
    \        }\n    \n        // \u5727\u7E2E\u5024 \u2192 \u5143\u306E\u5024: O(1)\n\
    \        const T& value(int idx) const {\n            assert(built);\n       \
    \     return v[idx];\n        }\n    \n        // \u914D\u5217\u3092\u5727\u7E2E\
    \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\u5217\u306B\u5909\u63DB\u3057\u3066\u8FD4\
    \u3059\uFF08\u5B58\u5728\u3057\u306A\u3044\u5024\u306F -1\uFF09: O(k log n)\n\
    \        std::vector<int> map(const std::vector<T>& a) const {\n            assert(built);\n\
    \            std::vector<int> res; res.reserve(a.size());\n            for (auto&\
    \ x : a) res.push_back(get(x));\n            return res;\n        }\n    };\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/compressor.hpp
  requiredBy:
  - tests/test.cpp
  timestamp: '2026-10-08 13:39:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/static_range_count_distinct.test.cpp
documentation_of: ds/compressor.hpp
layout: document
title: "\u5EA7\u6A19\u5727\u7E2E"
---

## 概要

`yesantikiss::Compressor<T>` は、登録した値をソート済みユニーク列の添字へ
変換します。

## API

- `add(x)`, `add_range(first, last)`: 圧縮対象を登録します。
- `build()`: 登録値からソート済みユニーク列を構築します。
- `size()`: 相異なる登録値の数を返します。
- `get(x)`: 登録値 `x` の圧縮後添字、未登録なら `-1` を返します。
- `has(x)`: `x` が登録済みかを返します。
- `lower_bound(x)`, `upper_bound(x)`: 境界位置を返します。
- `value(i)`: 圧縮後添字 `i` に対応する元の値を返します。
- `map(a)`: 配列を圧縮後添字の配列へ変換します。

## 要件・注意

- `add` をすべて終えてから `build()` を呼び、その後に検索してください。
- 構築後に値を追加した場合は、検索前に `build()` を再実行してください。
- `T` はソートと等値比較ができる必要があります。
- `value(i)` では `0 <= i < size()` を満たしてください。

## 計算量

登録値数を `N` とすると構築は `O(N log N)`、各検索は `O(log N)`、
`value` と `size` は `O(1)` です。
