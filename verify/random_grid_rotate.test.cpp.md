---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utils/grid_rotate.hpp
    title: "\u4E8C\u6B21\u5143\u914D\u5217\u306E\u56DE\u8EE2"
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
  bundledCode: "#line 1 \"verify/random_grid_rotate.test.cpp\"\n// \u7D20\u6734\u306A\
    \u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\u30E9\u30F3\u30C0\u30E0\
    \u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089 A + B \u3092\u89E3\u304F\
    \u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include\
    \ <cassert>\n#include <iostream>\n#include <random>\n#include <string>\n#include\
    \ <vector>\n\n#line 2 \"utils/grid_rotate.hpp\"\n\n#line 5 \"utils/grid_rotate.hpp\"\
    \n\nnamespace yesantikiss {\n    // \u4E8C\u6B21\u5143\u914D\u5217\u306E\u56DE\
    \u8EE2\uFF08\u3059\u3079\u3066\u6642\u8A08\u56DE\u308A\uFF09\n    // Row \u306F\
    \ std::vector<T> \u3067\u3082 std::string \u3067\u3082\u3088\u3044\n    // H\xD7\
    W \u306E a \u3092 90\xB0 \u56DE\u3059\u3068 W\xD7H \u306B\u306A\u308B: res[i][j]\
    \ = a[H-1-j][i]\n    template <class Row>\n    std::vector<Row> rotate90(const\
    \ std::vector<Row>& a) {\n        const int H = (int)a.size();\n        if (H\
    \ == 0) return {};\n        const int W = (int)a[0].size();\n        std::vector<Row>\
    \ res(W, Row(H, typename Row::value_type()));\n        for (int i = 0; i < H;\
    \ ++i) {\n            assert((int)a[i].size() == W);\n            for (int j =\
    \ 0; j < W; ++j) res[j][H - 1 - i] = a[i][j];\n        }\n        return res;\n\
    \    }\n\n    // 180\xB0: res[i][j] = a[H-1-i][W-1-j]\n    template <class Row>\n\
    \    std::vector<Row> rotate180(const std::vector<Row>& a) {\n        std::vector<Row>\
    \ res(a.rbegin(), a.rend());\n        for (auto& row : res) {\n            assert(row.size()\
    \ == a[0].size());\n            row = Row(row.rbegin(), row.rend());\n       \
    \ }\n        return res;\n    }\n\n    // 270\xB0\uFF08\u53CD\u6642\u8A08\u56DE\
    \u308A\u306B 90\xB0\uFF09: res[i][j] = a[j][W-1-i]\n    template <class Row>\n\
    \    std::vector<Row> rotate270(const std::vector<Row>& a) {\n        const int\
    \ H = (int)a.size();\n        if (H == 0) return {};\n        const int W = (int)a[0].size();\n\
    \        std::vector<Row> res(W, Row(H, typename Row::value_type()));\n      \
    \  for (int i = 0; i < H; ++i) {\n            assert((int)a[i].size() == W);\n\
    \            for (int j = 0; j < W; ++j) res[W - 1 - j][i] = a[i][j];\n      \
    \  }\n        return res;\n    }\n\n    // \u6642\u8A08\u56DE\u308A\u306B 90k\xB0\
    \uFF08k \u306F\u8CA0\u3067\u3082\u3088\u3044\uFF09\n    template <class Row>\n\
    \    std::vector<Row> rotate(const std::vector<Row>& a, int k) {\n        k =\
    \ (k % 4 + 4) % 4;\n        if (k == 1) return rotate90(a);\n        if (k ==\
    \ 2) return rotate180(a);\n        if (k == 3) return rotate270(a);\n        return\
    \ a;\n    }\n}\n#line 11 \"verify/random_grid_rotate.test.cpp\"\n\nint main()\
    \ {\n    std::mt19937 random(20261110);\n    using yesantikiss::rotate;\n    using\
    \ yesantikiss::rotate180;\n    using yesantikiss::rotate270;\n    using yesantikiss::rotate90;\n\
    \n    {\n        // \u5411\u304D\u3092\u53D6\u308A\u9055\u3048\u3066\u3044\u306A\
    \u3044\u304B\u3001\u624B\u3067\u66F8\u3044\u305F\u4F8B\u3067\u78BA\u304B\u3081\
    \u308B (\u6642\u8A08\u56DE\u308A)\n        std::vector<std::string> a{\"ab\",\
    \ \"cd\", \"ef\"};\n        assert((rotate90(a) == std::vector<std::string>{\"\
    eca\", \"fdb\"}));\n        assert((rotate180(a) == std::vector<std::string>{\"\
    fe\", \"dc\", \"ba\"}));\n        assert((rotate270(a) == std::vector<std::string>{\"\
    bdf\", \"ace\"}));\n\n        std::vector<std::string> empty;\n        assert(rotate90(empty).empty()\
    \ && rotate180(empty).empty());\n        assert(rotate270(empty).empty() && rotate(empty,\
    \ 5).empty());\n    }\n\n    for (int trial = 0; trial < 2000; ++trial) {\n  \
    \      int H = 1 + static_cast<int>(random() % 7);\n        int W = 1 + static_cast<int>(random()\
    \ % 7);\n        std::vector<std::vector<int>> a(H, std::vector<int>(W));\n  \
    \      std::vector<std::string> s(H, std::string(W, '.'));\n        for (int i\
    \ = 0; i < H; ++i) {\n            for (int j = 0; j < W; ++j) {\n            \
    \    a[i][j] = static_cast<int>(random() % 1000);\n                s[i][j] = static_cast<char>('a'\
    \ + random() % 26);\n            }\n        }\n\n        // \u5B9A\u7FA9\u3069\
    \u304A\u308A\u306E\u6DFB\u5B57\u3067\u6BD4\u3079\u308B\n        auto r90 = rotate90(a);\n\
    \        auto r180 = rotate180(a);\n        auto r270 = rotate270(a);\n      \
    \  auto s90 = rotate90(s);\n        auto s180 = rotate180(s);\n        auto s270\
    \ = rotate270(s);\n        assert(static_cast<int>(r90.size()) == W);\n      \
    \  assert(static_cast<int>(r180.size()) == H);\n        assert(static_cast<int>(r270.size())\
    \ == W);\n        for (int i = 0; i < W; ++i) {\n            assert(static_cast<int>(r90[i].size())\
    \ == H);\n            assert(static_cast<int>(r270[i].size()) == H);\n       \
    \     for (int j = 0; j < H; ++j) {\n                assert(r90[i][j] == a[H -\
    \ 1 - j][i]);\n                assert(r270[i][j] == a[j][W - 1 - i]);\n      \
    \          assert(s90[i][j] == s[H - 1 - j][i]);\n                assert(s270[i][j]\
    \ == s[j][W - 1 - i]);\n            }\n        }\n        for (int i = 0; i <\
    \ H; ++i) {\n            assert(static_cast<int>(r180[i].size()) == W);\n    \
    \        for (int j = 0; j < W; ++j) {\n                assert(r180[i][j] == a[H\
    \ - 1 - i][W - 1 - j]);\n                assert(s180[i][j] == s[H - 1 - i][W -\
    \ 1 - j]);\n            }\n        }\n\n        // rotate(a, k) \u306F 90 \u5EA6\
    \u3092 k \u56DE\u307E\u308F\u3057\u305F\u3082\u306E\u3068\u540C\u3058 (k \u306F\
    \u8CA0\u3067\u3082\u3088\u3044)\n        std::vector<std::vector<int>> turned\
    \ = a;\n        for (int k = 0; k <= 9; ++k) {\n            assert(rotate(a, k)\
    \ == turned);\n            assert(rotate(a, k - 12) == turned);\n            assert(rotate(rotate(a,\
    \ k), -k) == a);\n            turned = rotate90(turned);\n        }\n    }\n\n\
    \    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n\
    }\n"
  code: "// \u7D20\u6734\u306A\u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\
    \u30E9\u30F3\u30C0\u30E0\u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089\
    \ A + B \u3092\u89E3\u304F\u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#include <cassert>\n#include <iostream>\n#include <random>\n#include <string>\n\
    #include <vector>\n\n#include \"utils/grid_rotate.hpp\"\n\nint main() {\n    std::mt19937\
    \ random(20261110);\n    using yesantikiss::rotate;\n    using yesantikiss::rotate180;\n\
    \    using yesantikiss::rotate270;\n    using yesantikiss::rotate90;\n\n    {\n\
    \        // \u5411\u304D\u3092\u53D6\u308A\u9055\u3048\u3066\u3044\u306A\u3044\
    \u304B\u3001\u624B\u3067\u66F8\u3044\u305F\u4F8B\u3067\u78BA\u304B\u3081\u308B\
    \ (\u6642\u8A08\u56DE\u308A)\n        std::vector<std::string> a{\"ab\", \"cd\"\
    , \"ef\"};\n        assert((rotate90(a) == std::vector<std::string>{\"eca\", \"\
    fdb\"}));\n        assert((rotate180(a) == std::vector<std::string>{\"fe\", \"\
    dc\", \"ba\"}));\n        assert((rotate270(a) == std::vector<std::string>{\"\
    bdf\", \"ace\"}));\n\n        std::vector<std::string> empty;\n        assert(rotate90(empty).empty()\
    \ && rotate180(empty).empty());\n        assert(rotate270(empty).empty() && rotate(empty,\
    \ 5).empty());\n    }\n\n    for (int trial = 0; trial < 2000; ++trial) {\n  \
    \      int H = 1 + static_cast<int>(random() % 7);\n        int W = 1 + static_cast<int>(random()\
    \ % 7);\n        std::vector<std::vector<int>> a(H, std::vector<int>(W));\n  \
    \      std::vector<std::string> s(H, std::string(W, '.'));\n        for (int i\
    \ = 0; i < H; ++i) {\n            for (int j = 0; j < W; ++j) {\n            \
    \    a[i][j] = static_cast<int>(random() % 1000);\n                s[i][j] = static_cast<char>('a'\
    \ + random() % 26);\n            }\n        }\n\n        // \u5B9A\u7FA9\u3069\
    \u304A\u308A\u306E\u6DFB\u5B57\u3067\u6BD4\u3079\u308B\n        auto r90 = rotate90(a);\n\
    \        auto r180 = rotate180(a);\n        auto r270 = rotate270(a);\n      \
    \  auto s90 = rotate90(s);\n        auto s180 = rotate180(s);\n        auto s270\
    \ = rotate270(s);\n        assert(static_cast<int>(r90.size()) == W);\n      \
    \  assert(static_cast<int>(r180.size()) == H);\n        assert(static_cast<int>(r270.size())\
    \ == W);\n        for (int i = 0; i < W; ++i) {\n            assert(static_cast<int>(r90[i].size())\
    \ == H);\n            assert(static_cast<int>(r270[i].size()) == H);\n       \
    \     for (int j = 0; j < H; ++j) {\n                assert(r90[i][j] == a[H -\
    \ 1 - j][i]);\n                assert(r270[i][j] == a[j][W - 1 - i]);\n      \
    \          assert(s90[i][j] == s[H - 1 - j][i]);\n                assert(s270[i][j]\
    \ == s[j][W - 1 - i]);\n            }\n        }\n        for (int i = 0; i <\
    \ H; ++i) {\n            assert(static_cast<int>(r180[i].size()) == W);\n    \
    \        for (int j = 0; j < W; ++j) {\n                assert(r180[i][j] == a[H\
    \ - 1 - i][W - 1 - j]);\n                assert(s180[i][j] == s[H - 1 - i][W -\
    \ 1 - j]);\n            }\n        }\n\n        // rotate(a, k) \u306F 90 \u5EA6\
    \u3092 k \u56DE\u307E\u308F\u3057\u305F\u3082\u306E\u3068\u540C\u3058 (k \u306F\
    \u8CA0\u3067\u3082\u3088\u3044)\n        std::vector<std::vector<int>> turned\
    \ = a;\n        for (int k = 0; k <= 9; ++k) {\n            assert(rotate(a, k)\
    \ == turned);\n            assert(rotate(a, k - 12) == turned);\n            assert(rotate(rotate(a,\
    \ k), -k) == a);\n            turned = rotate90(turned);\n        }\n    }\n\n\
    \    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n\
    }\n"
  dependsOn:
  - utils/grid_rotate.hpp
  isVerificationFile: true
  path: verify/random_grid_rotate.test.cpp
  requiredBy: []
  timestamp: '2026-11-10 19:55:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/random_grid_rotate.test.cpp
layout: document
redirect_from:
- /verify/verify/random_grid_rotate.test.cpp
- /verify/verify/random_grid_rotate.test.cpp.html
title: verify/random_grid_rotate.test.cpp
---
