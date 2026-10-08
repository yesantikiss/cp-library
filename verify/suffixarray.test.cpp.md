---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash.hpp
    title: Rolling Hash
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/suffixarray
    links:
    - https://judge.yosupo.jp/problem/suffixarray
  bundledCode: "#line 1 \"verify/suffixarray.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\
    \n\n#include <algorithm>\n#include <iostream>\n#include <numeric>\n#include <string>\n\
    #include <vector>\n\n#line 2 \"string/rolling_hash.hpp\"\n\n#line 4 \"string/rolling_hash.hpp\"\
    \n#include <cassert>\n#include <random>\n#line 8 \"string/rolling_hash.hpp\"\n\
    \nnamespace yesantikiss {\n    struct RollingHash {\n        using ull = unsigned\
    \ long long;\n        static constexpr ull MOD = (1ULL << 61) - 1;\n    \n   \
    \     // \u5171\u6709\u8CC7\u6E90\uFF08\u5168\u30A4\u30F3\u30B9\u30BF\u30F3\u30B9\
    \u3067\u5171\u901A\uFF09\n        inline static ull base = 0;\n        inline\
    \ static std::vector<ull> pow_base;\n    \n        std::vector<ull> hash;  //\
    \ hash[i] = S[0..i) \u306E\u30CF\u30C3\u30B7\u30E5\n        int n = 0;\n    \n\
    \        // 2^61-1 \u7528\u306E\u6F14\u7B97\n        static inline ull add(ull\
    \ a, ull b) {\n            ull c = a + b;\n            if (c >= MOD) c -= MOD;\n\
    \            return c;\n        }\n        static inline ull mul(ull a, ull b)\
    \ {\n            unsigned __int128 t = (unsigned __int128)a * b;\n           \
    \ ull res = (ull)(t >> 61) + ((ull)t & MOD);\n            if (res >= MOD) res\
    \ -= MOD;\n            return res;\n        }\n    \n        static void init_base()\
    \ {\n            if (base != 0) return;\n            std::mt19937_64 rng(std::random_device{}());\n\
    \            std::uniform_int_distribution<ull> dist(1ULL, MOD - 1);\n       \
    \     base = dist(rng);\n            pow_base = {1};  // pow_base[0] = 1\n   \
    \     }\n    \n        static void ensure_pow(int len) {\n            if ((int)pow_base.size()\
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
    \ l1, r1, *this, l2, r2);\n        }\n    };\n    \n}\n#line 10 \"verify/suffixarray.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    std::string s;\n    std::cin >> s;\n    const int n = (int)s.size();\n\n\
    \    yesantikiss::RollingHash hash(s);\n    std::vector<int> order(n);\n    std::iota(order.begin(),\
    \ order.end(), 0);\n    std::sort(order.begin(), order.end(),\n              [&](int\
    \ i, int j) { return hash.compare(i, n, j, n) < 0; });\n\n    for (int i = 0;\
    \ i < n; ++i) {\n        if (i != 0) std::cout << ' ';\n        std::cout << order[i];\n\
    \    }\n    std::cout << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\n\n#include\
    \ <algorithm>\n#include <iostream>\n#include <numeric>\n#include <string>\n#include\
    \ <vector>\n\n#include \"string/rolling_hash.hpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    std::string s;\n    std::cin >> s;\n    const\
    \ int n = (int)s.size();\n\n    yesantikiss::RollingHash hash(s);\n    std::vector<int>\
    \ order(n);\n    std::iota(order.begin(), order.end(), 0);\n    std::sort(order.begin(),\
    \ order.end(),\n              [&](int i, int j) { return hash.compare(i, n, j,\
    \ n) < 0; });\n\n    for (int i = 0; i < n; ++i) {\n        if (i != 0) std::cout\
    \ << ' ';\n        std::cout << order[i];\n    }\n    std::cout << '\\n';\n}\n"
  dependsOn:
  - string/rolling_hash.hpp
  isVerificationFile: true
  path: verify/suffixarray.test.cpp
  requiredBy: []
  timestamp: '2026-10-08 13:39:00+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/suffixarray.test.cpp
layout: document
redirect_from:
- /verify/verify/suffixarray.test.cpp
- /verify/verify/suffixarray.test.cpp.html
title: verify/suffixarray.test.cpp
---
