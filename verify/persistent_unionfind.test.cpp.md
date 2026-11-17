---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/rollback_dsu.hpp
    title: "\u30ED\u30FC\u30EB\u30D0\u30C3\u30AF\u4ED8\u304D Union-Find"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/persistent_unionfind
    links:
    - https://judge.yosupo.jp/problem/persistent_unionfind
  bundledCode: "#line 1 \"verify/persistent_unionfind.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/persistent_unionfind\"\n\n// \u7248\u3092\u9802\
    \u70B9\u3068\u3059\u308B\u6728\u3092\u4F5C\u308A\u3001DFS \u3067\u6F5C\u308B\u3068\
    \u304D\u306B merge\u3001\u623B\u308B\u3068\u304D\u306B undo \u3059\u308B\u3002\
    \n#include <iostream>\n#include <utility>\n#include <vector>\n\n#line 2 \"ds/rollback_dsu.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#line 6 \"ds/rollback_dsu.hpp\"\n\
    \nnamespace yesantikiss {\n    // ACL dsu \u98A8 + \u30ED\u30FC\u30EB\u30D0\u30C3\
    \u30AF\n    // \u7D4C\u8DEF\u5727\u7E2E\u3092\u305B\u305A union by size \u3060\
    \u3051\u3067\u4F75\u5408\u3059\u308B\u306E\u3067\u3001merge \u3092\u65B0\u3057\
    \u3044\u9806\u306B\n    // \u53D6\u308A\u6D88\u305B\u308B\u3002merge \u306F\u540C\
    \u3058\u6210\u5206\u3069\u3046\u3057\u3067\u3082\u5C65\u6B74\u3092 1 \u4EF6\u7A4D\
    \u3080\u306E\u3067\u3001merge 1 \u56DE\u3068\n    // undo 1 \u56DE\u304C\u5FC5\
    \u305A\u5BFE\u5FDC\u3059\u308B\u3002\n    struct rollback_dsu {\n        rollback_dsu()\
    \ : rollback_dsu(0) {}\n        explicit rollback_dsu(int n_)\n            : n(n_),\
    \ components(n_), parent_or_size(n_, -1) {}\n\n        int leader(int a) const\
    \ {\n            assert(0 <= a && a < n);\n            while (parent_or_size[a]\
    \ >= 0) a = parent_or_size[a];\n            return a;\n        }\n\n        bool\
    \ same(int a, int b) const { return leader(a) == leader(b); }\n\n        int size(int\
    \ a) const { return -parent_or_size[leader(a)]; }\n\n        // \u9023\u7D50\u6210\
    \u5206\u306E\u500B\u6570\n        int count() const { return components; }\n\n\
    \        // ACL dsu \u3068\u540C\u3058\u304F\u3001\u4F75\u5408\u5F8C\u306E leader\
    \ \u3092\u8FD4\u3059\n        int merge(int a, int b) {\n            int x = leader(a),\
    \ y = leader(b);\n            if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x,\
    \ y);\n            history.push_back({x, y, parent_or_size[x], parent_or_size[y]});\n\
    \            if (x == y) return x;\n            parent_or_size[x] += parent_or_size[y];\n\
    \            parent_or_size[y] = x;\n            components--;\n            return\
    \ x;\n        }\n\n        // \u76F4\u524D\u306E merge \u3092 1 \u56DE\u53D6\u308A\
    \u6D88\u3059\n        void undo() {\n            assert(!history.empty());\n \
    \           const record& last = history.back();\n            parent_or_size[last.x]\
    \ = last.old_x;\n            parent_or_size[last.y] = last.old_y;\n          \
    \  if (last.x != last.y) components++;\n            history.pop_back();\n    \
    \    }\n\n        // \u3053\u308C\u307E\u3067\u306B\u53D6\u308A\u6D88\u3055\u308C\
    \u305A\u306B\u6B8B\u3063\u3066\u3044\u308B merge \u306E\u56DE\u6570\n        int\
    \ snapshot() const { return (int)history.size(); }\n\n        // snapshot() \u304C\
    \ state \u3092\u8FD4\u3057\u305F\u6642\u70B9\u307E\u3067\u623B\u3059\n       \
    \ void rollback(int state) {\n            assert(0 <= state && state <= (int)history.size());\n\
    \            while ((int)history.size() > state) undo();\n        }\n\n      \
    \  // \u5404\u9802\u70B9\u306E leader \u3092\u4E00\u6642\u914D\u5217\u306B\u30E1\
    \u30E2\u3057\u306A\u304C\u3089\u6C42\u3081\u308B\u306E\u3067 O(N)\n        std::vector<std::vector<int>>\
    \ groups() const {\n            std::vector<int> leader_buf(n, -1), group_size(n),\
    \ path;\n            for (int i = 0; i < n; i++) {\n                int v = i;\n\
    \                while (leader_buf[v] < 0 && parent_or_size[v] >= 0) {\n     \
    \               path.push_back(v);\n                    v = parent_or_size[v];\n\
    \                }\n                int r = leader_buf[v] < 0 ? v : leader_buf[v];\n\
    \                leader_buf[v] = r;\n                for (int u : path) leader_buf[u]\
    \ = r;\n                path.clear();\n                group_size[r]++;\n    \
    \        }\n            std::vector<std::vector<int>> result(n);\n           \
    \ for (int i = 0; i < n; i++) result[i].reserve(group_size[i]);\n            for\
    \ (int i = 0; i < n; i++) result[leader_buf[i]].push_back(i);\n            result.erase(std::remove_if(result.begin(),\
    \ result.end(),\n                                        [](const auto& v) { return\
    \ v.empty(); }),\n                         result.end());\n            return\
    \ result;\n        }\n\n      private:\n        struct record {\n            int\
    \ x, y, old_x, old_y;\n        };\n        int n;\n        int components;\n \
    \       std::vector<int> parent_or_size; // root: -size, else: parent\n      \
    \  std::vector<record> history;\n    };\n}\n#line 9 \"verify/persistent_unionfind.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, q;\n    std::cin >> n >> q;\n\n    // \u9802\u70B9 0 \u304C\u521D\
    \u671F\u72B6\u614B\u3001\u9802\u70B9 i + 1 \u304C\u30AF\u30A8\u30EA i \u306E\u5F8C\
    \u306E\u7248\n    std::vector<int> type(q + 1, -1), u(q + 1), v(q + 1);\n    std::vector<std::vector<int>>\
    \ children(q + 1);\n    for (int i = 1; i <= q; i++) {\n        int k;\n     \
    \   std::cin >> type[i] >> k >> u[i] >> v[i];\n        children[k + 1].push_back(i);\n\
    \    }\n\n    yesantikiss::rollback_dsu dsu(n);\n    std::vector<int> answer(q\
    \ + 1, -1);\n    // \u975E\u8CA0\u306A\u3089\u5165\u308B\u9802\u70B9\u3001\u8CA0\
    \u306A\u3089 ~\u9802\u70B9 \u304B\u3089\u51FA\u308B\n    std::vector<int> stack{0};\n\
    \    while (!stack.empty()) {\n        int x = stack.back();\n        stack.pop_back();\n\
    \        if (x < 0) {\n            if (type[~x] == 0) dsu.undo();\n          \
    \  continue;\n        }\n        if (type[x] == 0) dsu.merge(u[x], v[x]);\n  \
    \      if (type[x] == 1) answer[x] = dsu.same(u[x], v[x]);\n        stack.push_back(~x);\n\
    \        for (int c : children[x]) stack.push_back(c);\n    }\n\n    for (int\
    \ i = 1; i <= q; i++) {\n        if (type[i] == 1) std::cout << answer[i] << '\\\
    n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_unionfind\"\n\
    \n// \u7248\u3092\u9802\u70B9\u3068\u3059\u308B\u6728\u3092\u4F5C\u308A\u3001\
    DFS \u3067\u6F5C\u308B\u3068\u304D\u306B merge\u3001\u623B\u308B\u3068\u304D\u306B\
    \ undo \u3059\u308B\u3002\n#include <iostream>\n#include <utility>\n#include <vector>\n\
    \n#include \"ds/rollback_dsu.hpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, q;\n    std::cin >> n >> q;\n\n    //\
    \ \u9802\u70B9 0 \u304C\u521D\u671F\u72B6\u614B\u3001\u9802\u70B9 i + 1 \u304C\
    \u30AF\u30A8\u30EA i \u306E\u5F8C\u306E\u7248\n    std::vector<int> type(q + 1,\
    \ -1), u(q + 1), v(q + 1);\n    std::vector<std::vector<int>> children(q + 1);\n\
    \    for (int i = 1; i <= q; i++) {\n        int k;\n        std::cin >> type[i]\
    \ >> k >> u[i] >> v[i];\n        children[k + 1].push_back(i);\n    }\n\n    yesantikiss::rollback_dsu\
    \ dsu(n);\n    std::vector<int> answer(q + 1, -1);\n    // \u975E\u8CA0\u306A\u3089\
    \u5165\u308B\u9802\u70B9\u3001\u8CA0\u306A\u3089 ~\u9802\u70B9 \u304B\u3089\u51FA\
    \u308B\n    std::vector<int> stack{0};\n    while (!stack.empty()) {\n       \
    \ int x = stack.back();\n        stack.pop_back();\n        if (x < 0) {\n   \
    \         if (type[~x] == 0) dsu.undo();\n            continue;\n        }\n \
    \       if (type[x] == 0) dsu.merge(u[x], v[x]);\n        if (type[x] == 1) answer[x]\
    \ = dsu.same(u[x], v[x]);\n        stack.push_back(~x);\n        for (int c :\
    \ children[x]) stack.push_back(c);\n    }\n\n    for (int i = 1; i <= q; i++)\
    \ {\n        if (type[i] == 1) std::cout << answer[i] << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/rollback_dsu.hpp
  isVerificationFile: true
  path: verify/persistent_unionfind.test.cpp
  requiredBy: []
  timestamp: '2026-11-17 16:31:42+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/persistent_unionfind.test.cpp
layout: document
redirect_from:
- /verify/verify/persistent_unionfind.test.cpp
- /verify/verify/persistent_unionfind.test.cpp.html
title: verify/persistent_unionfind.test.cpp
---
