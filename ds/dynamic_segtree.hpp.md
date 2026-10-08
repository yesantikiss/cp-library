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
  bundledCode: "#line 2 \"ds/dynamic_segtree.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstddef>\n#include <vector>\n\n// \u52D5\u7684\uFF08implicit\uFF09\
    \u30BB\u30B0\u30E1\u30F3\u30C8\u6728\n// - \u533A\u9593 [0, n) \u3092\u6271\u3046\
    \n// - \u66F4\u65B0\u304C\u5165\u3063\u305F\u7D4C\u8DEF\u3060\u3051\u30CE\u30FC\
    \u30C9\u751F\u6210\n// - ACL segtree \u98A8\u30A4\u30F3\u30BF\u30D5\u30A7\u30FC\
    \u30B9\n\nnamespace yesantikiss {\n    // \u52D5\u7684\uFF08implicit\uFF09\u30BB\
    \u30B0\u30E1\u30F3\u30C8\u6728\n    // - \u533A\u9593 [0, n) \u3092\u6271\u3046\
    \n    // - \u66F4\u65B0\u304C\u5165\u3063\u305F\u7D4C\u8DEF\u3060\u3051\u30CE\u30FC\
    \u30C9\u751F\u6210\n    // - ACL segtree \u98A8\u30A4\u30F3\u30BF\u30D5\u30A7\u30FC\
    \u30B9\n    \n    template <class S, S (*op)(S, S), S (*e)()>\n    struct dynamic_segtree\
    \ {\n    private:\n        struct Node {\n            int l = -1, r = -1;\n  \
    \          S val;\n            Node() : val(e()) {}\n        };\n    \n      \
    \  long long n_ = 0;\n        unsigned long long size_ = 1;\n        int root_\
    \ = -1;\n        std::vector<Node> pool_;\n    \n        static unsigned long\
    \ long ceil_pow2_ull(unsigned long long x) {\n            unsigned long long p\
    \ = 1;\n            while (p < x) p <<= 1;\n            return p;\n        }\n\
    \    \n        int new_node() {\n            pool_.emplace_back();\n         \
    \   return (int)pool_.size() - 1;\n        }\n    \n        S node_val(int idx)\
    \ const {\n            return (idx == -1) ? e() : pool_[idx].val;\n        }\n\
    \    \n        S prod_rec(int idx,\n                   unsigned long long segL,\
    \ unsigned long long segR,\n                   unsigned long long ql, unsigned\
    \ long long qr) const {\n            if (idx == -1) return e();\n            if\
    \ (qr <= segL || segR <= ql) return e();\n            if (ql <= segL && segR <=\
    \ qr) return pool_[idx].val;\n            unsigned long long mid = (segL + segR)\
    \ >> 1;\n            S left = prod_rec(pool_[idx].l, segL, mid, ql, qr);\n   \
    \         S right = prod_rec(pool_[idx].r, mid, segR, ql, qr);\n            return\
    \ op(left, right);\n        }\n    \n        template <class F>\n        long\
    \ long max_right_rec(int idx,\n                                unsigned long long\
    \ segL, unsigned long long segR,\n                                unsigned long\
    \ long ql,\n                                F& f, S& sm) const {\n           \
    \ if (segR <= ql) return (long long)ql;\n            S segVal = (idx == -1) ?\
    \ e() : pool_[idx].val;\n            if (segL >= ql) {\n                S nxt\
    \ = op(sm, segVal);\n                if (f(nxt)) {\n                    sm = nxt;\n\
    \                    return (long long)segR;\n                }\n            \
    \    if (segR - segL == 1) return (long long)segL;\n            }\n          \
    \  unsigned long long mid = (segL + segR) >> 1;\n            int lch = (idx ==\
    \ -1) ? -1 : pool_[idx].l;\n            int rch = (idx == -1) ? -1 : pool_[idx].r;\n\
    \            long long resL = max_right_rec(lch, segL, mid, ql, f, sm);\n    \
    \        if ((unsigned long long)resL < mid) return resL;\n            return\
    \ max_right_rec(rch, mid, segR, ql, f, sm);\n        }\n    \n        template\
    \ <class F>\n        long long min_left_rec(int idx,\n                       \
    \        unsigned long long segL, unsigned long long segR,\n                 \
    \              unsigned long long qr,\n                               F& f, S&\
    \ sm) const {\n            if (qr <= segL) return (long long)qr;\n           \
    \ S segVal = (idx == -1) ? e() : pool_[idx].val;\n            if (segR <= qr)\
    \ {\n                S nxt = op(segVal, sm);\n                if (f(nxt)) {\n\
    \                    sm = nxt;\n                    return (long long)segL;\n\
    \                }\n                if (segR - segL == 1) return (long long)segR;\n\
    \            }\n            unsigned long long mid = (segL + segR) >> 1;\n   \
    \         int lch = (idx == -1) ? -1 : pool_[idx].l;\n            int rch = (idx\
    \ == -1) ? -1 : pool_[idx].r;\n            long long resR = min_left_rec(rch,\
    \ mid, segR, qr, f, sm);\n            if ((unsigned long long)resR > mid) return\
    \ resR;\n            return min_left_rec(lch, segL, mid, qr, f, sm);\n       \
    \ }\n    \n        template <bool APPLY>\n        void point_update(long long\
    \ p, const S& x) {\n            assert(0 <= p && p < n_);\n            if (root_\
    \ == -1) root_ = new_node();\n            int idx = root_;\n            unsigned\
    \ long long segL = 0, segR = size_;\n            int path[70];\n            int\
    \ psz = 0;\n            path[psz++] = idx;\n            while (segR - segL > 1)\
    \ {\n                unsigned long long mid = (segL + segR) >> 1;\n          \
    \      if ((unsigned long long)p < mid) {\n                    if (pool_[idx].l\
    \ == -1) {\n                        int child = new_node();\n                \
    \        pool_[idx].l = child;\n                    }\n                    idx\
    \ = pool_[idx].l;\n                    segR = mid;\n                } else {\n\
    \                    if (pool_[idx].r == -1) {\n                        int child\
    \ = new_node();\n                        pool_[idx].r = child;\n             \
    \       }\n                    idx = pool_[idx].r;\n                    segL =\
    \ mid;\n                }\n                path[psz++] = idx;\n            }\n\
    \            if constexpr (APPLY) {\n                pool_[idx].val = op(pool_[idx].val,\
    \ x);\n            } else {\n                pool_[idx].val = x;\n           \
    \ }\n            for (int i = psz - 2; i >= 0; --i) {\n                int v =\
    \ path[i];\n                pool_[v].val = op(node_val(pool_[v].l), node_val(pool_[v].r));\n\
    \            }\n        }\n    \n    public:\n        dynamic_segtree() = default;\n\
    \        explicit dynamic_segtree(long long n) { init(n); }\n    \n        void\
    \ init(long long n) {\n            assert(n >= 0);\n            n_ = n;\n    \
    \        size_ = ceil_pow2_ull((unsigned long long)std::max(1LL, n_));\n     \
    \       root_ = -1;\n            pool_.clear();\n        }\n    \n        void\
    \ reserve_nodes(std::size_t m) { pool_.reserve(m); }\n    \n        long long\
    \ size() const { return n_; }\n    \n        S all_prod() const {\n          \
    \  return (root_ == -1) ? e() : pool_[root_].val;\n        }\n    \n        S\
    \ get(long long p) const {\n            assert(0 <= p && p < n_);\n          \
    \  int idx = root_;\n            if (idx == -1) return e();\n            unsigned\
    \ long long segL = 0, segR = size_;\n            while (segR - segL > 1 && idx\
    \ != -1) {\n                unsigned long long mid = (segL + segR) >> 1;\n   \
    \             if ((unsigned long long)p < mid) {\n                    idx = pool_[idx].l;\n\
    \                    segR = mid;\n                } else {\n                 \
    \   idx = pool_[idx].r;\n                    segL = mid;\n                }\n\
    \            }\n            return (idx == -1) ? e() : pool_[idx].val;\n     \
    \   }\n    \n        void set(long long p, S x) { point_update<false>(p, x); }\n\
    \        void apply_point(long long p, S x) { point_update<true>(p, x); }\n  \
    \  \n        S prod(long long l, long long r) const {\n            assert(0 <=\
    \ l && l <= r && r <= n_);\n            if (l == r) return e();\n            if\
    \ (root_ == -1) return e();\n            return prod_rec(root_, 0, size_,\n  \
    \                          (unsigned long long)l, (unsigned long long)r);\n  \
    \      }\n    \n        template <class F>\n        long long max_right(long long\
    \ l, F f) const {\n            assert(0 <= l && l <= n_);\n            assert(f(e()));\n\
    \            if (l == n_) return n_;\n            S sm = e();\n            F ff\
    \ = f;\n            long long res = max_right_rec(root_, 0, size_, (unsigned long\
    \ long)l, ff, sm);\n            if (res > n_) res = n_;\n            return res;\n\
    \        }\n    \n        template <class F>\n        long long min_left(long\
    \ long r, F f) const {\n            assert(0 <= r && r <= n_);\n            assert(f(e()));\n\
    \            if (r == 0) return 0;\n            S sm = e();\n            F ff\
    \ = f;\n            long long res = min_left_rec(root_, 0, size_, (unsigned long\
    \ long)r, ff, sm);\n            if (res < 0) res = 0;\n            if (res > r)\
    \ res = r;\n            return res;\n        }\n    };\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <cstddef>\n\
    #include <vector>\n\n// \u52D5\u7684\uFF08implicit\uFF09\u30BB\u30B0\u30E1\u30F3\
    \u30C8\u6728\n// - \u533A\u9593 [0, n) \u3092\u6271\u3046\n// - \u66F4\u65B0\u304C\
    \u5165\u3063\u305F\u7D4C\u8DEF\u3060\u3051\u30CE\u30FC\u30C9\u751F\u6210\n// -\
    \ ACL segtree \u98A8\u30A4\u30F3\u30BF\u30D5\u30A7\u30FC\u30B9\n\nnamespace yesantikiss\
    \ {\n    // \u52D5\u7684\uFF08implicit\uFF09\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\
    \n    // - \u533A\u9593 [0, n) \u3092\u6271\u3046\n    // - \u66F4\u65B0\u304C\
    \u5165\u3063\u305F\u7D4C\u8DEF\u3060\u3051\u30CE\u30FC\u30C9\u751F\u6210\n   \
    \ // - ACL segtree \u98A8\u30A4\u30F3\u30BF\u30D5\u30A7\u30FC\u30B9\n    \n  \
    \  template <class S, S (*op)(S, S), S (*e)()>\n    struct dynamic_segtree {\n\
    \    private:\n        struct Node {\n            int l = -1, r = -1;\n      \
    \      S val;\n            Node() : val(e()) {}\n        };\n    \n        long\
    \ long n_ = 0;\n        unsigned long long size_ = 1;\n        int root_ = -1;\n\
    \        std::vector<Node> pool_;\n    \n        static unsigned long long ceil_pow2_ull(unsigned\
    \ long long x) {\n            unsigned long long p = 1;\n            while (p\
    \ < x) p <<= 1;\n            return p;\n        }\n    \n        int new_node()\
    \ {\n            pool_.emplace_back();\n            return (int)pool_.size() -\
    \ 1;\n        }\n    \n        S node_val(int idx) const {\n            return\
    \ (idx == -1) ? e() : pool_[idx].val;\n        }\n    \n        S prod_rec(int\
    \ idx,\n                   unsigned long long segL, unsigned long long segR,\n\
    \                   unsigned long long ql, unsigned long long qr) const {\n  \
    \          if (idx == -1) return e();\n            if (qr <= segL || segR <= ql)\
    \ return e();\n            if (ql <= segL && segR <= qr) return pool_[idx].val;\n\
    \            unsigned long long mid = (segL + segR) >> 1;\n            S left\
    \ = prod_rec(pool_[idx].l, segL, mid, ql, qr);\n            S right = prod_rec(pool_[idx].r,\
    \ mid, segR, ql, qr);\n            return op(left, right);\n        }\n    \n\
    \        template <class F>\n        long long max_right_rec(int idx,\n      \
    \                          unsigned long long segL, unsigned long long segR,\n\
    \                                unsigned long long ql,\n                    \
    \            F& f, S& sm) const {\n            if (segR <= ql) return (long long)ql;\n\
    \            S segVal = (idx == -1) ? e() : pool_[idx].val;\n            if (segL\
    \ >= ql) {\n                S nxt = op(sm, segVal);\n                if (f(nxt))\
    \ {\n                    sm = nxt;\n                    return (long long)segR;\n\
    \                }\n                if (segR - segL == 1) return (long long)segL;\n\
    \            }\n            unsigned long long mid = (segL + segR) >> 1;\n   \
    \         int lch = (idx == -1) ? -1 : pool_[idx].l;\n            int rch = (idx\
    \ == -1) ? -1 : pool_[idx].r;\n            long long resL = max_right_rec(lch,\
    \ segL, mid, ql, f, sm);\n            if ((unsigned long long)resL < mid) return\
    \ resL;\n            return max_right_rec(rch, mid, segR, ql, f, sm);\n      \
    \  }\n    \n        template <class F>\n        long long min_left_rec(int idx,\n\
    \                               unsigned long long segL, unsigned long long segR,\n\
    \                               unsigned long long qr,\n                     \
    \          F& f, S& sm) const {\n            if (qr <= segL) return (long long)qr;\n\
    \            S segVal = (idx == -1) ? e() : pool_[idx].val;\n            if (segR\
    \ <= qr) {\n                S nxt = op(segVal, sm);\n                if (f(nxt))\
    \ {\n                    sm = nxt;\n                    return (long long)segL;\n\
    \                }\n                if (segR - segL == 1) return (long long)segR;\n\
    \            }\n            unsigned long long mid = (segL + segR) >> 1;\n   \
    \         int lch = (idx == -1) ? -1 : pool_[idx].l;\n            int rch = (idx\
    \ == -1) ? -1 : pool_[idx].r;\n            long long resR = min_left_rec(rch,\
    \ mid, segR, qr, f, sm);\n            if ((unsigned long long)resR > mid) return\
    \ resR;\n            return min_left_rec(lch, segL, mid, qr, f, sm);\n       \
    \ }\n    \n        template <bool APPLY>\n        void point_update(long long\
    \ p, const S& x) {\n            assert(0 <= p && p < n_);\n            if (root_\
    \ == -1) root_ = new_node();\n            int idx = root_;\n            unsigned\
    \ long long segL = 0, segR = size_;\n            int path[70];\n            int\
    \ psz = 0;\n            path[psz++] = idx;\n            while (segR - segL > 1)\
    \ {\n                unsigned long long mid = (segL + segR) >> 1;\n          \
    \      if ((unsigned long long)p < mid) {\n                    if (pool_[idx].l\
    \ == -1) {\n                        int child = new_node();\n                \
    \        pool_[idx].l = child;\n                    }\n                    idx\
    \ = pool_[idx].l;\n                    segR = mid;\n                } else {\n\
    \                    if (pool_[idx].r == -1) {\n                        int child\
    \ = new_node();\n                        pool_[idx].r = child;\n             \
    \       }\n                    idx = pool_[idx].r;\n                    segL =\
    \ mid;\n                }\n                path[psz++] = idx;\n            }\n\
    \            if constexpr (APPLY) {\n                pool_[idx].val = op(pool_[idx].val,\
    \ x);\n            } else {\n                pool_[idx].val = x;\n           \
    \ }\n            for (int i = psz - 2; i >= 0; --i) {\n                int v =\
    \ path[i];\n                pool_[v].val = op(node_val(pool_[v].l), node_val(pool_[v].r));\n\
    \            }\n        }\n    \n    public:\n        dynamic_segtree() = default;\n\
    \        explicit dynamic_segtree(long long n) { init(n); }\n    \n        void\
    \ init(long long n) {\n            assert(n >= 0);\n            n_ = n;\n    \
    \        size_ = ceil_pow2_ull((unsigned long long)std::max(1LL, n_));\n     \
    \       root_ = -1;\n            pool_.clear();\n        }\n    \n        void\
    \ reserve_nodes(std::size_t m) { pool_.reserve(m); }\n    \n        long long\
    \ size() const { return n_; }\n    \n        S all_prod() const {\n          \
    \  return (root_ == -1) ? e() : pool_[root_].val;\n        }\n    \n        S\
    \ get(long long p) const {\n            assert(0 <= p && p < n_);\n          \
    \  int idx = root_;\n            if (idx == -1) return e();\n            unsigned\
    \ long long segL = 0, segR = size_;\n            while (segR - segL > 1 && idx\
    \ != -1) {\n                unsigned long long mid = (segL + segR) >> 1;\n   \
    \             if ((unsigned long long)p < mid) {\n                    idx = pool_[idx].l;\n\
    \                    segR = mid;\n                } else {\n                 \
    \   idx = pool_[idx].r;\n                    segL = mid;\n                }\n\
    \            }\n            return (idx == -1) ? e() : pool_[idx].val;\n     \
    \   }\n    \n        void set(long long p, S x) { point_update<false>(p, x); }\n\
    \        void apply_point(long long p, S x) { point_update<true>(p, x); }\n  \
    \  \n        S prod(long long l, long long r) const {\n            assert(0 <=\
    \ l && l <= r && r <= n_);\n            if (l == r) return e();\n            if\
    \ (root_ == -1) return e();\n            return prod_rec(root_, 0, size_,\n  \
    \                          (unsigned long long)l, (unsigned long long)r);\n  \
    \      }\n    \n        template <class F>\n        long long max_right(long long\
    \ l, F f) const {\n            assert(0 <= l && l <= n_);\n            assert(f(e()));\n\
    \            if (l == n_) return n_;\n            S sm = e();\n            F ff\
    \ = f;\n            long long res = max_right_rec(root_, 0, size_, (unsigned long\
    \ long)l, ff, sm);\n            if (res > n_) res = n_;\n            return res;\n\
    \        }\n    \n        template <class F>\n        long long min_left(long\
    \ long r, F f) const {\n            assert(0 <= r && r <= n_);\n            assert(f(e()));\n\
    \            if (r == 0) return 0;\n            S sm = e();\n            F ff\
    \ = f;\n            long long res = min_left_rec(root_, 0, size_, (unsigned long\
    \ long)r, ff, sm);\n            if (res < 0) res = 0;\n            if (res > r)\
    \ res = r;\n            return res;\n        }\n    };\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/dynamic_segtree.hpp
  requiredBy:
  - tests/test.cpp
  timestamp: '2026-10-08 13:39:00+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: ds/dynamic_segtree.hpp
layout: document
title: "\u52D5\u7684\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---

## 概要

`yesantikiss::dynamic_segtree<S, op, e>` は、更新された点へ至る経路だけを
生成する動的（implicit）セグメント木です。巨大で疎な添字範囲 `[0, n)` を
扱えます。

## API

- `dynamic_segtree(n)`, `init(n)`: 長さ `n` で初期化します。全要素は `e()` です。
- `reserve_nodes(m)`: 内部ノード領域を予約します。
- `set(p, x)`: 点 `p` を `x` に置き換えます。
- `apply_point(p, x)`: 点 `p` を `op(get(p), x)` に更新します。
- `get(p)`, `prod(l, r)`, `all_prod()`: 点、半開区間、全体の積を返します。
- `max_right(l, f)`, `min_left(r, f)`: ACL の `segtree` と同様の境界探索です。

## 要件・注意

- `op` は結合的で、`e()` はその単位元である必要があります。
- `0 <= p < n`、区間は `0 <= l <= r <= n` を満たしてください。
- 境界探索では `f(e()) == true` が必要です。また、正しい境界を得るには
  `f` が探索方向に対して単調で、副作用を持たない必要があります。
- 未更新の点は `e()` として扱われます。

## 計算量

点操作・区間積・境界探索は `O(log n)` です。点更新一回につき最大
`O(log n)` 個のノードを追加します。
