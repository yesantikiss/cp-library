---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: tests/test.cpp
    title: tests/test.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/unionfind.test.cpp
    title: verify/unionfind.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/unionfind_with_potential.test.cpp
    title: verify/unionfind_with_potential.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"ds/potential_dsu.hpp\"\n\n#include <algorithm>\n#include\
    \ <vector>\n\nnamespace yesantikiss {\n    // ACL dsu \u98A8 + \u30DD\u30C6\u30F3\
    \u30B7\u30E3\u30EB(\u5DEE\u5206)\u7BA1\u7406\n    // \u7D04\u675F: merge(a,b,w)\
    \ \u306F pot[b] - pot[a] = w \u3092\u8FFD\u52A0\u3059\u308B\n    //      diff(a,b)\
    \    \u306F pot[b] - pot[a] \u3092\u8FD4\u3059\uFF08\u540C\u4E00\u6210\u5206\u306E\
    \u3068\u304D\u306E\u307F\u547C\u3076\uFF09\n    template <class T>\n    struct\
    \ potential_dsu {\n        int n;\n        std::vector<int> parent_or_size; //\
    \ root: -size, else: parent\n        std::vector<T> diff_weight;      // diff_weight[v]\
    \ = pot[v] - pot[parent[v]] (root\u306F0)\n    \n        potential_dsu() : n(0)\
    \ {}\n        explicit potential_dsu(int n_) { init(n_); }\n    \n        void\
    \ init(int n_) {\n            n = n_;\n            parent_or_size.assign(n, -1);\n\
    \            diff_weight.assign(n, T{}); // 0\n        }\n    \n        // leader\
    \ \u3092\u6C42\u3081\u3064\u3064\u3001diff_weight \u3092 root \u57FA\u6E96\u306B\
    \u7573\u307F\u8FBC\u3080\n        int leader(int a) {\n            if (parent_or_size[a]\
    \ < 0) return a;\n            int p = parent_or_size[a];\n            int r =\
    \ leader(p);\n            diff_weight[a] += diff_weight[p];\n            parent_or_size[a]\
    \ = r;\n            return r;\n        }\n    \n        bool same(int a, int b)\
    \ { return leader(a) == leader(b); }\n    \n        int size(int a) { return -parent_or_size[leader(a)];\
    \ }\n    \n        // pot[a] - pot[leader(a)]\n        T potential(int a) {\n\
    \            leader(a);\n            return diff_weight[a];\n        }\n    \n\
    \        // pot[b] - pot[a]\n        T diff(int a, int b) {\n            // \u547C\
    \u3073\u51FA\u3057\u5074\u3067 same(a,b) \u3092\u4FDD\u8A3C\uFF08ACL dsu \u3068\
    \u540C\u69D8\u306B\u672A\u5B9A\u7FA9\u6271\u3044\uFF09\n            return potential(b)\
    \ - potential(a);\n        }\n    \n        // pot[b] - pot[a] = w \u3092\u8FFD\
    \u52A0\u3057\u3066\u30DE\u30FC\u30B8\uFF08ACL dsu \u3068\u540C\u3058\u304F leader\
    \ \u3092\u8FD4\u3059\uFF09\n        int merge(int a, int b, T w) {\n         \
    \   w += potential(a);\n            w -= potential(b);\n            int x = leader(a),\
    \ y = leader(b);\n            if (x == y) return x;\n    \n            // union\
    \ by size (ACL dsu \u98A8)\n            if (-parent_or_size[x] < -parent_or_size[y])\
    \ {\n                std::swap(x, y);\n                w = -w;\n            }\n\
    \    \n            parent_or_size[x] += parent_or_size[y];\n            parent_or_size[y]\
    \ = x;\n            diff_weight[y] = w; // pot[y] - pot[x] = w\n            return\
    \ x;\n        }\n    \n        std::vector<std::vector<int>> groups() {\n    \
    \        std::vector<int> leader_buf(n), group_size(n);\n            for (int\
    \ i = 0; i < n; i++) {\n                leader_buf[i] = leader(i);\n         \
    \       group_size[leader_buf[i]]++;\n            }\n            std::vector<std::vector<int>>\
    \ result(n);\n            for (int i = 0; i < n; i++) result[i].reserve(group_size[i]);\n\
    \            for (int i = 0; i < n; i++) result[leader_buf[i]].push_back(i);\n\
    \            result.erase(std::remove_if(result.begin(), result.end(),\n     \
    \                              [](const auto& v) { return v.empty(); }),\n   \
    \                      result.end());\n            return result;\n        }\n\
    \    };\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <vector>\n\nnamespace yesantikiss\
    \ {\n    // ACL dsu \u98A8 + \u30DD\u30C6\u30F3\u30B7\u30E3\u30EB(\u5DEE\u5206\
    )\u7BA1\u7406\n    // \u7D04\u675F: merge(a,b,w) \u306F pot[b] - pot[a] = w \u3092\
    \u8FFD\u52A0\u3059\u308B\n    //      diff(a,b)    \u306F pot[b] - pot[a] \u3092\
    \u8FD4\u3059\uFF08\u540C\u4E00\u6210\u5206\u306E\u3068\u304D\u306E\u307F\u547C\
    \u3076\uFF09\n    template <class T>\n    struct potential_dsu {\n        int\
    \ n;\n        std::vector<int> parent_or_size; // root: -size, else: parent\n\
    \        std::vector<T> diff_weight;      // diff_weight[v] = pot[v] - pot[parent[v]]\
    \ (root\u306F0)\n    \n        potential_dsu() : n(0) {}\n        explicit potential_dsu(int\
    \ n_) { init(n_); }\n    \n        void init(int n_) {\n            n = n_;\n\
    \            parent_or_size.assign(n, -1);\n            diff_weight.assign(n,\
    \ T{}); // 0\n        }\n    \n        // leader \u3092\u6C42\u3081\u3064\u3064\
    \u3001diff_weight \u3092 root \u57FA\u6E96\u306B\u7573\u307F\u8FBC\u3080\n   \
    \     int leader(int a) {\n            if (parent_or_size[a] < 0) return a;\n\
    \            int p = parent_or_size[a];\n            int r = leader(p);\n    \
    \        diff_weight[a] += diff_weight[p];\n            parent_or_size[a] = r;\n\
    \            return r;\n        }\n    \n        bool same(int a, int b) { return\
    \ leader(a) == leader(b); }\n    \n        int size(int a) { return -parent_or_size[leader(a)];\
    \ }\n    \n        // pot[a] - pot[leader(a)]\n        T potential(int a) {\n\
    \            leader(a);\n            return diff_weight[a];\n        }\n    \n\
    \        // pot[b] - pot[a]\n        T diff(int a, int b) {\n            // \u547C\
    \u3073\u51FA\u3057\u5074\u3067 same(a,b) \u3092\u4FDD\u8A3C\uFF08ACL dsu \u3068\
    \u540C\u69D8\u306B\u672A\u5B9A\u7FA9\u6271\u3044\uFF09\n            return potential(b)\
    \ - potential(a);\n        }\n    \n        // pot[b] - pot[a] = w \u3092\u8FFD\
    \u52A0\u3057\u3066\u30DE\u30FC\u30B8\uFF08ACL dsu \u3068\u540C\u3058\u304F leader\
    \ \u3092\u8FD4\u3059\uFF09\n        int merge(int a, int b, T w) {\n         \
    \   w += potential(a);\n            w -= potential(b);\n            int x = leader(a),\
    \ y = leader(b);\n            if (x == y) return x;\n    \n            // union\
    \ by size (ACL dsu \u98A8)\n            if (-parent_or_size[x] < -parent_or_size[y])\
    \ {\n                std::swap(x, y);\n                w = -w;\n            }\n\
    \    \n            parent_or_size[x] += parent_or_size[y];\n            parent_or_size[y]\
    \ = x;\n            diff_weight[y] = w; // pot[y] - pot[x] = w\n            return\
    \ x;\n        }\n    \n        std::vector<std::vector<int>> groups() {\n    \
    \        std::vector<int> leader_buf(n), group_size(n);\n            for (int\
    \ i = 0; i < n; i++) {\n                leader_buf[i] = leader(i);\n         \
    \       group_size[leader_buf[i]]++;\n            }\n            std::vector<std::vector<int>>\
    \ result(n);\n            for (int i = 0; i < n; i++) result[i].reserve(group_size[i]);\n\
    \            for (int i = 0; i < n; i++) result[leader_buf[i]].push_back(i);\n\
    \            result.erase(std::remove_if(result.begin(), result.end(),\n     \
    \                              [](const auto& v) { return v.empty(); }),\n   \
    \                      result.end());\n            return result;\n        }\n\
    \    };\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/potential_dsu.hpp
  requiredBy:
  - tests/test.cpp
  timestamp: '2026-08-04 23:10:17+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/unionfind.test.cpp
  - verify/unionfind_with_potential.test.cpp
documentation_of: ds/potential_dsu.hpp
layout: document
title: "\u30DD\u30C6\u30F3\u30B7\u30E3\u30EB\u4ED8\u304D Union-Find"
---

## 概要

`yesantikiss::potential_dsu<T>` は、連結成分と頂点間のポテンシャル差を管理する
Union-Find です。

## API

- `potential_dsu(n)`, `init(n)`: `n` 頂点で初期化します。
- `merge(a, b, w)`: 制約 `pot[b] - pot[a] = w` として成分を併合し、leader を返します。
- `diff(a, b)`: `pot[b] - pot[a]` を返します。
- `potential(a)`: `pot[a] - pot[leader(a)]` を返します。
- `leader(a)`, `same(a, b)`, `size(a)`, `groups()`: 通常の DSU 操作です。

## 要件・注意

- 頂点番号は `0 <= v < n` です。
- `diff(a, b)` は `same(a, b)` が真の場合だけ呼んでください。
- すでに同じ成分にある頂点へ `merge` しても、渡した制約の整合性は検査しません。
  必要なら事前に `diff(a, b) == w` を確認してください。
- `T` は零初期化、加算、減算、単項マイナスに対応する必要があります。

## 計算量

`groups()` 以外は償却 `O(alpha(N))`、`groups()` は `O(N)` です。メモリは
`O(N)` です。
