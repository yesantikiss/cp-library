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
  bundledCode: "#line 2 \"ds/2d_prefixsum.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace yesantikiss {\n    // 2D Prefix/Imos\
    \ (single diff, single O(HW) build)\n    // \u4ED5\u69D8: 0-index, \u534A\u958B\
    \u533A\u9593 [y1,y2)\xD7[x1,x2)\n    // \u4F7F\u3044\u5206\u3051: set_point\u306E\
    \u307F\u2192SET\u30E2\u30FC\u30C9 / add_rect_imos\u306E\u307F\u2192IMOS\u30E2\u30FC\
    \u30C9\uFF08\u4F75\u7528\u7981\u6B62\uFF09\n    template<class T>\n    struct\
    \ PS2D {\n        enum Mode { EMPTY, SET_MODE, IMOS_MODE };\n    \n        int\
    \ H, W;\n        Mode mode = EMPTY;\n        std::vector<std::vector<T>> buf;\
    \   // SET: \u5024\u884C\u5217\u3068\u3057\u3066H\xD7W\u306E\u307F\u4F7F\u7528\
    \ / IMOS: \u5DEE\u5206\u3068\u3057\u3066(H+1)\xD7(W+1)\u5168\u9762\u4F7F\u7528\
    \n        std::vector<std::vector<T>> grid;  // build\u5F8C\u306E\u5B8C\u6210\u30B0\
    \u30EA\u30C3\u30C9 H\xD7W\n        std::vector<std::vector<T>> pref;  // 2D\u7D2F\
    \u7A4D\u548C (H+1)\xD7(W+1)\n        bool built = false;\n    \n        PS2D(int\
    \ H, int W): H(H), W(W),\n            buf(H+1, std::vector<T>(W+1, T())),\n  \
    \          grid(H, std::vector<T>(W, T())),\n            pref(H+1, std::vector<T>(W+1,\
    \ T())) {}\n    \n        // \u5358\u70B9\u4E0A\u66F8\u304D: SET\u30E2\u30FC\u30C9\
    \u5C02\u7528\n        void set_point(int y, int x, T v) {\n            assert(0\
    \ <= y && y < H && 0 <= x && x < W);\n            assert(mode == EMPTY || mode\
    \ == SET_MODE);\n            mode = SET_MODE;\n            buf[y][x] = v;   //\
    \ buf\u306F\u5024\u884C\u5217\u3068\u3057\u3066\u4F7F\u7528\uFF08H\xD7W\u9818\u57DF\
    \uFF09\n            built = false;\n        }\n    \n        // \u9577\u65B9\u5F62\
    \u52A0\u7B97: IMOS\u30E2\u30FC\u30C9\u5C02\u7528\n        void add_rect_imos(int\
    \ y1, int x1, int y2, int x2, T v) {\n            assert(0 <= y1 && y1 <= y2 &&\
    \ y2 <= H);\n            assert(0 <= x1 && x1 <= x2 && x2 <= W);\n           \
    \ assert(mode == EMPTY || mode == IMOS_MODE);\n            mode = IMOS_MODE;\n\
    \            // buf\u306F\u5DEE\u5206\u3068\u3057\u3066\u4F7F\u7528\uFF08(H+1)\xD7\
    (W+1)\uFF09\n            buf[y1][x1] += v;\n            buf[y1][x2] -= v;\n  \
    \          buf[y2][x1] -= v;\n            buf[y2][x2] += v;\n            built\
    \ = false;\n        }\n    \n        // \u70B9\u52A0\u7B97(imos)\n        void\
    \ add_point_imos(int y, int x, T v) { add_rect_imos(y, x, y+1, x+1, v); }\n  \
    \  \n        // \u30AF\u30EA\u30A2\n        void clear_all() {\n            for\
    \ (int y = 0; y <= H; ++y) std::fill(buf[y].begin(), buf[y].end(), T());\n   \
    \         built = false;\n            mode = EMPTY;\n        }\n    \n       \
    \ // \u69CB\u7BC9: \u5E38\u306BO(HW) 1\u56DE\u3067 grid \u3068 pref \u3092\u540C\
    \u6642\u306B\u751F\u6210\n        void build() {\n            for (int y = 0;\
    \ y <= H; ++y) std::fill(pref[y].begin(), pref[y].end(), T());\n    \n       \
    \     if (mode == SET_MODE) {\n                // buf[y][x] \u3092\u5024\u3068\
    \u3057\u3066\u305D\u306E\u307E\u307E\u7D2F\u7A4D\n                for (int y =\
    \ 0; y < H; ++y) {\n                    T row_sum = T();\n                   \
    \ for (int x = 0; x < W; ++x) {\n                        T v = buf[y][x];\n  \
    \                      grid[y][x] = v;\n                        row_sum += v;\n\
    \                        pref[y+1][x+1] = pref[y][x+1] + row_sum;\n          \
    \          }\n                }\n            } else {\n                // IMOS_MODE\
    \ \u307E\u305F\u306F EMPTY\uFF08EMPTY\u306F\u51680\uFF09\n                // buf\u306F\
    \u5DEE\u5206\u3002grid\u306Bimos\u3092\u7D2F\u7A4D\u3057\u3064\u3064pref\u3082\
    \u540C\u6642\u306B\u4F5C\u308B\n                for (int y = 0; y < H; ++y) {\n\
    \                    for (int x = 0; x < W; ++x) {\n                        T\
    \ v = buf[y][x];\n                        if (y) v += grid[y-1][x];\n        \
    \                if (x) v += grid[y][x-1];\n                        if (y && x)\
    \ v -= grid[y-1][x-1];\n                        grid[y][x] = v;\n    \n      \
    \                  pref[y+1][x+1] = pref[y][x+1] + pref[y+1][x] - pref[y][x] +\
    \ v;\n                    }\n                }\n            }\n            built\
    \ = true;\n        }\n    \n        // \u5358\u70B9\u53D6\u5F97 O(1)\n       \
    \ T at(int y, int x) const {\n            assert(built);\n            assert(0\
    \ <= y && y < H && 0 <= x && x < W);\n            return grid[y][x];\n       \
    \ }\n        T operator()(int y, int x) const { return at(y, x); }\n    \n   \
    \     struct RowProxy {\n            const PS2D* p; int y;\n            T operator[](int\
    \ x) const {\n                assert(p->built); assert(0 <= x && x < p->W);\n\
    \                return p->grid[y][x];\n            }\n        };\n        RowProxy\
    \ operator[](int y) const { assert(built); return RowProxy{this, y}; }\n    \n\
    \        // \u9577\u65B9\u5F62\u548C O(1)  [y1,y2)\xD7[x1,x2)\n        T sum(int\
    \ y1, int x1, int y2, int x2) const {\n            assert(built);\n          \
    \  assert(0 <= y1 && y1 <= y2 && y2 <= H);\n            assert(0 <= x1 && x1 <=\
    \ x2 && x2 <= W);\n            return pref[y2][x2] - pref[y1][x2] - pref[y2][x1]\
    \ + pref[y1][x1];\n        }\n    \n        // \u5168\u4F53\u548C\n        T sum_all()\
    \ const { assert(built); return pref[H][W]; }\n    };\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\
    \nnamespace yesantikiss {\n    // 2D Prefix/Imos (single diff, single O(HW) build)\n\
    \    // \u4ED5\u69D8: 0-index, \u534A\u958B\u533A\u9593 [y1,y2)\xD7[x1,x2)\n \
    \   // \u4F7F\u3044\u5206\u3051: set_point\u306E\u307F\u2192SET\u30E2\u30FC\u30C9\
    \ / add_rect_imos\u306E\u307F\u2192IMOS\u30E2\u30FC\u30C9\uFF08\u4F75\u7528\u7981\
    \u6B62\uFF09\n    template<class T>\n    struct PS2D {\n        enum Mode { EMPTY,\
    \ SET_MODE, IMOS_MODE };\n    \n        int H, W;\n        Mode mode = EMPTY;\n\
    \        std::vector<std::vector<T>> buf;   // SET: \u5024\u884C\u5217\u3068\u3057\
    \u3066H\xD7W\u306E\u307F\u4F7F\u7528 / IMOS: \u5DEE\u5206\u3068\u3057\u3066(H+1)\xD7\
    (W+1)\u5168\u9762\u4F7F\u7528\n        std::vector<std::vector<T>> grid;  // build\u5F8C\
    \u306E\u5B8C\u6210\u30B0\u30EA\u30C3\u30C9 H\xD7W\n        std::vector<std::vector<T>>\
    \ pref;  // 2D\u7D2F\u7A4D\u548C (H+1)\xD7(W+1)\n        bool built = false;\n\
    \    \n        PS2D(int H, int W): H(H), W(W),\n            buf(H+1, std::vector<T>(W+1,\
    \ T())),\n            grid(H, std::vector<T>(W, T())),\n            pref(H+1,\
    \ std::vector<T>(W+1, T())) {}\n    \n        // \u5358\u70B9\u4E0A\u66F8\u304D\
    : SET\u30E2\u30FC\u30C9\u5C02\u7528\n        void set_point(int y, int x, T v)\
    \ {\n            assert(0 <= y && y < H && 0 <= x && x < W);\n            assert(mode\
    \ == EMPTY || mode == SET_MODE);\n            mode = SET_MODE;\n            buf[y][x]\
    \ = v;   // buf\u306F\u5024\u884C\u5217\u3068\u3057\u3066\u4F7F\u7528\uFF08H\xD7\
    W\u9818\u57DF\uFF09\n            built = false;\n        }\n    \n        // \u9577\
    \u65B9\u5F62\u52A0\u7B97: IMOS\u30E2\u30FC\u30C9\u5C02\u7528\n        void add_rect_imos(int\
    \ y1, int x1, int y2, int x2, T v) {\n            assert(0 <= y1 && y1 <= y2 &&\
    \ y2 <= H);\n            assert(0 <= x1 && x1 <= x2 && x2 <= W);\n           \
    \ assert(mode == EMPTY || mode == IMOS_MODE);\n            mode = IMOS_MODE;\n\
    \            // buf\u306F\u5DEE\u5206\u3068\u3057\u3066\u4F7F\u7528\uFF08(H+1)\xD7\
    (W+1)\uFF09\n            buf[y1][x1] += v;\n            buf[y1][x2] -= v;\n  \
    \          buf[y2][x1] -= v;\n            buf[y2][x2] += v;\n            built\
    \ = false;\n        }\n    \n        // \u70B9\u52A0\u7B97(imos)\n        void\
    \ add_point_imos(int y, int x, T v) { add_rect_imos(y, x, y+1, x+1, v); }\n  \
    \  \n        // \u30AF\u30EA\u30A2\n        void clear_all() {\n            for\
    \ (int y = 0; y <= H; ++y) std::fill(buf[y].begin(), buf[y].end(), T());\n   \
    \         built = false;\n            mode = EMPTY;\n        }\n    \n       \
    \ // \u69CB\u7BC9: \u5E38\u306BO(HW) 1\u56DE\u3067 grid \u3068 pref \u3092\u540C\
    \u6642\u306B\u751F\u6210\n        void build() {\n            for (int y = 0;\
    \ y <= H; ++y) std::fill(pref[y].begin(), pref[y].end(), T());\n    \n       \
    \     if (mode == SET_MODE) {\n                // buf[y][x] \u3092\u5024\u3068\
    \u3057\u3066\u305D\u306E\u307E\u307E\u7D2F\u7A4D\n                for (int y =\
    \ 0; y < H; ++y) {\n                    T row_sum = T();\n                   \
    \ for (int x = 0; x < W; ++x) {\n                        T v = buf[y][x];\n  \
    \                      grid[y][x] = v;\n                        row_sum += v;\n\
    \                        pref[y+1][x+1] = pref[y][x+1] + row_sum;\n          \
    \          }\n                }\n            } else {\n                // IMOS_MODE\
    \ \u307E\u305F\u306F EMPTY\uFF08EMPTY\u306F\u51680\uFF09\n                // buf\u306F\
    \u5DEE\u5206\u3002grid\u306Bimos\u3092\u7D2F\u7A4D\u3057\u3064\u3064pref\u3082\
    \u540C\u6642\u306B\u4F5C\u308B\n                for (int y = 0; y < H; ++y) {\n\
    \                    for (int x = 0; x < W; ++x) {\n                        T\
    \ v = buf[y][x];\n                        if (y) v += grid[y-1][x];\n        \
    \                if (x) v += grid[y][x-1];\n                        if (y && x)\
    \ v -= grid[y-1][x-1];\n                        grid[y][x] = v;\n    \n      \
    \                  pref[y+1][x+1] = pref[y][x+1] + pref[y+1][x] - pref[y][x] +\
    \ v;\n                    }\n                }\n            }\n            built\
    \ = true;\n        }\n    \n        // \u5358\u70B9\u53D6\u5F97 O(1)\n       \
    \ T at(int y, int x) const {\n            assert(built);\n            assert(0\
    \ <= y && y < H && 0 <= x && x < W);\n            return grid[y][x];\n       \
    \ }\n        T operator()(int y, int x) const { return at(y, x); }\n    \n   \
    \     struct RowProxy {\n            const PS2D* p; int y;\n            T operator[](int\
    \ x) const {\n                assert(p->built); assert(0 <= x && x < p->W);\n\
    \                return p->grid[y][x];\n            }\n        };\n        RowProxy\
    \ operator[](int y) const { assert(built); return RowProxy{this, y}; }\n    \n\
    \        // \u9577\u65B9\u5F62\u548C O(1)  [y1,y2)\xD7[x1,x2)\n        T sum(int\
    \ y1, int x1, int y2, int x2) const {\n            assert(built);\n          \
    \  assert(0 <= y1 && y1 <= y2 && y2 <= H);\n            assert(0 <= x1 && x1 <=\
    \ x2 && x2 <= W);\n            return pref[y2][x2] - pref[y1][x2] - pref[y2][x1]\
    \ + pref[y1][x1];\n        }\n    \n        // \u5168\u4F53\u548C\n        T sum_all()\
    \ const { assert(built); return pref[H][W]; }\n    };\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/2d_prefixsum.hpp
  requiredBy:
  - tests/test.cpp
  timestamp: '2026-10-08 13:39:00+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: ds/2d_prefixsum.hpp
layout: document
title: "\u4E8C\u6B21\u5143\u7D2F\u7A4D\u548C\u30FB\u4E8C\u6B21\u5143\u3044\u3082\u3059\
  \u6CD5"
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
