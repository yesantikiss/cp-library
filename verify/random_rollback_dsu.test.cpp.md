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
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/random_rollback_dsu.test.cpp\"\n// \u7D20\u6734\u306A\
    \u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\u30E9\u30F3\u30C0\u30E0\
    \u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089 A + B \u3092\u89E3\u304F\
    \u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <iostream>\n#include <random>\n#include\
    \ <utility>\n#include <vector>\n\n#line 2 \"ds/rollback_dsu.hpp\"\n\n#line 6 \"\
    ds/rollback_dsu.hpp\"\n\nnamespace yesantikiss {\n    // ACL dsu \u98A8 + \u30ED\
    \u30FC\u30EB\u30D0\u30C3\u30AF\n    // \u7D4C\u8DEF\u5727\u7E2E\u3092\u305B\u305A\
    \ union by size \u3060\u3051\u3067\u4F75\u5408\u3059\u308B\u306E\u3067\u3001merge\
    \ \u3092\u65B0\u3057\u3044\u9806\u306B\n    // \u53D6\u308A\u6D88\u305B\u308B\u3002\
    merge \u306F\u540C\u3058\u6210\u5206\u3069\u3046\u3057\u3067\u3082\u5C65\u6B74\
    \u3092 1 \u4EF6\u7A4D\u3080\u306E\u3067\u3001merge 1 \u56DE\u3068\n    // undo\
    \ 1 \u56DE\u304C\u5FC5\u305A\u5BFE\u5FDC\u3059\u308B\u3002\n    struct rollback_dsu\
    \ {\n        rollback_dsu() : rollback_dsu(0) {}\n        explicit rollback_dsu(int\
    \ n_)\n            : n(n_), components(n_), parent_or_size(n_, -1) {}\n\n    \
    \    int leader(int a) const {\n            assert(0 <= a && a < n);\n       \
    \     while (parent_or_size[a] >= 0) a = parent_or_size[a];\n            return\
    \ a;\n        }\n\n        bool same(int a, int b) const { return leader(a) ==\
    \ leader(b); }\n\n        int size(int a) const { return -parent_or_size[leader(a)];\
    \ }\n\n        // \u9023\u7D50\u6210\u5206\u306E\u500B\u6570\n        int count()\
    \ const { return components; }\n\n        // ACL dsu \u3068\u540C\u3058\u304F\u3001\
    \u4F75\u5408\u5F8C\u306E leader \u3092\u8FD4\u3059\n        int merge(int a, int\
    \ b) {\n            int x = leader(a), y = leader(b);\n            if (-parent_or_size[x]\
    \ < -parent_or_size[y]) std::swap(x, y);\n            history.push_back({x, y,\
    \ parent_or_size[x], parent_or_size[y]});\n            if (x == y) return x;\n\
    \            parent_or_size[x] += parent_or_size[y];\n            parent_or_size[y]\
    \ = x;\n            components--;\n            return x;\n        }\n\n      \
    \  // \u76F4\u524D\u306E merge \u3092 1 \u56DE\u53D6\u308A\u6D88\u3059\n     \
    \   void undo() {\n            assert(!history.empty());\n            const record&\
    \ last = history.back();\n            parent_or_size[last.x] = last.old_x;\n \
    \           parent_or_size[last.y] = last.old_y;\n            if (last.x != last.y)\
    \ components++;\n            history.pop_back();\n        }\n\n        // \u3053\
    \u308C\u307E\u3067\u306B\u53D6\u308A\u6D88\u3055\u308C\u305A\u306B\u6B8B\u3063\
    \u3066\u3044\u308B merge \u306E\u56DE\u6570\n        int snapshot() const { return\
    \ (int)history.size(); }\n\n        // snapshot() \u304C state \u3092\u8FD4\u3057\
    \u305F\u6642\u70B9\u307E\u3067\u623B\u3059\n        void rollback(int state) {\n\
    \            assert(0 <= state && state <= (int)history.size());\n           \
    \ while ((int)history.size() > state) undo();\n        }\n\n        // \u5404\u9802\
    \u70B9\u306E leader \u3092\u4E00\u6642\u914D\u5217\u306B\u30E1\u30E2\u3057\u306A\
    \u304C\u3089\u6C42\u3081\u308B\u306E\u3067 O(N)\n        std::vector<std::vector<int>>\
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
    \  std::vector<record> history;\n    };\n}\n#line 12 \"verify/random_rollback_dsu.test.cpp\"\
    \n\nnamespace {\n    // \u5F35\u3063\u305F\u8FBA\u306E\u5217\u304B\u3089\u3001\
    \u5404\u9802\u70B9\u306E\u6210\u5206\u756A\u53F7 (\u6210\u5206\u5185\u3067\u6700\
    \u5C0F\u306E\u9802\u70B9) \u3092\u6C42\u3081\u308B\u3002\n    std::vector<int>\
    \ naive_labels(int n,\n                                  const std::vector<std::pair<int,\
    \ int>>& edges) {\n        std::vector<int> label(n);\n        for (int i = 0;\
    \ i < n; i++) label[i] = i;\n        bool changed = true;\n        while (changed)\
    \ {\n            changed = false;\n            for (auto [a, b] : edges) {\n \
    \               int m = std::min(label[a], label[b]);\n                if (label[a]\
    \ != m || label[b] != m) {\n                    label[a] = label[b] = m;\n   \
    \                 changed = true;\n                }\n            }\n        }\n\
    \        return label;\n    }\n\n    void check(const yesantikiss::rollback_dsu&\
    \ dsu, int n,\n               const std::vector<std::pair<int, int>>& edges) {\n\
    \        std::vector<int> label = naive_labels(n, edges);\n        std::vector<int>\
    \ naive_size(n);\n        int naive_count = 0;\n        for (int i = 0; i < n;\
    \ i++) {\n            naive_size[label[i]]++;\n            if (label[i] == i)\
    \ naive_count++;\n        }\n        assert(dsu.count() == naive_count);\n   \
    \     assert(dsu.snapshot() == (int)edges.size());\n        for (int a = 0; a\
    \ < n; a++) {\n            int r = dsu.leader(a);\n            assert(0 <= r &&\
    \ r < n && label[r] == label[a]);\n            assert(dsu.size(a) == naive_size[label[a]]);\n\
    \            for (int b = 0; b < n; b++) {\n                assert(dsu.same(a,\
    \ b) == (label[a] == label[b]));\n            }\n        }\n\n        std::vector<std::vector<int>>\
    \ expected(n);\n        for (int i = 0; i < n; i++) expected[label[i]].push_back(i);\n\
    \        expected.erase(std::remove_if(expected.begin(), expected.end(),\n   \
    \                                   [](const auto& g) { return g.empty(); }),\n\
    \                       expected.end());\n        auto actual = dsu.groups();\n\
    \        for (auto& g : actual) std::sort(g.begin(), g.end());\n        std::sort(actual.begin(),\
    \ actual.end());\n        assert(actual == expected);\n    }\n}\n\nint main()\
    \ {\n    std::mt19937 random(20261117);\n    auto uniform = [&](int low, int high)\
    \ {\n        return std::uniform_int_distribution<int>(low, high)(random);\n \
    \   };\n\n    {\n        yesantikiss::rollback_dsu empty;\n        assert(empty.count()\
    \ == 0 && empty.snapshot() == 0);\n        assert(empty.groups().empty());\n \
    \       empty.rollback(0);\n    }\n\n    for (int trial = 0; trial < 3000; ++trial)\
    \ {\n        int n = uniform(1, 12);\n        yesantikiss::rollback_dsu dsu(n);\n\
    \        // \u540C\u3058\u6210\u5206\u3069\u3046\u3057\u306E merge \u3082 1 \u4EF6\
    \u3068\u3057\u3066\u7A4D\u3080\n        std::vector<std::pair<int, int>> edges;\n\
    \        std::vector<int> snapshots;\n        check(dsu, n, edges);\n\n      \
    \  for (int query = 0; query < 60; ++query) {\n            int type = uniform(0,\
    \ 9);\n            if (type <= 4) {\n                int a = uniform(0, n - 1),\
    \ b = uniform(0, n - 1);\n                int ra = dsu.leader(a), rb = dsu.leader(b);\n\
    \                int size_a = dsu.size(a), size_b = dsu.size(b);\n           \
    \     int r = dsu.merge(a, b);\n                assert(r == dsu.leader(a) && r\
    \ == dsu.leader(b));\n                // union by size: \u5927\u304D\u3044\u65B9\
    \u306E leader \u304C\u6B8B\u308B\n                assert(r == ra || r == rb);\n\
    \                if (size_a > size_b) assert(r == ra);\n                if (size_a\
    \ < size_b) assert(r == rb);\n                edges.emplace_back(a, b);\n    \
    \        } else if (type <= 6) {\n                if (edges.empty()) continue;\n\
    \                dsu.undo();\n                edges.pop_back();\n            \
    \    // \u53D6\u308A\u6D88\u3057\u305F merge \u3088\u308A\u5F8C\u306E snapshot\
    \ \u306F\u4F7F\u3048\u306A\u304F\u306A\u308B\n                while (!snapshots.empty()\
    \ &&\n                       snapshots.back() > (int)edges.size()) {\n       \
    \             snapshots.pop_back();\n                }\n            } else if\
    \ (type == 7) {\n                snapshots.push_back(dsu.snapshot());\n      \
    \      } else {\n                // \u5165\u308C\u5B50\u306E snapshot \u306E\u3069\
    \u308C\u304B\u3078\u623B\u3059\n                if (snapshots.empty()) continue;\n\
    \                int i = uniform(0, (int)snapshots.size() - 1);\n            \
    \    int state = snapshots[i];\n                snapshots.resize(i + 1);\n   \
    \             dsu.rollback(state);\n                edges.resize(state);\n   \
    \             if (uniform(0, 1)) dsu.rollback(state); // \u540C\u3058\u6642\u70B9\
    \u3078\u306F\u4F55\u3082\u3057\u306A\u3044\n            }\n            check(dsu,\
    \ n, edges);\n        }\n        dsu.rollback(0);\n        edges.clear();\n  \
    \      check(dsu, n, edges);\n    }\n\n    // \u5927\u304D\u3081\u306E n \u3067\
    \u3001\u307E\u3068\u3081\u3066\u5DFB\u304D\u623B\u3057\u305F\u3042\u3068\u306E\
    \u72B6\u614B\u3068 groups \u3092\u78BA\u304B\u3081\u308B\u3002\n    {\n      \
    \  const int n = 1 << 12;\n        yesantikiss::rollback_dsu dsu(n);\n       \
    \ for (int step = 1; step < n; step *= 2) {\n            for (int i = 0; i + step\
    \ < n; i += 2 * step) {\n                dsu.merge(i + step, i);\n           \
    \ }\n        }\n        assert(dsu.count() == 1 && dsu.size(0) == n);\n      \
    \  int state = dsu.snapshot();\n        for (int i = 0; i < 1000; i++) {\n   \
    \         dsu.merge(uniform(0, n - 1), uniform(0, n - 1));\n        }\n      \
    \  assert(dsu.snapshot() == state + 1000 && dsu.count() == 1);\n        dsu.rollback(state);\n\
    \        dsu.rollback(0);\n        assert(dsu.count() == n && dsu.size(n - 1)\
    \ == 1);\n        assert((int)dsu.groups().size() == n);\n\n        // union by\
    \ size \u304C\u306A\u3051\u308C\u3070\u6DF1\u3055 N \u306E\u9396\u306B\u306A\u308B\
    \u4F75\u5408\u9806\n        for (int i = 1; i < n; i++) dsu.merge(i, i - 1);\n\
    \        assert(dsu.count() == 1);\n        auto groups = dsu.groups();\n    \
    \    assert(groups.size() == 1 && (int)groups[0].size() == n);\n    }\n\n    long\
    \ long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "// \u7D20\u6734\u306A\u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\
    \u30E9\u30F3\u30C0\u30E0\u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089\
    \ A + B \u3092\u89E3\u304F\u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <random>\n\
    #include <utility>\n#include <vector>\n\n#include \"ds/rollback_dsu.hpp\"\n\n\
    namespace {\n    // \u5F35\u3063\u305F\u8FBA\u306E\u5217\u304B\u3089\u3001\u5404\
    \u9802\u70B9\u306E\u6210\u5206\u756A\u53F7 (\u6210\u5206\u5185\u3067\u6700\u5C0F\
    \u306E\u9802\u70B9) \u3092\u6C42\u3081\u308B\u3002\n    std::vector<int> naive_labels(int\
    \ n,\n                                  const std::vector<std::pair<int, int>>&\
    \ edges) {\n        std::vector<int> label(n);\n        for (int i = 0; i < n;\
    \ i++) label[i] = i;\n        bool changed = true;\n        while (changed) {\n\
    \            changed = false;\n            for (auto [a, b] : edges) {\n     \
    \           int m = std::min(label[a], label[b]);\n                if (label[a]\
    \ != m || label[b] != m) {\n                    label[a] = label[b] = m;\n   \
    \                 changed = true;\n                }\n            }\n        }\n\
    \        return label;\n    }\n\n    void check(const yesantikiss::rollback_dsu&\
    \ dsu, int n,\n               const std::vector<std::pair<int, int>>& edges) {\n\
    \        std::vector<int> label = naive_labels(n, edges);\n        std::vector<int>\
    \ naive_size(n);\n        int naive_count = 0;\n        for (int i = 0; i < n;\
    \ i++) {\n            naive_size[label[i]]++;\n            if (label[i] == i)\
    \ naive_count++;\n        }\n        assert(dsu.count() == naive_count);\n   \
    \     assert(dsu.snapshot() == (int)edges.size());\n        for (int a = 0; a\
    \ < n; a++) {\n            int r = dsu.leader(a);\n            assert(0 <= r &&\
    \ r < n && label[r] == label[a]);\n            assert(dsu.size(a) == naive_size[label[a]]);\n\
    \            for (int b = 0; b < n; b++) {\n                assert(dsu.same(a,\
    \ b) == (label[a] == label[b]));\n            }\n        }\n\n        std::vector<std::vector<int>>\
    \ expected(n);\n        for (int i = 0; i < n; i++) expected[label[i]].push_back(i);\n\
    \        expected.erase(std::remove_if(expected.begin(), expected.end(),\n   \
    \                                   [](const auto& g) { return g.empty(); }),\n\
    \                       expected.end());\n        auto actual = dsu.groups();\n\
    \        for (auto& g : actual) std::sort(g.begin(), g.end());\n        std::sort(actual.begin(),\
    \ actual.end());\n        assert(actual == expected);\n    }\n}\n\nint main()\
    \ {\n    std::mt19937 random(20261117);\n    auto uniform = [&](int low, int high)\
    \ {\n        return std::uniform_int_distribution<int>(low, high)(random);\n \
    \   };\n\n    {\n        yesantikiss::rollback_dsu empty;\n        assert(empty.count()\
    \ == 0 && empty.snapshot() == 0);\n        assert(empty.groups().empty());\n \
    \       empty.rollback(0);\n    }\n\n    for (int trial = 0; trial < 3000; ++trial)\
    \ {\n        int n = uniform(1, 12);\n        yesantikiss::rollback_dsu dsu(n);\n\
    \        // \u540C\u3058\u6210\u5206\u3069\u3046\u3057\u306E merge \u3082 1 \u4EF6\
    \u3068\u3057\u3066\u7A4D\u3080\n        std::vector<std::pair<int, int>> edges;\n\
    \        std::vector<int> snapshots;\n        check(dsu, n, edges);\n\n      \
    \  for (int query = 0; query < 60; ++query) {\n            int type = uniform(0,\
    \ 9);\n            if (type <= 4) {\n                int a = uniform(0, n - 1),\
    \ b = uniform(0, n - 1);\n                int ra = dsu.leader(a), rb = dsu.leader(b);\n\
    \                int size_a = dsu.size(a), size_b = dsu.size(b);\n           \
    \     int r = dsu.merge(a, b);\n                assert(r == dsu.leader(a) && r\
    \ == dsu.leader(b));\n                // union by size: \u5927\u304D\u3044\u65B9\
    \u306E leader \u304C\u6B8B\u308B\n                assert(r == ra || r == rb);\n\
    \                if (size_a > size_b) assert(r == ra);\n                if (size_a\
    \ < size_b) assert(r == rb);\n                edges.emplace_back(a, b);\n    \
    \        } else if (type <= 6) {\n                if (edges.empty()) continue;\n\
    \                dsu.undo();\n                edges.pop_back();\n            \
    \    // \u53D6\u308A\u6D88\u3057\u305F merge \u3088\u308A\u5F8C\u306E snapshot\
    \ \u306F\u4F7F\u3048\u306A\u304F\u306A\u308B\n                while (!snapshots.empty()\
    \ &&\n                       snapshots.back() > (int)edges.size()) {\n       \
    \             snapshots.pop_back();\n                }\n            } else if\
    \ (type == 7) {\n                snapshots.push_back(dsu.snapshot());\n      \
    \      } else {\n                // \u5165\u308C\u5B50\u306E snapshot \u306E\u3069\
    \u308C\u304B\u3078\u623B\u3059\n                if (snapshots.empty()) continue;\n\
    \                int i = uniform(0, (int)snapshots.size() - 1);\n            \
    \    int state = snapshots[i];\n                snapshots.resize(i + 1);\n   \
    \             dsu.rollback(state);\n                edges.resize(state);\n   \
    \             if (uniform(0, 1)) dsu.rollback(state); // \u540C\u3058\u6642\u70B9\
    \u3078\u306F\u4F55\u3082\u3057\u306A\u3044\n            }\n            check(dsu,\
    \ n, edges);\n        }\n        dsu.rollback(0);\n        edges.clear();\n  \
    \      check(dsu, n, edges);\n    }\n\n    // \u5927\u304D\u3081\u306E n \u3067\
    \u3001\u307E\u3068\u3081\u3066\u5DFB\u304D\u623B\u3057\u305F\u3042\u3068\u306E\
    \u72B6\u614B\u3068 groups \u3092\u78BA\u304B\u3081\u308B\u3002\n    {\n      \
    \  const int n = 1 << 12;\n        yesantikiss::rollback_dsu dsu(n);\n       \
    \ for (int step = 1; step < n; step *= 2) {\n            for (int i = 0; i + step\
    \ < n; i += 2 * step) {\n                dsu.merge(i + step, i);\n           \
    \ }\n        }\n        assert(dsu.count() == 1 && dsu.size(0) == n);\n      \
    \  int state = dsu.snapshot();\n        for (int i = 0; i < 1000; i++) {\n   \
    \         dsu.merge(uniform(0, n - 1), uniform(0, n - 1));\n        }\n      \
    \  assert(dsu.snapshot() == state + 1000 && dsu.count() == 1);\n        dsu.rollback(state);\n\
    \        dsu.rollback(0);\n        assert(dsu.count() == n && dsu.size(n - 1)\
    \ == 1);\n        assert((int)dsu.groups().size() == n);\n\n        // union by\
    \ size \u304C\u306A\u3051\u308C\u3070\u6DF1\u3055 N \u306E\u9396\u306B\u306A\u308B\
    \u4F75\u5408\u9806\n        for (int i = 1; i < n; i++) dsu.merge(i, i - 1);\n\
    \        assert(dsu.count() == 1);\n        auto groups = dsu.groups();\n    \
    \    assert(groups.size() == 1 && (int)groups[0].size() == n);\n    }\n\n    long\
    \ long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - ds/rollback_dsu.hpp
  isVerificationFile: true
  path: verify/random_rollback_dsu.test.cpp
  requiredBy: []
  timestamp: '2026-11-17 16:31:42+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/random_rollback_dsu.test.cpp
layout: document
redirect_from:
- /verify/verify/random_rollback_dsu.test.cpp
- /verify/verify/random_rollback_dsu.test.cpp.html
title: verify/random_rollback_dsu.test.cpp
---
