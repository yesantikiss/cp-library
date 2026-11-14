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
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/random_binary_trie.test.cpp\"\n// \u7D20\u6734\u306A\
    \u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\u30E9\u30F3\u30C0\u30E0\
    \u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089 A + B \u3092\u89E3\u304F\
    \u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <iostream>\n#include <random>\n#include\
    \ <set>\n#include <vector>\n\n#line 2 \"ds/binary_trie.hpp\"\n\n#line 5 \"ds/binary_trie.hpp\"\
    \n\nnamespace yesantikiss {\n    template<int B>\n    struct BinaryTrie {\n  \
    \      static_assert(0 < B && B <= 63);\n        using ull = unsigned long long;\n\
    \    \n        struct Node {\n            int ch[2];\n            long long cnt;\
    \ // subtree size (with multiplicity)\n            long long end; // exact value\
    \ count at leaf\n            Node() : ch{-1, -1}, cnt(0), end(0) {}\n        };\n\
    \    \n        std::vector<Node> tr;\n        BinaryTrie() { tr.emplace_back();\
    \ }\n    \n        long long size() const { return tr[0].cnt; }\n        bool\
    \ empty() const { return size() == 0; }\n    \n        void insert(ull x) { add_raw(x,\
    \ +1); }\n    \n        // erase one occurrence; returns false if not present\n\
    \        bool erase(ull x) {\n            if (count_raw(x) == 0) return false;\n\
    \            add_raw(x, -1);\n            return true;\n        }\n    \n    \
    \    // count/contains in {v xor T} multiset (T=0 => normal)\n        long long\
    \ count(ull v, ull T = 0) const { return count_raw(v ^ T); }\n        bool contains(ull\
    \ v, ull T = 0) const { return count(v, T) > 0; }\n    \n        // kth (0-index)\
    \ in sorted {x xor T}\n        ull kth(long long k, ull T = 0) const {\n     \
    \       assert(0 <= k && k < size());\n            int v = 0;\n            ull\
    \ y = 0;\n    \n            for (int b = B - 1; b >= 0; --b) {\n             \
    \   int tb = (T >> b) & 1ULL;\n                int pref = tb;      // ybit=0 needs\
    \ xbit=tb\n                int other = tb ^ 1;\n    \n                int vp =\
    \ tr[v].ch[pref];\n                long long cnt_pref = (vp == -1 ? 0 : tr[vp].cnt);\n\
    \    \n                if (k < cnt_pref) {\n                    v = vp; // ybit=0\n\
    \                    assert(v != -1);\n                } else {\n            \
    \        k -= cnt_pref;\n                    v = tr[v].ch[other]; // ybit=1\n\
    \                    assert(v != -1);\n                    y |= (1ULL << b);\n\
    \                }\n            }\n            return y;\n        }\n    \n  \
    \      // number of elements y in {x xor T} with y < r (r may be >= 2^B)\n   \
    \     long long count_less(ull r, ull T = 0) const {\n            if ((r >> B)\
    \ != 0) return size();\n            int v = 0;\n            long long res = 0;\n\
    \            for (int b = B - 1; b >= 0; --b) {\n                int tb = (T >>\
    \ b) & 1ULL;\n                int rb = (r >> b) & 1ULL;\n                if (rb\
    \ == 1) {\n                    int vz = tr[v].ch[tb]; // ybit=0 subtree is entirely\
    \ < r\n                    if (vz != -1) res += tr[vz].cnt;\n                \
    \    v = tr[v].ch[tb ^ 1];\n                } else {\n                    v =\
    \ tr[v].ch[tb];\n                }\n                if (v == -1) return res;\n\
    \            }\n            return res;\n        }\n    \n        // number of\
    \ elements y in {x xor T} with l <= y < r (0 if l >= r)\n        long long count_range(ull\
    \ l, ull r, ull T = 0) const {\n            if (l >= r) return 0;\n          \
    \  return count_less(r, T) - count_less(l, T);\n        }\n    \n        ull min_element(ull\
    \ T = 0) const {\n            assert(!empty());\n            return kth(0, T);\n\
    \        }\n    \n        ull max_element(ull T = 0) const {\n            assert(!empty());\n\
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
    \ // for [0, 1e9]\n    \n}\n#line 12 \"verify/random_binary_trie.test.cpp\"\n\n\
    namespace {\n    using ull = unsigned long long;\n\n    template <int B>\n   \
    \ void run(std::mt19937_64& random, int trials, ull value_mask) {\n        for\
    \ (int trial = 0; trial < trials; ++trial) {\n            yesantikiss::BinaryTrie<B>\
    \ trie;\n            std::multiset<ull> values;\n            std::vector<ull>\
    \ pool;\n            auto value = [&]() {\n                // \u540C\u3058\u5024\
    \u304C\u4F55\u5EA6\u3082\u51FA\u308B\u3088\u3046\u306B\u3001\u65E2\u51FA\u306E\
    \u5024\u3092\u534A\u5206\u306E\u78BA\u7387\u3067\u4F7F\u3046\n               \
    \ if (!pool.empty() && random() % 2 == 0) {\n                    return pool[random()\
    \ % pool.size()];\n                }\n                ull x = random() & value_mask;\n\
    \                pool.push_back(x);\n                return x;\n            };\n\
    \            assert(trie.empty() && trie.size() == 0);\n\n            for (int\
    \ query = 0; query < 80; ++query) {\n                ull x = value();\n      \
    \          ull mask = random() % 4 == 0 ? 0 : random() & value_mask;\n       \
    \         int type = static_cast<int>(random() % 5);\n                if (type\
    \ == 0) {\n                    trie.insert(x);\n                    values.insert(x);\n\
    \                } else if (type == 1) {\n                    bool exists = values.count(x)\
    \ > 0;\n                    assert(trie.erase(x) == exists);\n               \
    \     if (exists) values.erase(values.find(x));\n                } else if (type\
    \ == 2 && !values.empty()) {\n                    std::vector<ull> sorted;\n \
    \                   for (ull y : values) sorted.push_back(y ^ mask);\n       \
    \             std::sort(sorted.begin(), sorted.end());\n                    long\
    \ long k = static_cast<long long>(\n                        random() % sorted.size());\n\
    \                    assert(trie.kth(k, mask) == sorted[k]);\n               \
    \     assert(trie.min_element(mask) == sorted.front());\n                    assert(trie.max_element(mask)\
    \ == sorted.back());\n                } else if (type == 3) {\n              \
    \      // count_range(l, r, T) \u306F {x xor T} \u306E\u3046\u3061 [l, r) \u306E\
    \u500B\u6570\n                    auto bound = [&]() -> ull {\n              \
    \          int kind = static_cast<int>(random() % 6);\n                      \
    \  if (kind == 0) return 0;\n                        if (kind == 1) return value_mask\
    \ + 1; // 2^B\n                        if (kind == 2) return ~0ULL;\n        \
    \                ull y = value() ^ mask; // \u5909\u63DB\u5F8C\u306E\u65E2\u5B58\
    \u5024\u3061\u3087\u3046\u3069\n                        if (kind == 3) return\
    \ y;\n                        if (kind == 4) return y + 1;\n                 \
    \       return random() & value_mask;\n                    };\n              \
    \      ull l = bound(), r = bound();\n                    long long less_l = 0,\
    \ less_r = 0, in_range = 0;\n                    for (ull y : values) {\n    \
    \                    ull z = y ^ mask;\n                        if (z < l) ++less_l;\n\
    \                        if (z < r) ++less_r;\n                        if (l <=\
    \ z && z < r) ++in_range;\n                    }\n                    assert(trie.count_less(l,\
    \ mask) == less_l);\n                    assert(trie.count_less(r, mask) == less_r);\n\
    \                    assert(trie.count_range(l, r, mask) == in_range);\n     \
    \               assert(trie.count_range(l, l, mask) == 0);\n                }\
    \ else {\n                    // count(v, T) \u306F {x xor T} \u306E\u4E2D\u306E\
    \ v \u306E\u500B\u6570\n                    assert(trie.count(x, mask) ==\n  \
    \                         static_cast<long long>(values.count(x ^ mask)));\n \
    \                   assert(trie.contains(x, mask) ==\n                       \
    \    (values.count(x ^ mask) > 0));\n                }\n                assert(trie.size()\
    \ == static_cast<long long>(values.size()));\n                assert(trie.empty()\
    \ == values.empty());\n            }\n        }\n    }\n}\n\nint main() {\n  \
    \  std::mt19937_64 random(20261110);\n    run<1>(random, 300, 1);\n    run<5>(random,\
    \ 2000, 31);\n    run<30>(random, 500, (1ULL << 30) - 1);\n    run<63>(random,\
    \ 500, (1ULL << 63) - 1);\n\n    long long a, b;\n    std::cin >> a >> b;\n  \
    \  std::cout << a + b << '\\n';\n}\n"
  code: "// \u7D20\u6734\u306A\u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\
    \u30E9\u30F3\u30C0\u30E0\u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089\
    \ A + B \u3092\u89E3\u304F\u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <random>\n\
    #include <set>\n#include <vector>\n\n#include \"ds/binary_trie.hpp\"\n\nnamespace\
    \ {\n    using ull = unsigned long long;\n\n    template <int B>\n    void run(std::mt19937_64&\
    \ random, int trials, ull value_mask) {\n        for (int trial = 0; trial < trials;\
    \ ++trial) {\n            yesantikiss::BinaryTrie<B> trie;\n            std::multiset<ull>\
    \ values;\n            std::vector<ull> pool;\n            auto value = [&]()\
    \ {\n                // \u540C\u3058\u5024\u304C\u4F55\u5EA6\u3082\u51FA\u308B\
    \u3088\u3046\u306B\u3001\u65E2\u51FA\u306E\u5024\u3092\u534A\u5206\u306E\u78BA\
    \u7387\u3067\u4F7F\u3046\n                if (!pool.empty() && random() % 2 ==\
    \ 0) {\n                    return pool[random() % pool.size()];\n           \
    \     }\n                ull x = random() & value_mask;\n                pool.push_back(x);\n\
    \                return x;\n            };\n            assert(trie.empty() &&\
    \ trie.size() == 0);\n\n            for (int query = 0; query < 80; ++query) {\n\
    \                ull x = value();\n                ull mask = random() % 4 ==\
    \ 0 ? 0 : random() & value_mask;\n                int type = static_cast<int>(random()\
    \ % 5);\n                if (type == 0) {\n                    trie.insert(x);\n\
    \                    values.insert(x);\n                } else if (type == 1)\
    \ {\n                    bool exists = values.count(x) > 0;\n                \
    \    assert(trie.erase(x) == exists);\n                    if (exists) values.erase(values.find(x));\n\
    \                } else if (type == 2 && !values.empty()) {\n                \
    \    std::vector<ull> sorted;\n                    for (ull y : values) sorted.push_back(y\
    \ ^ mask);\n                    std::sort(sorted.begin(), sorted.end());\n   \
    \                 long long k = static_cast<long long>(\n                    \
    \    random() % sorted.size());\n                    assert(trie.kth(k, mask)\
    \ == sorted[k]);\n                    assert(trie.min_element(mask) == sorted.front());\n\
    \                    assert(trie.max_element(mask) == sorted.back());\n      \
    \          } else if (type == 3) {\n                    // count_range(l, r, T)\
    \ \u306F {x xor T} \u306E\u3046\u3061 [l, r) \u306E\u500B\u6570\n            \
    \        auto bound = [&]() -> ull {\n                        int kind = static_cast<int>(random()\
    \ % 6);\n                        if (kind == 0) return 0;\n                  \
    \      if (kind == 1) return value_mask + 1; // 2^B\n                        if\
    \ (kind == 2) return ~0ULL;\n                        ull y = value() ^ mask; //\
    \ \u5909\u63DB\u5F8C\u306E\u65E2\u5B58\u5024\u3061\u3087\u3046\u3069\n       \
    \                 if (kind == 3) return y;\n                        if (kind ==\
    \ 4) return y + 1;\n                        return random() & value_mask;\n  \
    \                  };\n                    ull l = bound(), r = bound();\n   \
    \                 long long less_l = 0, less_r = 0, in_range = 0;\n          \
    \          for (ull y : values) {\n                        ull z = y ^ mask;\n\
    \                        if (z < l) ++less_l;\n                        if (z <\
    \ r) ++less_r;\n                        if (l <= z && z < r) ++in_range;\n   \
    \                 }\n                    assert(trie.count_less(l, mask) == less_l);\n\
    \                    assert(trie.count_less(r, mask) == less_r);\n           \
    \         assert(trie.count_range(l, r, mask) == in_range);\n                \
    \    assert(trie.count_range(l, l, mask) == 0);\n                } else {\n  \
    \                  // count(v, T) \u306F {x xor T} \u306E\u4E2D\u306E v \u306E\
    \u500B\u6570\n                    assert(trie.count(x, mask) ==\n            \
    \               static_cast<long long>(values.count(x ^ mask)));\n           \
    \         assert(trie.contains(x, mask) ==\n                           (values.count(x\
    \ ^ mask) > 0));\n                }\n                assert(trie.size() == static_cast<long\
    \ long>(values.size()));\n                assert(trie.empty() == values.empty());\n\
    \            }\n        }\n    }\n}\n\nint main() {\n    std::mt19937_64 random(20261110);\n\
    \    run<1>(random, 300, 1);\n    run<5>(random, 2000, 31);\n    run<30>(random,\
    \ 500, (1ULL << 30) - 1);\n    run<63>(random, 500, (1ULL << 63) - 1);\n\n   \
    \ long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n\
    }\n"
  dependsOn:
  - ds/binary_trie.hpp
  isVerificationFile: true
  path: verify/random_binary_trie.test.cpp
  requiredBy: []
  timestamp: '2026-11-14 15:53:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/random_binary_trie.test.cpp
layout: document
redirect_from:
- /verify/verify/random_binary_trie.test.cpp
- /verify/verify/random_binary_trie.test.cpp.html
title: verify/random_binary_trie.test.cpp
---
