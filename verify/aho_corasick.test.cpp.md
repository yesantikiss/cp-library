---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/aho_corasick.hpp
    title: Aho-Corasick automaton
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aho_corasick
    links:
    - https://judge.yosupo.jp/problem/aho_corasick
  bundledCode: "#line 1 \"verify/aho_corasick.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aho_corasick\"\
    \n\n#include <iostream>\n#include <string>\n#include <vector>\n\n#line 2 \"string/aho_corasick.hpp\"\
    \n\n#include <array>\n#include <cassert>\n#include <queue>\n#line 8 \"string/aho_corasick.hpp\"\
    \n\nnamespace yesantikiss {\n    template<int SIGMA = 26, char BASE = 'a'>\n \
    \   struct AhoCorasick {\n        struct Node {\n            std::array<int, SIGMA>\
    \ nxt;\n            int link = 0;\n            int parent = -1;\n            int\
    \ pch = -1;\n    \n            Node(int parent = -1, int pch = -1)\n         \
    \       : parent(parent), pch(pch) {\n                nxt.fill(-1);\n        \
    \    }\n        };\n    \n        std::vector<Node> nodes;\n        std::vector<int>\
    \ order;\n    \n        AhoCorasick() {\n            nodes.emplace_back();\n \
    \       }\n    \n        int enc(char ch) const {\n            return ch - BASE;\n\
    \        }\n    \n        int add(const std::string& s) {\n            int v =\
    \ 0;\n            for (char ch : s) {\n                int c = enc(ch);\n    \
    \            assert(0 <= c && c < SIGMA);\n    \n                if (nodes[v].nxt[c]\
    \ == -1) {\n                    nodes[v].nxt[c] = (int)nodes.size();\n       \
    \             nodes.emplace_back(v, c);\n                }\n                v\
    \ = nodes[v].nxt[c];\n            }\n            return v;\n        }\n    \n\
    \        void build() {\n            std::queue<int> q;\n            order.clear();\n\
    \            order.push_back(0);\n    \n            for (int c = 0; c < SIGMA;\
    \ c++) {\n                int u = nodes[0].nxt[c];\n                if (u == -1)\
    \ {\n                    nodes[0].nxt[c] = 0;\n                } else {\n    \
    \                nodes[u].link = 0;\n                    q.push(u);\n        \
    \        }\n            }\n    \n            while (!q.empty()) {\n          \
    \      int v = q.front();\n                q.pop();\n                order.push_back(v);\n\
    \    \n                for (int c = 0; c < SIGMA; c++) {\n                   \
    \ int u = nodes[v].nxt[c];\n    \n                    if (u == -1) {\n       \
    \                 nodes[v].nxt[c] = nodes[nodes[v].link].nxt[c];\n           \
    \         } else {\n                        nodes[u].link = nodes[nodes[v].link].nxt[c];\n\
    \                        q.push(u);\n                    }\n                }\n\
    \            }\n        }\n    \n        int move(int v, int c) const {\n    \
    \        return nodes[v].nxt[c];\n        }\n    \n        int move(int v, char\
    \ ch) const {\n            return move(v, enc(ch));\n        }\n    \n       \
    \ int link(int v) const {\n            return nodes[v].link;\n        }\n    \n\
    \        int parent(int v) const {\n            return nodes[v].parent;\n    \
    \    }\n    \n        int size() const {\n            return (int)nodes.size();\n\
    \        }\n    };\n}\n#line 8 \"verify/aho_corasick.test.cpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ int n;\n    std::cin >> n;\n\n    yesantikiss::AhoCorasick<> aho;\n    std::vector<int>\
    \ terminal(n);\n    for (int& vertex : terminal) {\n        std::string s;\n \
    \       std::cin >> s;\n        vertex = aho.add(s);\n    }\n    aho.build();\n\
    \n    std::cout << aho.size() << '\\n';\n    for (int vertex = 1; vertex < aho.size();\
    \ ++vertex) {\n        std::cout << aho.parent(vertex) << ' ' << aho.link(vertex)\
    \ << '\\n';\n    }\n    for (int i = 0; i < n; ++i) {\n        if (i != 0) std::cout\
    \ << ' ';\n        std::cout << terminal[i];\n    }\n    std::cout << '\\n';\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aho_corasick\"\n\n#include\
    \ <iostream>\n#include <string>\n#include <vector>\n\n#include \"string/aho_corasick.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n;\n    std::cin >> n;\n\n    yesantikiss::AhoCorasick<> aho;\n    std::vector<int>\
    \ terminal(n);\n    for (int& vertex : terminal) {\n        std::string s;\n \
    \       std::cin >> s;\n        vertex = aho.add(s);\n    }\n    aho.build();\n\
    \n    std::cout << aho.size() << '\\n';\n    for (int vertex = 1; vertex < aho.size();\
    \ ++vertex) {\n        std::cout << aho.parent(vertex) << ' ' << aho.link(vertex)\
    \ << '\\n';\n    }\n    for (int i = 0; i < n; ++i) {\n        if (i != 0) std::cout\
    \ << ' ';\n        std::cout << terminal[i];\n    }\n    std::cout << '\\n';\n\
    }\n"
  dependsOn:
  - string/aho_corasick.hpp
  isVerificationFile: true
  path: verify/aho_corasick.test.cpp
  requiredBy: []
  timestamp: '2026-10-08 13:39:00+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/aho_corasick.test.cpp
layout: document
redirect_from:
- /verify/verify/aho_corasick.test.cpp
- /verify/verify/aho_corasick.test.cpp.html
title: verify/aho_corasick.test.cpp
---
