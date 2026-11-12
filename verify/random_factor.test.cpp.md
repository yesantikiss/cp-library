---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/factor.hpp
    title: "\u6700\u5C0F\u7D20\u56E0\u6570\u30C6\u30FC\u30D6\u30EB"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/random_factor.test.cpp\"\n// \u7D20\u6734\u306A\u5B9F\
    \u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\u30E9\u30F3\u30C0\u30E0\u30C6\
    \u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089 A + B \u3092\u89E3\u304F\u3002\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <iostream>\n#include <utility>\n#include <vector>\n\n#line 2 \"math/factor.hpp\"\
    \n\n#line 6 \"math/factor.hpp\"\n\nnamespace yesantikiss {\n    // \u6700\u5C0F\
    \u7D20\u56E0\u6570\u30C6\u30FC\u30D6\u30EB (Least Prime Factor / LPF)\n    //\
    \ 1..N \u3092 O(N) \u3067\u69CB\u7BC9\u3057\u3066\u3001\u5404 x \u3092 O(\u7D20\
    \u56E0\u6570\u306E\u500B\u6570) \u3067\u5206\u89E3\u3067\u304D\u308B\n    struct\
    \ Factor {\n        int N = 0;\n        std::vector<int> lpf;     // lpf[x] =\
    \ x \u306E\u6700\u5C0F\u7D20\u56E0\u6570 (x>=2), lpf[1]=1\n        std::vector<int>\
    \ primes;  // \u7D20\u6570\u5217\uFF08\u304A\u307E\u3051\uFF09\n    \n       \
    \ Factor() {}\n        explicit Factor(int n) { build(n); }\n    \n        void\
    \ build(int n) {\n            assert(n >= 0);\n            N = n;\n          \
    \  lpf.assign(N + 1, 0);\n            primes.clear();\n            if (N >= 1)\
    \ lpf[1] = 1;\n    \n            for (int i = 2; i <= N; i++) {\n            \
    \    if (lpf[i] == 0) {\n                    lpf[i] = i;\n                   \
    \ primes.emplace_back(i);\n                }\n                for (int p : primes)\
    \ {\n                    long long v = 1LL * p * i;\n                    if (v\
    \ > N) break;\n                    lpf[(int)v] = p;\n                    if (p\
    \ == lpf[i]) break;\n                }\n            }\n        }\n    \n     \
    \   // x \u3092\u7D20\u56E0\u6570\u5206\u89E3\u3057\u3066 (prime, exponent) \u3092\
    \u8FD4\u3059\n        // \u4E8B\u524D\u306B build(maxA) \u304C\u5FC5\u8981\u3002\
    x==1 \u306F\u7A7A\u3092\u8FD4\u3059\u3002\n        std::vector<std::pair<int,int>>\
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
    \ N);\n            return x >= 2 && lpf[x] == x;\n        }\n    };\n}\n#line\
    \ 10 \"verify/random_factor.test.cpp\"\n\nint main() {\n    {\n        yesantikiss::Factor\
    \ empty(0);\n        assert(empty.primes.empty());\n        yesantikiss::Factor\
    \ one(1);\n        assert(one.primes.empty() && !one.is_prime(1));\n        assert(one.factorize(1).empty()\
    \ && one.factor_list(1).empty());\n    }\n\n    // \u8A66\u3057\u5272\u308A\u306E\
    \u7D50\u679C\u3068\u3001N \u4EE5\u4E0B\u306E\u3059\u3079\u3066\u306E\u6570\u3067\
    \u6BD4\u3079\u308B\u3002\n    for (int n : {2, 3, 4, 10, 97, 100, 30000}) {\n\
    \        yesantikiss::Factor factor(n);\n        std::vector<int> primes;\n  \
    \      for (int x = 1; x <= n; ++x) {\n            std::vector<std::pair<int,\
    \ int>> expected;\n            std::vector<int> expected_list;\n            int\
    \ rest = x;\n            for (int p = 2; p * p <= rest; ++p) {\n             \
    \   if (rest % p != 0) continue;\n                int count = 0;\n           \
    \     while (rest % p == 0) {\n                    rest /= p;\n              \
    \      ++count;\n                    expected_list.push_back(p);\n           \
    \     }\n                expected.emplace_back(p, count);\n            }\n   \
    \         if (rest > 1) {\n                expected.emplace_back(rest, 1);\n \
    \               expected_list.push_back(rest);\n            }\n\n            bool\
    \ prime = x >= 2 && expected.size() == 1 &&\n                         expected[0].second\
    \ == 1;\n            if (prime) primes.push_back(x);\n            assert(factor.is_prime(x)\
    \ == prime);\n            assert(factor.factorize(x) == expected);\n         \
    \   assert(factor.factor_list(x) == expected_list);\n            assert(factor.lpf[x]\
    \ == (x == 1 ? 1 : expected[0].first));\n        }\n        assert(factor.primes\
    \ == primes);\n\n        // build \u3057\u76F4\u3057\u3066\u3082\u524D\u306E\u7D50\
    \u679C\u304C\u6B8B\u3089\u306A\u3044\n        factor.build(n / 2);\n        assert(factor.N\
    \ == n / 2);\n        assert(static_cast<int>(factor.lpf.size()) == n / 2 + 1);\n\
    \        for (int p : factor.primes) assert(p <= n / 2);\n    }\n\n    long long\
    \ a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "// \u7D20\u6734\u306A\u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\
    \u30E9\u30F3\u30C0\u30E0\u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089\
    \ A + B \u3092\u89E3\u304F\u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#include <cassert>\n#include <iostream>\n#include <utility>\n#include <vector>\n\
    \n#include \"math/factor.hpp\"\n\nint main() {\n    {\n        yesantikiss::Factor\
    \ empty(0);\n        assert(empty.primes.empty());\n        yesantikiss::Factor\
    \ one(1);\n        assert(one.primes.empty() && !one.is_prime(1));\n        assert(one.factorize(1).empty()\
    \ && one.factor_list(1).empty());\n    }\n\n    // \u8A66\u3057\u5272\u308A\u306E\
    \u7D50\u679C\u3068\u3001N \u4EE5\u4E0B\u306E\u3059\u3079\u3066\u306E\u6570\u3067\
    \u6BD4\u3079\u308B\u3002\n    for (int n : {2, 3, 4, 10, 97, 100, 30000}) {\n\
    \        yesantikiss::Factor factor(n);\n        std::vector<int> primes;\n  \
    \      for (int x = 1; x <= n; ++x) {\n            std::vector<std::pair<int,\
    \ int>> expected;\n            std::vector<int> expected_list;\n            int\
    \ rest = x;\n            for (int p = 2; p * p <= rest; ++p) {\n             \
    \   if (rest % p != 0) continue;\n                int count = 0;\n           \
    \     while (rest % p == 0) {\n                    rest /= p;\n              \
    \      ++count;\n                    expected_list.push_back(p);\n           \
    \     }\n                expected.emplace_back(p, count);\n            }\n   \
    \         if (rest > 1) {\n                expected.emplace_back(rest, 1);\n \
    \               expected_list.push_back(rest);\n            }\n\n            bool\
    \ prime = x >= 2 && expected.size() == 1 &&\n                         expected[0].second\
    \ == 1;\n            if (prime) primes.push_back(x);\n            assert(factor.is_prime(x)\
    \ == prime);\n            assert(factor.factorize(x) == expected);\n         \
    \   assert(factor.factor_list(x) == expected_list);\n            assert(factor.lpf[x]\
    \ == (x == 1 ? 1 : expected[0].first));\n        }\n        assert(factor.primes\
    \ == primes);\n\n        // build \u3057\u76F4\u3057\u3066\u3082\u524D\u306E\u7D50\
    \u679C\u304C\u6B8B\u3089\u306A\u3044\n        factor.build(n / 2);\n        assert(factor.N\
    \ == n / 2);\n        assert(static_cast<int>(factor.lpf.size()) == n / 2 + 1);\n\
    \        for (int p : factor.primes) assert(p <= n / 2);\n    }\n\n    long long\
    \ a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - math/factor.hpp
  isVerificationFile: true
  path: verify/random_factor.test.cpp
  requiredBy: []
  timestamp: '2026-11-12 13:12:40+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/random_factor.test.cpp
layout: document
redirect_from:
- /verify/verify/random_factor.test.cpp
- /verify/verify/random_factor.test.cpp.html
title: verify/random_factor.test.cpp
---
