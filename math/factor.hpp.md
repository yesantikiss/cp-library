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
  bundledCode: "#line 2 \"math/factor.hpp\"\n\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n\nnamespace yesantikiss {\n    // \u6700\u5C0F\u7D20\u56E0\u6570\
    \u30C6\u30FC\u30D6\u30EB (Least Prime Factor / LPF)\n    // 1..N \u3092 O(N) \u3067\
    \u69CB\u7BC9\u3057\u3066\u3001\u5404 x \u3092 O(\u7D20\u56E0\u6570\u306E\u500B\
    \u6570) \u3067\u5206\u89E3\u3067\u304D\u308B\n    struct Factor {\n        int\
    \ N = 0;\n        std::vector<int> lpf;     // lpf[x] = x \u306E\u6700\u5C0F\u7D20\
    \u56E0\u6570 (x>=2), lpf[1]=1\n        std::vector<int> primes;  // \u7D20\u6570\
    \u5217\uFF08\u304A\u307E\u3051\uFF09\n    \n        Factor() {}\n        explicit\
    \ Factor(int n) { build(n); }\n    \n        void build(int n) {\n           \
    \ assert(n >= 0);\n            N = n;\n            lpf.assign(N + 1, 0);\n   \
    \         primes.clear();\n            if (N >= 1) lpf[1] = 1;\n    \n       \
    \     for (int i = 2; i <= N; i++) {\n                if (lpf[i] == 0) {\n   \
    \                 lpf[i] = i;\n                    primes.emplace_back(i);\n \
    \               }\n                for (int p : primes) {\n                  \
    \  long long v = 1LL * p * i;\n                    if (v > N) break;\n       \
    \             lpf[(int)v] = p;\n                    if (p == lpf[i]) break;\n\
    \                }\n            }\n        }\n    \n        // x \u3092\u7D20\u56E0\
    \u6570\u5206\u89E3\u3057\u3066 (prime, exponent) \u3092\u8FD4\u3059\n        //\
    \ \u4E8B\u524D\u306B build(maxA) \u304C\u5FC5\u8981\u3002x==1 \u306F\u7A7A\u3092\
    \u8FD4\u3059\u3002\n        std::vector<std::pair<int,int>> factorize(int x) const\
    \ {\n            assert(1 <= x && x <= N);\n            std::vector<std::pair<int,int>>\
    \ res;\n            while (x > 1) {\n                int p = lpf[x];\n       \
    \         int c = 0;\n                while (x % p == 0) { x /= p; c++; }\n  \
    \              res.push_back({p, c});\n            }\n            return res;\n\
    \        }\n    \n        // (\u7D20\u56E0\u6570\u3092\u5217\u6319\u3057\u305F\
    \u3044\u3060\u3051) p,p,p,... \u306E\u5F62\u3067\u8FD4\u3059\n        std::vector<int>\
    \ factor_list(int x) const {\n            assert(1 <= x && x <= N);\n        \
    \    std::vector<int> res;\n            while (x > 1) {\n                int p\
    \ = lpf[x];\n                res.push_back(p);\n                x /= p;\n    \
    \        }\n            return res;\n        }\n    \n        bool is_prime(int\
    \ x) const {\n            assert(1 <= x && x <= N);\n            return x >= 2\
    \ && lpf[x] == x;\n        }\n    };\n}\n"
  code: "#pragma once\n\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \nnamespace yesantikiss {\n    // \u6700\u5C0F\u7D20\u56E0\u6570\u30C6\u30FC\u30D6\
    \u30EB (Least Prime Factor / LPF)\n    // 1..N \u3092 O(N) \u3067\u69CB\u7BC9\u3057\
    \u3066\u3001\u5404 x \u3092 O(\u7D20\u56E0\u6570\u306E\u500B\u6570) \u3067\u5206\
    \u89E3\u3067\u304D\u308B\n    struct Factor {\n        int N = 0;\n        std::vector<int>\
    \ lpf;     // lpf[x] = x \u306E\u6700\u5C0F\u7D20\u56E0\u6570 (x>=2), lpf[1]=1\n\
    \        std::vector<int> primes;  // \u7D20\u6570\u5217\uFF08\u304A\u307E\u3051\
    \uFF09\n    \n        Factor() {}\n        explicit Factor(int n) { build(n);\
    \ }\n    \n        void build(int n) {\n            assert(n >= 0);\n        \
    \    N = n;\n            lpf.assign(N + 1, 0);\n            primes.clear();\n\
    \            if (N >= 1) lpf[1] = 1;\n    \n            for (int i = 2; i <= N;\
    \ i++) {\n                if (lpf[i] == 0) {\n                    lpf[i] = i;\n\
    \                    primes.emplace_back(i);\n                }\n            \
    \    for (int p : primes) {\n                    long long v = 1LL * p * i;\n\
    \                    if (v > N) break;\n                    lpf[(int)v] = p;\n\
    \                    if (p == lpf[i]) break;\n                }\n            }\n\
    \        }\n    \n        // x \u3092\u7D20\u56E0\u6570\u5206\u89E3\u3057\u3066\
    \ (prime, exponent) \u3092\u8FD4\u3059\n        // \u4E8B\u524D\u306B build(maxA)\
    \ \u304C\u5FC5\u8981\u3002x==1 \u306F\u7A7A\u3092\u8FD4\u3059\u3002\n        std::vector<std::pair<int,int>>\
    \ factorize(int x) const {\n            assert(1 <= x && x <= N);\n          \
    \  std::vector<std::pair<int,int>> res;\n            while (x > 1) {\n       \
    \         int p = lpf[x];\n                int c = 0;\n                while (x\
    \ % p == 0) { x /= p; c++; }\n                res.push_back({p, c});\n       \
    \     }\n            return res;\n        }\n    \n        // (\u7D20\u56E0\u6570\
    \u3092\u5217\u6319\u3057\u305F\u3044\u3060\u3051) p,p,p,... \u306E\u5F62\u3067\
    \u8FD4\u3059\n        std::vector<int> factor_list(int x) const {\n          \
    \  assert(1 <= x && x <= N);\n            std::vector<int> res;\n            while\
    \ (x > 1) {\n                int p = lpf[x];\n                res.push_back(p);\n\
    \                x /= p;\n            }\n            return res;\n        }\n\
    \    \n        bool is_prime(int x) const {\n            assert(1 <= x && x <=\
    \ N);\n            return x >= 2 && lpf[x] == x;\n        }\n    };\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: math/factor.hpp
  requiredBy:
  - tests/test.cpp
  timestamp: '2026-10-08 13:39:00+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/factor.hpp
layout: document
title: "\u6700\u5C0F\u7D20\u56E0\u6570\u30C6\u30FC\u30D6\u30EB"
---

## 概要

`yesantikiss::Factor` は線形篩で `1` から `N` までの最小素因数を構築し、
素因数分解と素数判定を行います。

## API

- `Factor(n)`, `build(n)`: `N = n` までのテーブルを構築します。
- `factorize(x)`: `(素因数, 指数)` の昇順列を返します。
- `factor_list(x)`: 重複込みの素因数の昇順列を返します。
- `is_prime(x)`: `x` が素数かを返します。
- `primes`: `N` 以下の素数の昇順列です。

## 要件・注意

- `build` には `n >= 0` を指定してください。
- 問い合わせは構築後に `1 <= x <= N` の範囲で行ってください。
- `x == 1` の素因数列は空です。

## 計算量

構築は `O(N)` 時間・`O(N)` メモリ、素数判定は `O(1)` です。素因数分解は
重複込みの素因数数に比例します。
