---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/binary_trie.hpp
    title: Binary Trie
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/set_xor_min
    links:
    - https://judge.yosupo.jp/problem/set_xor_min
  bundledCode: "#line 1 \"verify/set_xor_min.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/set_xor_min\"\
    \n\n#include <iostream>\n\n#line 2 \"ds/binary_trie.hpp\"\n\n#include <cassert>\n\
    #include <vector>\n\nnamespace yesantikiss {\n    template<int B>\n    struct\
    \ BinaryTrie {\n        static_assert(0 < B && B <= 63);\n        using ull =\
    \ unsigned long long;\n    \n        struct Node {\n            int ch[2];\n \
    \           long long cnt; // subtree size (with multiplicity)\n            long\
    \ long end; // exact value count at leaf\n            Node() : ch{-1, -1}, cnt(0),\
    \ end(0) {}\n        };\n    \n        std::vector<Node> tr;\n        BinaryTrie()\
    \ { tr.emplace_back(); }\n    \n        long long size() const { return tr[0].cnt;\
    \ }\n        bool empty() const { return size() == 0; }\n    \n        void insert(ull\
    \ x) { add_raw(x, +1); }\n    \n        // erase one occurrence; returns false\
    \ if not present\n        bool erase(ull x) {\n            if (count_raw(x) ==\
    \ 0) return false;\n            add_raw(x, -1);\n            return true;\n  \
    \      }\n    \n        // count/contains in {v xor T} multiset (T=0 => normal)\n\
    \        long long count(ull v, ull T = 0) const { return count_raw(v ^ T); }\n\
    \        bool contains(ull v, ull T = 0) const { return count(v, T) > 0; }\n \
    \   \n        // kth (0-index) in sorted {x xor T}\n        ull kth(long long\
    \ k, ull T = 0) const {\n            assert(0 <= k && k < size());\n         \
    \   int v = 0;\n            ull y = 0;\n    \n            for (int b = B - 1;\
    \ b >= 0; --b) {\n                int tb = (T >> b) & 1ULL;\n                int\
    \ pref = tb;      // ybit=0 needs xbit=tb\n                int other = tb ^ 1;\n\
    \    \n                int vp = tr[v].ch[pref];\n                long long cnt_pref\
    \ = (vp == -1 ? 0 : tr[vp].cnt);\n    \n                if (k < cnt_pref) {\n\
    \                    v = vp; // ybit=0\n                    assert(v != -1);\n\
    \                } else {\n                    k -= cnt_pref;\n              \
    \      v = tr[v].ch[other]; // ybit=1\n                    assert(v != -1);\n\
    \                    y |= (1ULL << b);\n                }\n            }\n   \
    \         return y;\n        }\n    \n        ull min_element(ull T = 0) const\
    \ {\n            assert(!empty());\n            return kth(0, T);\n        }\n\
    \    \n        ull max_element(ull T = 0) const {\n            assert(!empty());\n\
    \            return kth(size() - 1, T);\n        }\n    \n    private:\n     \
    \   void add_raw(ull x, long long delta) {\n            int v = 0;\n         \
    \   tr[v].cnt += delta;\n            for (int b = B - 1; b >= 0; --b) {\n    \
    \            int bit = (x >> b) & 1ULL;\n                if (tr[v].ch[bit] ==\
    \ -1) {\n                    tr[v].ch[bit] = (int)tr.size();\n               \
    \     tr.emplace_back();\n                }\n                v = tr[v].ch[bit];\n\
    \                tr[v].cnt += delta;\n            }\n            tr[v].end +=\
    \ delta;\n        }\n    \n        long long count_raw(ull x) const {\n      \
    \      int v = 0;\n            for (int b = B - 1; b >= 0; --b) {\n          \
    \      int bit = (x >> b) & 1ULL;\n                v = tr[v].ch[bit];\n      \
    \          if (v == -1) return 0;\n            }\n            return tr[v].end;\n\
    \        }\n    };\n    \n    // usage example:\n    // using BT = BinaryTrie<30>;\
    \ // for [0, 1e9]\n    \n}\n#line 6 \"verify/set_xor_min.test.cpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ int q;\n    std::cin >> q;\n\n    yesantikiss::BinaryTrie<30> values;\n    while\
    \ (q--) {\n        int type;\n        unsigned long long x;\n        std::cin\
    \ >> type >> x;\n\n        if (type == 0) {\n            if (!values.contains(x))\
    \ values.insert(x);\n        } else if (type == 1) {\n            values.erase(x);\n\
    \        } else {\n            std::cout << values.min_element(x) << '\\n';\n\
    \        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/set_xor_min\"\n\n#include\
    \ <iostream>\n\n#include \"ds/binary_trie.hpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int q;\n    std::cin >> q;\n\n    yesantikiss::BinaryTrie<30>\
    \ values;\n    while (q--) {\n        int type;\n        unsigned long long x;\n\
    \        std::cin >> type >> x;\n\n        if (type == 0) {\n            if (!values.contains(x))\
    \ values.insert(x);\n        } else if (type == 1) {\n            values.erase(x);\n\
    \        } else {\n            std::cout << values.min_element(x) << '\\n';\n\
    \        }\n    }\n}\n"
  dependsOn:
  - ds/binary_trie.hpp
  isVerificationFile: true
  path: verify/set_xor_min.test.cpp
  requiredBy: []
  timestamp: '2026-08-04 23:10:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/set_xor_min.test.cpp
layout: document
redirect_from:
- /verify/verify/set_xor_min.test.cpp
- /verify/verify/set_xor_min.test.cpp.html
title: verify/set_xor_min.test.cpp
---
