---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: tests/test.cpp
    title: tests/test.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/set_xor_min.test.cpp
    title: verify/set_xor_min.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"ds/binary_trie.hpp\"\n\n#include <cassert>\n#include <vector>\n\
    \nnamespace yesantikiss {\n    template<int B>\n    struct BinaryTrie {\n    \
    \    static_assert(0 < B && B <= 63);\n        using ull = unsigned long long;\n\
    \    \n        struct Node {\n            int ch[2];\n            long long cnt;\
    \ // subtree size (with multiplicity)\n            long long end; // exact value\
    \ count at leaf\n            Node() : ch{-1, -1}, cnt(0), end(0) {}\n        };\n\
    \    \n        std::vector<Node> tr;\n        BinaryTrie() { tr.emplace_back();\
    \ }\n    \n        long long size() const { return tr[0].cnt; }\n        bool\
    \ empty() const { return size() == 0; }\n    \n        void insert(ull x) { add_raw(x,\
    \ +1); }\n    \n        // erase one occurrence; returns false if not present\n\
    \        bool erase(ull x) {\n            if (count_raw(x) == 0) return false;\n\
    \            add_raw(x, -1);\n            return true;\n        }\n    \n    \
    \    // count/contains in {v xor T} multiset (T=0 => normal)\n        long long\
    \ count(ull v, ull T = 0) const { return count_raw(v ^ T); }\n        bool contains(ull\
    \ v, ull T = 0) const { return count(v, T) > 0; }\n    \n        // kth (0-index)\
    \ in sorted {x xor T}\n        ull kth(long long k, ull T = 0) const {\n     \
    \       assert(0 <= k && k < size());\n            int v = 0;\n            ull\
    \ y = 0;\n    \n            for (int b = B - 1; b >= 0; --b) {\n             \
    \   int tb = (T >> b) & 1ULL;\n                int pref = tb;      // ybit=0 needs\
    \ xbit=tb\n                int other = tb ^ 1;\n    \n                int vp =\
    \ tr[v].ch[pref];\n                long long cnt_pref = (vp == -1 ? 0 : tr[vp].cnt);\n\
    \    \n                if (k < cnt_pref) {\n                    v = vp; // ybit=0\n\
    \                    assert(v != -1);\n                } else {\n            \
    \        k -= cnt_pref;\n                    v = tr[v].ch[other]; // ybit=1\n\
    \                    assert(v != -1);\n                    y |= (1ULL << b);\n\
    \                }\n            }\n            return y;\n        }\n    \n  \
    \      ull min_element(ull T = 0) const {\n            assert(!empty());\n   \
    \         return kth(0, T);\n        }\n    \n        ull max_element(ull T =\
    \ 0) const {\n            assert(!empty());\n            return kth(size() - 1,\
    \ T);\n        }\n    \n    private:\n        void add_raw(ull x, long long delta)\
    \ {\n            int v = 0;\n            tr[v].cnt += delta;\n            for\
    \ (int b = B - 1; b >= 0; --b) {\n                int bit = (x >> b) & 1ULL;\n\
    \                if (tr[v].ch[bit] == -1) {\n                    tr[v].ch[bit]\
    \ = (int)tr.size();\n                    tr.emplace_back();\n                }\n\
    \                v = tr[v].ch[bit];\n                tr[v].cnt += delta;\n   \
    \         }\n            tr[v].end += delta;\n        }\n    \n        long long\
    \ count_raw(ull x) const {\n            int v = 0;\n            for (int b = B\
    \ - 1; b >= 0; --b) {\n                int bit = (x >> b) & 1ULL;\n          \
    \      v = tr[v].ch[bit];\n                if (v == -1) return 0;\n          \
    \  }\n            return tr[v].end;\n        }\n    };\n    \n    // usage example:\n\
    \    // using BT = BinaryTrie<30>; // for [0, 1e9]\n    \n}\n"
  code: "#pragma once\n\n#include <cassert>\n#include <vector>\n\nnamespace yesantikiss\
    \ {\n    template<int B>\n    struct BinaryTrie {\n        static_assert(0 < B\
    \ && B <= 63);\n        using ull = unsigned long long;\n    \n        struct\
    \ Node {\n            int ch[2];\n            long long cnt; // subtree size (with\
    \ multiplicity)\n            long long end; // exact value count at leaf\n   \
    \         Node() : ch{-1, -1}, cnt(0), end(0) {}\n        };\n    \n        std::vector<Node>\
    \ tr;\n        BinaryTrie() { tr.emplace_back(); }\n    \n        long long size()\
    \ const { return tr[0].cnt; }\n        bool empty() const { return size() == 0;\
    \ }\n    \n        void insert(ull x) { add_raw(x, +1); }\n    \n        // erase\
    \ one occurrence; returns false if not present\n        bool erase(ull x) {\n\
    \            if (count_raw(x) == 0) return false;\n            add_raw(x, -1);\n\
    \            return true;\n        }\n    \n        // count/contains in {v xor\
    \ T} multiset (T=0 => normal)\n        long long count(ull v, ull T = 0) const\
    \ { return count_raw(v ^ T); }\n        bool contains(ull v, ull T = 0) const\
    \ { return count(v, T) > 0; }\n    \n        // kth (0-index) in sorted {x xor\
    \ T}\n        ull kth(long long k, ull T = 0) const {\n            assert(0 <=\
    \ k && k < size());\n            int v = 0;\n            ull y = 0;\n    \n  \
    \          for (int b = B - 1; b >= 0; --b) {\n                int tb = (T >>\
    \ b) & 1ULL;\n                int pref = tb;      // ybit=0 needs xbit=tb\n  \
    \              int other = tb ^ 1;\n    \n                int vp = tr[v].ch[pref];\n\
    \                long long cnt_pref = (vp == -1 ? 0 : tr[vp].cnt);\n    \n   \
    \             if (k < cnt_pref) {\n                    v = vp; // ybit=0\n   \
    \                 assert(v != -1);\n                } else {\n               \
    \     k -= cnt_pref;\n                    v = tr[v].ch[other]; // ybit=1\n   \
    \                 assert(v != -1);\n                    y |= (1ULL << b);\n  \
    \              }\n            }\n            return y;\n        }\n    \n    \
    \    ull min_element(ull T = 0) const {\n            assert(!empty());\n     \
    \       return kth(0, T);\n        }\n    \n        ull max_element(ull T = 0)\
    \ const {\n            assert(!empty());\n            return kth(size() - 1, T);\n\
    \        }\n    \n    private:\n        void add_raw(ull x, long long delta) {\n\
    \            int v = 0;\n            tr[v].cnt += delta;\n            for (int\
    \ b = B - 1; b >= 0; --b) {\n                int bit = (x >> b) & 1ULL;\n    \
    \            if (tr[v].ch[bit] == -1) {\n                    tr[v].ch[bit] = (int)tr.size();\n\
    \                    tr.emplace_back();\n                }\n                v\
    \ = tr[v].ch[bit];\n                tr[v].cnt += delta;\n            }\n     \
    \       tr[v].end += delta;\n        }\n    \n        long long count_raw(ull\
    \ x) const {\n            int v = 0;\n            for (int b = B - 1; b >= 0;\
    \ --b) {\n                int bit = (x >> b) & 1ULL;\n                v = tr[v].ch[bit];\n\
    \                if (v == -1) return 0;\n            }\n            return tr[v].end;\n\
    \        }\n    };\n    \n    // usage example:\n    // using BT = BinaryTrie<30>;\
    \ // for [0, 1e9]\n    \n}\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/binary_trie.hpp
  requiredBy:
  - tests/test.cpp
  timestamp: '2026-10-08 13:39:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/set_xor_min.test.cpp
documentation_of: ds/binary_trie.hpp
layout: document
title: Binary Trie
---

## 概要

`yesantikiss::BinaryTrie<B>` は、`B` ビット非負整数の多重集合です。
全要素に XOR を適用したとみなした順序統計も取得できます。

## API

- `insert(x)`: `x` を一つ追加します。
- `erase(x)`: `x` を一つ削除し、存在したかを返します。
- `count(v, T)`, `contains(v, T)`: 多重集合 `{x xor T}` に含まれる
  `v` の個数・有無を返します。`T` の既定値は `0` です。
- `kth(k, T)`: `{x xor T}` を昇順に並べた 0-indexed の `k` 番目を返します。
- `min_element(T)`, `max_element(T)`: 変換後の最小値・最大値を返します。
- `size()`, `empty()`: 重複を含む要素数・空判定です。

## 要件・注意

- `1 <= B <= 63` が必要です。
- 格納する値と XOR マスクは `B` ビット以内、すなわち
  `0 <= x, T < 2^B` としてください。上位ビットは区別されません。
- `kth` は `0 <= k < size()`、最小値・最大値の取得は非空の場合に限ります。
- 削除後も内部ノードは解放されません。

## 計算量

各更新・検索・順序統計は `O(B)`、メモリは追加した相異なるビット列の
Trie ノード数に比例します。
