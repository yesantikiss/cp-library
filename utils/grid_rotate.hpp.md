---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: tests/test.cpp
    title: tests/test.cpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utils/grid_rotate.hpp\"\n\n#include <cassert>\n#include\
    \ <vector>\n\nnamespace yesantikiss {\n    // \u4E8C\u6B21\u5143\u914D\u5217\u306E\
    \u56DE\u8EE2\uFF08\u3059\u3079\u3066\u6642\u8A08\u56DE\u308A\uFF09\n    // Row\
    \ \u306F std::vector<T> \u3067\u3082 std::string \u3067\u3082\u3088\u3044\n  \
    \  // H\xD7W \u306E a \u3092 90\xB0 \u56DE\u3059\u3068 W\xD7H \u306B\u306A\u308B\
    : res[i][j] = a[H-1-j][i]\n    template <class Row>\n    std::vector<Row> rotate90(const\
    \ std::vector<Row>& a) {\n        const int H = (int)a.size();\n        if (H\
    \ == 0) return {};\n        const int W = (int)a[0].size();\n        std::vector<Row>\
    \ res(W, Row(H, typename Row::value_type()));\n        for (int i = 0; i < H;\
    \ ++i) {\n            assert((int)a[i].size() == W);\n            for (int j =\
    \ 0; j < W; ++j) res[j][H - 1 - i] = a[i][j];\n        }\n        return res;\n\
    \    }\n\n    // 180\xB0: res[i][j] = a[H-1-i][W-1-j]\n    template <class Row>\n\
    \    std::vector<Row> rotate180(const std::vector<Row>& a) {\n        std::vector<Row>\
    \ res(a.rbegin(), a.rend());\n        for (auto& row : res) {\n            assert(row.size()\
    \ == a[0].size());\n            row = Row(row.rbegin(), row.rend());\n       \
    \ }\n        return res;\n    }\n\n    // 270\xB0\uFF08\u53CD\u6642\u8A08\u56DE\
    \u308A\u306B 90\xB0\uFF09: res[i][j] = a[j][W-1-i]\n    template <class Row>\n\
    \    std::vector<Row> rotate270(const std::vector<Row>& a) {\n        const int\
    \ H = (int)a.size();\n        if (H == 0) return {};\n        const int W = (int)a[0].size();\n\
    \        std::vector<Row> res(W, Row(H, typename Row::value_type()));\n      \
    \  for (int i = 0; i < H; ++i) {\n            assert((int)a[i].size() == W);\n\
    \            for (int j = 0; j < W; ++j) res[W - 1 - j][i] = a[i][j];\n      \
    \  }\n        return res;\n    }\n\n    // \u6642\u8A08\u56DE\u308A\u306B 90k\xB0\
    \uFF08k \u306F\u8CA0\u3067\u3082\u3088\u3044\uFF09\n    template <class Row>\n\
    \    std::vector<Row> rotate(const std::vector<Row>& a, int k) {\n        k =\
    \ (k % 4 + 4) % 4;\n        if (k == 1) return rotate90(a);\n        if (k ==\
    \ 2) return rotate180(a);\n        if (k == 3) return rotate270(a);\n        return\
    \ a;\n    }\n}\n"
  code: "#pragma once\n\n#include <cassert>\n#include <vector>\n\nnamespace yesantikiss\
    \ {\n    // \u4E8C\u6B21\u5143\u914D\u5217\u306E\u56DE\u8EE2\uFF08\u3059\u3079\
    \u3066\u6642\u8A08\u56DE\u308A\uFF09\n    // Row \u306F std::vector<T> \u3067\u3082\
    \ std::string \u3067\u3082\u3088\u3044\n    // H\xD7W \u306E a \u3092 90\xB0 \u56DE\
    \u3059\u3068 W\xD7H \u306B\u306A\u308B: res[i][j] = a[H-1-j][i]\n    template\
    \ <class Row>\n    std::vector<Row> rotate90(const std::vector<Row>& a) {\n  \
    \      const int H = (int)a.size();\n        if (H == 0) return {};\n        const\
    \ int W = (int)a[0].size();\n        std::vector<Row> res(W, Row(H, typename Row::value_type()));\n\
    \        for (int i = 0; i < H; ++i) {\n            assert((int)a[i].size() ==\
    \ W);\n            for (int j = 0; j < W; ++j) res[j][H - 1 - i] = a[i][j];\n\
    \        }\n        return res;\n    }\n\n    // 180\xB0: res[i][j] = a[H-1-i][W-1-j]\n\
    \    template <class Row>\n    std::vector<Row> rotate180(const std::vector<Row>&\
    \ a) {\n        std::vector<Row> res(a.rbegin(), a.rend());\n        for (auto&\
    \ row : res) {\n            assert(row.size() == a[0].size());\n            row\
    \ = Row(row.rbegin(), row.rend());\n        }\n        return res;\n    }\n\n\
    \    // 270\xB0\uFF08\u53CD\u6642\u8A08\u56DE\u308A\u306B 90\xB0\uFF09: res[i][j]\
    \ = a[j][W-1-i]\n    template <class Row>\n    std::vector<Row> rotate270(const\
    \ std::vector<Row>& a) {\n        const int H = (int)a.size();\n        if (H\
    \ == 0) return {};\n        const int W = (int)a[0].size();\n        std::vector<Row>\
    \ res(W, Row(H, typename Row::value_type()));\n        for (int i = 0; i < H;\
    \ ++i) {\n            assert((int)a[i].size() == W);\n            for (int j =\
    \ 0; j < W; ++j) res[W - 1 - j][i] = a[i][j];\n        }\n        return res;\n\
    \    }\n\n    // \u6642\u8A08\u56DE\u308A\u306B 90k\xB0\uFF08k \u306F\u8CA0\u3067\
    \u3082\u3088\u3044\uFF09\n    template <class Row>\n    std::vector<Row> rotate(const\
    \ std::vector<Row>& a, int k) {\n        k = (k % 4 + 4) % 4;\n        if (k ==\
    \ 1) return rotate90(a);\n        if (k == 2) return rotate180(a);\n        if\
    \ (k == 3) return rotate270(a);\n        return a;\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/grid_rotate.hpp
  requiredBy:
  - tests/test.cpp
  timestamp: '2026-10-29 20:48:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/grid_rotate.hpp
layout: document
title: "\u4E8C\u6B21\u5143\u914D\u5217\u306E\u56DE\u8EE2"
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
