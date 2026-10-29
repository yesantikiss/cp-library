---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_li_chao_tree.hpp
    title: "\u52D5\u7684 Li Chao Tree"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/segment_add_get_min
    links:
    - https://judge.yosupo.jp/problem/segment_add_get_min
  bundledCode: "#line 1 \"verify/segment_add_get_min.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/segment_add_get_min\"\n\n#include <iostream>\n\
    \n#line 2 \"ds/dynamic_li_chao_tree.hpp\"\n\n#include <cassert>\n#include <cstddef>\n\
    #include <functional>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \nnamespace yesantikiss {\n    // \u52D5\u7684 Li Chao Tree\n    // - \u5EA7\u6A19\
    \u7BC4\u56F2 [lo, hi) \u306E\u6574\u6570\u70B9\u3067\u76F4\u7DDA\u30FB\u7DDA\u5206\
    \u306E\u6700\u5C0F\u5024\uFF08\u6700\u5927\u5024\uFF09\u3092\u6271\u3046\n   \
    \ // - \u76F4\u7DDA\u304C\u5165\u3063\u305F\u7D4C\u8DEF\u3060\u3051\u30CE\u30FC\
    \u30C9\u751F\u6210\n    // - add_all \u3067\u5168\u76F4\u7DDA\u306B\u4E00\u6B21\
    \u95A2\u6570\u3092\u4E00\u62EC\u52A0\u7B97\n    // - T: \u5EA7\u6A19\u306E\u578B\
    \uFF08\u6574\u6570\u578B\u306E\u307F\uFF09, U: \u4FC2\u6570\u3068\u8A55\u4FA1\u306B\
    \u4F7F\u3046\u578B\uFF08\u30AA\u30FC\u30D0\u30FC\u30D5\u30ED\u30FC\u3059\u308B\
    \u306A\u3089 __int128\uFF09\n    // - Compare: std::less<> \u306A\u3089\u6700\u5C0F\
    \u5024\u3001std::greater<> \u306A\u3089\u6700\u5927\u5024\n\n    template <class\
    \ T, class Compare = std::less<>, class U = T>\n    struct DynamicLiChaoTree {\n\
    \        static_assert(std::is_integral_v<T> || std::is_same_v<T, __int128>,\n\
    \                      \"T must be an integer type\");\n\n    private:\n     \
    \   struct Line {\n            U a, b;\n            U eval(T x) const { return\
    \ a * U(x) + b; }\n        };\n\n        struct Node {\n            Line line{U(0),\
    \ U(0)};\n            bool has = false;\n            int l = -1, r = -1;\n   \
    \     };\n\n        T lo_ = 0, hi_ = 1;\n        U add_a_ = 0, add_b_ = 0;\n \
    \       int root_ = -1;\n        std::vector<Node> pool_;\n\n        static bool\
    \ better(const Line& f, const Line& g, T x) {\n            return Compare{}(f.eval(x),\
    \ g.eval(x));\n        }\n\n        int new_node() {\n            pool_.emplace_back();\n\
    \            return (int)pool_.size() - 1;\n        }\n\n        int child(int\
    \ v, bool right) {\n            int c = right ? pool_[v].r : pool_[v].l;\n   \
    \         if (c == -1) {\n                c = new_node();\n                (right\
    \ ? pool_[v].r : pool_[v].l) = c;\n            }\n            return c;\n    \
    \    }\n\n        // \u30CE\u30FC\u30C9 v\uFF08\u62C5\u5F53\u533A\u9593 [l, r)\uFF09\
    \u4EE5\u4E0B\u306B\u76F4\u7DDA f \u3092\u5165\u308C\u308B\n        void insert_line(int\
    \ v, T l, T r, Line f) {\n            while (true) {\n                Node& nd\
    \ = pool_[v];\n                if (!nd.has) {\n                    nd.line = f;\n\
    \                    nd.has = true;\n                    return;\n           \
    \     }\n                bool left_better = better(f, nd.line, l);\n         \
    \       bool right_better = better(f, nd.line, r - 1);\n                // \u533A\
    \u9593\u306E\u4E21\u7AEF\u3067\u8CA0\u3051\u308B\u306A\u3089\u5168\u4F53\u3067\
    \u8CA0\u3051\u3001\u4E21\u7AEF\u3067\u52DD\u3064\u306A\u3089\u5168\u4F53\u3067\
    \u52DD\u3061\n                if (!left_better && !right_better) return;\n   \
    \             if (left_better && right_better) {\n                    nd.line\
    \ = f;\n                    return;\n                }\n                T m =\
    \ l + (r - l) / 2;\n                bool mid_better = better(f, nd.line, m);\n\
    \                if (mid_better) std::swap(nd.line, f);\n                if (r\
    \ - l == 1) return;\n                if (left_better != mid_better) {\n      \
    \              v = child(v, false);\n                    r = m;\n            \
    \    } else {\n                    v = child(v, true);\n                    l\
    \ = m;\n                }\n            }\n        }\n\n        void insert_segment(int\
    \ v, T nl, T nr, T l, T r, const Line& f) {\n            if (r <= nl || nr <=\
    \ l) return;\n            if (l <= nl && nr <= r) {\n                insert_line(v,\
    \ nl, nr, f);\n                return;\n            }\n            T m = nl +\
    \ (nr - nl) / 2;\n            if (l < m) insert_segment(child(v, false), nl, m,\
    \ l, r, f);\n            if (m < r) insert_segment(child(v, true), m, nr, l, r,\
    \ f);\n        }\n\n        // x \u3092\u901A\u308B\u7D4C\u8DEF\u4E0A\u306E\u6700\
    \u826F\u5024\u3002\u76F4\u7DDA\u304C\u306A\u3051\u308C\u3070 first = false\n \
    \       std::pair<bool, U> query(T x) const {\n            assert(lo_ <= x &&\
    \ x < hi_);\n            bool found = false;\n            U best = 0;\n      \
    \      int v = root_;\n            T l = lo_, r = hi_;\n            while (v !=\
    \ -1) {\n                const Node& nd = pool_[v];\n                if (nd.has)\
    \ {\n                    U y = nd.line.eval(x);\n                    if (!found\
    \ || Compare{}(y, best)) best = y;\n                    found = true;\n      \
    \          }\n                if (r - l == 1) break;\n                T m = l\
    \ + (r - l) / 2;\n                if (x < m) {\n                    v = nd.l;\n\
    \                    r = m;\n                } else {\n                    v =\
    \ nd.r;\n                    l = m;\n                }\n            }\n      \
    \      return {found, best};\n        }\n\n    public:\n        DynamicLiChaoTree()\
    \ = default;\n        DynamicLiChaoTree(T lo, T hi) { init(lo, hi); }\n\n    \
    \    void init(T lo, T hi) {\n            assert(lo < hi);\n            lo_ =\
    \ lo;\n            hi_ = hi;\n            add_a_ = add_b_ = 0;\n            root_\
    \ = -1;\n            pool_.clear();\n        }\n\n        void reserve_nodes(std::size_t\
    \ m) { pool_.reserve(m); }\n\n        // \u76F4\u7DDA ax + b \u3092\u5168\u57DF\
    \u306B\u8FFD\u52A0\n        void add_line(U a, U b) {\n            if (root_ ==\
    \ -1) root_ = new_node();\n            insert_line(root_, lo_, hi_, Line{a - add_a_,\
    \ b - add_b_});\n        }\n\n        // \u7DDA\u5206 ax + b \u3092 [l, r) \u306B\
    \u3060\u3051\u8FFD\u52A0\n        void add_segment(U a, U b, T l, T r) {\n   \
    \         assert(lo_ <= l && l <= r && r <= hi_);\n            if (l == r) return;\n\
    \            if (root_ == -1) root_ = new_node();\n            insert_segment(root_,\
    \ lo_, hi_, l, r,\n                           Line{a - add_a_, b - add_b_});\n\
    \        }\n\n        // \u8FFD\u52A0\u6E08\u307F\u306E\u3059\u3079\u3066\u306E\
    \u76F4\u7DDA\u306B px + q \u3092\u52A0\u7B97\n        void add_all(U p, U q) {\n\
    \            add_a_ += p;\n            add_b_ += q;\n        }\n\n        bool\
    \ has_line(T x) const { return query(x).first; }\n\n        // x \u3067\u306E\u6700\
    \u5C0F\u5024\uFF08std::greater<> \u306A\u3089\u6700\u5927\u5024\uFF09\u3002x \u306B\
    \u76F4\u7DDA\u304C\u3042\u308B\u5FC5\u8981\u3042\u308A\n        U get(T x) const\
    \ {\n            std::pair<bool, U> res = query(x);\n            assert(res.first);\n\
    \            return res.second + add_a_ * U(x) + add_b_;\n        }\n    };\n\
    }\n#line 6 \"verify/segment_add_get_min.test.cpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n\n    yesantikiss::DynamicLiChaoTree<long\
    \ long> lines(-1000000000, 1000000001);\n    lines.reserve_nodes(12000000);\n\
    \    for (int i = 0; i < n; ++i) {\n        long long l, r, a, b;\n        std::cin\
    \ >> l >> r >> a >> b;\n        lines.add_segment(a, b, l, r);\n    }\n    while\
    \ (q--) {\n        int type;\n        std::cin >> type;\n        if (type == 0)\
    \ {\n            long long l, r, a, b;\n            std::cin >> l >> r >> a >>\
    \ b;\n            lines.add_segment(a, b, l, r);\n        } else {\n         \
    \   long long p;\n            std::cin >> p;\n            if (lines.has_line(p))\
    \ {\n                std::cout << lines.get(p) << '\\n';\n            } else {\n\
    \                std::cout << \"INFINITY\\n\";\n            }\n        }\n   \
    \ }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/segment_add_get_min\"\n\
    \n#include <iostream>\n\n#include \"ds/dynamic_li_chao_tree.hpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ int n, q;\n    std::cin >> n >> q;\n\n    yesantikiss::DynamicLiChaoTree<long\
    \ long> lines(-1000000000, 1000000001);\n    lines.reserve_nodes(12000000);\n\
    \    for (int i = 0; i < n; ++i) {\n        long long l, r, a, b;\n        std::cin\
    \ >> l >> r >> a >> b;\n        lines.add_segment(a, b, l, r);\n    }\n    while\
    \ (q--) {\n        int type;\n        std::cin >> type;\n        if (type == 0)\
    \ {\n            long long l, r, a, b;\n            std::cin >> l >> r >> a >>\
    \ b;\n            lines.add_segment(a, b, l, r);\n        } else {\n         \
    \   long long p;\n            std::cin >> p;\n            if (lines.has_line(p))\
    \ {\n                std::cout << lines.get(p) << '\\n';\n            } else {\n\
    \                std::cout << \"INFINITY\\n\";\n            }\n        }\n   \
    \ }\n}\n"
  dependsOn:
  - ds/dynamic_li_chao_tree.hpp
  isVerificationFile: true
  path: verify/segment_add_get_min.test.cpp
  requiredBy: []
  timestamp: '2026-10-29 20:48:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/segment_add_get_min.test.cpp
layout: document
redirect_from:
- /verify/verify/segment_add_get_min.test.cpp
- /verify/verify/segment_add_get_min.test.cpp.html
title: verify/segment_add_get_min.test.cpp
---
