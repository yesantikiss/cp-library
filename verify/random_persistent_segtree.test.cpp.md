---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/persistent_segtree.hpp
    title: "\u6C38\u7D9A\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
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
  bundledCode: "#line 1 \"verify/random_persistent_segtree.test.cpp\"\n// \u7D20\u6734\
    \u306A\u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\u30E9\u30F3\u30C0\
    \u30E0\u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089 A + B \u3092\u89E3\
    \u304F\u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include\
    \ <cassert>\n#include <iostream>\n#include <random>\n#include <string>\n#include\
    \ <vector>\n\n#line 2 \"ds/persistent_segtree.hpp\"\n\n#include <algorithm>\n\
    #line 6 \"ds/persistent_segtree.hpp\"\n\nnamespace yesantikiss {\n    template<class\
    \ S, S (*op)(S, S), S (*e)()>\n    struct persistent_segtree {\n        struct\
    \ Node {\n            S val;\n            int lch, rch;\n        };\n    \n  \
    \      int n = 0;\n        std::vector<Node> nodes;\n        std::vector<int>\
    \ roots; // roots[version] = \u305D\u306E\u7248\u306E\u6839\u30CE\u30FC\u30C9\
    \ index\n    \n        persistent_segtree() = default;\n    \n        explicit\
    \ persistent_segtree(const std::vector<S>& a) {\n            init(a);\n      \
    \  }\n    \n        explicit persistent_segtree(int n_) {\n            init(std::vector<S>(n_,\
    \ e()));\n        }\n    \n        int new_node(const S& val, int lch = -1, int\
    \ rch = -1) {\n            nodes.push_back({val, lch, rch});\n            return\
    \ (int)nodes.size() - 1;\n        }\n    \n        int build(int l, int r, const\
    \ std::vector<S>& a) {\n            if (r - l == 1) {\n                return\
    \ new_node(a[l]);\n            }\n            int m = (l + r) >> 1;\n        \
    \    int lc = build(l, m, a);\n            int rc = build(m, r, a);\n        \
    \    return new_node(op(nodes[lc].val, nodes[rc].val), lc, rc);\n        }\n \
    \   \n        void init(const std::vector<S>& a) {\n            n = (int)a.size();\n\
    \            nodes.clear();\n            roots.clear();\n    \n            nodes.reserve(std::max(1,\
    \ 2 * n));\n    \n            if (n == 0) {\n                roots.push_back(-1);\
    \ // version 0 \u306F\u7A7A\u914D\u5217\u7248\n                return;\n     \
    \       }\n    \n            int root0 = build(0, n, a);\n            roots.push_back(root0);\
    \ // \u521D\u671F\u7248\u306E version \u306F 0\n        }\n    \n        int versions()\
    \ const {\n            return (int)roots.size();\n        }\n    \n        int\
    \ latest_version() const {\n            return (int)roots.size() - 1;\n      \
    \  }\n    \n        int normalize_version(int ver) const {\n            if (ver\
    \ == -1) return latest_version();\n            assert(0 <= ver && ver < (int)roots.size());\n\
    \            return ver;\n        }\n    \n        int set_rec(int node, int l,\
    \ int r, int p, const S& x) {\n            if (r - l == 1) {\n               \
    \ return new_node(x);\n            }\n    \n            int m = (l + r) >> 1;\n\
    \            int lc = nodes[node].lch;\n            int rc = nodes[node].rch;\n\
    \    \n            if (p < m) {\n                lc = set_rec(lc, l, m, p, x);\n\
    \            } else {\n                rc = set_rec(rc, m, r, p, x);\n       \
    \     }\n    \n            return new_node(op(nodes[lc].val, nodes[rc].val), lc,\
    \ rc);\n        }\n    \n        S get_rec(int node, int l, int r, int p) const\
    \ {\n            if (r - l == 1) {\n                return nodes[node].val;\n\
    \            }\n    \n            int m = (l + r) >> 1;\n            if (p < m)\
    \ return get_rec(nodes[node].lch, l, m, p);\n            return get_rec(nodes[node].rch,\
    \ m, r, p);\n        }\n    \n        S prod_rec(int node, int l, int r, int ql,\
    \ int qr) const {\n            if (qr <= l || r <= ql) return e();\n         \
    \   if (ql <= l && r <= qr) return nodes[node].val;\n    \n            int m =\
    \ (l + r) >> 1;\n            return op(\n                prod_rec(nodes[node].lch,\
    \ l, m, ql, qr),\n                prod_rec(nodes[node].rch, m, r, ql, qr)\n  \
    \          );\n        }\n    \n        // ver \u7248\u3092\u5143\u306B p \u756A\
    \u76EE\u3092 x \u306B\u5909\u66F4\u3057\u305F\u65B0\u3057\u3044\u7248\u3092\u672B\
    \u5C3E\u306B\u8FFD\u52A0\n        // ver = -1 \u306A\u3089\u6700\u65B0\u7248\u3092\
    \u5143\u306B\u3059\u308B\n        // \u8FD4\u308A\u5024\u306F\u65B0\u3057\u3044\
    \ version \u756A\u53F7\n        int set(int p, const S& x, int ver = -1) {\n \
    \           assert(0 <= p && p < n);\n            ver = normalize_version(ver);\n\
    \            int new_root = set_rec(roots[ver], 0, n, p, x);\n            roots.push_back(new_root);\n\
    \            return latest_version();\n        }\n    \n        S get(int p, int\
    \ ver = -1) const {\n            assert(0 <= p && p < n);\n            ver = normalize_version(ver);\n\
    \            return get_rec(roots[ver], 0, n, p);\n        }\n    \n        S\
    \ prod(int l, int r, int ver = -1) const {\n            assert(0 <= l && l <=\
    \ r && r <= n);\n            ver = normalize_version(ver);\n            if (n\
    \ == 0) return e();\n            return prod_rec(roots[ver], 0, n, l, r);\n  \
    \      }\n    \n        S all_prod(int ver = -1) const {\n            ver = normalize_version(ver);\n\
    \            if (n == 0) return e();\n            return nodes[roots[ver]].val;\n\
    \        }\n    };\n}\n#line 11 \"verify/random_persistent_segtree.test.cpp\"\n\
    \nnamespace {\n    // \u975E\u53EF\u63DB\u306A\u6F14\u7B97\u3067\u3001\u5DE6\u53F3\
    \u306E\u9806\u5E8F\u3092\u53D6\u308A\u9055\u3048\u3066\u3044\u306A\u3044\u304B\
    \u78BA\u304B\u3081\u308B\u3002\n    std::string op_concat(std::string a, std::string\
    \ b) { return a + b; }\n    std::string e_concat() { return \"\"; }\n}\n\nint\
    \ main() {\n    std::mt19937 random(20261110);\n    auto uniform = [&](int low,\
    \ int high) {\n        return std::uniform_int_distribution<int>(low, high)(random);\n\
    \    };\n    using Segtree =\n        yesantikiss::persistent_segtree<std::string,\
    \ op_concat, e_concat>;\n\n    {\n        Segtree empty(0);\n        assert(empty.versions()\
    \ == 1 && empty.latest_version() == 0);\n        assert(empty.prod(0, 0) == \"\
    \" && empty.all_prod() == \"\");\n        Segtree identity(3);\n        assert(identity.all_prod()\
    \ == \"\" && identity.get(1) == \"\");\n    }\n\n    for (int trial = 0; trial\
    \ < 2000; ++trial) {\n        int n = uniform(1, 20);\n        std::vector<std::string>\
    \ initial(n);\n        for (std::string& s : initial) {\n            s = std::string(1,\
    \ static_cast<char>('a' + uniform(0, 25)));\n        }\n        Segtree seg(initial);\n\
    \        // versions[i] \u306F i \u756A\u76EE\u306E\u7248\u306E\u914D\u5217\u305D\
    \u306E\u3082\u306E\n        std::vector<std::vector<std::string>> versions{initial};\n\
    \n        for (int query = 0; query < 40; ++query) {\n            // -1 \u306F\
    \u6700\u65B0\u7248\u3092\u6307\u3059\n            int version = uniform(-1, static_cast<int>(versions.size())\
    \ - 1);\n            int actual_version =\n                version == -1 ? static_cast<int>(versions.size())\
    \ - 1\n                              : version;\n            if (uniform(0, 1)\
    \ == 0) {\n                int p = uniform(0, n - 1);\n                std::string\
    \ x(1, static_cast<char>('a' + uniform(0, 25)));\n                std::vector<std::string>\
    \ next = versions[actual_version];\n                next[p] = x;\n           \
    \     int created = seg.set(p, x, version);\n                assert(created ==\
    \ static_cast<int>(versions.size()));\n                versions.push_back(next);\n\
    \                assert(seg.versions() == static_cast<int>(versions.size()));\n\
    \                assert(seg.latest_version() == created);\n            } else\
    \ {\n                const std::vector<std::string>& a = versions[actual_version];\n\
    \                int l = uniform(0, n);\n                int r = uniform(l, n);\n\
    \                std::string expected, all;\n                for (int i = l; i\
    \ < r; ++i) expected += a[i];\n                for (int i = 0; i < n; ++i) all\
    \ += a[i];\n                assert(seg.prod(l, r, version) == expected);\n   \
    \             assert(seg.all_prod(version) == all);\n                int p = uniform(0,\
    \ n - 1);\n                assert(seg.get(p, version) == a[p]);\n            }\n\
    \        }\n\n        // \u53E4\u3044\u7248\u304C\u5F8C\u306E\u66F4\u65B0\u3067\
    \u58CA\u308C\u3066\u3044\u306A\u3044\u304B\u3001\u6700\u5F8C\u306B\u5168\u90E8\
    \u78BA\u304B\u3081\u308B\u3002\n        for (int version = 0; version < static_cast<int>(versions.size());\n\
    \             ++version) {\n            for (int p = 0; p < n; ++p) {\n      \
    \          assert(seg.get(p, version) == versions[version][p]);\n            }\n\
    \        }\n    }\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  code: "// \u7D20\u6734\u306A\u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\
    \u30E9\u30F3\u30C0\u30E0\u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089\
    \ A + B \u3092\u89E3\u304F\u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#include <cassert>\n#include <iostream>\n#include <random>\n#include <string>\n\
    #include <vector>\n\n#include \"ds/persistent_segtree.hpp\"\n\nnamespace {\n \
    \   // \u975E\u53EF\u63DB\u306A\u6F14\u7B97\u3067\u3001\u5DE6\u53F3\u306E\u9806\
    \u5E8F\u3092\u53D6\u308A\u9055\u3048\u3066\u3044\u306A\u3044\u304B\u78BA\u304B\
    \u3081\u308B\u3002\n    std::string op_concat(std::string a, std::string b) {\
    \ return a + b; }\n    std::string e_concat() { return \"\"; }\n}\n\nint main()\
    \ {\n    std::mt19937 random(20261110);\n    auto uniform = [&](int low, int high)\
    \ {\n        return std::uniform_int_distribution<int>(low, high)(random);\n \
    \   };\n    using Segtree =\n        yesantikiss::persistent_segtree<std::string,\
    \ op_concat, e_concat>;\n\n    {\n        Segtree empty(0);\n        assert(empty.versions()\
    \ == 1 && empty.latest_version() == 0);\n        assert(empty.prod(0, 0) == \"\
    \" && empty.all_prod() == \"\");\n        Segtree identity(3);\n        assert(identity.all_prod()\
    \ == \"\" && identity.get(1) == \"\");\n    }\n\n    for (int trial = 0; trial\
    \ < 2000; ++trial) {\n        int n = uniform(1, 20);\n        std::vector<std::string>\
    \ initial(n);\n        for (std::string& s : initial) {\n            s = std::string(1,\
    \ static_cast<char>('a' + uniform(0, 25)));\n        }\n        Segtree seg(initial);\n\
    \        // versions[i] \u306F i \u756A\u76EE\u306E\u7248\u306E\u914D\u5217\u305D\
    \u306E\u3082\u306E\n        std::vector<std::vector<std::string>> versions{initial};\n\
    \n        for (int query = 0; query < 40; ++query) {\n            // -1 \u306F\
    \u6700\u65B0\u7248\u3092\u6307\u3059\n            int version = uniform(-1, static_cast<int>(versions.size())\
    \ - 1);\n            int actual_version =\n                version == -1 ? static_cast<int>(versions.size())\
    \ - 1\n                              : version;\n            if (uniform(0, 1)\
    \ == 0) {\n                int p = uniform(0, n - 1);\n                std::string\
    \ x(1, static_cast<char>('a' + uniform(0, 25)));\n                std::vector<std::string>\
    \ next = versions[actual_version];\n                next[p] = x;\n           \
    \     int created = seg.set(p, x, version);\n                assert(created ==\
    \ static_cast<int>(versions.size()));\n                versions.push_back(next);\n\
    \                assert(seg.versions() == static_cast<int>(versions.size()));\n\
    \                assert(seg.latest_version() == created);\n            } else\
    \ {\n                const std::vector<std::string>& a = versions[actual_version];\n\
    \                int l = uniform(0, n);\n                int r = uniform(l, n);\n\
    \                std::string expected, all;\n                for (int i = l; i\
    \ < r; ++i) expected += a[i];\n                for (int i = 0; i < n; ++i) all\
    \ += a[i];\n                assert(seg.prod(l, r, version) == expected);\n   \
    \             assert(seg.all_prod(version) == all);\n                int p = uniform(0,\
    \ n - 1);\n                assert(seg.get(p, version) == a[p]);\n            }\n\
    \        }\n\n        // \u53E4\u3044\u7248\u304C\u5F8C\u306E\u66F4\u65B0\u3067\
    \u58CA\u308C\u3066\u3044\u306A\u3044\u304B\u3001\u6700\u5F8C\u306B\u5168\u90E8\
    \u78BA\u304B\u3081\u308B\u3002\n        for (int version = 0; version < static_cast<int>(versions.size());\n\
    \             ++version) {\n            for (int p = 0; p < n; ++p) {\n      \
    \          assert(seg.get(p, version) == versions[version][p]);\n            }\n\
    \        }\n    }\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  dependsOn:
  - ds/persistent_segtree.hpp
  isVerificationFile: true
  path: verify/random_persistent_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-11-10 19:55:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/random_persistent_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/random_persistent_segtree.test.cpp
- /verify/verify/random_persistent_segtree.test.cpp.html
title: verify/random_persistent_segtree.test.cpp
---
