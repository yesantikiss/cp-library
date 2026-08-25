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
  bundledCode: "#line 2 \"algo/mo.hpp\"\n\n#include <algorithm>\n#include <cmath>\n\
    #include <numeric>\n#include <utility>\n#include <vector>\n\nnamespace yesantikiss\
    \ {\n    struct Mo {\n        int n;\n        std::vector<std::pair<int, int>>\
    \ queries; // [l, r)\n    \n        explicit Mo(int n) : n(n) {}\n        void\
    \ add_query(int l, int r) { queries.emplace_back(l, r); }\n    \n        // add(i),\
    \ del(i) \u3057\u304B\u8981\u3089\u306A\u3044\u30B1\u30FC\u30B9\uFF08\u4E92\u63DB\
    \uFF09\n        template <class Add, class Del, class Out>\n        void solve(const\
    \ Add& add, const Del& del, const Out& out) {\n            solve(add, add, del,\
    \ del, out); // \u5DE6\u53F3\u540C\u3058\u95A2\u6570\u3068\u3057\u3066\u6271\u3046\
    \n        }\n    \n        // \u5DE6\u53F3\u3067 add/del \u3092\u5206\u3051\u305F\
    \u3044\u30B1\u30FC\u30B9\n        // addL: \u5DE6\u306B\u4F38\u3070\u3059\u3068\
    \u304D\u306B\u8FFD\u52A0 (l--)\n        // addR: \u53F3\u306B\u4F38\u3070\u3059\
    \u3068\u304D\u306B\u8FFD\u52A0 (r++)\n        // delL: \u5DE6\u3092\u7E2E\u3081\
    \u308B\u3068\u304D\u306B\u524A\u9664 (l++)\n        // delR: \u53F3\u3092\u7E2E\
    \u3081\u308B\u3068\u304D\u306B\u524A\u9664 (r--)\n        template <class AddL,\
    \ class AddR, class DelL, class DelR, class Out>\n        void solve(const AddL&\
    \ addL, const AddR& addR, const DelL& delL, const DelR& delR, const Out& out)\
    \ {\n            int q = (int)queries.size();\n            if (q == 0) return;\n\
    \    \n            int bs = std::max(1, (int)(n / std::sqrt((double)q)));\n  \
    \          std::vector<int> ord(q);\n            std::iota(ord.begin(), ord.end(),\
    \ 0);\n    \n            std::sort(ord.begin(), ord.end(), [&](int a, int b) {\n\
    \                int ab = queries[a].first / bs, bb = queries[b].first / bs;\n\
    \                if (ab != bb) return ab < bb;\n                return (ab & 1)\
    \ ? queries[a].second > queries[b].second\n                                : queries[a].second\
    \ < queries[b].second;\n            });\n    \n            int l = 0, r = 0;\n\
    \            for (int idx : ord) {\n                auto [ql, qr] = queries[idx];\n\
    \    \n                while (l > ql) addL(--l);\n                while (r < qr)\
    \ addR(r++);\n                while (l < ql) delL(l++);\n                while\
    \ (r > qr) delR(--r);\n    \n                out(idx);\n            }\n      \
    \  }\n    };\n    \n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cmath>\n#include <numeric>\n\
    #include <utility>\n#include <vector>\n\nnamespace yesantikiss {\n    struct Mo\
    \ {\n        int n;\n        std::vector<std::pair<int, int>> queries; // [l,\
    \ r)\n    \n        explicit Mo(int n) : n(n) {}\n        void add_query(int l,\
    \ int r) { queries.emplace_back(l, r); }\n    \n        // add(i), del(i) \u3057\
    \u304B\u8981\u3089\u306A\u3044\u30B1\u30FC\u30B9\uFF08\u4E92\u63DB\uFF09\n   \
    \     template <class Add, class Del, class Out>\n        void solve(const Add&\
    \ add, const Del& del, const Out& out) {\n            solve(add, add, del, del,\
    \ out); // \u5DE6\u53F3\u540C\u3058\u95A2\u6570\u3068\u3057\u3066\u6271\u3046\n\
    \        }\n    \n        // \u5DE6\u53F3\u3067 add/del \u3092\u5206\u3051\u305F\
    \u3044\u30B1\u30FC\u30B9\n        // addL: \u5DE6\u306B\u4F38\u3070\u3059\u3068\
    \u304D\u306B\u8FFD\u52A0 (l--)\n        // addR: \u53F3\u306B\u4F38\u3070\u3059\
    \u3068\u304D\u306B\u8FFD\u52A0 (r++)\n        // delL: \u5DE6\u3092\u7E2E\u3081\
    \u308B\u3068\u304D\u306B\u524A\u9664 (l++)\n        // delR: \u53F3\u3092\u7E2E\
    \u3081\u308B\u3068\u304D\u306B\u524A\u9664 (r--)\n        template <class AddL,\
    \ class AddR, class DelL, class DelR, class Out>\n        void solve(const AddL&\
    \ addL, const AddR& addR, const DelL& delL, const DelR& delR, const Out& out)\
    \ {\n            int q = (int)queries.size();\n            if (q == 0) return;\n\
    \    \n            int bs = std::max(1, (int)(n / std::sqrt((double)q)));\n  \
    \          std::vector<int> ord(q);\n            std::iota(ord.begin(), ord.end(),\
    \ 0);\n    \n            std::sort(ord.begin(), ord.end(), [&](int a, int b) {\n\
    \                int ab = queries[a].first / bs, bb = queries[b].first / bs;\n\
    \                if (ab != bb) return ab < bb;\n                return (ab & 1)\
    \ ? queries[a].second > queries[b].second\n                                : queries[a].second\
    \ < queries[b].second;\n            });\n    \n            int l = 0, r = 0;\n\
    \            for (int idx : ord) {\n                auto [ql, qr] = queries[idx];\n\
    \    \n                while (l > ql) addL(--l);\n                while (r < qr)\
    \ addR(r++);\n                while (l < ql) delL(l++);\n                while\
    \ (r > qr) delR(--r);\n    \n                out(idx);\n            }\n      \
    \  }\n    };\n    \n}\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/mo.hpp
  requiredBy:
  - tests/test.cpp
  timestamp: '2026-08-25 15:58:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/static_range_count_distinct.test.cpp
documentation_of: algo/mo.hpp
layout: document
title: Mo's algorithm
---

## 概要

静的な区間クエリを並べ替え、現在の区間を少しずつ伸縮させて処理する
Mo's algorithm です。区間は 0-indexed の半開区間 `[l, r)` です。

## API

- `Mo(n)`: 対象列の長さを指定します。
- `add_query(l, r)`: クエリ `[l, r)` を追加します。
- `solve(add, del, out)`: 左右で共通の追加・削除処理を使います。
- `solve(addL, addR, delL, delR, out)`: 左右で異なる処理を使います。
- `out(i)`: クエリ `i` の区間に移動した後に呼ばれます。`i` は
  `add_query` で追加した順番です。

各コールバックが受け取る添字は次のとおりです。

- `addL(--l)`, `addR(r++)`
- `delL(l++)`, `delR(--r)`

## 要件・注意

- すべてのクエリで `0 <= l <= r <= n` を満たしてください。
- `solve` の呼び出し時点では、コールバックが管理する区間を空区間
  `[0, 0)` に対応させてください。
- `add` と `del` は互いに逆の更新になる必要があります。

## 計算量

追加・削除が `O(1)` の場合、典型的には `O((N + Q) sqrt(Q))` 程度です。
クエリの保持には `O(Q)` を使います。
