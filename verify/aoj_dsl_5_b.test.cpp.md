---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/2d_prefixsum.hpp
    title: "\u4E8C\u6B21\u5143\u7D2F\u7A4D\u548C\u30FB\u4E8C\u6B21\u5143\u3044\u3082\
      \u3059\u6CD5"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/5/DSL_5_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/5/DSL_5_B
  bundledCode: "#line 1 \"verify/aoj_dsl_5_b.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/5/DSL_5_B\"\
    \n\n#include <algorithm>\n#include <iostream>\n\n#line 2 \"ds/2d_prefixsum.hpp\"\
    \n\n#include <cassert>\n#include <vector>\n\nnamespace yesantikiss {\n    // \u4E8C\
    \u6B21\u5143\u7D2F\u7A4D\u548C + \u4E8C\u6B21\u5143\u3044\u3082\u3059\u6CD5\n\
    \    // \u4ED5\u69D8: 0-index, \u534A\u958B\u533A\u9593 [y1,y2)\xD7[x1,x2)\n \
    \   // \u66F4\u65B0\u306F\u3059\u3079\u3066\u5DEE\u5206\u914D\u5217\u3078\u306E\
    \u52A0\u7B97\u306A\u306E\u3067\u3001\u70B9\u52A0\u7B97\u3068\u9577\u65B9\u5F62\
    \u52A0\u7B97\u306F\u81EA\u7531\u306B\u6DF7\u305C\u3066\u3088\u3044\n    template\
    \ <class T>\n    struct PS2D {\n        int H, W;\n        std::vector<std::vector<T>>\
    \ diff;  // \u5DEE\u5206 (H+1)\xD7(W+1)\n        std::vector<std::vector<T>> pref;\
    \  // \u5B8C\u6210\u30B0\u30EA\u30C3\u30C9\u306E\u7D2F\u7A4D\u548C (H+1)\xD7(W+1)\n\
    \        bool built = false;\n\n        PS2D(int H, int W)\n            : H(H),\
    \ W(W),\n              diff(H + 1, std::vector<T>(W + 1, T())),\n            \
    \  pref(H + 1, std::vector<T>(W + 1, T())) {}\n\n        // \u521D\u671F\u30B0\
    \u30EA\u30C3\u30C9\u304B\u3089\u69CB\u7BC9\u6E08\u307F\u306E\u72B6\u614B\u3067\
    \u4F5C\u308B: O(HW)\n        explicit PS2D(const std::vector<std::vector<T>>&\
    \ a)\n            : PS2D((int)a.size(), a.empty() ? 0 : (int)a[0].size()) {\n\
    \            for (int y = 0; y < H; ++y) {\n                assert((int)a[y].size()\
    \ == W);\n                for (int x = 0; x < W; ++x) add(y, x, a[y][x]);\n  \
    \          }\n            build();\n        }\n\n        // \u9577\u65B9\u5F62\
    \u52A0\u7B97: O(1)\n        void add_rect(int y1, int x1, int y2, int x2, const\
    \ T& v) {\n            assert(0 <= y1 && y1 <= y2 && y2 <= H);\n            assert(0\
    \ <= x1 && x1 <= x2 && x2 <= W);\n            diff[y1][x1] += v;\n           \
    \ diff[y1][x2] -= v;\n            diff[y2][x1] -= v;\n            diff[y2][x2]\
    \ += v;\n            built = false;\n        }\n\n        // \u70B9\u52A0\u7B97\
    : O(1)\n        void add(int y, int x, const T& v) { add_rect(y, x, y + 1, x +\
    \ 1, v); }\n\n        // \u5DEE\u5206\u30922\u56DE\u7D2F\u7A4D\u3057\u3066 pref\
    \ \u3092\u4F5C\u308B: O(HW)\n        void build() {\n            for (int y =\
    \ 0; y < H; ++y) {\n                for (int x = 0; x < W; ++x) pref[y + 1][x\
    \ + 1] = diff[y][x];\n            }\n            for (int k = 0; k < 2; ++k) {\
    \  // 1\u56DE\u76EE\u3067\u5B8C\u6210\u30B0\u30EA\u30C3\u30C9\u30012\u56DE\u76EE\
    \u3067\u7D2F\u7A4D\u548C\n                for (int y = 1; y <= H; ++y) {\n   \
    \                 for (int x = 1; x <= W; ++x) {\n                        pref[y][x]\
    \ += pref[y - 1][x] + pref[y][x - 1] - pref[y - 1][x - 1];\n                 \
    \   }\n                }\n            }\n            built = true;\n        }\n\
    \n        // \u9577\u65B9\u5F62\u548C: O(1)\n        T sum(int y1, int x1, int\
    \ y2, int x2) const {\n            assert(built);\n            assert(0 <= y1\
    \ && y1 <= y2 && y2 <= H);\n            assert(0 <= x1 && x1 <= x2 && x2 <= W);\n\
    \            return pref[y2][x2] - pref[y1][x2] - pref[y2][x1] + pref[y1][x1];\n\
    \        }\n\n        // \u5168\u4F53\u548C: O(1)\n        T sum() const { return\
    \ sum(0, 0, H, W); }\n\n        // \u70B9\u53D6\u5F97: O(1)\n        T get(int\
    \ y, int x) const {\n            assert(0 <= y && y < H && 0 <= x && x < W);\n\
    \            return sum(y, x, y + 1, x + 1);\n        }\n\n        // \u66F4\u65B0\
    \u3092\u3059\u3079\u3066\u6D88\u53BB: O(HW)\n        void clear() {\n        \
    \    for (auto& row : diff) row.assign(W + 1, T());\n            built = false;\n\
    \        }\n    };\n}\n#line 7 \"verify/aoj_dsl_5_b.test.cpp\"\n\nint main() {\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    constexpr\
    \ int MAX = 1000;\n    int n;\n    std::cin >> n;\n\n    yesantikiss::PS2D<int>\
    \ imos(MAX, MAX);\n    while (n--) {\n        int x1, y1, x2, y2;\n        std::cin\
    \ >> x1 >> y1 >> x2 >> y2;\n        imos.add_rect(y1, x1, y2, x2, 1);\n    }\n\
    \    imos.build();\n\n    int answer = 0;\n    for (int y = 0; y < MAX; ++y) {\n\
    \        for (int x = 0; x < MAX; ++x) answer = std::max(answer, imos.get(y, x));\n\
    \    }\n    std::cout << answer << '\\n';\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/5/DSL_5_B\"\
    \n\n#include <algorithm>\n#include <iostream>\n\n#include \"ds/2d_prefixsum.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    constexpr int MAX = 1000;\n    int n;\n    std::cin >> n;\n\n    yesantikiss::PS2D<int>\
    \ imos(MAX, MAX);\n    while (n--) {\n        int x1, y1, x2, y2;\n        std::cin\
    \ >> x1 >> y1 >> x2 >> y2;\n        imos.add_rect(y1, x1, y2, x2, 1);\n    }\n\
    \    imos.build();\n\n    int answer = 0;\n    for (int y = 0; y < MAX; ++y) {\n\
    \        for (int x = 0; x < MAX; ++x) answer = std::max(answer, imos.get(y, x));\n\
    \    }\n    std::cout << answer << '\\n';\n}\n"
  dependsOn:
  - ds/2d_prefixsum.hpp
  isVerificationFile: true
  path: verify/aoj_dsl_5_b.test.cpp
  requiredBy: []
  timestamp: '2026-10-17 14:30:16+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/aoj_dsl_5_b.test.cpp
layout: document
redirect_from:
- /verify/verify/aoj_dsl_5_b.test.cpp
- /verify/verify/aoj_dsl_5_b.test.cpp.html
title: verify/aoj_dsl_5_b.test.cpp
---
