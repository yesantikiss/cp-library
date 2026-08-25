---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: tests/rolling_hash_tu.cpp
    title: tests/rolling_hash_tu.cpp
  - icon: ':warning:'
    path: tests/test.cpp
    title: tests/test.cpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"string/rolling_hash.hpp\"\n\n#include <cassert>\n#include\
    \ <random>\n#include <string>\n#include <vector>\n\nnamespace yesantikiss {\n\
    \    struct RollingHash {\n        using ull = unsigned long long;\n        static\
    \ constexpr ull MOD = (1ULL << 61) - 1;\n    \n        // \u5171\u6709\u8CC7\u6E90\
    \uFF08\u5168\u30A4\u30F3\u30B9\u30BF\u30F3\u30B9\u3067\u5171\u901A\uFF09\n   \
    \     inline static ull base = 0;\n        inline static std::vector<ull> pow_base;\n\
    \    \n        std::vector<ull> hash;  // hash[i] = S[0..i) \u306E\u30CF\u30C3\
    \u30B7\u30E5\n        int n = 0;\n    \n        // 2^61-1 \u7528\u306E\u6F14\u7B97\
    \n        static inline ull add(ull a, ull b) {\n            ull c = a + b;\n\
    \            if (c >= MOD) c -= MOD;\n            return c;\n        }\n     \
    \   static inline ull mul(ull a, ull b) {\n            __int128 t = (__int128)a\
    \ * b;\n            t = (t >> 61) + (t & MOD);\n            if (t >= MOD) t -=\
    \ MOD;\n            return (ull)t;\n        }\n    \n        static void init_base()\
    \ {\n            if (base != 0) return;\n            std::mt19937_64 rng(std::random_device{}());\n\
    \            std::uniform_int_distribution<ull> dist(1ULL, MOD - 1);\n       \
    \     base = dist(rng);\n            pow_base = {1};  // pow_base[0] = 1\n   \
    \     }\n    \n        static void ensure_pow(int len) {\n            if ((int)pow_base.size()\
    \ >= len + 1) return;\n            int cur = (int)pow_base.size();\n         \
    \   pow_base.resize(len + 1);\n            for (int i = cur; i <= len; ++i) {\n\
    \                pow_base[i] = mul(pow_base[i - 1], base);\n            }\n  \
    \      }\n    \n        RollingHash() : n(0) {}\n    \n        RollingHash(const\
    \ std::string &s) {\n            build(s);\n        }\n    \n        void build(const\
    \ std::string &s) {\n            init_base();\n            n = (int)s.size();\n\
    \            ensure_pow(n);\n            hash.assign(n + 1, 0);\n            for\
    \ (int i = 0; i < n; ++i) {\n                hash[i + 1] = add(mul(hash[i], base),\
    \ (ull)(unsigned char)s[i] + 1);\n            }\n        }\n    \n        // S[l..r)\
    \ \u306E\u30CF\u30C3\u30B7\u30E5\u3092\u53D6\u5F97\n        ull get(int l, int\
    \ r) const {\n            assert(0 <= l && l <= r && r <= n);\n            ull\
    \ res = hash[r] + MOD - mul(hash[l], pow_base[r - l]);\n            if (res >=\
    \ MOD) res -= MOD;\n            return res;\n        }\n    \n        // \u540C\
    \u3058\u6587\u5B57\u5217\u306E\u4E2D\u3067\u90E8\u5206\u6587\u5B57\u5217\u304C\
    \u7B49\u3057\u3044\u304B\n        bool equals(int l1, int r1, int l2, int r2)\
    \ const {\n            if (r1 - l1 != r2 - l2) return false;\n            return\
    \ get(l1, r1) == get(l2, r2);\n        }\n    };\n    \n}\n"
  code: "#pragma once\n\n#include <cassert>\n#include <random>\n#include <string>\n\
    #include <vector>\n\nnamespace yesantikiss {\n    struct RollingHash {\n     \
    \   using ull = unsigned long long;\n        static constexpr ull MOD = (1ULL\
    \ << 61) - 1;\n    \n        // \u5171\u6709\u8CC7\u6E90\uFF08\u5168\u30A4\u30F3\
    \u30B9\u30BF\u30F3\u30B9\u3067\u5171\u901A\uFF09\n        inline static ull base\
    \ = 0;\n        inline static std::vector<ull> pow_base;\n    \n        std::vector<ull>\
    \ hash;  // hash[i] = S[0..i) \u306E\u30CF\u30C3\u30B7\u30E5\n        int n =\
    \ 0;\n    \n        // 2^61-1 \u7528\u306E\u6F14\u7B97\n        static inline\
    \ ull add(ull a, ull b) {\n            ull c = a + b;\n            if (c >= MOD)\
    \ c -= MOD;\n            return c;\n        }\n        static inline ull mul(ull\
    \ a, ull b) {\n            __int128 t = (__int128)a * b;\n            t = (t >>\
    \ 61) + (t & MOD);\n            if (t >= MOD) t -= MOD;\n            return (ull)t;\n\
    \        }\n    \n        static void init_base() {\n            if (base != 0)\
    \ return;\n            std::mt19937_64 rng(std::random_device{}());\n        \
    \    std::uniform_int_distribution<ull> dist(1ULL, MOD - 1);\n            base\
    \ = dist(rng);\n            pow_base = {1};  // pow_base[0] = 1\n        }\n \
    \   \n        static void ensure_pow(int len) {\n            if ((int)pow_base.size()\
    \ >= len + 1) return;\n            int cur = (int)pow_base.size();\n         \
    \   pow_base.resize(len + 1);\n            for (int i = cur; i <= len; ++i) {\n\
    \                pow_base[i] = mul(pow_base[i - 1], base);\n            }\n  \
    \      }\n    \n        RollingHash() : n(0) {}\n    \n        RollingHash(const\
    \ std::string &s) {\n            build(s);\n        }\n    \n        void build(const\
    \ std::string &s) {\n            init_base();\n            n = (int)s.size();\n\
    \            ensure_pow(n);\n            hash.assign(n + 1, 0);\n            for\
    \ (int i = 0; i < n; ++i) {\n                hash[i + 1] = add(mul(hash[i], base),\
    \ (ull)(unsigned char)s[i] + 1);\n            }\n        }\n    \n        // S[l..r)\
    \ \u306E\u30CF\u30C3\u30B7\u30E5\u3092\u53D6\u5F97\n        ull get(int l, int\
    \ r) const {\n            assert(0 <= l && l <= r && r <= n);\n            ull\
    \ res = hash[r] + MOD - mul(hash[l], pow_base[r - l]);\n            if (res >=\
    \ MOD) res -= MOD;\n            return res;\n        }\n    \n        // \u540C\
    \u3058\u6587\u5B57\u5217\u306E\u4E2D\u3067\u90E8\u5206\u6587\u5B57\u5217\u304C\
    \u7B49\u3057\u3044\u304B\n        bool equals(int l1, int r1, int l2, int r2)\
    \ const {\n            if (r1 - l1 != r2 - l2) return false;\n            return\
    \ get(l1, r1) == get(l2, r2);\n        }\n    };\n    \n}\n"
  dependsOn: []
  isVerificationFile: false
  path: string/rolling_hash.hpp
  requiredBy:
  - tests/test.cpp
  - tests/rolling_hash_tu.cpp
  timestamp: '2026-08-25 15:58:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: string/rolling_hash.hpp
layout: document
title: Rolling Hash
---

## 概要

`yesantikiss::RollingHash` は法 `2^61 - 1` の文字列用ローリングハッシュです。
基数はプロセスごとにランダムに選ばれ、全インスタンスで共有されます。

## API

- `RollingHash(s)`, `build(s)`: 文字列の prefix hash を構築します。
- `get(l, r)`: 半開区間 `s[l, r)` のハッシュを返します。
- `equals(l1, r1, l2, r2)`: 同じ構築元文字列内の二つの部分文字列を比較します。

## 要件・注意

- 既定構築した場合は、取得前に `build(s)` を呼んでください。
- 各区間は `0 <= l <= r <= s.size()` を満たす必要があります。
- ハッシュが一致しても文字列が等しいとは限らず、衝突の可能性はゼロではありません。
- 基数を共有するため、異なるインスタンスの同じ内容・長さの部分文字列も
  ハッシュ値で比較できます。ただし API の `equals` は同一インスタンス内用です。

## 計算量

構築は `O(N)` 時間・メモリ、部分文字列ハッシュと比較は `O(1)` です。
