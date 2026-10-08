---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: tests/test.cpp
    title: tests/test.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/cartesian_tree.test.cpp
    title: verify/cartesian_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"ds/cartesian_tree.hpp\"\n\n#include <functional>\n#include\
    \ <vector>\n\nnamespace yesantikiss {\n    template <class T, class Compare =\
    \ std::less<T>>\n    struct CartesianTree {\n        int n = 0;\n        std::vector<T>\
    \ a;\n        std::vector<int> par, left, right;\n        int root = -1;\n   \
    \     Compare comp;\n    \n        CartesianTree() {}\n    \n        CartesianTree(const\
    \ std::vector<T>& _a, Compare _comp = Compare())\n            : n((int)_a.size()),\n\
    \              a(_a),\n              par(n, -1),\n              left(n, -1),\n\
    \              right(n, -1),\n              root(-1),\n              comp(_comp)\
    \ {\n            build();\n        }\n    \n        // comp(a[i], a[j]) == true\
    \ \u306A\u3089 i \u306E\u65B9\u304C j \u3088\u308A\u4E0A\u306B\u6765\u308B\n \
    \       // less<T>    : min Cartesian Tree\n        // greater<T> : max Cartesian\
    \ Tree\n        void build() {\n            std::vector<int> st;\n           \
    \ st.reserve(n);\n    \n            for (int i = 0; i < n; i++) {\n          \
    \      int last = -1;\n    \n                while (!st.empty() && comp(a[i],\
    \ a[st.back()])) {\n                    last = st.back();\n                  \
    \  st.pop_back();\n                }\n    \n                if (!st.empty()) {\n\
    \                    par[i] = st.back();\n                    right[st.back()]\
    \ = i;\n                }\n    \n                if (last != -1) {\n         \
    \           par[last] = i;\n                    left[i] = last;\n            \
    \    }\n    \n                st.push_back(i);\n            }\n    \n        \
    \    for (int i = 0; i < n; i++) {\n                if (par[i] == -1) {\n    \
    \                root = i;\n                    break;\n                }\n  \
    \          }\n        }\n    };\n}\n"
  code: "#pragma once\n\n#include <functional>\n#include <vector>\n\nnamespace yesantikiss\
    \ {\n    template <class T, class Compare = std::less<T>>\n    struct CartesianTree\
    \ {\n        int n = 0;\n        std::vector<T> a;\n        std::vector<int> par,\
    \ left, right;\n        int root = -1;\n        Compare comp;\n    \n        CartesianTree()\
    \ {}\n    \n        CartesianTree(const std::vector<T>& _a, Compare _comp = Compare())\n\
    \            : n((int)_a.size()),\n              a(_a),\n              par(n,\
    \ -1),\n              left(n, -1),\n              right(n, -1),\n            \
    \  root(-1),\n              comp(_comp) {\n            build();\n        }\n \
    \   \n        // comp(a[i], a[j]) == true \u306A\u3089 i \u306E\u65B9\u304C j\
    \ \u3088\u308A\u4E0A\u306B\u6765\u308B\n        // less<T>    : min Cartesian\
    \ Tree\n        // greater<T> : max Cartesian Tree\n        void build() {\n \
    \           std::vector<int> st;\n            st.reserve(n);\n    \n         \
    \   for (int i = 0; i < n; i++) {\n                int last = -1;\n    \n    \
    \            while (!st.empty() && comp(a[i], a[st.back()])) {\n             \
    \       last = st.back();\n                    st.pop_back();\n              \
    \  }\n    \n                if (!st.empty()) {\n                    par[i] = st.back();\n\
    \                    right[st.back()] = i;\n                }\n    \n        \
    \        if (last != -1) {\n                    par[last] = i;\n             \
    \       left[i] = last;\n                }\n    \n                st.push_back(i);\n\
    \            }\n    \n            for (int i = 0; i < n; i++) {\n            \
    \    if (par[i] == -1) {\n                    root = i;\n                    break;\n\
    \                }\n            }\n        }\n    };\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/cartesian_tree.hpp
  requiredBy:
  - tests/test.cpp
  timestamp: '2026-10-08 13:39:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/cartesian_tree.test.cpp
documentation_of: ds/cartesian_tree.hpp
layout: document
title: Cartesian Tree
---

## 概要

配列から `yesantikiss::CartesianTree<T, Compare>` を構築します。中順巡回が
元の配列順になり、比較関数によるヒープ条件を満たす二分木です。

## API

- `CartesianTree(a, comp)`: 配列 `a` から木を構築します。
- `root`: 根の添字です。空配列では `-1` です。
- `par[i]`, `left[i]`, `right[i]`: 親・左の子・右の子の添字です。
  存在しない場合は `-1` です。

既定の `std::less<T>` では min Cartesian Tree、`std::greater<T>` では
max Cartesian Tree になります。

## 要件・注意

- `Compare` は狭義弱順序を満たす必要があります。
- 同値な要素はスタックから取り除かれないため、同値要素間では先に現れた
  要素が上側になります。
- 頂点番号は元配列の添字と同じです。

## 計算量

構築は `O(N)` 時間、`O(N)` メモリです。
