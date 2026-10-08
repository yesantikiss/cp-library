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
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/suffixarray.test.cpp
    title: verify/suffixarray.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/zalgorithm.test.cpp
    title: verify/zalgorithm.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"string/rolling_hash.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <random>\n#include <string>\n#include <vector>\n\nnamespace\
    \ yesantikiss {\n    struct RollingHash {\n        using ull = unsigned long long;\n\
    \        static constexpr ull MOD = (1ULL << 61) - 1;\n    \n        // \u5171\
    \u6709\u8CC7\u6E90\uFF08\u5168\u30A4\u30F3\u30B9\u30BF\u30F3\u30B9\u3067\u5171\
    \u901A\uFF09\n        inline static ull base = 0;\n        inline static std::vector<ull>\
    \ pow_base;\n    \n        std::vector<ull> hash;  // hash[i] = S[0..i) \u306E\
    \u30CF\u30C3\u30B7\u30E5\n        int n = 0;\n    \n        // 2^61-1 \u7528\u306E\
    \u6F14\u7B97\n        static inline ull add(ull a, ull b) {\n            ull c\
    \ = a + b;\n            if (c >= MOD) c -= MOD;\n            return c;\n     \
    \   }\n        static inline ull mul(ull a, ull b) {\n            unsigned __int128\
    \ t = (unsigned __int128)a * b;\n            ull res = (ull)(t >> 61) + ((ull)t\
    \ & MOD);\n            if (res >= MOD) res -= MOD;\n            return res;\n\
    \        }\n    \n        static void init_base() {\n            if (base != 0)\
    \ return;\n            std::mt19937_64 rng(std::random_device{}());\n        \
    \    std::uniform_int_distribution<ull> dist(1ULL, MOD - 1);\n            base\
    \ = dist(rng);\n            pow_base = {1};  // pow_base[0] = 1\n        }\n \
    \   \n        static void ensure_pow(int len) {\n            if ((int)pow_base.size()\
    \ >= len + 1) return;\n            int cur = (int)pow_base.size();\n         \
    \   pow_base.resize(len + 1);\n            for (int i = cur; i <= len; ++i) {\n\
    \                pow_base[i] = mul(pow_base[i - 1], base);\n            }\n  \
    \      }\n    \n        // hash(A + B) \u3092 hash(A), hash(B), |B| \u304B\u3089\
    \u6C42\u3081\u308B\n        static ull concat(ull h1, ull h2, int len2) {\n  \
    \          assert(len2 >= 0);\n            init_base();\n            ensure_pow(len2);\n\
    \            return add(mul(h1, pow_base[len2]), h2);\n        }\n\n        //\
    \ \u9577\u3055\u4ED8\u304D\u306E\u30CF\u30C3\u30B7\u30E5\u5024\u3002+ \u3067\u6587\
    \u5B57\u5217\u306E\u9023\u7D50\u306B\u5BFE\u5FDC\u3059\u308B\u30CF\u30C3\u30B7\
    \u30E5\u304C\u5F97\u3089\u308C\u308B\n        // \u65E2\u5B9A\u5024\u306F\u7A7A\
    \u6587\u5B57\u5217\uFF08+ \u306E\u5358\u4F4D\u5143\uFF09\n        struct Hash\
    \ {\n            ull val = 0;\n            int len = 0;\n\n            Hash()\
    \ = default;\n            Hash(ull val, int len) : val(val), len(len) {}\n   \
    \         // 1 \u6587\u5B57 / \u6587\u5B57\u5217\u5168\u4F53\u306E\u30CF\u30C3\
    \u30B7\u30E5\uFF08prefix hash \u3092\u6301\u305F\u305A\u306B\u6C42\u3081\u308B\
    \uFF09\n            explicit Hash(char c) : val((ull)(unsigned char)c + 1), len(1)\
    \ { init_base(); }\n            explicit Hash(const std::string &s) : len((int)s.size())\
    \ {\n                init_base();\n                for (char c : s) val = add(mul(val,\
    \ base), (ull)(unsigned char)c + 1);\n            }\n\n            friend Hash\
    \ operator+(const Hash &a, const Hash &b) {\n                return {concat(a.val,\
    \ b.val, b.len), a.len + b.len};\n            }\n            Hash &operator+=(const\
    \ Hash &o) { return *this = *this + o; }\n            friend bool operator==(const\
    \ Hash &a, const Hash &b) {\n                return a.val == b.val && a.len ==\
    \ b.len;\n            }\n            friend bool operator!=(const Hash &a, const\
    \ Hash &b) { return !(a == b); }\n        };\n\n        RollingHash() : n(0) {}\n\
    \    \n        RollingHash(const std::string &s) {\n            build(s);\n  \
    \      }\n    \n        void build(const std::string &s) {\n            init_base();\n\
    \            n = (int)s.size();\n            ensure_pow(n);\n            hash.assign(n\
    \ + 1, 0);\n            for (int i = 0; i < n; ++i) {\n                hash[i\
    \ + 1] = add(mul(hash[i], base), (ull)(unsigned char)s[i] + 1);\n            }\n\
    \        }\n    \n        // S[l..r) \u306E\u30CF\u30C3\u30B7\u30E5\u3092\u53D6\
    \u5F97\n        ull get(int l, int r) const {\n            assert(0 <= l && l\
    \ <= r && r <= n);\n            ull res = hash[r] + MOD - mul(hash[l], pow_base[r\
    \ - l]);\n            if (res >= MOD) res -= MOD;\n            return res;\n \
    \       }\n    \n        // S[l..r) \u306E\u9577\u3055\u4ED8\u304D\u30CF\u30C3\
    \u30B7\u30E5\u3092\u53D6\u5F97\uFF08+ \u3067\u9023\u7D50\u3067\u304D\u308B\uFF09\
    \n        Hash slice(int l, int r) const {\n            return {get(l, r), r -\
    \ l};\n        }\n\n        // \u540C\u3058\u6587\u5B57\u5217\u306E\u4E2D\u3067\
    \u90E8\u5206\u6587\u5B57\u5217\u304C\u7B49\u3057\u3044\u304B\n        bool equals(int\
    \ l1, int r1, int l2, int r2) const {\n            if (r1 - l1 != r2 - l2) return\
    \ false;\n            return get(l1, r1) == get(l2, r2);\n        }\n\n      \
    \  // a \u306E [l1, r1) \u3068 b \u306E [l2, r2) \u306E\u6700\u9577\u5171\u901A\
    \u63A5\u982D\u8F9E\u306E\u9577\u3055  O(log N)\n        static int lcp(const RollingHash\
    \ &a, int l1, int r1, const RollingHash &b, int l2, int r2) {\n            assert(0\
    \ <= l1 && l1 <= r1 && r1 <= a.n);\n            assert(0 <= l2 && l2 <= r2 &&\
    \ r2 <= b.n);\n            // get(l1, l1 + len) == get(l2, l2 + len) \u3092\u4E57\
    \u7B97 1 \u56DE\u3067\u5224\u5B9A\u3059\u308B\n            const ull diff = add(a.hash[l1],\
    \ MOD - b.hash[l2]);\n            auto same = [&](int len) {\n               \
    \ return add(a.hash[l1 + len], MOD - b.hash[l2 + len]) == mul(diff, pow_base[len]);\n\
    \            };\n            const int limit = std::min(r1 - l1, r2 - l2);\n \
    \           // \u7B54\u3048\u304C\u77ED\u3044\u5834\u5408\u306B\u901F\u3044\u3088\
    \u3046\u3001\u9577\u3055 32 \u307E\u3067\u306F\u500D\u3005\u3067\u78BA\u304B\u3081\
    \u3066\u304B\u3089\u4E8C\u5206\u63A2\u7D22\u3059\u308B\n            int ok = 0,\
    \ ng = 1;\n            while (true) {\n                if (ng > limit || !same(ng))\
    \ break;\n                ok = ng;\n                if (ng >= 32) {\n        \
    \            ng = limit + 1;\n                    break;\n                }\n\
    \                ng *= 2;\n            }\n            if (ng > limit + 1) ng =\
    \ limit + 1;\n            while (ng - ok > 1) {\n                int mid = ok\
    \ + (ng - ok) / 2;\n                if (same(mid)) ok = mid;\n               \
    \ else ng = mid;\n            }\n            return ok;\n        }\n        int\
    \ lcp(int l1, int r1, int l2, int r2) const {\n            return lcp(*this, l1,\
    \ r1, *this, l2, r2);\n        }\n\n        // a \u306E [l1, r1) \u3068 b \u306E\
    \ [l2, r2) \u3092\u8F9E\u66F8\u9806\u3067\u6BD4\u8F03  O(log N)\n        // \u8CA0\
    : a \u5074\u304C\u5C0F\u3055\u3044\u30010: \u7B49\u3057\u3044\u3001\u6B63: a \u5074\
    \u304C\u5927\u304D\u3044\uFF08std::string::compare \u3068\u540C\u3058\u9806\u5E8F\
    \uFF09\n        static int compare(const RollingHash &a, int l1, int r1, const\
    \ RollingHash &b, int l2, int r2) {\n            int len1 = r1 - l1, len2 = r2\
    \ - l2;\n            int k = lcp(a, l1, r1, b, l2, r2);\n            if (k ==\
    \ len1 || k == len2) return (len1 > len2) - (len1 < len2);\n            // \u9577\
    \u3055 1 \u306E\u30CF\u30C3\u30B7\u30E5\u306F \u6587\u5B57 + 1 \u305D\u306E\u3082\
    \u306E\n            ull c1 = a.get(l1 + k, l1 + k + 1), c2 = b.get(l2 + k, l2\
    \ + k + 1);\n            return (c1 > c2) - (c1 < c2);\n        }\n        int\
    \ compare(int l1, int r1, int l2, int r2) const {\n            return compare(*this,\
    \ l1, r1, *this, l2, r2);\n        }\n    };\n    \n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <random>\n\
    #include <string>\n#include <vector>\n\nnamespace yesantikiss {\n    struct RollingHash\
    \ {\n        using ull = unsigned long long;\n        static constexpr ull MOD\
    \ = (1ULL << 61) - 1;\n    \n        // \u5171\u6709\u8CC7\u6E90\uFF08\u5168\u30A4\
    \u30F3\u30B9\u30BF\u30F3\u30B9\u3067\u5171\u901A\uFF09\n        inline static\
    \ ull base = 0;\n        inline static std::vector<ull> pow_base;\n    \n    \
    \    std::vector<ull> hash;  // hash[i] = S[0..i) \u306E\u30CF\u30C3\u30B7\u30E5\
    \n        int n = 0;\n    \n        // 2^61-1 \u7528\u306E\u6F14\u7B97\n     \
    \   static inline ull add(ull a, ull b) {\n            ull c = a + b;\n      \
    \      if (c >= MOD) c -= MOD;\n            return c;\n        }\n        static\
    \ inline ull mul(ull a, ull b) {\n            unsigned __int128 t = (unsigned\
    \ __int128)a * b;\n            ull res = (ull)(t >> 61) + ((ull)t & MOD);\n  \
    \          if (res >= MOD) res -= MOD;\n            return res;\n        }\n \
    \   \n        static void init_base() {\n            if (base != 0) return;\n\
    \            std::mt19937_64 rng(std::random_device{}());\n            std::uniform_int_distribution<ull>\
    \ dist(1ULL, MOD - 1);\n            base = dist(rng);\n            pow_base =\
    \ {1};  // pow_base[0] = 1\n        }\n    \n        static void ensure_pow(int\
    \ len) {\n            if ((int)pow_base.size() >= len + 1) return;\n         \
    \   int cur = (int)pow_base.size();\n            pow_base.resize(len + 1);\n \
    \           for (int i = cur; i <= len; ++i) {\n                pow_base[i] =\
    \ mul(pow_base[i - 1], base);\n            }\n        }\n    \n        // hash(A\
    \ + B) \u3092 hash(A), hash(B), |B| \u304B\u3089\u6C42\u3081\u308B\n        static\
    \ ull concat(ull h1, ull h2, int len2) {\n            assert(len2 >= 0);\n   \
    \         init_base();\n            ensure_pow(len2);\n            return add(mul(h1,\
    \ pow_base[len2]), h2);\n        }\n\n        // \u9577\u3055\u4ED8\u304D\u306E\
    \u30CF\u30C3\u30B7\u30E5\u5024\u3002+ \u3067\u6587\u5B57\u5217\u306E\u9023\u7D50\
    \u306B\u5BFE\u5FDC\u3059\u308B\u30CF\u30C3\u30B7\u30E5\u304C\u5F97\u3089\u308C\
    \u308B\n        // \u65E2\u5B9A\u5024\u306F\u7A7A\u6587\u5B57\u5217\uFF08+ \u306E\
    \u5358\u4F4D\u5143\uFF09\n        struct Hash {\n            ull val = 0;\n  \
    \          int len = 0;\n\n            Hash() = default;\n            Hash(ull\
    \ val, int len) : val(val), len(len) {}\n            // 1 \u6587\u5B57 / \u6587\
    \u5B57\u5217\u5168\u4F53\u306E\u30CF\u30C3\u30B7\u30E5\uFF08prefix hash \u3092\
    \u6301\u305F\u305A\u306B\u6C42\u3081\u308B\uFF09\n            explicit Hash(char\
    \ c) : val((ull)(unsigned char)c + 1), len(1) { init_base(); }\n            explicit\
    \ Hash(const std::string &s) : len((int)s.size()) {\n                init_base();\n\
    \                for (char c : s) val = add(mul(val, base), (ull)(unsigned char)c\
    \ + 1);\n            }\n\n            friend Hash operator+(const Hash &a, const\
    \ Hash &b) {\n                return {concat(a.val, b.val, b.len), a.len + b.len};\n\
    \            }\n            Hash &operator+=(const Hash &o) { return *this = *this\
    \ + o; }\n            friend bool operator==(const Hash &a, const Hash &b) {\n\
    \                return a.val == b.val && a.len == b.len;\n            }\n   \
    \         friend bool operator!=(const Hash &a, const Hash &b) { return !(a ==\
    \ b); }\n        };\n\n        RollingHash() : n(0) {}\n    \n        RollingHash(const\
    \ std::string &s) {\n            build(s);\n        }\n    \n        void build(const\
    \ std::string &s) {\n            init_base();\n            n = (int)s.size();\n\
    \            ensure_pow(n);\n            hash.assign(n + 1, 0);\n            for\
    \ (int i = 0; i < n; ++i) {\n                hash[i + 1] = add(mul(hash[i], base),\
    \ (ull)(unsigned char)s[i] + 1);\n            }\n        }\n    \n        // S[l..r)\
    \ \u306E\u30CF\u30C3\u30B7\u30E5\u3092\u53D6\u5F97\n        ull get(int l, int\
    \ r) const {\n            assert(0 <= l && l <= r && r <= n);\n            ull\
    \ res = hash[r] + MOD - mul(hash[l], pow_base[r - l]);\n            if (res >=\
    \ MOD) res -= MOD;\n            return res;\n        }\n    \n        // S[l..r)\
    \ \u306E\u9577\u3055\u4ED8\u304D\u30CF\u30C3\u30B7\u30E5\u3092\u53D6\u5F97\uFF08\
    + \u3067\u9023\u7D50\u3067\u304D\u308B\uFF09\n        Hash slice(int l, int r)\
    \ const {\n            return {get(l, r), r - l};\n        }\n\n        // \u540C\
    \u3058\u6587\u5B57\u5217\u306E\u4E2D\u3067\u90E8\u5206\u6587\u5B57\u5217\u304C\
    \u7B49\u3057\u3044\u304B\n        bool equals(int l1, int r1, int l2, int r2)\
    \ const {\n            if (r1 - l1 != r2 - l2) return false;\n            return\
    \ get(l1, r1) == get(l2, r2);\n        }\n\n        // a \u306E [l1, r1) \u3068\
    \ b \u306E [l2, r2) \u306E\u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E\u306E\u9577\
    \u3055  O(log N)\n        static int lcp(const RollingHash &a, int l1, int r1,\
    \ const RollingHash &b, int l2, int r2) {\n            assert(0 <= l1 && l1 <=\
    \ r1 && r1 <= a.n);\n            assert(0 <= l2 && l2 <= r2 && r2 <= b.n);\n \
    \           // get(l1, l1 + len) == get(l2, l2 + len) \u3092\u4E57\u7B97 1 \u56DE\
    \u3067\u5224\u5B9A\u3059\u308B\n            const ull diff = add(a.hash[l1], MOD\
    \ - b.hash[l2]);\n            auto same = [&](int len) {\n                return\
    \ add(a.hash[l1 + len], MOD - b.hash[l2 + len]) == mul(diff, pow_base[len]);\n\
    \            };\n            const int limit = std::min(r1 - l1, r2 - l2);\n \
    \           // \u7B54\u3048\u304C\u77ED\u3044\u5834\u5408\u306B\u901F\u3044\u3088\
    \u3046\u3001\u9577\u3055 32 \u307E\u3067\u306F\u500D\u3005\u3067\u78BA\u304B\u3081\
    \u3066\u304B\u3089\u4E8C\u5206\u63A2\u7D22\u3059\u308B\n            int ok = 0,\
    \ ng = 1;\n            while (true) {\n                if (ng > limit || !same(ng))\
    \ break;\n                ok = ng;\n                if (ng >= 32) {\n        \
    \            ng = limit + 1;\n                    break;\n                }\n\
    \                ng *= 2;\n            }\n            if (ng > limit + 1) ng =\
    \ limit + 1;\n            while (ng - ok > 1) {\n                int mid = ok\
    \ + (ng - ok) / 2;\n                if (same(mid)) ok = mid;\n               \
    \ else ng = mid;\n            }\n            return ok;\n        }\n        int\
    \ lcp(int l1, int r1, int l2, int r2) const {\n            return lcp(*this, l1,\
    \ r1, *this, l2, r2);\n        }\n\n        // a \u306E [l1, r1) \u3068 b \u306E\
    \ [l2, r2) \u3092\u8F9E\u66F8\u9806\u3067\u6BD4\u8F03  O(log N)\n        // \u8CA0\
    : a \u5074\u304C\u5C0F\u3055\u3044\u30010: \u7B49\u3057\u3044\u3001\u6B63: a \u5074\
    \u304C\u5927\u304D\u3044\uFF08std::string::compare \u3068\u540C\u3058\u9806\u5E8F\
    \uFF09\n        static int compare(const RollingHash &a, int l1, int r1, const\
    \ RollingHash &b, int l2, int r2) {\n            int len1 = r1 - l1, len2 = r2\
    \ - l2;\n            int k = lcp(a, l1, r1, b, l2, r2);\n            if (k ==\
    \ len1 || k == len2) return (len1 > len2) - (len1 < len2);\n            // \u9577\
    \u3055 1 \u306E\u30CF\u30C3\u30B7\u30E5\u306F \u6587\u5B57 + 1 \u305D\u306E\u3082\
    \u306E\n            ull c1 = a.get(l1 + k, l1 + k + 1), c2 = b.get(l2 + k, l2\
    \ + k + 1);\n            return (c1 > c2) - (c1 < c2);\n        }\n        int\
    \ compare(int l1, int r1, int l2, int r2) const {\n            return compare(*this,\
    \ l1, r1, *this, l2, r2);\n        }\n    };\n    \n}\n"
  dependsOn: []
  isVerificationFile: false
  path: string/rolling_hash.hpp
  requiredBy:
  - tests/rolling_hash_tu.cpp
  - tests/test.cpp
  timestamp: '2026-10-08 13:39:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/zalgorithm.test.cpp
  - verify/suffixarray.test.cpp
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

### 辞書順比較

- `lcp(l1, r1, l2, r2)`: `s[l1, r1)` と `s[l2, r2)` の最長共通接頭辞の長さを返します。
- `compare(l1, r1, l2, r2)`: 辞書順で比較し、負・0・正を返します（`std::string::compare` と同じ順序）。
- `RollingHash::lcp(a, l1, r1, b, l2, r2)`, `RollingHash::compare(a, l1, r1, b, l2, r2)`:
  別インスタンス `a`, `b` の部分文字列どうしで同じことをします。

```cpp
RollingHash rh(s);
// 接尾辞のソート
std::sort(idx.begin(), idx.end(), [&](int i, int j) { return rh.compare(i, n, j, n) < 0; });
```

### 連結

`get` は `unsigned long long` を返すので、連結には長さの情報が別途必要です。
長さを一緒に持つ `RollingHash::Hash`（`val`, `len`）を使うと `+` で連結できます。

- `slice(l, r)`: `s[l, r)` の `Hash` を返します。
- `a + b`, `a += b`: 連結した文字列の `Hash` を返します。既定構築の `Hash()` は空文字列で、`+` の単位元です。
- `==`, `!=`: 比較。`map` / `set` のキーにしたいときは `get` の値を使ってください。
- `Hash(c)`, `Hash(s)`: 1 文字・文字列全体の `Hash` を prefix hash を持たずに求めます（`explicit`）。
- `Hash(val, len)`: ハッシュ値と長さから直接作ります。
- `RollingHash::concat(h1, h2, len2)`: `get` の値のまま連結する版です。`len2` は後ろ側の長さです。

```cpp
RollingHash a("abra"), b("cadabra"), c("abracadabra");
assert(a.slice(0, 4) + b.slice(0, 7) == c.slice(0, 11));
```

`Hash` は `+` と `Hash()` でモノイドになるので、そのままセグメント木に載せられます。

```cpp
using Hash = yesantikiss::RollingHash::Hash;
Hash op(Hash a, Hash b) { return a + b; }
Hash e() { return Hash(); }

atcoder::segtree<Hash, op, e> seg(n);
for (int i = 0; i < n; i++) seg.set(i, Hash(s[i]));
bool same = seg.prod(l1, r1) == seg.prod(l2, r2);
```

逆向きのハッシュ（回文判定など）は `op` を `b + a` にしたセグメント木を別に持ちます。

## 要件・注意

- 既定構築した場合は、取得前に `build(s)` を呼んでください。
- 各区間は `0 <= l <= r <= s.size()` を満たす必要があります。
- ハッシュが一致しても文字列が等しいとは限らず、衝突の可能性はゼロではありません。
- 基数を共有するため、異なるインスタンスの同じ内容・長さの部分文字列も
  ハッシュ値で比較できます。ただし API の `equals` は同一インスタンス内用です。

## 計算量

構築は `O(N)` 時間・メモリ、部分文字列ハッシュと比較は `O(1)` です。
`lcp`, `compare` は `O(log N)` です。
連結は、基数の累乗テーブルが足りていれば `O(1)`（足りない分は初回のみ伸長）、`Hash(s)` は `O(|s|)` です。
