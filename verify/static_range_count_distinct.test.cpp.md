---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/mo.hpp
    title: Mo's algorithm
  - icon: ':heavy_check_mark:'
    path: ds/compressor.hpp
    title: "\u5EA7\u6A19\u5727\u7E2E"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_count_distinct
    links:
    - https://judge.yosupo.jp/problem/static_range_count_distinct
  bundledCode: "#line 1 \"verify/static_range_count_distinct.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/static_range_count_distinct\"\n\n#include\
    \ <iostream>\n#include <vector>\n\n#line 2 \"algo/mo.hpp\"\n\n#include <algorithm>\n\
    #include <cmath>\n#include <numeric>\n#include <utility>\n#line 8 \"algo/mo.hpp\"\
    \n\nnamespace yesantikiss {\n    struct Mo {\n        int n;\n        std::vector<std::pair<int,\
    \ int>> queries; // [l, r)\n    \n        explicit Mo(int n) : n(n) {}\n     \
    \   void add_query(int l, int r) { queries.emplace_back(l, r); }\n    \n     \
    \   // add(i), del(i) \u3057\u304B\u8981\u3089\u306A\u3044\u30B1\u30FC\u30B9\uFF08\
    \u4E92\u63DB\uFF09\n        template <class Add, class Del, class Out>\n     \
    \   void solve(const Add& add, const Del& del, const Out& out) {\n           \
    \ solve(add, add, del, del, out); // \u5DE6\u53F3\u540C\u3058\u95A2\u6570\u3068\
    \u3057\u3066\u6271\u3046\n        }\n    \n        // \u5DE6\u53F3\u3067 add/del\
    \ \u3092\u5206\u3051\u305F\u3044\u30B1\u30FC\u30B9\n        // addL: \u5DE6\u306B\
    \u4F38\u3070\u3059\u3068\u304D\u306B\u8FFD\u52A0 (l--)\n        // addR: \u53F3\
    \u306B\u4F38\u3070\u3059\u3068\u304D\u306B\u8FFD\u52A0 (r++)\n        // delL:\
    \ \u5DE6\u3092\u7E2E\u3081\u308B\u3068\u304D\u306B\u524A\u9664 (l++)\n       \
    \ // delR: \u53F3\u3092\u7E2E\u3081\u308B\u3068\u304D\u306B\u524A\u9664 (r--)\n\
    \        template <class AddL, class AddR, class DelL, class DelR, class Out>\n\
    \        void solve(const AddL& addL, const AddR& addR, const DelL& delL, const\
    \ DelR& delR, const Out& out) {\n            int q = (int)queries.size();\n  \
    \          if (q == 0) return;\n    \n            int bs = std::max(1, (int)(n\
    \ / std::sqrt((double)q)));\n            std::vector<int> ord(q);\n          \
    \  std::iota(ord.begin(), ord.end(), 0);\n    \n            std::sort(ord.begin(),\
    \ ord.end(), [&](int a, int b) {\n                int ab = queries[a].first /\
    \ bs, bb = queries[b].first / bs;\n                if (ab != bb) return ab < bb;\n\
    \                return (ab & 1) ? queries[a].second > queries[b].second\n   \
    \                             : queries[a].second < queries[b].second;\n     \
    \       });\n    \n            int l = 0, r = 0;\n            for (int idx : ord)\
    \ {\n                auto [ql, qr] = queries[idx];\n    \n                while\
    \ (l > ql) addL(--l);\n                while (r < qr) addR(r++);\n           \
    \     while (l < ql) delL(l++);\n                while (r > qr) delR(--r);\n \
    \   \n                out(idx);\n            }\n        }\n    };\n    \n}\n#line\
    \ 2 \"ds/compressor.hpp\"\n\n#line 4 \"ds/compressor.hpp\"\n#include <cassert>\n\
    #line 6 \"ds/compressor.hpp\"\n\nnamespace yesantikiss {\n    template <class\
    \ T>\n    struct Compressor {\n        std::vector<T> xs;   // \u8FFD\u52A0\u3055\
    \u308C\u305F\u5024\uFF08\u91CD\u8907\u3042\u308A\uFF09\n        std::vector<T>\
    \ v;    // \u30BD\u30FC\u30C8\u6E08\u307F\u30E6\u30CB\u30FC\u30AF\u5217\n    \
    \    bool built = false;\n    \n        // \u5024\u3092\u8FFD\u52A0: \u5E73\u5747\
    \ O(1)\n        void add(const T& x) {\n            xs.push_back(x);\n       \
    \ }\n    \n        // \u7BC4\u56F2\u8FFD\u52A0: O(k)\n        template <class\
    \ It>\n        void add_range(It first, It last) {\n            xs.insert(xs.end(),\
    \ first, last);\n        }\n    \n        // \u69CB\u7BC9: O(n log n)  n = add\
    \ \u3055\u308C\u305F\u7DCF\u6570\n        void build() {\n            v = xs;\n\
    \            std::sort(v.begin(), v.end());\n            v.erase(std::unique(v.begin(),\
    \ v.end()), v.end());\n            built = true;\n        }\n    \n        //\
    \ \u5727\u7E2E\u5F8C\u306E\u8981\u7D20\u6570: O(1)\n        int size() const {\n\
    \            return (int)v.size();\n        }\n    \n        // x \u306E\u5727\
    \u7E2E\u5F8C\u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\u3092\u8FD4\u3059\u3002\u5B58\
    \u5728\u3057\u306A\u3051\u308C\u3070 -1: O(log n)\n        int get(const T& x)\
    \ const {\n            assert(built);\n            auto it = std::lower_bound(v.begin(),\
    \ v.end(), x);\n            if (it == v.end() || *it != x) return -1;\n      \
    \      return (int)(it - v.begin());\n        }\n    \n        // x \u304C\u5B58\
    \u5728\u3059\u308B\u304B: O(log n)\n        bool has(const T& x) const {\n   \
    \         return get(x) != -1;\n        }\n    \n        // v[i] >= x \u3068\u306A\
    \u308B\u6700\u5C0F i \u3092\u8FD4\u3059\u3002\u5168\u3066 < x \u306A\u3089 size():\
    \ O(log n)\n        int lower_bound(const T& x) const {\n            assert(built);\n\
    \            return (int)(std::lower_bound(v.begin(), v.end(), x) - v.begin());\n\
    \        }\n    \n        // v[i] > x \u3068\u306A\u308B\u6700\u5C0F i \u3092\u8FD4\
    \u3059\u3002\u5168\u3066 <= x \u306A\u3089 size(): O(log n)\n        int upper_bound(const\
    \ T& x) const {\n            assert(built);\n            return (int)(std::upper_bound(v.begin(),\
    \ v.end(), x) - v.begin());\n        }\n    \n        // \u5727\u7E2E\u5024 \u2192\
    \ \u5143\u306E\u5024: O(1)\n        const T& value(int idx) const {\n        \
    \    assert(built);\n            return v[idx];\n        }\n    \n        // \u914D\
    \u5217\u3092\u5727\u7E2E\u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\u5217\u306B\u5909\
    \u63DB\u3057\u3066\u8FD4\u3059\uFF08\u5B58\u5728\u3057\u306A\u3044\u5024\u306F\
    \ -1\uFF09: O(k log n)\n        std::vector<int> map(const std::vector<T>& a)\
    \ const {\n            assert(built);\n            std::vector<int> res; res.reserve(a.size());\n\
    \            for (auto& x : a) res.push_back(get(x));\n            return res;\n\
    \        }\n    };\n}\n#line 8 \"verify/static_range_count_distinct.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<int> values(n);\n\
    \    yesantikiss::Compressor<int> compressor;\n    for (int& value : values) {\n\
    \        std::cin >> value;\n        compressor.add(value);\n    }\n    compressor.build();\n\
    \    values = compressor.map(values);\n\n    yesantikiss::Mo mo(n);\n    for (int\
    \ i = 0; i < q; ++i) {\n        int left, right;\n        std::cin >> left >>\
    \ right;\n        mo.add_query(left, right);\n    }\n\n    std::vector<int> frequency(compressor.size());\n\
    \    std::vector<int> answer(q);\n    int distinct = 0;\n    auto add = [&](int\
    \ index) {\n        if (frequency[values[index]]++ == 0) ++distinct;\n    };\n\
    \    auto erase = [&](int index) {\n        if (--frequency[values[index]] ==\
    \ 0) --distinct;\n    };\n    mo.solve(add, erase, [&](int query) {\n        answer[query]\
    \ = distinct;\n    });\n\n    for (int value : answer) std::cout << value << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_count_distinct\"\
    \n\n#include <iostream>\n#include <vector>\n\n#include \"algo/mo.hpp\"\n#include\
    \ \"ds/compressor.hpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n\n    std::vector<int>\
    \ values(n);\n    yesantikiss::Compressor<int> compressor;\n    for (int& value\
    \ : values) {\n        std::cin >> value;\n        compressor.add(value);\n  \
    \  }\n    compressor.build();\n    values = compressor.map(values);\n\n    yesantikiss::Mo\
    \ mo(n);\n    for (int i = 0; i < q; ++i) {\n        int left, right;\n      \
    \  std::cin >> left >> right;\n        mo.add_query(left, right);\n    }\n\n \
    \   std::vector<int> frequency(compressor.size());\n    std::vector<int> answer(q);\n\
    \    int distinct = 0;\n    auto add = [&](int index) {\n        if (frequency[values[index]]++\
    \ == 0) ++distinct;\n    };\n    auto erase = [&](int index) {\n        if (--frequency[values[index]]\
    \ == 0) --distinct;\n    };\n    mo.solve(add, erase, [&](int query) {\n     \
    \   answer[query] = distinct;\n    });\n\n    for (int value : answer) std::cout\
    \ << value << '\\n';\n}\n"
  dependsOn:
  - algo/mo.hpp
  - ds/compressor.hpp
  isVerificationFile: true
  path: verify/static_range_count_distinct.test.cpp
  requiredBy: []
  timestamp: '2026-08-25 15:58:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/static_range_count_distinct.test.cpp
layout: document
redirect_from:
- /verify/verify/static_range_count_distinct.test.cpp
- /verify/verify/static_range_count_distinct.test.cpp.html
title: verify/static_range_count_distinct.test.cpp
---
