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
  bundledCode: "#line 2 \"ds/persistent_segtree.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace yesantikiss {\n    template<class\
    \ S, S (*op)(S, S), S (*e)()>\n    struct persistent_segtree {\n        struct\
    \ Node {\n            S val;\n            int lch, rch;\n        };\n    \n  \
    \      int n = 0;\n        std::vector<Node> nodes;\n        std::vector<int>\
    \ roots; // roots[version] = \u305D\u306E\u7248\u306E\u6839\u30CE\u30FC\u30C9\
    \ index\n    \n        persistent_segtree() = default;\n    \n        explicit\
    \ persistent_segtree(const std::vector<S>& a) {\n            init(a);\n      \
    \  }\n    \n        explicit persistent_segtree(int n_) {\n            init(std::vector<S>(n_,\
    \ e()));\n        }\n    \n        int new_node(const S& val, int lch = -1, int\
    \ rch = -1) {\n            nodes.push_back({val, lch, rch});\n            return\
    \ (int)nodes.size() - 1;\n        }\n    \n        int build(int l, int r, const\
    \ std::vector<S>& a) {\n            if (r - l == 1) {\n                return\
    \ new_node(a[l]);\n            }\n            int m = (l + r) >> 1;\n        \
    \    int lc = build(l, m, a);\n            int rc = build(m, r, a);\n        \
    \    return new_node(op(nodes[lc].val, nodes[rc].val), lc, rc);\n        }\n \
    \   \n        void init(const std::vector<S>& a) {\n            n = (int)a.size();\n\
    \            nodes.clear();\n            roots.clear();\n    \n            nodes.reserve(std::max(1,\
    \ 2 * n));\n    \n            if (n == 0) {\n                roots.push_back(-1);\
    \ // version 0 \u306F\u7A7A\u914D\u5217\u7248\n                return;\n     \
    \       }\n    \n            int root0 = build(0, n, a);\n            roots.push_back(root0);\
    \ // \u521D\u671F\u7248\u306E version \u306F 0\n        }\n    \n        int versions()\
    \ const {\n            return (int)roots.size();\n        }\n    \n        int\
    \ latest_version() const {\n            return (int)roots.size() - 1;\n      \
    \  }\n    \n        int normalize_version(int ver) const {\n            if (ver\
    \ == -1) return latest_version();\n            assert(0 <= ver && ver < (int)roots.size());\n\
    \            return ver;\n        }\n    \n        int set_rec(int node, int l,\
    \ int r, int p, const S& x) {\n            if (r - l == 1) {\n               \
    \ return new_node(x);\n            }\n    \n            int m = (l + r) >> 1;\n\
    \            int lc = nodes[node].lch;\n            int rc = nodes[node].rch;\n\
    \    \n            if (p < m) {\n                lc = set_rec(lc, l, m, p, x);\n\
    \            } else {\n                rc = set_rec(rc, m, r, p, x);\n       \
    \     }\n    \n            return new_node(op(nodes[lc].val, nodes[rc].val), lc,\
    \ rc);\n        }\n    \n        S get_rec(int node, int l, int r, int p) const\
    \ {\n            if (r - l == 1) {\n                return nodes[node].val;\n\
    \            }\n    \n            int m = (l + r) >> 1;\n            if (p < m)\
    \ return get_rec(nodes[node].lch, l, m, p);\n            return get_rec(nodes[node].rch,\
    \ m, r, p);\n        }\n    \n        S prod_rec(int node, int l, int r, int ql,\
    \ int qr) const {\n            if (qr <= l || r <= ql) return e();\n         \
    \   if (ql <= l && r <= qr) return nodes[node].val;\n    \n            int m =\
    \ (l + r) >> 1;\n            return op(\n                prod_rec(nodes[node].lch,\
    \ l, m, ql, qr),\n                prod_rec(nodes[node].rch, m, r, ql, qr)\n  \
    \          );\n        }\n    \n        // ver \u7248\u3092\u5143\u306B p \u756A\
    \u76EE\u3092 x \u306B\u5909\u66F4\u3057\u305F\u65B0\u3057\u3044\u7248\u3092\u672B\
    \u5C3E\u306B\u8FFD\u52A0\n        // ver = -1 \u306A\u3089\u6700\u65B0\u7248\u3092\
    \u5143\u306B\u3059\u308B\n        // \u8FD4\u308A\u5024\u306F\u65B0\u3057\u3044\
    \ version \u756A\u53F7\n        int set(int p, const S& x, int ver = -1) {\n \
    \           assert(0 <= p && p < n);\n            ver = normalize_version(ver);\n\
    \            int new_root = set_rec(roots[ver], 0, n, p, x);\n            roots.push_back(new_root);\n\
    \            return latest_version();\n        }\n    \n        S get(int p, int\
    \ ver = -1) const {\n            assert(0 <= p && p < n);\n            ver = normalize_version(ver);\n\
    \            return get_rec(roots[ver], 0, n, p);\n        }\n    \n        S\
    \ prod(int l, int r, int ver = -1) const {\n            assert(0 <= l && l <=\
    \ r && r <= n);\n            ver = normalize_version(ver);\n            if (n\
    \ == 0) return e();\n            return prod_rec(roots[ver], 0, n, l, r);\n  \
    \      }\n    \n        S all_prod(int ver = -1) const {\n            ver = normalize_version(ver);\n\
    \            if (n == 0) return e();\n            return nodes[roots[ver]].val;\n\
    \        }\n    };\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\
    \nnamespace yesantikiss {\n    template<class S, S (*op)(S, S), S (*e)()>\n  \
    \  struct persistent_segtree {\n        struct Node {\n            S val;\n  \
    \          int lch, rch;\n        };\n    \n        int n = 0;\n        std::vector<Node>\
    \ nodes;\n        std::vector<int> roots; // roots[version] = \u305D\u306E\u7248\
    \u306E\u6839\u30CE\u30FC\u30C9 index\n    \n        persistent_segtree() = default;\n\
    \    \n        explicit persistent_segtree(const std::vector<S>& a) {\n      \
    \      init(a);\n        }\n    \n        explicit persistent_segtree(int n_)\
    \ {\n            init(std::vector<S>(n_, e()));\n        }\n    \n        int\
    \ new_node(const S& val, int lch = -1, int rch = -1) {\n            nodes.push_back({val,\
    \ lch, rch});\n            return (int)nodes.size() - 1;\n        }\n    \n  \
    \      int build(int l, int r, const std::vector<S>& a) {\n            if (r -\
    \ l == 1) {\n                return new_node(a[l]);\n            }\n         \
    \   int m = (l + r) >> 1;\n            int lc = build(l, m, a);\n            int\
    \ rc = build(m, r, a);\n            return new_node(op(nodes[lc].val, nodes[rc].val),\
    \ lc, rc);\n        }\n    \n        void init(const std::vector<S>& a) {\n  \
    \          n = (int)a.size();\n            nodes.clear();\n            roots.clear();\n\
    \    \n            nodes.reserve(std::max(1, 2 * n));\n    \n            if (n\
    \ == 0) {\n                roots.push_back(-1); // version 0 \u306F\u7A7A\u914D\
    \u5217\u7248\n                return;\n            }\n    \n            int root0\
    \ = build(0, n, a);\n            roots.push_back(root0); // \u521D\u671F\u7248\
    \u306E version \u306F 0\n        }\n    \n        int versions() const {\n   \
    \         return (int)roots.size();\n        }\n    \n        int latest_version()\
    \ const {\n            return (int)roots.size() - 1;\n        }\n    \n      \
    \  int normalize_version(int ver) const {\n            if (ver == -1) return latest_version();\n\
    \            assert(0 <= ver && ver < (int)roots.size());\n            return\
    \ ver;\n        }\n    \n        int set_rec(int node, int l, int r, int p, const\
    \ S& x) {\n            if (r - l == 1) {\n                return new_node(x);\n\
    \            }\n    \n            int m = (l + r) >> 1;\n            int lc =\
    \ nodes[node].lch;\n            int rc = nodes[node].rch;\n    \n            if\
    \ (p < m) {\n                lc = set_rec(lc, l, m, p, x);\n            } else\
    \ {\n                rc = set_rec(rc, m, r, p, x);\n            }\n    \n    \
    \        return new_node(op(nodes[lc].val, nodes[rc].val), lc, rc);\n        }\n\
    \    \n        S get_rec(int node, int l, int r, int p) const {\n            if\
    \ (r - l == 1) {\n                return nodes[node].val;\n            }\n   \
    \ \n            int m = (l + r) >> 1;\n            if (p < m) return get_rec(nodes[node].lch,\
    \ l, m, p);\n            return get_rec(nodes[node].rch, m, r, p);\n        }\n\
    \    \n        S prod_rec(int node, int l, int r, int ql, int qr) const {\n  \
    \          if (qr <= l || r <= ql) return e();\n            if (ql <= l && r <=\
    \ qr) return nodes[node].val;\n    \n            int m = (l + r) >> 1;\n     \
    \       return op(\n                prod_rec(nodes[node].lch, l, m, ql, qr),\n\
    \                prod_rec(nodes[node].rch, m, r, ql, qr)\n            );\n   \
    \     }\n    \n        // ver \u7248\u3092\u5143\u306B p \u756A\u76EE\u3092 x\
    \ \u306B\u5909\u66F4\u3057\u305F\u65B0\u3057\u3044\u7248\u3092\u672B\u5C3E\u306B\
    \u8FFD\u52A0\n        // ver = -1 \u306A\u3089\u6700\u65B0\u7248\u3092\u5143\u306B\
    \u3059\u308B\n        // \u8FD4\u308A\u5024\u306F\u65B0\u3057\u3044 version \u756A\
    \u53F7\n        int set(int p, const S& x, int ver = -1) {\n            assert(0\
    \ <= p && p < n);\n            ver = normalize_version(ver);\n            int\
    \ new_root = set_rec(roots[ver], 0, n, p, x);\n            roots.push_back(new_root);\n\
    \            return latest_version();\n        }\n    \n        S get(int p, int\
    \ ver = -1) const {\n            assert(0 <= p && p < n);\n            ver = normalize_version(ver);\n\
    \            return get_rec(roots[ver], 0, n, p);\n        }\n    \n        S\
    \ prod(int l, int r, int ver = -1) const {\n            assert(0 <= l && l <=\
    \ r && r <= n);\n            ver = normalize_version(ver);\n            if (n\
    \ == 0) return e();\n            return prod_rec(roots[ver], 0, n, l, r);\n  \
    \      }\n    \n        S all_prod(int ver = -1) const {\n            ver = normalize_version(ver);\n\
    \            if (n == 0) return e();\n            return nodes[roots[ver]].val;\n\
    \        }\n    };\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/persistent_segtree.hpp
  requiredBy:
  - tests/test.cpp
  timestamp: '2026-08-25 15:58:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: ds/persistent_segtree.hpp
layout: document
title: "\u6C38\u7D9A\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---

## 概要

`yesantikiss::persistent_segtree<S, op, e>` は、一点更新のたびに新しい版を作る
完全永続セグメント木です。古い版への参照と、古い版からの分岐更新ができます。

## API

- `persistent_segtree(a)`: 配列 `a` を version `0` として構築します。
- `persistent_segtree(n)`: `e()` が `n` 個並んだ version `0` を構築します。
- `set(p, x, ver)`: `ver` の点 `p` を更新した版を末尾に追加し、版番号を返します。
- `get(p, ver)`, `prod(l, r, ver)`, `all_prod(ver)`: 指定版を参照します。
- `versions()`, `latest_version()`: 版数・最新版の番号を返します。

`ver = -1` は最新版を表します。

## 要件・注意

- `op` は結合的で、`e()` はその単位元である必要があります。
- `0 <= p < n`、区間は 0-indexed の `0 <= l <= r <= n` です。
- 版番号は `0 <= ver < versions()` または `-1` を指定してください。
- 空配列でも version `0` は存在し、区間積と全体積は `e()` です。点操作は
  できません。

## 計算量

初期構築は `O(N)` 時間・メモリ、一点更新と区間積は `O(log N)` です。
一点更新ごとに `O(log N)` 個のノードを追加します。
