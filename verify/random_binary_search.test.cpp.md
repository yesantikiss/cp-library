---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/binary_search.hpp
    title: "\u4E8C\u5206\u63A2\u7D22"
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
  bundledCode: "#line 1 \"verify/random_binary_search.test.cpp\"\n// \u7D20\u6734\u306A\
    \u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\u30E9\u30F3\u30C0\u30E0\
    \u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089 A + B \u3092\u89E3\u304F\
    \u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include\
    \ <cassert>\n#include <iostream>\n#include <limits>\n#include <random>\n\n#line\
    \ 2 \"algo/binary_search.hpp\"\n\nnamespace yesantikiss {\n    // (left, right]\
    \ \u306E\u7BC4\u56F2\u3067 f(x) \u304C true \u306B\u306A\u308B\u6700\u5C0F\u306E\
    \ x \u3092\u8FD4\u3059\n    // \u5358\u8ABF\u6027: false...false,true...true\n\
    \    // left \u3068 right \u306F\u756A\u5175\u3067\u3001f(left) == false, f(right)\
    \ == true \u3068\u307F\u306A\u3059\n    // (f(left), f(right) \u306F\u8A55\u4FA1\
    \u3057\u306A\u3044\u3002true \u304C\u306A\u3051\u308C\u3070 right \u3092\u8FD4\
    \u3059)\n    template<class F, class T>\n    T binary_search_min_left(T left,\
    \ T right, F f){\n        while (right - left > 1){\n            T mid = left\
    \ + (right - left) / 2;\n            if(f(mid)) right = mid;\n            else\
    \ left = mid;\n        }\n        return right;\n    }\n\n    // [left, right)\
    \ \u306E\u7BC4\u56F2\u3067 f(x) \u304C true \u306B\u306A\u308B\u6700\u5927\u306E\
    \ x \u3092\u8FD4\u3059\n    // \u5358\u8ABF\u6027: true...true,false...false\n\
    \    // left \u3068 right \u306F\u756A\u5175\u3067\u3001f(left) == true, f(right)\
    \ == false \u3068\u307F\u306A\u3059\n    // (f(left), f(right) \u306F\u8A55\u4FA1\
    \u3057\u306A\u3044\u3002true \u304C\u306A\u3051\u308C\u3070 left \u3092\u8FD4\u3059\
    )\n    template<class F, class T>\n    T binary_search_max_right(T left, T right,\
    \ F f){\n        while (right - left > 1){\n            T mid = left + (right\
    \ - left) / 2;\n            if(f(mid)) left = mid;\n            else right = mid;\n\
    \        }\n        return left;\n    }\n}\n#line 10 \"verify/random_binary_search.test.cpp\"\
    \n\nint main() {\n    using yesantikiss::binary_search_max_right;\n    using yesantikiss::binary_search_min_left;\n\
    \n    // \u5C0F\u3055\u3044\u7BC4\u56F2\u3067\u306F\u3001\u756A\u5175\u3068\u5883\
    \u754C\u306E\u7D44\u3092\u3059\u3079\u3066\u8A66\u3059\u3002\n    for (int left\
    \ = -6; left <= 6; ++left) {\n        for (int right = left + 1; right <= left\
    \ + 12; ++right) {\n            // f(x) = (x >= border)\u3002left \u306F false\u3001\
    right \u306F true \u306E\u756A\u5175\n            for (int border = left + 1;\
    \ border <= right; ++border) {\n                int calls = 0;\n             \
    \   int found = binary_search_min_left(left, right, [&](int x) {\n           \
    \         assert(left < x && x < right);  // \u756A\u5175\u306F\u8A55\u4FA1\u3057\
    \u306A\u3044\n                    ++calls;\n                    return x >= border;\n\
    \                });\n                assert(found == border);\n             \
    \   assert(calls <= 5);\n            }\n            // f(x) = (x <= border)\u3002\
    left \u306F true\u3001right \u306F false \u306E\u756A\u5175\n            for (int\
    \ border = left; border < right; ++border) {\n                int found = binary_search_max_right(left,\
    \ right, [&](int x) {\n                    assert(left < x && x < right);\n  \
    \                  return x <= border;\n                });\n                assert(found\
    \ == border);\n            }\n        }\n    }\n\n    // \u5927\u304D\u3044\u7BC4\
    \u56F2\u3067\u3082\u3001\u9014\u4E2D\u306E\u8A08\u7B97\u304C\u3042\u3075\u308C\
    \u306A\u3044\u3002\n    std::mt19937_64 random(20261110);\n    const long long\
    \ max = std::numeric_limits<long long>::max();\n    for (int trial = 0; trial\
    \ < 20000; ++trial) {\n        long long left = static_cast<long long>(random()\
    \ >> 2);\n        long long right = left + 1 + static_cast<long long>(random()\
    \ >> 2);\n        if (trial % 3 == 0) right = max;\n        // \u756A\u5175\u3068\
    \u3057\u3066 -1 \u3092\u6E21\u3059\u5F62 (right - left \u304C\u3042\u3075\u308C\
    \u306A\u3044\u7BC4\u56F2\u3067)\n        if (trial % 3 != 0 && trial % 7 == 0)\
    \ left = -1;\n        unsigned long long width =\n            static_cast<unsigned\
    \ long long>(right - left);\n        long long border = left + 1 +\n         \
    \                  static_cast<long long>(random() % width);\n        assert(binary_search_min_left(left,\
    \ right, [&](long long x) {\n                   return x >= border;\n        \
    \       }) == border);\n        assert(binary_search_max_right(left, right, [&](long\
    \ long x) {\n                   return x < border;\n               }) == border\
    \ - 1);\n    }\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  code: "// \u7D20\u6734\u306A\u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\
    \u30E9\u30F3\u30C0\u30E0\u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089\
    \ A + B \u3092\u89E3\u304F\u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#include <cassert>\n#include <iostream>\n#include <limits>\n#include <random>\n\
    \n#include \"algo/binary_search.hpp\"\n\nint main() {\n    using yesantikiss::binary_search_max_right;\n\
    \    using yesantikiss::binary_search_min_left;\n\n    // \u5C0F\u3055\u3044\u7BC4\
    \u56F2\u3067\u306F\u3001\u756A\u5175\u3068\u5883\u754C\u306E\u7D44\u3092\u3059\
    \u3079\u3066\u8A66\u3059\u3002\n    for (int left = -6; left <= 6; ++left) {\n\
    \        for (int right = left + 1; right <= left + 12; ++right) {\n         \
    \   // f(x) = (x >= border)\u3002left \u306F false\u3001right \u306F true \u306E\
    \u756A\u5175\n            for (int border = left + 1; border <= right; ++border)\
    \ {\n                int calls = 0;\n                int found = binary_search_min_left(left,\
    \ right, [&](int x) {\n                    assert(left < x && x < right);  //\
    \ \u756A\u5175\u306F\u8A55\u4FA1\u3057\u306A\u3044\n                    ++calls;\n\
    \                    return x >= border;\n                });\n              \
    \  assert(found == border);\n                assert(calls <= 5);\n           \
    \ }\n            // f(x) = (x <= border)\u3002left \u306F true\u3001right \u306F\
    \ false \u306E\u756A\u5175\n            for (int border = left; border < right;\
    \ ++border) {\n                int found = binary_search_max_right(left, right,\
    \ [&](int x) {\n                    assert(left < x && x < right);\n         \
    \           return x <= border;\n                });\n                assert(found\
    \ == border);\n            }\n        }\n    }\n\n    // \u5927\u304D\u3044\u7BC4\
    \u56F2\u3067\u3082\u3001\u9014\u4E2D\u306E\u8A08\u7B97\u304C\u3042\u3075\u308C\
    \u306A\u3044\u3002\n    std::mt19937_64 random(20261110);\n    const long long\
    \ max = std::numeric_limits<long long>::max();\n    for (int trial = 0; trial\
    \ < 20000; ++trial) {\n        long long left = static_cast<long long>(random()\
    \ >> 2);\n        long long right = left + 1 + static_cast<long long>(random()\
    \ >> 2);\n        if (trial % 3 == 0) right = max;\n        // \u756A\u5175\u3068\
    \u3057\u3066 -1 \u3092\u6E21\u3059\u5F62 (right - left \u304C\u3042\u3075\u308C\
    \u306A\u3044\u7BC4\u56F2\u3067)\n        if (trial % 3 != 0 && trial % 7 == 0)\
    \ left = -1;\n        unsigned long long width =\n            static_cast<unsigned\
    \ long long>(right - left);\n        long long border = left + 1 +\n         \
    \                  static_cast<long long>(random() % width);\n        assert(binary_search_min_left(left,\
    \ right, [&](long long x) {\n                   return x >= border;\n        \
    \       }) == border);\n        assert(binary_search_max_right(left, right, [&](long\
    \ long x) {\n                   return x < border;\n               }) == border\
    \ - 1);\n    }\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  dependsOn:
  - algo/binary_search.hpp
  isVerificationFile: true
  path: verify/random_binary_search.test.cpp
  requiredBy: []
  timestamp: '2026-11-12 13:12:40+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/random_binary_search.test.cpp
layout: document
redirect_from:
- /verify/verify/random_binary_search.test.cpp
- /verify/verify/random_binary_search.test.cpp.html
title: verify/random_binary_search.test.cpp
---
