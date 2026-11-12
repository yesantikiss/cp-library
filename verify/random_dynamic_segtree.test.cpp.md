---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_segtree.hpp
    title: "\u52D5\u7684\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
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
  bundledCode: "#line 1 \"verify/random_dynamic_segtree.test.cpp\"\n// \u7D20\u6734\
    \u306A\u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\u30E9\u30F3\u30C0\
    \u30E0\u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089 A + B \u3092\u89E3\
    \u304F\u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <iostream>\n#include <limits>\n#include\
    \ <random>\n#include <string>\n#include <vector>\n\n#line 2 \"ds/dynamic_segtree.hpp\"\
    \n\n#line 5 \"ds/dynamic_segtree.hpp\"\n#include <cstddef>\n#line 7 \"ds/dynamic_segtree.hpp\"\
    \n\n// \u52D5\u7684\uFF08implicit\uFF09\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\n\
    // - \u533A\u9593 [0, n) \u3092\u6271\u3046\n// - \u66F4\u65B0\u304C\u5165\u3063\
    \u305F\u7D4C\u8DEF\u3060\u3051\u30CE\u30FC\u30C9\u751F\u6210\n// - ACL segtree\
    \ \u98A8\u30A4\u30F3\u30BF\u30D5\u30A7\u30FC\u30B9\n\nnamespace yesantikiss {\n\
    \    // \u52D5\u7684\uFF08implicit\uFF09\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\n\
    \    // - \u533A\u9593 [0, n) \u3092\u6271\u3046\n    // - \u66F4\u65B0\u304C\u5165\
    \u3063\u305F\u7D4C\u8DEF\u3060\u3051\u30CE\u30FC\u30C9\u751F\u6210\n    // - ACL\
    \ segtree \u98A8\u30A4\u30F3\u30BF\u30D5\u30A7\u30FC\u30B9\n    \n    template\
    \ <class S, S (*op)(S, S), S (*e)()>\n    struct dynamic_segtree {\n    private:\n\
    \        struct Node {\n            int l = -1, r = -1;\n            S val;\n\
    \            Node() : val(e()) {}\n        };\n    \n        long long n_ = 0;\n\
    \        unsigned long long size_ = 1;\n        int root_ = -1;\n        std::vector<Node>\
    \ pool_;\n    \n        static unsigned long long ceil_pow2_ull(unsigned long\
    \ long x) {\n            unsigned long long p = 1;\n            while (p < x)\
    \ p <<= 1;\n            return p;\n        }\n    \n        int new_node() {\n\
    \            pool_.emplace_back();\n            return (int)pool_.size() - 1;\n\
    \        }\n    \n        S node_val(int idx) const {\n            return (idx\
    \ == -1) ? e() : pool_[idx].val;\n        }\n    \n        S prod_rec(int idx,\n\
    \                   unsigned long long segL, unsigned long long segR,\n      \
    \             unsigned long long ql, unsigned long long qr) const {\n        \
    \    if (idx == -1) return e();\n            if (qr <= segL || segR <= ql) return\
    \ e();\n            if (ql <= segL && segR <= qr) return pool_[idx].val;\n   \
    \         unsigned long long mid = (segL + segR) >> 1;\n            S left = prod_rec(pool_[idx].l,\
    \ segL, mid, ql, qr);\n            S right = prod_rec(pool_[idx].r, mid, segR,\
    \ ql, qr);\n            return op(left, right);\n        }\n    \n        template\
    \ <class F>\n        long long max_right_rec(int idx,\n                      \
    \          unsigned long long segL, unsigned long long segR,\n               \
    \                 unsigned long long ql,\n                                F& f,\
    \ S& sm) const {\n            if (segR <= ql) return (long long)ql;\n        \
    \    S segVal = (idx == -1) ? e() : pool_[idx].val;\n            if (segL >= ql)\
    \ {\n                S nxt = op(sm, segVal);\n                if (f(nxt)) {\n\
    \                    sm = nxt;\n                    return (long long)segR;\n\
    \                }\n                if (segR - segL == 1) return (long long)segL;\n\
    \            }\n            unsigned long long mid = (segL + segR) >> 1;\n   \
    \         int lch = (idx == -1) ? -1 : pool_[idx].l;\n            int rch = (idx\
    \ == -1) ? -1 : pool_[idx].r;\n            long long resL = max_right_rec(lch,\
    \ segL, mid, ql, f, sm);\n            if ((unsigned long long)resL < mid) return\
    \ resL;\n            return max_right_rec(rch, mid, segR, ql, f, sm);\n      \
    \  }\n    \n        template <class F>\n        long long min_left_rec(int idx,\n\
    \                               unsigned long long segL, unsigned long long segR,\n\
    \                               unsigned long long qr,\n                     \
    \          F& f, S& sm) const {\n            if (qr <= segL) return (long long)qr;\n\
    \            S segVal = (idx == -1) ? e() : pool_[idx].val;\n            if (segR\
    \ <= qr) {\n                S nxt = op(segVal, sm);\n                if (f(nxt))\
    \ {\n                    sm = nxt;\n                    return (long long)segL;\n\
    \                }\n                if (segR - segL == 1) return (long long)segR;\n\
    \            }\n            unsigned long long mid = (segL + segR) >> 1;\n   \
    \         int lch = (idx == -1) ? -1 : pool_[idx].l;\n            int rch = (idx\
    \ == -1) ? -1 : pool_[idx].r;\n            long long resR = min_left_rec(rch,\
    \ mid, segR, qr, f, sm);\n            if ((unsigned long long)resR > mid) return\
    \ resR;\n            return min_left_rec(lch, segL, mid, qr, f, sm);\n       \
    \ }\n    \n        template <bool APPLY>\n        void point_update(long long\
    \ p, const S& x) {\n            assert(0 <= p && p < n_);\n            if (root_\
    \ == -1) root_ = new_node();\n            int idx = root_;\n            unsigned\
    \ long long segL = 0, segR = size_;\n            int path[70];\n            int\
    \ psz = 0;\n            path[psz++] = idx;\n            while (segR - segL > 1)\
    \ {\n                unsigned long long mid = (segL + segR) >> 1;\n          \
    \      if ((unsigned long long)p < mid) {\n                    if (pool_[idx].l\
    \ == -1) {\n                        int child = new_node();\n                \
    \        pool_[idx].l = child;\n                    }\n                    idx\
    \ = pool_[idx].l;\n                    segR = mid;\n                } else {\n\
    \                    if (pool_[idx].r == -1) {\n                        int child\
    \ = new_node();\n                        pool_[idx].r = child;\n             \
    \       }\n                    idx = pool_[idx].r;\n                    segL =\
    \ mid;\n                }\n                path[psz++] = idx;\n            }\n\
    \            if constexpr (APPLY) {\n                pool_[idx].val = op(pool_[idx].val,\
    \ x);\n            } else {\n                pool_[idx].val = x;\n           \
    \ }\n            for (int i = psz - 2; i >= 0; --i) {\n                int v =\
    \ path[i];\n                pool_[v].val = op(node_val(pool_[v].l), node_val(pool_[v].r));\n\
    \            }\n        }\n    \n    public:\n        dynamic_segtree() = default;\n\
    \        explicit dynamic_segtree(long long n) { init(n); }\n    \n        void\
    \ init(long long n) {\n            assert(n >= 0);\n            n_ = n;\n    \
    \        size_ = ceil_pow2_ull((unsigned long long)std::max(1LL, n_));\n     \
    \       root_ = -1;\n            pool_.clear();\n        }\n    \n        void\
    \ reserve_nodes(std::size_t m) { pool_.reserve(m); }\n    \n        long long\
    \ size() const { return n_; }\n    \n        S all_prod() const {\n          \
    \  return (root_ == -1) ? e() : pool_[root_].val;\n        }\n    \n        S\
    \ get(long long p) const {\n            assert(0 <= p && p < n_);\n          \
    \  int idx = root_;\n            if (idx == -1) return e();\n            unsigned\
    \ long long segL = 0, segR = size_;\n            while (segR - segL > 1 && idx\
    \ != -1) {\n                unsigned long long mid = (segL + segR) >> 1;\n   \
    \             if ((unsigned long long)p < mid) {\n                    idx = pool_[idx].l;\n\
    \                    segR = mid;\n                } else {\n                 \
    \   idx = pool_[idx].r;\n                    segL = mid;\n                }\n\
    \            }\n            return (idx == -1) ? e() : pool_[idx].val;\n     \
    \   }\n    \n        void set(long long p, S x) { point_update<false>(p, x); }\n\
    \        void apply_point(long long p, S x) { point_update<true>(p, x); }\n  \
    \  \n        S prod(long long l, long long r) const {\n            assert(0 <=\
    \ l && l <= r && r <= n_);\n            if (l == r) return e();\n            if\
    \ (root_ == -1) return e();\n            return prod_rec(root_, 0, size_,\n  \
    \                          (unsigned long long)l, (unsigned long long)r);\n  \
    \      }\n    \n        template <class F>\n        long long max_right(long long\
    \ l, F f) const {\n            assert(0 <= l && l <= n_);\n            assert(f(e()));\n\
    \            if (l == n_) return n_;\n            S sm = e();\n            F ff\
    \ = f;\n            long long res = max_right_rec(root_, 0, size_, (unsigned long\
    \ long)l, ff, sm);\n            if (res > n_) res = n_;\n            return res;\n\
    \        }\n    \n        template <class F>\n        long long min_left(long\
    \ long r, F f) const {\n            assert(0 <= r && r <= n_);\n            assert(f(e()));\n\
    \            if (r == 0) return 0;\n            S sm = e();\n            F ff\
    \ = f;\n            long long res = min_left_rec(root_, 0, size_, (unsigned long\
    \ long)r, ff, sm);\n            if (res < 0) res = 0;\n            if (res > r)\
    \ res = r;\n            return res;\n        }\n    };\n}\n#line 13 \"verify/random_dynamic_segtree.test.cpp\"\
    \n\nnamespace {\n    using ll = long long;\n\n    ll op_sum(ll a, ll b) { return\
    \ a + b; }\n    ll e_sum() { return 0; }\n    ll op_max(ll a, ll b) { return std::max(a,\
    \ b); }\n    ll e_max() { return std::numeric_limits<ll>::min(); }\n    // \u975E\
    \u53EF\u63DB\u306A\u6F14\u7B97\u3067\u3001\u5DE6\u53F3\u306E\u9806\u5E8F\u3092\
    \u53D6\u308A\u9055\u3048\u3066\u3044\u306A\u3044\u304B\u78BA\u304B\u3081\u308B\
    \u3002\n    std::string op_concat(std::string a, std::string b) { return a + b;\
    \ }\n    std::string e_concat() { return \"\"; }\n\n    std::mt19937_64 random_engine(20261110);\n\
    \n    ll uniform(ll low, ll high) {\n        return std::uniform_int_distribution<ll>(low,\
    \ high)(random_engine);\n    }\n\n    void test_small() {\n        for (int trial\
    \ = 0; trial < 2000; ++trial) {\n            int n = static_cast<int>(uniform(0,\
    \ 40));\n            yesantikiss::dynamic_segtree<ll, op_sum, e_sum> sum(n);\n\
    \            yesantikiss::dynamic_segtree<ll, op_max, e_max> max(n);\n       \
    \     yesantikiss::dynamic_segtree<std::string, op_concat, e_concat>\n       \
    \         concat(n);\n            std::vector<ll> a(n, 0), b(n, e_max());\n  \
    \          std::vector<std::string> c(n);\n            assert(sum.size() == n);\n\
    \n            for (int query = 0; query < 60; ++query) {\n                if (n\
    \ == 0) {\n                    assert(sum.all_prod() == 0 && sum.prod(0, 0) ==\
    \ 0);\n                    assert(sum.max_right(0, [](ll) { return true; }) ==\
    \ 0);\n                    assert(sum.min_left(0, [](ll) { return true; }) ==\
    \ 0);\n                    break;\n                }\n                int type\
    \ = static_cast<int>(uniform(0, 5));\n                if (type == 0) {\n     \
    \               int p = static_cast<int>(uniform(0, n - 1));\n               \
    \     ll x = uniform(0, 9);\n                    sum.set(p, x);\n            \
    \        max.set(p, x);\n                    a[p] = b[p] = x;\n              \
    \      c[p] = std::string(1, static_cast<char>('a' + x));\n                  \
    \  concat.set(p, c[p]);\n                } else if (type == 1) {\n           \
    \         int p = static_cast<int>(uniform(0, n - 1));\n                    ll\
    \ x = uniform(0, 9);\n                    sum.apply_point(p, x);\n           \
    \         a[p] += x;\n                    std::string s(1, static_cast<char>('a'\
    \ + x));\n                    concat.apply_point(p, s);\n                    c[p]\
    \ += s;\n                } else if (type == 2) {\n                    int l =\
    \ static_cast<int>(uniform(0, n));\n                    int r = static_cast<int>(uniform(l,\
    \ n));\n                    ll expected_sum = 0, expected_max = e_max();\n   \
    \                 std::string expected_concat;\n                    for (int i\
    \ = l; i < r; ++i) {\n                        expected_sum += a[i];\n        \
    \                expected_max = std::max(expected_max, b[i]);\n              \
    \          expected_concat += c[i];\n                    }\n                 \
    \   assert(sum.prod(l, r) == expected_sum);\n                    assert(max.prod(l,\
    \ r) == expected_max);\n                    assert(concat.prod(l, r) == expected_concat);\n\
    \                } else if (type == 3) {\n                    int l = static_cast<int>(uniform(0,\
    \ n));\n                    ll limit = uniform(0, 30);\n                    int\
    \ r = l;\n                    ll total = 0;\n                    while (r < n\
    \ && total + a[r] <= limit) total += a[r++];\n                    assert(sum.max_right(\n\
    \                               l, [&](ll x) { return x <= limit; }) == r);\n\n\
    \                    ll bound = uniform(-1, 9);\n                    r = l;\n\
    \                    while (r < n && b[r] <= bound) ++r;\n                   \
    \ assert(max.max_right(\n                               l, [&](ll x) { return\
    \ x <= bound; }) == r);\n\n                    // \u975E\u53EF\u63DB: l \u304B\
    \u3089\u5148\u3092\u3064\u306A\u3052\u305F\u6587\u5B57\u5217\u306E\u63A5\u982D\
    \u8F9E\u306B\u306A\u3063\u3066\u3044\u308B\u304B\n                    std::string\
    \ rest;\n                    for (int i = l; i < n; ++i) rest += c[i];\n     \
    \               std::size_t length = static_cast<std::size_t>(limit) / 3;\n  \
    \                  r = l;\n                    std::size_t used = 0;\n       \
    \             while (r < n && used + c[r].size() <= length) {\n              \
    \          used += c[r++].size();\n                    }\n                   \
    \ assert(concat.max_right(l, [&](const std::string& x) {\n                   \
    \     return x.size() <= length &&\n                               rest.compare(0,\
    \ x.size(), x) == 0;\n                    }) == r);\n                } else if\
    \ (type == 4) {\n                    int r = static_cast<int>(uniform(0, n));\n\
    \                    ll limit = uniform(0, 30);\n                    int l = r;\n\
    \                    ll total = 0;\n                    while (l > 0 && total\
    \ + a[l - 1] <= limit) total += a[--l];\n                    assert(sum.min_left(\n\
    \                               r, [&](ll x) { return x <= limit; }) == l);\n\n\
    \                    ll bound = uniform(-1, 9);\n                    l = r;\n\
    \                    while (l > 0 && b[l - 1] <= bound) --l;\n               \
    \     assert(max.min_left(\n                               r, [&](ll x) { return\
    \ x <= bound; }) == l);\n\n                    // \u975E\u53EF\u63DB: r \u3088\
    \u308A\u524D\u3092\u3064\u306A\u3052\u305F\u6587\u5B57\u5217\u306E\u63A5\u5C3E\
    \u8F9E\u306B\u306A\u3063\u3066\u3044\u308B\u304B\n                    std::string\
    \ before;\n                    for (int i = 0; i < r; ++i) before += c[i];\n \
    \                   std::size_t length = static_cast<std::size_t>(limit) / 3;\n\
    \                    l = r;\n                    std::size_t used = 0;\n     \
    \               while (l > 0 && used + c[l - 1].size() <= length) {\n        \
    \                used += c[--l].size();\n                    }\n             \
    \       assert(concat.min_left(r, [&](const std::string& x) {\n              \
    \          return x.size() <= length &&\n                               before.compare(before.size()\
    \ - x.size(),\n                                              x.size(), x) == 0;\n\
    \                    }) == l);\n                } else {\n                   \
    \ int p = static_cast<int>(uniform(0, n - 1));\n                    assert(sum.get(p)\
    \ == a[p]);\n                    assert(max.get(p) == b[p]);\n               \
    \     assert(concat.get(p) == c[p]);\n                }\n                ll expected_all\
    \ = 0;\n                for (ll x : a) expected_all += x;\n                assert(sum.all_prod()\
    \ == expected_all);\n            }\n        }\n    }\n\n    // \u6DFB\u5B57\u304C\
    \u5927\u304D\u3044\u3068\u304D\u306F\u3001\u5024\u306E\u5165\u3063\u305F\u4F4D\
    \u7F6E\u3060\u3051\u3092\u899A\u3048\u305F\u7D20\u6734\u89E3\u3068\u6BD4\u3079\
    \u308B\u3002\n    void test_huge() {\n        for (int trial = 0; trial < 200;\
    \ ++trial) {\n            ll n = trial % 2 == 0 ? 4000000000000000000LL\n    \
    \                              : uniform(1, 4000000000000000000LL);\n        \
    \    yesantikiss::dynamic_segtree<ll, op_sum, e_sum> sum(n);\n            std::vector<std::pair<ll,\
    \ ll>> points;\n            auto position = [&]() {\n                int kind\
    \ = static_cast<int>(uniform(0, 3));\n                if (kind == 0) return uniform(0,\
    \ std::min<ll>(n - 1, 5));\n                if (kind == 1) return n - 1 - uniform(0,\
    \ std::min<ll>(n - 1, 5));\n                if (kind == 2 && !points.empty())\
    \ {\n                    return points[uniform(0, static_cast<ll>(points.size())\
    \ - 1)]\n                        .first;\n                }\n                return\
    \ uniform(0, n - 1);\n            };\n            auto range_sum = [&](ll l, ll\
    \ r) {\n                ll total = 0;\n                for (auto [p, x] : points)\
    \ {\n                    if (l <= p && p < r) total += x;\n                }\n\
    \                return total;\n            };\n            for (int query = 0;\
    \ query < 40; ++query) {\n                int type = static_cast<int>(uniform(0,\
    \ 3));\n                if (type == 0) {\n                    ll p = position(),\
    \ x = uniform(1, 9);\n                    sum.set(p, x);\n                   \
    \ bool found = false;\n                    for (auto& point : points) {\n    \
    \                    if (point.first == p) {\n                            point.second\
    \ = x;\n                            found = true;\n                        }\n\
    \                    }\n                    if (!found) points.emplace_back(p,\
    \ x);\n                } else if (type == 1) {\n                    ll l = position(),\
    \ r = position() + 1;\n                    if (l > r) std::swap(l, r);\n     \
    \               assert(sum.prod(l, r) == range_sum(l, r));\n                }\
    \ else if (type == 2) {\n                    ll l = position(), limit = uniform(0,\
    \ 20);\n                    // \u548C\u304C limit \u3092\u8D85\u3048\u308B\u6700\
    \u521D\u306E\u4F4D\u7F6E\u3092\u7D20\u6734\u306B\u63A2\u3059\n               \
    \     std::vector<std::pair<ll, ll>> sorted = points;\n                    std::sort(sorted.begin(),\
    \ sorted.end());\n                    ll expected = n, total = 0;\n          \
    \          for (auto [p, x] : sorted) {\n                        if (p < l) continue;\n\
    \                        total += x;\n                        if (total > limit)\
    \ {\n                            expected = p;\n                            break;\n\
    \                        }\n                    }\n                    assert(sum.max_right(\n\
    \                               l, [&](ll x) { return x <= limit; }) ==\n    \
    \                       expected);\n                } else {\n               \
    \     ll r = position() + 1, limit = uniform(0, 20);\n                    std::vector<std::pair<ll,\
    \ ll>> sorted = points;\n                    std::sort(sorted.rbegin(), sorted.rend());\n\
    \                    ll expected = 0, total = 0;\n                    for (auto\
    \ [p, x] : sorted) {\n                        if (p >= r) continue;\n        \
    \                total += x;\n                        if (total > limit) {\n \
    \                           expected = p + 1;\n                            break;\n\
    \                        }\n                    }\n                    assert(sum.min_left(\n\
    \                               r, [&](ll x) { return x <= limit; }) ==\n    \
    \                       expected);\n                }\n            }\n       \
    \ }\n    }\n}\n\nint main() {\n    test_small();\n    test_huge();\n\n    long\
    \ long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "// \u7D20\u6734\u306A\u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\
    \u30E9\u30F3\u30C0\u30E0\u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089\
    \ A + B \u3092\u89E3\u304F\u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <limits>\n\
    #include <random>\n#include <string>\n#include <vector>\n\n#include \"ds/dynamic_segtree.hpp\"\
    \n\nnamespace {\n    using ll = long long;\n\n    ll op_sum(ll a, ll b) { return\
    \ a + b; }\n    ll e_sum() { return 0; }\n    ll op_max(ll a, ll b) { return std::max(a,\
    \ b); }\n    ll e_max() { return std::numeric_limits<ll>::min(); }\n    // \u975E\
    \u53EF\u63DB\u306A\u6F14\u7B97\u3067\u3001\u5DE6\u53F3\u306E\u9806\u5E8F\u3092\
    \u53D6\u308A\u9055\u3048\u3066\u3044\u306A\u3044\u304B\u78BA\u304B\u3081\u308B\
    \u3002\n    std::string op_concat(std::string a, std::string b) { return a + b;\
    \ }\n    std::string e_concat() { return \"\"; }\n\n    std::mt19937_64 random_engine(20261110);\n\
    \n    ll uniform(ll low, ll high) {\n        return std::uniform_int_distribution<ll>(low,\
    \ high)(random_engine);\n    }\n\n    void test_small() {\n        for (int trial\
    \ = 0; trial < 2000; ++trial) {\n            int n = static_cast<int>(uniform(0,\
    \ 40));\n            yesantikiss::dynamic_segtree<ll, op_sum, e_sum> sum(n);\n\
    \            yesantikiss::dynamic_segtree<ll, op_max, e_max> max(n);\n       \
    \     yesantikiss::dynamic_segtree<std::string, op_concat, e_concat>\n       \
    \         concat(n);\n            std::vector<ll> a(n, 0), b(n, e_max());\n  \
    \          std::vector<std::string> c(n);\n            assert(sum.size() == n);\n\
    \n            for (int query = 0; query < 60; ++query) {\n                if (n\
    \ == 0) {\n                    assert(sum.all_prod() == 0 && sum.prod(0, 0) ==\
    \ 0);\n                    assert(sum.max_right(0, [](ll) { return true; }) ==\
    \ 0);\n                    assert(sum.min_left(0, [](ll) { return true; }) ==\
    \ 0);\n                    break;\n                }\n                int type\
    \ = static_cast<int>(uniform(0, 5));\n                if (type == 0) {\n     \
    \               int p = static_cast<int>(uniform(0, n - 1));\n               \
    \     ll x = uniform(0, 9);\n                    sum.set(p, x);\n            \
    \        max.set(p, x);\n                    a[p] = b[p] = x;\n              \
    \      c[p] = std::string(1, static_cast<char>('a' + x));\n                  \
    \  concat.set(p, c[p]);\n                } else if (type == 1) {\n           \
    \         int p = static_cast<int>(uniform(0, n - 1));\n                    ll\
    \ x = uniform(0, 9);\n                    sum.apply_point(p, x);\n           \
    \         a[p] += x;\n                    std::string s(1, static_cast<char>('a'\
    \ + x));\n                    concat.apply_point(p, s);\n                    c[p]\
    \ += s;\n                } else if (type == 2) {\n                    int l =\
    \ static_cast<int>(uniform(0, n));\n                    int r = static_cast<int>(uniform(l,\
    \ n));\n                    ll expected_sum = 0, expected_max = e_max();\n   \
    \                 std::string expected_concat;\n                    for (int i\
    \ = l; i < r; ++i) {\n                        expected_sum += a[i];\n        \
    \                expected_max = std::max(expected_max, b[i]);\n              \
    \          expected_concat += c[i];\n                    }\n                 \
    \   assert(sum.prod(l, r) == expected_sum);\n                    assert(max.prod(l,\
    \ r) == expected_max);\n                    assert(concat.prod(l, r) == expected_concat);\n\
    \                } else if (type == 3) {\n                    int l = static_cast<int>(uniform(0,\
    \ n));\n                    ll limit = uniform(0, 30);\n                    int\
    \ r = l;\n                    ll total = 0;\n                    while (r < n\
    \ && total + a[r] <= limit) total += a[r++];\n                    assert(sum.max_right(\n\
    \                               l, [&](ll x) { return x <= limit; }) == r);\n\n\
    \                    ll bound = uniform(-1, 9);\n                    r = l;\n\
    \                    while (r < n && b[r] <= bound) ++r;\n                   \
    \ assert(max.max_right(\n                               l, [&](ll x) { return\
    \ x <= bound; }) == r);\n\n                    // \u975E\u53EF\u63DB: l \u304B\
    \u3089\u5148\u3092\u3064\u306A\u3052\u305F\u6587\u5B57\u5217\u306E\u63A5\u982D\
    \u8F9E\u306B\u306A\u3063\u3066\u3044\u308B\u304B\n                    std::string\
    \ rest;\n                    for (int i = l; i < n; ++i) rest += c[i];\n     \
    \               std::size_t length = static_cast<std::size_t>(limit) / 3;\n  \
    \                  r = l;\n                    std::size_t used = 0;\n       \
    \             while (r < n && used + c[r].size() <= length) {\n              \
    \          used += c[r++].size();\n                    }\n                   \
    \ assert(concat.max_right(l, [&](const std::string& x) {\n                   \
    \     return x.size() <= length &&\n                               rest.compare(0,\
    \ x.size(), x) == 0;\n                    }) == r);\n                } else if\
    \ (type == 4) {\n                    int r = static_cast<int>(uniform(0, n));\n\
    \                    ll limit = uniform(0, 30);\n                    int l = r;\n\
    \                    ll total = 0;\n                    while (l > 0 && total\
    \ + a[l - 1] <= limit) total += a[--l];\n                    assert(sum.min_left(\n\
    \                               r, [&](ll x) { return x <= limit; }) == l);\n\n\
    \                    ll bound = uniform(-1, 9);\n                    l = r;\n\
    \                    while (l > 0 && b[l - 1] <= bound) --l;\n               \
    \     assert(max.min_left(\n                               r, [&](ll x) { return\
    \ x <= bound; }) == l);\n\n                    // \u975E\u53EF\u63DB: r \u3088\
    \u308A\u524D\u3092\u3064\u306A\u3052\u305F\u6587\u5B57\u5217\u306E\u63A5\u5C3E\
    \u8F9E\u306B\u306A\u3063\u3066\u3044\u308B\u304B\n                    std::string\
    \ before;\n                    for (int i = 0; i < r; ++i) before += c[i];\n \
    \                   std::size_t length = static_cast<std::size_t>(limit) / 3;\n\
    \                    l = r;\n                    std::size_t used = 0;\n     \
    \               while (l > 0 && used + c[l - 1].size() <= length) {\n        \
    \                used += c[--l].size();\n                    }\n             \
    \       assert(concat.min_left(r, [&](const std::string& x) {\n              \
    \          return x.size() <= length &&\n                               before.compare(before.size()\
    \ - x.size(),\n                                              x.size(), x) == 0;\n\
    \                    }) == l);\n                } else {\n                   \
    \ int p = static_cast<int>(uniform(0, n - 1));\n                    assert(sum.get(p)\
    \ == a[p]);\n                    assert(max.get(p) == b[p]);\n               \
    \     assert(concat.get(p) == c[p]);\n                }\n                ll expected_all\
    \ = 0;\n                for (ll x : a) expected_all += x;\n                assert(sum.all_prod()\
    \ == expected_all);\n            }\n        }\n    }\n\n    // \u6DFB\u5B57\u304C\
    \u5927\u304D\u3044\u3068\u304D\u306F\u3001\u5024\u306E\u5165\u3063\u305F\u4F4D\
    \u7F6E\u3060\u3051\u3092\u899A\u3048\u305F\u7D20\u6734\u89E3\u3068\u6BD4\u3079\
    \u308B\u3002\n    void test_huge() {\n        for (int trial = 0; trial < 200;\
    \ ++trial) {\n            ll n = trial % 2 == 0 ? 4000000000000000000LL\n    \
    \                              : uniform(1, 4000000000000000000LL);\n        \
    \    yesantikiss::dynamic_segtree<ll, op_sum, e_sum> sum(n);\n            std::vector<std::pair<ll,\
    \ ll>> points;\n            auto position = [&]() {\n                int kind\
    \ = static_cast<int>(uniform(0, 3));\n                if (kind == 0) return uniform(0,\
    \ std::min<ll>(n - 1, 5));\n                if (kind == 1) return n - 1 - uniform(0,\
    \ std::min<ll>(n - 1, 5));\n                if (kind == 2 && !points.empty())\
    \ {\n                    return points[uniform(0, static_cast<ll>(points.size())\
    \ - 1)]\n                        .first;\n                }\n                return\
    \ uniform(0, n - 1);\n            };\n            auto range_sum = [&](ll l, ll\
    \ r) {\n                ll total = 0;\n                for (auto [p, x] : points)\
    \ {\n                    if (l <= p && p < r) total += x;\n                }\n\
    \                return total;\n            };\n            for (int query = 0;\
    \ query < 40; ++query) {\n                int type = static_cast<int>(uniform(0,\
    \ 3));\n                if (type == 0) {\n                    ll p = position(),\
    \ x = uniform(1, 9);\n                    sum.set(p, x);\n                   \
    \ bool found = false;\n                    for (auto& point : points) {\n    \
    \                    if (point.first == p) {\n                            point.second\
    \ = x;\n                            found = true;\n                        }\n\
    \                    }\n                    if (!found) points.emplace_back(p,\
    \ x);\n                } else if (type == 1) {\n                    ll l = position(),\
    \ r = position() + 1;\n                    if (l > r) std::swap(l, r);\n     \
    \               assert(sum.prod(l, r) == range_sum(l, r));\n                }\
    \ else if (type == 2) {\n                    ll l = position(), limit = uniform(0,\
    \ 20);\n                    // \u548C\u304C limit \u3092\u8D85\u3048\u308B\u6700\
    \u521D\u306E\u4F4D\u7F6E\u3092\u7D20\u6734\u306B\u63A2\u3059\n               \
    \     std::vector<std::pair<ll, ll>> sorted = points;\n                    std::sort(sorted.begin(),\
    \ sorted.end());\n                    ll expected = n, total = 0;\n          \
    \          for (auto [p, x] : sorted) {\n                        if (p < l) continue;\n\
    \                        total += x;\n                        if (total > limit)\
    \ {\n                            expected = p;\n                            break;\n\
    \                        }\n                    }\n                    assert(sum.max_right(\n\
    \                               l, [&](ll x) { return x <= limit; }) ==\n    \
    \                       expected);\n                } else {\n               \
    \     ll r = position() + 1, limit = uniform(0, 20);\n                    std::vector<std::pair<ll,\
    \ ll>> sorted = points;\n                    std::sort(sorted.rbegin(), sorted.rend());\n\
    \                    ll expected = 0, total = 0;\n                    for (auto\
    \ [p, x] : sorted) {\n                        if (p >= r) continue;\n        \
    \                total += x;\n                        if (total > limit) {\n \
    \                           expected = p + 1;\n                            break;\n\
    \                        }\n                    }\n                    assert(sum.min_left(\n\
    \                               r, [&](ll x) { return x <= limit; }) ==\n    \
    \                       expected);\n                }\n            }\n       \
    \ }\n    }\n}\n\nint main() {\n    test_small();\n    test_huge();\n\n    long\
    \ long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - ds/dynamic_segtree.hpp
  isVerificationFile: true
  path: verify/random_dynamic_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-11-12 13:24:34+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/random_dynamic_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/random_dynamic_segtree.test.cpp
- /verify/verify/random_dynamic_segtree.test.cpp.html
title: verify/random_dynamic_segtree.test.cpp
---
