---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/persistent_unionfind.test.cpp
    title: verify/persistent_unionfind.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/random_rollback_dsu.test.cpp
    title: verify/random_rollback_dsu.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"ds/rollback_dsu.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace yesantikiss {\n    // ACL dsu \u98A8\
    \ + \u30ED\u30FC\u30EB\u30D0\u30C3\u30AF\n    // \u7D4C\u8DEF\u5727\u7E2E\u3092\
    \u305B\u305A union by size \u3060\u3051\u3067\u4F75\u5408\u3059\u308B\u306E\u3067\
    \u3001merge \u3092\u65B0\u3057\u3044\u9806\u306B\n    // \u53D6\u308A\u6D88\u305B\
    \u308B\u3002merge \u306F\u540C\u3058\u6210\u5206\u3069\u3046\u3057\u3067\u3082\
    \u5C65\u6B74\u3092 1 \u4EF6\u7A4D\u3080\u306E\u3067\u3001merge 1 \u56DE\u3068\n\
    \    // undo 1 \u56DE\u304C\u5FC5\u305A\u5BFE\u5FDC\u3059\u308B\u3002\n    struct\
    \ rollback_dsu {\n        rollback_dsu() : rollback_dsu(0) {}\n        explicit\
    \ rollback_dsu(int n_)\n            : n(n_), components(n_), parent_or_size(n_,\
    \ -1) {}\n\n        int leader(int a) const {\n            assert(0 <= a && a\
    \ < n);\n            while (parent_or_size[a] >= 0) a = parent_or_size[a];\n \
    \           return a;\n        }\n\n        bool same(int a, int b) const { return\
    \ leader(a) == leader(b); }\n\n        int size(int a) const { return -parent_or_size[leader(a)];\
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
    \  std::vector<record> history;\n    };\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\
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
    \  std::vector<record> history;\n    };\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/rollback_dsu.hpp
  requiredBy: []
  timestamp: '2026-11-17 16:31:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/persistent_unionfind.test.cpp
  - verify/random_rollback_dsu.test.cpp
documentation_of: ds/rollback_dsu.hpp
layout: document
title: "\u30ED\u30FC\u30EB\u30D0\u30C3\u30AF\u4ED8\u304D Union-Find"
---

## 概要

`yesantikiss::rollback_dsu` は、直前の `merge` を取り消せる Union-Find です。
経路圧縮をせず union by size だけで併合するので、`merge` を新しい順に
`O(1)` で取り消せます。オフラインの動的連結性や、DFS しながら状態を巻き戻す
処理に使えます。

## API

- `rollback_dsu(n)`: `n` 頂点で初期化します。
- `merge(a, b)`: `a` と `b` の成分を併合し、併合後の leader を返します。
- `undo()`: 直前の `merge` を 1 回取り消します。
- `snapshot()`: 取り消されずに残っている `merge` の回数を返します。
- `rollback(state)`: `snapshot()` が `state` を返した時点まで戻します。
- `count()`: 連結成分の個数を返します。
- `leader(a)`, `same(a, b)`, `size(a)`, `groups()`: 通常の DSU 操作です。

```cpp
yesantikiss::rollback_dsu dsu(4);
dsu.merge(0, 1);
int state = dsu.snapshot();
dsu.merge(1, 2);
dsu.merge(0, 2);      // 同じ成分どうしでも履歴を積む
dsu.undo();           // merge(0, 2) を取り消す
dsu.rollback(state);  // merge(1, 2) も取り消す
```

## 要件・注意

- 頂点番号は `0 <= v < n` です。
- すでに同じ成分にある頂点どうしの `merge` も履歴を 1 件積みます。そのため
  `merge` 1 回と `undo` 1 回が必ず対応します。
- `undo()` は取り消せる `merge` が残っているときだけ呼んでください。
- `rollback(state)` の `state` は `0 <= state <= snapshot()` です。いったん
  `state` より前まで戻したあとに再び `merge` した場合、古い `state` は別の
  状態を指すので注意してください。
- `leader` などの参照系の関数は状態を書き換えず、`const` で呼べます。

## 計算量

`leader(a)`, `same(a, b)`, `size(a)`, `merge(a, b)` は `O(log N)`、`undo()` と
`count()`, `snapshot()` は `O(1)` です。`rollback(state)` は取り消す `merge`
1 回あたり `O(1)` です。`groups()` は各頂点の leader を一時配列にメモしながら
求めるので `O(N)` で、本体の配列は書き換えません。メモリは `O(N + M)`
（`M` は履歴の長さ）です。
