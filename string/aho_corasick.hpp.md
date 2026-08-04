---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: tests/test.cpp
    title: tests/test.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/aho_corasick.test.cpp
    title: verify/aho_corasick.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"string/aho_corasick.hpp\"\n\n#include <array>\n#include\
    \ <cassert>\n#include <queue>\n#include <string>\n#include <vector>\n\nnamespace\
    \ yesantikiss {\n    template<int SIGMA = 26, char BASE = 'a'>\n    struct AhoCorasick\
    \ {\n        struct Node {\n            std::array<int, SIGMA> nxt;\n        \
    \    int link = 0;\n            int parent = -1;\n            int pch = -1;\n\
    \    \n            Node(int parent = -1, int pch = -1)\n                : parent(parent),\
    \ pch(pch) {\n                nxt.fill(-1);\n            }\n        };\n    \n\
    \        std::vector<Node> nodes;\n        std::vector<int> order;\n    \n   \
    \     AhoCorasick() {\n            nodes.emplace_back();\n        }\n    \n  \
    \      int enc(char ch) const {\n            return ch - BASE;\n        }\n  \
    \  \n        int add(const std::string& s) {\n            int v = 0;\n       \
    \     for (char ch : s) {\n                int c = enc(ch);\n                assert(0\
    \ <= c && c < SIGMA);\n    \n                if (nodes[v].nxt[c] == -1) {\n  \
    \                  nodes[v].nxt[c] = (int)nodes.size();\n                    nodes.emplace_back(v,\
    \ c);\n                }\n                v = nodes[v].nxt[c];\n            }\n\
    \            return v;\n        }\n    \n        void build() {\n            std::queue<int>\
    \ q;\n            order.clear();\n            order.push_back(0);\n    \n    \
    \        for (int c = 0; c < SIGMA; c++) {\n                int u = nodes[0].nxt[c];\n\
    \                if (u == -1) {\n                    nodes[0].nxt[c] = 0;\n  \
    \              } else {\n                    nodes[u].link = 0;\n            \
    \        q.push(u);\n                }\n            }\n    \n            while\
    \ (!q.empty()) {\n                int v = q.front();\n                q.pop();\n\
    \                order.push_back(v);\n    \n                for (int c = 0; c\
    \ < SIGMA; c++) {\n                    int u = nodes[v].nxt[c];\n    \n      \
    \              if (u == -1) {\n                        nodes[v].nxt[c] = nodes[nodes[v].link].nxt[c];\n\
    \                    } else {\n                        nodes[u].link = nodes[nodes[v].link].nxt[c];\n\
    \                        q.push(u);\n                    }\n                }\n\
    \            }\n        }\n    \n        int move(int v, int c) const {\n    \
    \        return nodes[v].nxt[c];\n        }\n    \n        int move(int v, char\
    \ ch) const {\n            return move(v, enc(ch));\n        }\n    \n       \
    \ int link(int v) const {\n            return nodes[v].link;\n        }\n    \n\
    \        int parent(int v) const {\n            return nodes[v].parent;\n    \
    \    }\n    \n        int size() const {\n            return (int)nodes.size();\n\
    \        }\n    };\n}\n"
  code: "#pragma once\n\n#include <array>\n#include <cassert>\n#include <queue>\n\
    #include <string>\n#include <vector>\n\nnamespace yesantikiss {\n    template<int\
    \ SIGMA = 26, char BASE = 'a'>\n    struct AhoCorasick {\n        struct Node\
    \ {\n            std::array<int, SIGMA> nxt;\n            int link = 0;\n    \
    \        int parent = -1;\n            int pch = -1;\n    \n            Node(int\
    \ parent = -1, int pch = -1)\n                : parent(parent), pch(pch) {\n \
    \               nxt.fill(-1);\n            }\n        };\n    \n        std::vector<Node>\
    \ nodes;\n        std::vector<int> order;\n    \n        AhoCorasick() {\n   \
    \         nodes.emplace_back();\n        }\n    \n        int enc(char ch) const\
    \ {\n            return ch - BASE;\n        }\n    \n        int add(const std::string&\
    \ s) {\n            int v = 0;\n            for (char ch : s) {\n            \
    \    int c = enc(ch);\n                assert(0 <= c && c < SIGMA);\n    \n  \
    \              if (nodes[v].nxt[c] == -1) {\n                    nodes[v].nxt[c]\
    \ = (int)nodes.size();\n                    nodes.emplace_back(v, c);\n      \
    \          }\n                v = nodes[v].nxt[c];\n            }\n          \
    \  return v;\n        }\n    \n        void build() {\n            std::queue<int>\
    \ q;\n            order.clear();\n            order.push_back(0);\n    \n    \
    \        for (int c = 0; c < SIGMA; c++) {\n                int u = nodes[0].nxt[c];\n\
    \                if (u == -1) {\n                    nodes[0].nxt[c] = 0;\n  \
    \              } else {\n                    nodes[u].link = 0;\n            \
    \        q.push(u);\n                }\n            }\n    \n            while\
    \ (!q.empty()) {\n                int v = q.front();\n                q.pop();\n\
    \                order.push_back(v);\n    \n                for (int c = 0; c\
    \ < SIGMA; c++) {\n                    int u = nodes[v].nxt[c];\n    \n      \
    \              if (u == -1) {\n                        nodes[v].nxt[c] = nodes[nodes[v].link].nxt[c];\n\
    \                    } else {\n                        nodes[u].link = nodes[nodes[v].link].nxt[c];\n\
    \                        q.push(u);\n                    }\n                }\n\
    \            }\n        }\n    \n        int move(int v, int c) const {\n    \
    \        return nodes[v].nxt[c];\n        }\n    \n        int move(int v, char\
    \ ch) const {\n            return move(v, enc(ch));\n        }\n    \n       \
    \ int link(int v) const {\n            return nodes[v].link;\n        }\n    \n\
    \        int parent(int v) const {\n            return nodes[v].parent;\n    \
    \    }\n    \n        int size() const {\n            return (int)nodes.size();\n\
    \        }\n    };\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: string/aho_corasick.hpp
  requiredBy:
  - tests/test.cpp
  timestamp: '2026-08-04 23:10:17+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/aho_corasick.test.cpp
documentation_of: string/aho_corasick.hpp
layout: document
title: Aho-Corasick automaton
---

## 概要

`yesantikiss::AhoCorasick<SIGMA, BASE>` は、複数パターンの文字列照合に使う
Aho-Corasick オートマトンです。既定では `'a'` から始まる英小文字 26 文字を
扱います。

## API

- `add(s)`: パターンを Trie に追加し、その終端ノード番号を返します。
- `build()`: failure link と全遷移を構築します。
- `move(v, c)`, `move(v, ch)`: 状態 `v` から遷移します。
- `link(v)`: failure link、`parent(v)`: Trie 上の親を返します。
- `size()`: ノード数を返します。
- `order`: 根から始まる BFS 順のノード列です。failure link を使った集計に
  利用できます。

## 要件・注意

- すべてのパターンを `add` してから `build()` を一度呼んでください。
  構築後の追加や再構築には対応していません。
- 文字 `ch` は `BASE <= ch < BASE + SIGMA` を満たす必要があります。
- 遷移を使う前に `build()` が必要です。
- パターンの終端情報は利用側で `add` の返り値として保持してください。

## 計算量

パターン総長を `L`、ノード数を `V` とすると、追加は合計 `O(L)`、構築は
`O(V * SIGMA)`、一文字の遷移は `O(1)` です。メモリは `O(V * SIGMA)` です。
