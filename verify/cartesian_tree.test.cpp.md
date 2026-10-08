---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/cartesian_tree.hpp
    title: Cartesian Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/cartesian_tree
    links:
    - https://judge.yosupo.jp/problem/cartesian_tree
  bundledCode: "#line 1 \"verify/cartesian_tree.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\
    \n\n#include <iostream>\n#include <vector>\n\n#line 2 \"ds/cartesian_tree.hpp\"\
    \n\n#include <functional>\n#line 5 \"ds/cartesian_tree.hpp\"\n\nnamespace yesantikiss\
    \ {\n    template <class T, class Compare = std::less<T>>\n    struct CartesianTree\
    \ {\n        int n = 0;\n        std::vector<T> a;\n        std::vector<int> par,\
    \ left, right;\n        int root = -1;\n        Compare comp;\n    \n        CartesianTree()\
    \ {}\n    \n        CartesianTree(const std::vector<T>& _a, Compare _comp = Compare())\n\
    \            : n((int)_a.size()),\n              a(_a),\n              par(n,\
    \ -1),\n              left(n, -1),\n              right(n, -1),\n            \
    \  root(-1),\n              comp(_comp) {\n            build();\n        }\n \
    \   \n        // comp(a[i], a[j]) == true \u306A\u3089 i \u306E\u65B9\u304C j\
    \ \u3088\u308A\u4E0A\u306B\u6765\u308B\n        // less<T>    : min Cartesian\
    \ Tree\n        // greater<T> : max Cartesian Tree\n        void build() {\n \
    \           std::vector<int> st;\n            st.reserve(n);\n    \n         \
    \   for (int i = 0; i < n; i++) {\n                int last = -1;\n    \n    \
    \            while (!st.empty() && comp(a[i], a[st.back()])) {\n             \
    \       last = st.back();\n                    st.pop_back();\n              \
    \  }\n    \n                if (!st.empty()) {\n                    par[i] = st.back();\n\
    \                    right[st.back()] = i;\n                }\n    \n        \
    \        if (last != -1) {\n                    par[last] = i;\n             \
    \       left[i] = last;\n                }\n    \n                st.push_back(i);\n\
    \            }\n    \n            for (int i = 0; i < n; i++) {\n            \
    \    if (par[i] == -1) {\n                    root = i;\n                    break;\n\
    \                }\n            }\n        }\n    };\n}\n#line 7 \"verify/cartesian_tree.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n;\n    std::cin >> n;\n    std::vector<int> values(n);\n    for (int&\
    \ value : values) std::cin >> value;\n\n    yesantikiss::CartesianTree<int> tree(values);\n\
    \    tree.par[tree.root] = tree.root;\n    for (int i = 0; i < n; ++i) {\n   \
    \     if (i != 0) std::cout << ' ';\n        std::cout << tree.par[i];\n    }\n\
    \    std::cout << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\n\n#include\
    \ <iostream>\n#include <vector>\n\n#include \"ds/cartesian_tree.hpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ int n;\n    std::cin >> n;\n    std::vector<int> values(n);\n    for (int& value\
    \ : values) std::cin >> value;\n\n    yesantikiss::CartesianTree<int> tree(values);\n\
    \    tree.par[tree.root] = tree.root;\n    for (int i = 0; i < n; ++i) {\n   \
    \     if (i != 0) std::cout << ' ';\n        std::cout << tree.par[i];\n    }\n\
    \    std::cout << '\\n';\n}\n"
  dependsOn:
  - ds/cartesian_tree.hpp
  isVerificationFile: true
  path: verify/cartesian_tree.test.cpp
  requiredBy: []
  timestamp: '2026-10-08 13:39:00+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/cartesian_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/cartesian_tree.test.cpp
- /verify/verify/cartesian_tree.test.cpp.html
title: verify/cartesian_tree.test.cpp
---
