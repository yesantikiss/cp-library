---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/mo.hpp
    title: Mo's algorithm
  - icon: ':warning:'
    path: ds/2d_prefixsum.hpp
    title: "\u4E8C\u6B21\u5143\u7D2F\u7A4D\u548C\u30FB\u4E8C\u6B21\u5143\u3044\u3082\
      \u3059\u6CD5"
  - icon: ':heavy_check_mark:'
    path: ds/binary_trie.hpp
    title: Binary Trie
  - icon: ':heavy_check_mark:'
    path: ds/cartesian_tree.hpp
    title: Cartesian Tree
  - icon: ':heavy_check_mark:'
    path: ds/compressor.hpp
    title: "\u5EA7\u6A19\u5727\u7E2E"
  - icon: ':warning:'
    path: ds/dynamic_segtree.hpp
    title: "\u52D5\u7684\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: ds/interval_map.hpp
    title: "\u533A\u9593 map"
  - icon: ':warning:'
    path: ds/persistent_segtree.hpp
    title: "\u6C38\u7D9A\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: ds/potential_dsu.hpp
    title: "\u30DD\u30C6\u30F3\u30B7\u30E3\u30EB\u4ED8\u304D Union-Find"
  - icon: ':warning:'
    path: math/factor.hpp
    title: "\u6700\u5C0F\u7D20\u56E0\u6570\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: string/aho_corasick.hpp
    title: Aho-Corasick automaton
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash.hpp
    title: Rolling Hash
  - icon: ':heavy_check_mark:'
    path: tree/heavy_light_decomposition.hpp
    title: Heavy-Light Decomposition
  - icon: ':heavy_check_mark:'
    path: tree/lca_binary_lifting.hpp
    title: LCA (Binary Lifting)
  - icon: ':heavy_check_mark:'
    path: tree/lca_euler_tour.hpp
    title: LCA (Euler Tour + Sparse Table)
  - icon: ':warning:'
    path: utils/fraction.hpp
    title: "\u6709\u7406\u6570"
  - icon: ':heavy_check_mark:'
    path: utils/hash.hpp
    title: "\u4E71\u6570\u5316\u30CF\u30C3\u30B7\u30E5\u30B3\u30F3\u30C6\u30CA"
  - icon: ':heavy_check_mark:'
    path: utils/int128.hpp
    title: "128 bit \u6574\u6570\u306E\u5165\u51FA\u529B"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tests/test.cpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <functional>\n#include <limits>\n#include <sstream>\n#include <string>\n\
    #include <vector>\n\n#line 2 \"algo/mo.hpp\"\n\n#line 4 \"algo/mo.hpp\"\n#include\
    \ <cmath>\n#include <numeric>\n#include <utility>\n#line 8 \"algo/mo.hpp\"\n\n\
    namespace yesantikiss {\n    struct Mo {\n        int n;\n        std::vector<std::pair<int,\
    \ int>> queries; // [l, r)\n    \n        explicit Mo(int n) : n(n) {}\n     \
    \   void add_query(int l, int r) { queries.emplace_back(l, r); }\n    \n     \
    \   // add(i), del(i) \u3057\u304B\u8981\u3089\u306A\u3044\u30B1\u30FC\u30B9\uFF08\
    \u4E92\u63DB\uFF09\n        template <class Add, class Del, class Out>\n     \
    \   void solve(const Add& add, const Del& del, const Out& out) {\n           \
    \ solve(add, add, del, del, out); // \u5DE6\u53F3\u540C\u3058\u95A2\u6570\u3068\
    \u3057\u3066\u6271\u3046\n        }\n    \n        // \u5DE6\u53F3\u3067 add/del\
    \ \u3092\u5206\u3051\u305F\u3044\u30B1\u30FC\u30B9\n        // addL: \u5DE6\u306B\
    \u4F38\u3070\u3059\u3068\u304D\u306B\u8FFD\u52A0 (l--)\n        // addR: \u53F3\
    \u306B\u4F38\u3070\u3059\u3068\u304D\u306B\u8FFD\u52A0 (r++)\n        // delL:\
    \ \u5DE6\u3092\u7E2E\u3081\u308B\u3068\u304D\u306B\u524A\u9664 (l++)\n       \
    \ // delR: \u53F3\u3092\u7E2E\u3081\u308B\u3068\u304D\u306B\u524A\u9664 (r--)\n\
    \        template <class AddL, class AddR, class DelL, class DelR, class Out>\n\
    \        void solve(const AddL& addL, const AddR& addR, const DelL& delL, const\
    \ DelR& delR, const Out& out) {\n            int q = (int)queries.size();\n  \
    \          if (q == 0) return;\n    \n            int bs = std::max(1, (int)(n\
    \ / std::sqrt((double)q)));\n            std::vector<int> ord(q);\n          \
    \  std::iota(ord.begin(), ord.end(), 0);\n    \n            std::sort(ord.begin(),\
    \ ord.end(), [&](int a, int b) {\n                int ab = queries[a].first /\
    \ bs, bb = queries[b].first / bs;\n                if (ab != bb) return ab < bb;\n\
    \                return (ab & 1) ? queries[a].second > queries[b].second\n   \
    \                             : queries[a].second < queries[b].second;\n     \
    \       });\n    \n            int l = 0, r = 0;\n            for (int idx : ord)\
    \ {\n                auto [ql, qr] = queries[idx];\n    \n                while\
    \ (l > ql) addL(--l);\n                while (r < qr) addR(r++);\n           \
    \     while (l < ql) delL(l++);\n                while (r > qr) delR(--r);\n \
    \   \n                out(idx);\n            }\n        }\n    };\n    \n}\n#line\
    \ 2 \"ds/2d_prefixsum.hpp\"\n\n#line 6 \"ds/2d_prefixsum.hpp\"\n\nnamespace yesantikiss\
    \ {\n    // 2D Prefix/Imos (single diff, single O(HW) build)\n    // \u4ED5\u69D8\
    : 0-index, \u534A\u958B\u533A\u9593 [y1,y2)\xD7[x1,x2)\n    // \u4F7F\u3044\u5206\
    \u3051: set_point\u306E\u307F\u2192SET\u30E2\u30FC\u30C9 / add_rect_imos\u306E\
    \u307F\u2192IMOS\u30E2\u30FC\u30C9\uFF08\u4F75\u7528\u7981\u6B62\uFF09\n    template<class\
    \ T>\n    struct PS2D {\n        enum Mode { EMPTY, SET_MODE, IMOS_MODE };\n \
    \   \n        int H, W;\n        Mode mode = EMPTY;\n        std::vector<std::vector<T>>\
    \ buf;   // SET: \u5024\u884C\u5217\u3068\u3057\u3066H\xD7W\u306E\u307F\u4F7F\u7528\
    \ / IMOS: \u5DEE\u5206\u3068\u3057\u3066(H+1)\xD7(W+1)\u5168\u9762\u4F7F\u7528\
    \n        std::vector<std::vector<T>> grid;  // build\u5F8C\u306E\u5B8C\u6210\u30B0\
    \u30EA\u30C3\u30C9 H\xD7W\n        std::vector<std::vector<T>> pref;  // 2D\u7D2F\
    \u7A4D\u548C (H+1)\xD7(W+1)\n        bool built = false;\n    \n        PS2D(int\
    \ H, int W): H(H), W(W),\n            buf(H+1, std::vector<T>(W+1, T())),\n  \
    \          grid(H, std::vector<T>(W, T())),\n            pref(H+1, std::vector<T>(W+1,\
    \ T())) {}\n    \n        // \u5358\u70B9\u4E0A\u66F8\u304D: SET\u30E2\u30FC\u30C9\
    \u5C02\u7528\n        void set_point(int y, int x, T v) {\n            assert(0\
    \ <= y && y < H && 0 <= x && x < W);\n            assert(mode == EMPTY || mode\
    \ == SET_MODE);\n            mode = SET_MODE;\n            buf[y][x] = v;   //\
    \ buf\u306F\u5024\u884C\u5217\u3068\u3057\u3066\u4F7F\u7528\uFF08H\xD7W\u9818\u57DF\
    \uFF09\n            built = false;\n        }\n    \n        // \u9577\u65B9\u5F62\
    \u52A0\u7B97: IMOS\u30E2\u30FC\u30C9\u5C02\u7528\n        void add_rect_imos(int\
    \ y1, int x1, int y2, int x2, T v) {\n            assert(0 <= y1 && y1 <= y2 &&\
    \ y2 <= H);\n            assert(0 <= x1 && x1 <= x2 && x2 <= W);\n           \
    \ assert(mode == EMPTY || mode == IMOS_MODE);\n            mode = IMOS_MODE;\n\
    \            // buf\u306F\u5DEE\u5206\u3068\u3057\u3066\u4F7F\u7528\uFF08(H+1)\xD7\
    (W+1)\uFF09\n            buf[y1][x1] += v;\n            buf[y1][x2] -= v;\n  \
    \          buf[y2][x1] -= v;\n            buf[y2][x2] += v;\n            built\
    \ = false;\n        }\n    \n        // \u70B9\u52A0\u7B97(imos)\n        void\
    \ add_point_imos(int y, int x, T v) { add_rect_imos(y, x, y+1, x+1, v); }\n  \
    \  \n        // \u30AF\u30EA\u30A2\n        void clear_all() {\n            for\
    \ (int y = 0; y <= H; ++y) std::fill(buf[y].begin(), buf[y].end(), T());\n   \
    \         built = false;\n            mode = EMPTY;\n        }\n    \n       \
    \ // \u69CB\u7BC9: \u5E38\u306BO(HW) 1\u56DE\u3067 grid \u3068 pref \u3092\u540C\
    \u6642\u306B\u751F\u6210\n        void build() {\n            for (int y = 0;\
    \ y <= H; ++y) std::fill(pref[y].begin(), pref[y].end(), T());\n    \n       \
    \     if (mode == SET_MODE) {\n                // buf[y][x] \u3092\u5024\u3068\
    \u3057\u3066\u305D\u306E\u307E\u307E\u7D2F\u7A4D\n                for (int y =\
    \ 0; y < H; ++y) {\n                    T row_sum = T();\n                   \
    \ for (int x = 0; x < W; ++x) {\n                        T v = buf[y][x];\n  \
    \                      grid[y][x] = v;\n                        row_sum += v;\n\
    \                        pref[y+1][x+1] = pref[y][x+1] + row_sum;\n          \
    \          }\n                }\n            } else {\n                // IMOS_MODE\
    \ \u307E\u305F\u306F EMPTY\uFF08EMPTY\u306F\u51680\uFF09\n                // buf\u306F\
    \u5DEE\u5206\u3002grid\u306Bimos\u3092\u7D2F\u7A4D\u3057\u3064\u3064pref\u3082\
    \u540C\u6642\u306B\u4F5C\u308B\n                for (int y = 0; y < H; ++y) {\n\
    \                    for (int x = 0; x < W; ++x) {\n                        T\
    \ v = buf[y][x];\n                        if (y) v += grid[y-1][x];\n        \
    \                if (x) v += grid[y][x-1];\n                        if (y && x)\
    \ v -= grid[y-1][x-1];\n                        grid[y][x] = v;\n    \n      \
    \                  pref[y+1][x+1] = pref[y][x+1] + pref[y+1][x] - pref[y][x] +\
    \ v;\n                    }\n                }\n            }\n            built\
    \ = true;\n        }\n    \n        // \u5358\u70B9\u53D6\u5F97 O(1)\n       \
    \ T at(int y, int x) const {\n            assert(built);\n            assert(0\
    \ <= y && y < H && 0 <= x && x < W);\n            return grid[y][x];\n       \
    \ }\n        T operator()(int y, int x) const { return at(y, x); }\n    \n   \
    \     struct RowProxy {\n            const PS2D* p; int y;\n            T operator[](int\
    \ x) const {\n                assert(p->built); assert(0 <= x && x < p->W);\n\
    \                return p->grid[y][x];\n            }\n        };\n        RowProxy\
    \ operator[](int y) const { assert(built); return RowProxy{this, y}; }\n    \n\
    \        // \u9577\u65B9\u5F62\u548C O(1)  [y1,y2)\xD7[x1,x2)\n        T sum(int\
    \ y1, int x1, int y2, int x2) const {\n            assert(built);\n          \
    \  assert(0 <= y1 && y1 <= y2 && y2 <= H);\n            assert(0 <= x1 && x1 <=\
    \ x2 && x2 <= W);\n            return pref[y2][x2] - pref[y1][x2] - pref[y2][x1]\
    \ + pref[y1][x1];\n        }\n    \n        // \u5168\u4F53\u548C\n        T sum_all()\
    \ const { assert(built); return pref[H][W]; }\n    };\n}\n#line 2 \"ds/binary_trie.hpp\"\
    \n\n#line 5 \"ds/binary_trie.hpp\"\n\nnamespace yesantikiss {\n    template<int\
    \ B>\n    struct BinaryTrie {\n        static_assert(0 < B && B <= 63);\n    \
    \    using ull = unsigned long long;\n    \n        struct Node {\n          \
    \  int ch[2];\n            long long cnt; // subtree size (with multiplicity)\n\
    \            long long end; // exact value count at leaf\n            Node() :\
    \ ch{-1, -1}, cnt(0), end(0) {}\n        };\n    \n        std::vector<Node> tr;\n\
    \        BinaryTrie() { tr.emplace_back(); }\n    \n        long long size() const\
    \ { return tr[0].cnt; }\n        bool empty() const { return size() == 0; }\n\
    \    \n        void insert(ull x) { add_raw(x, +1); }\n    \n        // erase\
    \ one occurrence; returns false if not present\n        bool erase(ull x) {\n\
    \            if (count_raw(x) == 0) return false;\n            add_raw(x, -1);\n\
    \            return true;\n        }\n    \n        // count/contains in {v xor\
    \ T} multiset (T=0 => normal)\n        long long count(ull v, ull T = 0) const\
    \ { return count_raw(v ^ T); }\n        bool contains(ull v, ull T = 0) const\
    \ { return count(v, T) > 0; }\n    \n        // kth (0-index) in sorted {x xor\
    \ T}\n        ull kth(long long k, ull T = 0) const {\n            assert(0 <=\
    \ k && k < size());\n            int v = 0;\n            ull y = 0;\n    \n  \
    \          for (int b = B - 1; b >= 0; --b) {\n                int tb = (T >>\
    \ b) & 1ULL;\n                int pref = tb;      // ybit=0 needs xbit=tb\n  \
    \              int other = tb ^ 1;\n    \n                int vp = tr[v].ch[pref];\n\
    \                long long cnt_pref = (vp == -1 ? 0 : tr[vp].cnt);\n    \n   \
    \             if (k < cnt_pref) {\n                    v = vp; // ybit=0\n   \
    \                 assert(v != -1);\n                } else {\n               \
    \     k -= cnt_pref;\n                    v = tr[v].ch[other]; // ybit=1\n   \
    \                 assert(v != -1);\n                    y |= (1ULL << b);\n  \
    \              }\n            }\n            return y;\n        }\n    \n    \
    \    ull min_element(ull T = 0) const {\n            assert(!empty());\n     \
    \       return kth(0, T);\n        }\n    \n        ull max_element(ull T = 0)\
    \ const {\n            assert(!empty());\n            return kth(size() - 1, T);\n\
    \        }\n    \n    private:\n        void add_raw(ull x, long long delta) {\n\
    \            int v = 0;\n            tr[v].cnt += delta;\n            for (int\
    \ b = B - 1; b >= 0; --b) {\n                int bit = (x >> b) & 1ULL;\n    \
    \            if (tr[v].ch[bit] == -1) {\n                    tr[v].ch[bit] = (int)tr.size();\n\
    \                    tr.emplace_back();\n                }\n                v\
    \ = tr[v].ch[bit];\n                tr[v].cnt += delta;\n            }\n     \
    \       tr[v].end += delta;\n        }\n    \n        long long count_raw(ull\
    \ x) const {\n            int v = 0;\n            for (int b = B - 1; b >= 0;\
    \ --b) {\n                int bit = (x >> b) & 1ULL;\n                v = tr[v].ch[bit];\n\
    \                if (v == -1) return 0;\n            }\n            return tr[v].end;\n\
    \        }\n    };\n    \n    // usage example:\n    // using BT = BinaryTrie<30>;\
    \ // for [0, 1e9]\n    \n}\n#line 2 \"ds/cartesian_tree.hpp\"\n\n#line 5 \"ds/cartesian_tree.hpp\"\
    \n\nnamespace yesantikiss {\n    template <class T, class Compare = std::less<T>>\n\
    \    struct CartesianTree {\n        int n = 0;\n        std::vector<T> a;\n \
    \       std::vector<int> par, left, right;\n        int root = -1;\n        Compare\
    \ comp;\n    \n        CartesianTree() {}\n    \n        CartesianTree(const std::vector<T>&\
    \ _a, Compare _comp = Compare())\n            : n((int)_a.size()),\n         \
    \     a(_a),\n              par(n, -1),\n              left(n, -1),\n        \
    \      right(n, -1),\n              root(-1),\n              comp(_comp) {\n \
    \           build();\n        }\n    \n        // comp(a[i], a[j]) == true \u306A\
    \u3089 i \u306E\u65B9\u304C j \u3088\u308A\u4E0A\u306B\u6765\u308B\n        //\
    \ less<T>    : min Cartesian Tree\n        // greater<T> : max Cartesian Tree\n\
    \        void build() {\n            std::vector<int> st;\n            st.reserve(n);\n\
    \    \n            for (int i = 0; i < n; i++) {\n                int last = -1;\n\
    \    \n                while (!st.empty() && comp(a[i], a[st.back()])) {\n   \
    \                 last = st.back();\n                    st.pop_back();\n    \
    \            }\n    \n                if (!st.empty()) {\n                   \
    \ par[i] = st.back();\n                    right[st.back()] = i;\n           \
    \     }\n    \n                if (last != -1) {\n                    par[last]\
    \ = i;\n                    left[i] = last;\n                }\n    \n       \
    \         st.push_back(i);\n            }\n    \n            for (int i = 0; i\
    \ < n; i++) {\n                if (par[i] == -1) {\n                    root =\
    \ i;\n                    break;\n                }\n            }\n        }\n\
    \    };\n}\n#line 2 \"ds/compressor.hpp\"\n\n#line 6 \"ds/compressor.hpp\"\n\n\
    namespace yesantikiss {\n    template <class T>\n    struct Compressor {\n   \
    \     std::vector<T> xs;   // \u8FFD\u52A0\u3055\u308C\u305F\u5024\uFF08\u91CD\
    \u8907\u3042\u308A\uFF09\n        std::vector<T> v;    // \u30BD\u30FC\u30C8\u6E08\
    \u307F\u30E6\u30CB\u30FC\u30AF\u5217\n        bool built = false;\n    \n    \
    \    // \u5024\u3092\u8FFD\u52A0: \u5E73\u5747 O(1)\n        void add(const T&\
    \ x) {\n            xs.push_back(x);\n        }\n    \n        // \u7BC4\u56F2\
    \u8FFD\u52A0: O(k)\n        template <class It>\n        void add_range(It first,\
    \ It last) {\n            xs.insert(xs.end(), first, last);\n        }\n    \n\
    \        // \u69CB\u7BC9: O(n log n)  n = add \u3055\u308C\u305F\u7DCF\u6570\n\
    \        void build() {\n            v = xs;\n            std::sort(v.begin(),\
    \ v.end());\n            v.erase(std::unique(v.begin(), v.end()), v.end());\n\
    \            built = true;\n        }\n    \n        // \u5727\u7E2E\u5F8C\u306E\
    \u8981\u7D20\u6570: O(1)\n        int size() const {\n            return (int)v.size();\n\
    \        }\n    \n        // x \u306E\u5727\u7E2E\u5F8C\u30A4\u30F3\u30C7\u30C3\
    \u30AF\u30B9\u3092\u8FD4\u3059\u3002\u5B58\u5728\u3057\u306A\u3051\u308C\u3070\
    \ -1: O(log n)\n        int get(const T& x) const {\n            assert(built);\n\
    \            auto it = std::lower_bound(v.begin(), v.end(), x);\n            if\
    \ (it == v.end() || *it != x) return -1;\n            return (int)(it - v.begin());\n\
    \        }\n    \n        // x \u304C\u5B58\u5728\u3059\u308B\u304B: O(log n)\n\
    \        bool has(const T& x) const {\n            return get(x) != -1;\n    \
    \    }\n    \n        // v[i] >= x \u3068\u306A\u308B\u6700\u5C0F i \u3092\u8FD4\
    \u3059\u3002\u5168\u3066 < x \u306A\u3089 size(): O(log n)\n        int lower_bound(const\
    \ T& x) const {\n            assert(built);\n            return (int)(std::lower_bound(v.begin(),\
    \ v.end(), x) - v.begin());\n        }\n    \n        // v[i] > x \u3068\u306A\
    \u308B\u6700\u5C0F i \u3092\u8FD4\u3059\u3002\u5168\u3066 <= x \u306A\u3089 size():\
    \ O(log n)\n        int upper_bound(const T& x) const {\n            assert(built);\n\
    \            return (int)(std::upper_bound(v.begin(), v.end(), x) - v.begin());\n\
    \        }\n    \n        // \u5727\u7E2E\u5024 \u2192 \u5143\u306E\u5024: O(1)\n\
    \        const T& value(int idx) const {\n            assert(built);\n       \
    \     return v[idx];\n        }\n    \n        // \u914D\u5217\u3092\u5727\u7E2E\
    \u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\u5217\u306B\u5909\u63DB\u3057\u3066\u8FD4\
    \u3059\uFF08\u5B58\u5728\u3057\u306A\u3044\u5024\u306F -1\uFF09: O(k log n)\n\
    \        std::vector<int> map(const std::vector<T>& a) const {\n            assert(built);\n\
    \            std::vector<int> res; res.reserve(a.size());\n            for (auto&\
    \ x : a) res.push_back(get(x));\n            return res;\n        }\n    };\n\
    }\n#line 2 \"ds/dynamic_segtree.hpp\"\n\n#line 5 \"ds/dynamic_segtree.hpp\"\n\
    #include <cstddef>\n#line 7 \"ds/dynamic_segtree.hpp\"\n\n// \u52D5\u7684\uFF08\
    implicit\uFF09\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\n// - \u533A\u9593 [0, n) \u3092\
    \u6271\u3046\n// - \u66F4\u65B0\u304C\u5165\u3063\u305F\u7D4C\u8DEF\u3060\u3051\
    \u30CE\u30FC\u30C9\u751F\u6210\n// - ACL segtree \u98A8\u30A4\u30F3\u30BF\u30D5\
    \u30A7\u30FC\u30B9\n\nnamespace yesantikiss {\n    // \u52D5\u7684\uFF08implicit\uFF09\
    \u30BB\u30B0\u30E1\u30F3\u30C8\u6728\n    // - \u533A\u9593 [0, n) \u3092\u6271\
    \u3046\n    // - \u66F4\u65B0\u304C\u5165\u3063\u305F\u7D4C\u8DEF\u3060\u3051\u30CE\
    \u30FC\u30C9\u751F\u6210\n    // - ACL segtree \u98A8\u30A4\u30F3\u30BF\u30D5\u30A7\
    \u30FC\u30B9\n    \n    template <class S, S (*op)(S, S), S (*e)()>\n    struct\
    \ dynamic_segtree {\n    private:\n        struct Node {\n            int l =\
    \ -1, r = -1;\n            S val;\n            Node() : val(e()) {}\n        };\n\
    \    \n        long long n_ = 0;\n        unsigned long long size_ = 1;\n    \
    \    int root_ = -1;\n        std::vector<Node> pool_;\n    \n        static unsigned\
    \ long long ceil_pow2_ull(unsigned long long x) {\n            unsigned long long\
    \ p = 1;\n            while (p < x) p <<= 1;\n            return p;\n        }\n\
    \    \n        int new_node() {\n            pool_.emplace_back();\n         \
    \   return (int)pool_.size() - 1;\n        }\n    \n        S node_val(int idx)\
    \ const {\n            return (idx == -1) ? e() : pool_[idx].val;\n        }\n\
    \    \n        S prod_rec(int idx,\n                   unsigned long long segL,\
    \ unsigned long long segR,\n                   unsigned long long ql, unsigned\
    \ long long qr) const {\n            if (idx == -1) return e();\n            if\
    \ (qr <= segL || segR <= ql) return e();\n            if (ql <= segL && segR <=\
    \ qr) return pool_[idx].val;\n            unsigned long long mid = (segL + segR)\
    \ >> 1;\n            S left = prod_rec(pool_[idx].l, segL, mid, ql, qr);\n   \
    \         S right = prod_rec(pool_[idx].r, mid, segR, ql, qr);\n            return\
    \ op(left, right);\n        }\n    \n        template <class F>\n        long\
    \ long max_right_rec(int idx,\n                                unsigned long long\
    \ segL, unsigned long long segR,\n                                unsigned long\
    \ long ql,\n                                F& f, S& sm) const {\n           \
    \ if (segR <= ql) return (long long)ql;\n            S segVal = (idx == -1) ?\
    \ e() : pool_[idx].val;\n            if (segL >= ql) {\n                S nxt\
    \ = op(sm, segVal);\n                if (f(nxt)) {\n                    sm = nxt;\n\
    \                    return (long long)segR;\n                }\n            \
    \    if (segR - segL == 1) return (long long)segL;\n            }\n          \
    \  unsigned long long mid = (segL + segR) >> 1;\n            int lch = (idx ==\
    \ -1) ? -1 : pool_[idx].l;\n            int rch = (idx == -1) ? -1 : pool_[idx].r;\n\
    \            long long resL = max_right_rec(lch, segL, mid, ql, f, sm);\n    \
    \        if ((unsigned long long)resL < mid) return resL;\n            return\
    \ max_right_rec(rch, mid, segR, ql, f, sm);\n        }\n    \n        template\
    \ <class F>\n        long long min_left_rec(int idx,\n                       \
    \        unsigned long long segL, unsigned long long segR,\n                 \
    \              unsigned long long qr,\n                               F& f, S&\
    \ sm) const {\n            if (qr <= segL) return (long long)qr;\n           \
    \ S segVal = (idx == -1) ? e() : pool_[idx].val;\n            if (segR <= qr)\
    \ {\n                S nxt = op(segVal, sm);\n                if (f(nxt)) {\n\
    \                    sm = nxt;\n                    return (long long)segL;\n\
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
    \ res = r;\n            return res;\n        }\n    };\n}\n#line 2 \"ds/interval_map.hpp\"\
    \n\n#line 6 \"ds/interval_map.hpp\"\n#include <iterator>\n#include <ostream>\n\
    #include <set>\n#include <tuple>\n#include <type_traits>\n#line 13 \"ds/interval_map.hpp\"\
    \n\nnamespace yesantikiss {\n    using std::distance;\n    using std::max;\n \
    \   using std::min;\n    using std::next;\n    using std::ostream;\n    using\
    \ std::prev;\n    using std::set;\n    using std::vector;\n    /*\n      IntervalMap\uFF08\
    \u533A\u9593 map / \u533A\u9593 set \u7BA1\u7406\uFF1A\u5B8C\u6210\u5F62\uFF09\
    \n      ==============================================\n      \u534A\u958B\u533A\
    \u9593 [l, r) \u3092 set \u3067\u7BA1\u7406\u3057\u3001\u5404\u533A\u9593\u306B\
    \u5024 v \u3092\u6301\u305F\u305B\u308B\u3002\n    \n      \u25A0 \u4E0D\u5909\
    \u91CF\uFF08\u3053\u308C\u304C\u5D29\u308C\u306A\u3044\u3088\u3046\u306B\u5B9F\
    \u88C5\u3059\u308B\uFF09\n      ----------------------------------------\n   \
    \   1) \u533A\u9593\u306F\u4E92\u3044\u306B\u4EA4\u5DEE\u3057\u306A\u3044\n  \
    \    2) \u5E38\u306B [L, R) \u3092\u5B8C\u5168\u306B\u88AB\u8986\u3057\u3066\u3044\
    \u308B\uFF08init \u3067 1 \u672C\u5165\u308C\u3066\u958B\u59CB\uFF09\n      3)\
    \ \u96A3\u63A5\u3057\u3066\u5024\u304C\u540C\u3058\u533A\u9593\u306F\u5B58\u5728\
    \u3057\u306A\u3044\uFF08\u81EA\u52D5\u30DE\u30FC\u30B8\u3067\u6F70\u3059\uFF09\
    \n    \n      \u25A0 \u4E3B\u8981 API\n      ----------\n      - locate(x)   \
    \     : x \u3092\u542B\u3080\u533A\u9593\u306E iterator \u3092\u8FD4\u3059\uFF08\
    \u8D70\u67FB\u30FB\u30B8\u30E3\u30F3\u30D7\u7528\uFF09\n      - get_val(x)   \
    \    : \u70B9 x \u306E\u5024\n      - assign(l,r,v)    : [l,r) \u3092 v \u306B\
    \u300C\u4EE3\u5165\u300D\uFF08split + erase + insert + merge\uFF09\n      - apply(l,r,f)\
    \     : [l,r) \u306B\u304B\u304B\u308B\u5404\u533A\u9593\u306E\u5024\u3092 f \u3067\
    \u5909\u63DB\n          f \u306F\u4EE5\u4E0B\u3069\u3061\u3089\u3067\u3082OK:\n\
    \            (A) V f(const V&)\n            (B) V f(T l, T r, const V&)\n    \
    \  - enumerate_cut(l,r,f) : [l,r) \u306B\u304B\u304B\u308B\u533A\u9593\u3092\u300C\
    \u5FC5\u305A [l,r) \u306B\u5207\u3063\u305F\u5F62\u300D\u3067\u5217\u6319\n  \
    \    - segments_cut(l,r)    : enumerate_cut \u306E vector \u7248\uFF08\u30C7\u30D0\
    \u30C3\u30B0\u30FB\u56DE\u7B54\u751F\u6210\u7528\uFF09\n    \n      \u25A0 add/del\
    \ \u30B3\u30FC\u30EB\u30D0\u30C3\u30AF\n      --------------------------------------\n\
    \      split / assign / apply / merge \u304C\u5185\u90E8\u3067\u533A\u9593\u3092\
    \u6D88\u3057\u305F\u308A\u4F5C\u3063\u305F\u308A\u3059\u308B\u306E\u3067\u3001\
    \n      \u300C\u533A\u9593\u304C\u5897\u6E1B\u3057\u305F\u3068\u304D\u306E\u5BC4\
    \u4E0E\u66F4\u65B0\u300D\u3092\u5916\u304B\u3089\u6E21\u305B\u308B\u3088\u3046\
    \u306B\u3059\u308B\u3002\n    \n        add(l,r,v): \u533A\u9593 [l,r) \u306E\u5024\
    \ v \u304C \u201C\u8FFD\u52A0\u201D \u3055\u308C\u305F\n        del(l,r,v): \u533A\
    \u9593 [l,r) \u306E\u5024 v \u304C \u201C\u524A\u9664\u201D \u3055\u308C\u305F\
    \n    \n      \u4F8B\uFF1A\u5024\u3054\u3068\u306E\u7DCF\u9577 len[v] \u3092\u7DAD\
    \u6301\u3057\u305F\u3044\n        add: len[v] += (r-l)\n        del: len[v] -=\
    \ (r-l)\n    \n      \u25A0 \u8D85\u91CD\u8981\u306A\u6CE8\u610F\n      --------------\n\
    \      assign/apply/enumerate_cut \u306F\u5185\u90E8\u3067 erase/insert \u3092\
    \u884C\u3046\u305F\u3081\u3001\n      \u305D\u308C\u4EE5\u524D\u306B\u53D6\u3063\
    \u305F iterator \u306F\u7121\u52B9\u5316\u3055\u308C\u5F97\u308B\u3002\n     \
    \ \u2192 \u66F4\u65B0\u5F8C\u306B iterator \u3092\u4F7F\u3044\u56DE\u3055\u305A\
    \u3001locate \u306A\u3069\u3067\u53D6\u308A\u76F4\u3059\u3002\n    */\n    \n\
    \    template <class T, class V>\n    struct IntervalMap {\n        struct Node\
    \ {\n            T l, r;\n            V v;\n        };\n    \n        // set \u306F\
    \ l \u306E\u6607\u9806\u3002transparent comparator \u306B\u3057\u3066 lower_bound(x)\
    \ \u3092\u76F4\u63A5\u4F7F\u3048\u308B\u3088\u3046\u306B\u3059\u308B\u3002\n \
    \       struct Cmp {\n            using is_transparent = void;\n            bool\
    \ operator()(const Node& a, const Node& b) const { return a.l < b.l; }\n     \
    \       bool operator()(const Node& a, const T& x)   const { return a.l < x; }\n\
    \            bool operator()(const T& x, const Node& a)   const { return x < a.l;\
    \ }\n        };\n    \n        T L, R;\n        set<Node, Cmp> s;\n    \n    \
    \    IntervalMap() = default;\n    \n        // [L, R) \u3092 init \u3067\u5B8C\
    \u5168\u88AB\u8986\u3057\u3066\u30B9\u30BF\u30FC\u30C8\uFF08\u756A\u5175\u3092\
    \u517C\u306D\u308B\uFF09\n        IntervalMap(T L_, T R_, V init) : L(L_), R(R_)\
    \ {\n            assert(L < R);\n            s.insert(Node{L, R, init});\n   \
    \     }\n    \n        auto begin() { return s.begin(); }\n        auto end()\
    \   { return s.end(); }\n        auto begin() const { return s.begin(); }\n  \
    \      auto end()   const { return s.end(); }\n    \n        // x \u3092\u542B\
    \u3080\u533A\u9593\u306E iterator \u3092\u8FD4\u3059\uFF08L <= x < R \u3092\u524D\
    \u63D0\uFF09\n        auto locate(T x) {\n            assert(L <= x && x < R);\n\
    \            auto it = s.upper_bound(x); // l > x \u3068\u306A\u308B\u6700\u521D\
    \n            --it;                       // \u305D\u306E1\u3064\u524D\u304C\u5FC5\
    \u305A x \u3092\u542B\u3080\uFF08\u5B8C\u5168\u88AB\u8986\u306A\u306E\u3067\uFF09\
    \n            return it;\n        }\n        auto locate(T x) const {\n      \
    \      assert(L <= x && x < R);\n            auto it = s.upper_bound(x);\n   \
    \         --it;\n            return it;\n        }\n    \n        // \u70B9\u306E\
    \u5024\n        V get_val(T x) const {\n            return locate(x)->v;\n   \
    \     }\n    \n    private:\n        // f \u3092\u547C\u3076\uFF1Af(v) \u307E\u305F\
    \u306F f(l,r,v) \u306B\u5BFE\u5FDC\n        template <class F>\n        static\
    \ V call_f(F& f, T l, T r, const V& v) {\n            if constexpr (std::is_invocable_r_v<V,\
    \ F, const V&>) {\n                return f(v);\n            } else {\n      \
    \          static_assert(std::is_invocable_r_v<V, F, T, T, const V&>,\n      \
    \                        \"apply: f must be V(const V&) or V(T,T,const V&)\");\n\
    \                return f(l, r, v);\n            }\n        }\n    \n        //\
    \ split(x): x \u3092\u5883\u306B\u533A\u9593\u3092\u5272\u3063\u3066\u300Cx \u304B\
    \u3089\u59CB\u307E\u308B\u533A\u9593\u300D\u306E iterator \u3092\u8FD4\u3059\n\
    \        // split \u3082\u533A\u9593\u69CB\u9020\u3092\u5909\u3048\u308B\u306E\
    \u3067 add/del \u3092\u547C\u3093\u3067\u96C6\u8A08\u306E\u6574\u5408\u3092\u4FDD\
    \u3064\u3002\n        template <class ADD, class DEL>\n        auto split(T x,\
    \ ADD add, DEL del) {\n            if (x <= L) return s.begin();\n           \
    \ if (x >= R) return s.end();\n    \n            auto it = locate(x);\n      \
    \      if (it->l == x) return it; // \u3059\u3067\u306B\u5883\u754C\u304C\u3042\
    \u308B\n    \n            Node cur = *it;\n    \n            // \u5143\u533A\u9593\
    \u306E\u5BC4\u4E0E\u3092\u6D88\u3057\u3066\u304B\u3089\u5206\u5272\n         \
    \   del(cur.l, cur.r, cur.v);\n            s.erase(it);\n    \n            auto\
    \ itL = s.insert(Node{cur.l, x, cur.v}).first;\n            auto itR = s.insert(Node{x,\
    \ cur.r, cur.v}).first;\n            add(itL->l, itL->r, itL->v);\n          \
    \  add(itR->l, itR->r, itR->v);\n    \n            return itR;\n        }\n  \
    \  \n        // it \u306E\u5DE6\u53F3\u3092\u898B\u3066\u300C\u96A3\u63A5\u304B\
    \u3064\u540C\u5024\u300D\u3092\u53EF\u80FD\u306A\u9650\u308A\u30DE\u30FC\u30B8\
    \n        template <class ADD, class DEL>\n        auto merge_around(typename\
    \ set<Node, Cmp>::iterator it, ADD add, DEL del) {\n            bool changed =\
    \ true;\n            while (changed) {\n                changed = false;\n   \
    \ \n                // \u5DE6\u3068\u30DE\u30FC\u30B8\n                if (it\
    \ != s.begin()) {\n                    auto pv = prev(it);\n                 \
    \   if (pv->r == it->l && pv->v == it->v) {\n                        Node a =\
    \ *pv, b = *it;\n                        del(a.l, a.r, a.v);\n               \
    \         del(b.l, b.r, b.v);\n                        s.erase(pv);\n        \
    \                s.erase(it);\n                        it = s.insert(Node{a.l,\
    \ b.r, a.v}).first;\n                        add(it->l, it->r, it->v);\n     \
    \                   changed = true;\n                        continue;\n     \
    \               }\n                }\n    \n                // \u53F3\u3068\u30DE\
    \u30FC\u30B8\n                auto nx = next(it);\n                if (nx != s.end())\
    \ {\n                    if (it->r == nx->l && it->v == nx->v) {\n           \
    \             Node a = *it, b = *nx;\n                        del(a.l, a.r, a.v);\n\
    \                        del(b.l, b.r, b.v);\n                        s.erase(it);\n\
    \                        s.erase(nx);\n                        it = s.insert(Node{a.l,\
    \ b.r, a.v}).first;\n                        add(it->l, it->r, it->v);\n     \
    \                   changed = true;\n                        continue;\n     \
    \               }\n                }\n            }\n            return it;\n\
    \        }\n    \n        // \u3042\u308B\u8FD1\u508D\u3060\u3051\u300C\u96A3\u63A5\
    \u540C\u5024\u300D\u3092\u6F70\u3059\uFF08apply/enumerate_cut \u3067 split \u3057\
    \u305F\u3042\u3068\u306B\u4F7F\u3046\uFF09\n        template <class ADD, class\
    \ DEL>\n        void normalize_window(T l, T r, ADD add, DEL del) {\n        \
    \    auto it = s.lower_bound(l);\n            if (it != s.begin()) it = prev(it);\n\
    \    \n            while (it != s.end()) {\n                auto nx = next(it);\n\
    \                if (nx == s.end()) break;\n    \n                if (it->r ==\
    \ nx->l && it->v == nx->v) {\n                    Node a = *it, b = *nx;\n   \
    \                 del(a.l, a.r, a.v);\n                    del(b.l, b.r, b.v);\n\
    \                    s.erase(it);\n                    s.erase(nx);\n        \
    \            it = s.insert(Node{a.l, b.r, a.v}).first;\n                    add(it->l,\
    \ it->r, it->v);\n                    if (it != s.begin()) it = prev(it);\n  \
    \              } else {\n                    // \u89E6\u3063\u305F\u7BC4\u56F2\
    \u3088\u308A\u5341\u5206\u53F3\u306B\u6765\u305F\u3089\u6253\u3061\u5207\u308A\
    \uFF08\u4FDD\u5B88\u7684\uFF09\n                    if (it->l >= r && nx->l >=\
    \ r) break;\n                    it = nx;\n                }\n            }\n\
    \        }\n    \n    public:\n        // assign: [l,r) \u3092 v \u306B\u4EE3\u5165\
    \uFF08add/del \u4ED8\u304D\uFF09\n        template <class ADD, class DEL>\n  \
    \      void assign(T l, T r, const V& v, ADD add, DEL del) {\n            l =\
    \ max(l, L);\n            r = min(r, R);\n            if (l >= r) return;\n  \
    \  \n            auto itr = split(r, add, del);\n            auto itl = split(l,\
    \ add, del);\n    \n            for (auto it = itl; it != itr; ) {\n         \
    \       del(it->l, it->r, it->v);\n                it = s.erase(it);\n       \
    \     }\n    \n            auto it = s.insert(Node{l, r, v}).first;\n        \
    \    add(l, r, v);\n    \n            merge_around(it, add, del);\n        }\n\
    \    \n        // assign: \u30B3\u30FC\u30EB\u30D0\u30C3\u30AF\u306A\u3057\n \
    \       void assign(T l, T r, const V& v) {\n            assign(l, r, v,\n   \
    \                [](T, T, const V&) {},\n                   [](T, T, const V&)\
    \ {});\n        }\n    \n        // apply: [l,r) \u306B\u304B\u304B\u308B\u5404\
    \u533A\u9593\u306E\u5024\u3092 f \u3067\u5909\u63DB\uFF08add/del \u4ED8\u304D\uFF09\
    \n        template <class F, class ADD, class DEL>\n        void apply(T l, T\
    \ r, F f, ADD add, DEL del) {\n            l = max(l, L);\n            r = min(r,\
    \ R);\n            if (l >= r) return;\n    \n            auto itr = split(r,\
    \ add, del);\n            auto itl = split(l, add, del);\n    \n            //\
    \ set \u3092\u3044\u3058\u308A\u306A\u304C\u3089\u5909\u63DB\u3059\u308B\u3068\
    \u58CA\u308C\u3084\u3059\u3044\u306E\u3067\u3001\u4E00\u65E6\u9000\u907F\u3057\
    \u3066\u304B\u3089\u5165\u308C\u76F4\u3059\n            vector<Node> segs;\n \
    \           segs.reserve(distance(itl, itr));\n    \n            for (auto it\
    \ = itl; it != itr; ++it) {\n                Node nd = *it;\n                del(nd.l,\
    \ nd.r, nd.v);\n                nd.v = call_f(f, nd.l, nd.r, nd.v);\n        \
    \        segs.push_back(nd);\n            }\n    \n            for (auto it =\
    \ itl; it != itr; ) it = s.erase(it);\n    \n            for (auto &nd : segs)\
    \ {\n                s.insert(nd);\n                add(nd.l, nd.r, nd.v);\n \
    \           }\n    \n            // split \u306E\u7D50\u679C\u751F\u307E\u308C\
    \u305F\u540C\u5024\u96A3\u63A5\u3092\u6F70\u3059\n            normalize_window(l,\
    \ r, add, del);\n        }\n    \n        // apply: \u30B3\u30FC\u30EB\u30D0\u30C3\
    \u30AF\u306A\u3057\n        template <class F>\n        void apply(T l, T r, F\
    \ f) {\n            apply(l, r, f,\n                  [](T, T, const V&) {},\n\
    \                  [](T, T, const V&) {});\n        }\n    \n        /*\n    \
    \      enumerate_cut(l, r, f):\n          ----------------------\n          [l,r)\
    \ \u306B\u304B\u304B\u308B\u533A\u9593\u3092\u300C\u5FC5\u305A [l,r) \u306B\u5207\
    \u3063\u305F\u5F62\u300D\u3067\u5217\u6319\u3059\u308B\u3002\n    \n         \
    \ \u4F8B\uFF1A\n            \u5143\u304C [0,10)=A \u3067 enumerate_cut(3,7) \u3092\
    \u547C\u3076\u3068\u3001\n            split \u306B\u3088\u308A [0,3)=A [3,7)=A\
    \ [7,10)=A \u306E\u5F62\u306B\u4E00\u65E6\u306A\u308A\u3001\n            f(3,7,A)\
    \ \u304C\u547C\u3070\u308C\u308B\u3002\n    \n          \u8A08\u7B97\u91CF\uFF08\
    \u76EE\u5B89\uFF09: O(log M + k)\n            - split \u304C\u9AD8\u30052\u56DE\
    : O(log M)\uFF08M=\u533A\u9593\u6570\uFF09\n            - \u4EA4\u5DEE\u533A\u9593\
    \u3092 k \u500B\u5217\u6319: O(k)\n            - normalize \u306F\u89E6\u3063\u305F\
    \u5468\u8FBA\u3060\u3051\uFF08\u5B9A\u6570\u500D\u304C\u5C11\u3057\u5897\u3048\
    \u308B\u7A0B\u5EA6\uFF09\n        */\n        template <class F, class ADD, class\
    \ DEL>\n        void enumerate_cut(T l, T r, F f, ADD add, DEL del) {\n      \
    \      l = max(l, L);\n            r = min(r, R);\n            if (l >= r) return;\n\
    \    \n            auto itr = split(r, add, del);\n            auto itl = split(l,\
    \ add, del);\n    \n            for (auto it = itl; it != itr; ++it) {\n     \
    \           f(it->l, it->r, it->v);\n            }\n    \n            // split\u3067\
    \u540C\u5024\u96A3\u63A5\u304C\u751F\u307E\u308C\u305F\u53EF\u80FD\u6027\u304C\
    \u3042\u308B\u306E\u3067\u623B\u3059\n            normalize_window(l, r, add,\
    \ del);\n        }\n    \n        template <class F>\n        void enumerate_cut(T\
    \ l, T r, F f) {\n            enumerate_cut(l, r, f,\n                       \
    \   [](T, T, const V&) {},\n                          [](T, T, const V&) {});\n\
    \        }\n    \n        // vector \u3067\u6B32\u3057\u3044\u5834\u5408\uFF08\
    \u30C7\u30D0\u30C3\u30B0\u3084\u300C\u533A\u9593\u5217\u3092\u6750\u6599\u306B\
    \u7B54\u3048\u3092\u4F5C\u308B\u300D\u7528\u9014\uFF09\n        vector<Node> segments_cut(T\
    \ l, T r) {\n            vector<Node> res;\n            enumerate_cut(l, r, [&](T\
    \ a, T b, const V& v) {\n                res.push_back(Node{a, b, v});\n     \
    \       });\n            return res;\n        }\n    \n        // \u30C7\u30D0\
    \u30C3\u30B0\uFF1A\u5168\u533A\u9593\u3092\u51FA\u529B\n        friend ostream&\
    \ operator<<(ostream& os, const IntervalMap& im) {\n            for (auto &nd\
    \ : im.s) {\n                os << \"[\" << nd.l << \",\" << nd.r << \")=\" <<\
    \ nd.v << \" \";\n            }\n            return os;\n        }\n    };\n}\n\
    #line 2 \"ds/persistent_segtree.hpp\"\n\n#line 6 \"ds/persistent_segtree.hpp\"\
    \n\nnamespace yesantikiss {\n    template<class S, S (*op)(S, S), S (*e)()>\n\
    \    struct persistent_segtree {\n        struct Node {\n            S val;\n\
    \            int lch, rch;\n        };\n    \n        int n = 0;\n        std::vector<Node>\
    \ nodes;\n        std::vector<int> roots; // roots[version] = \u305D\u306E\u7248\
    \u306E\u6839\u30CE\u30FC\u30C9 index\n    \n        persistent_segtree() = default;\n\
    \    \n        explicit persistent_segtree(const std::vector<S>& a) {\n      \
    \      init(a);\n        }\n    \n        explicit persistent_segtree(int n_)\
    \ {\n            init(std::vector<S>(n_, e()));\n        }\n    \n        int\
    \ new_node(const S& val, int lch = -1, int rch = -1) {\n            nodes.push_back({val,\
    \ lch, rch});\n            return (int)nodes.size() - 1;\n        }\n    \n  \
    \      int build(int l, int r, const std::vector<S>& a) {\n            if (r -\
    \ l == 1) {\n                return new_node(a[l]);\n            }\n         \
    \   int m = (l + r) >> 1;\n            int lc = build(l, m, a);\n            int\
    \ rc = build(m, r, a);\n            return new_node(op(nodes[lc].val, nodes[rc].val),\
    \ lc, rc);\n        }\n    \n        void init(const std::vector<S>& a) {\n  \
    \          n = (int)a.size();\n            nodes.clear();\n            roots.clear();\n\
    \    \n            nodes.reserve(std::max(1, 2 * n));\n    \n            if (n\
    \ == 0) {\n                roots.push_back(-1); // version 0 \u306F\u7A7A\u914D\
    \u5217\u7248\n                return;\n            }\n    \n            int root0\
    \ = build(0, n, a);\n            roots.push_back(root0); // \u521D\u671F\u7248\
    \u306E version \u306F 0\n        }\n    \n        int versions() const {\n   \
    \         return (int)roots.size();\n        }\n    \n        int latest_version()\
    \ const {\n            return (int)roots.size() - 1;\n        }\n    \n      \
    \  int normalize_version(int ver) const {\n            if (ver == -1) return latest_version();\n\
    \            assert(0 <= ver && ver < (int)roots.size());\n            return\
    \ ver;\n        }\n    \n        int set_rec(int node, int l, int r, int p, const\
    \ S& x) {\n            if (r - l == 1) {\n                return new_node(x);\n\
    \            }\n    \n            int m = (l + r) >> 1;\n            int lc =\
    \ nodes[node].lch;\n            int rc = nodes[node].rch;\n    \n            if\
    \ (p < m) {\n                lc = set_rec(lc, l, m, p, x);\n            } else\
    \ {\n                rc = set_rec(rc, m, r, p, x);\n            }\n    \n    \
    \        return new_node(op(nodes[lc].val, nodes[rc].val), lc, rc);\n        }\n\
    \    \n        S get_rec(int node, int l, int r, int p) const {\n            if\
    \ (r - l == 1) {\n                return nodes[node].val;\n            }\n   \
    \ \n            int m = (l + r) >> 1;\n            if (p < m) return get_rec(nodes[node].lch,\
    \ l, m, p);\n            return get_rec(nodes[node].rch, m, r, p);\n        }\n\
    \    \n        S prod_rec(int node, int l, int r, int ql, int qr) const {\n  \
    \          if (qr <= l || r <= ql) return e();\n            if (ql <= l && r <=\
    \ qr) return nodes[node].val;\n    \n            int m = (l + r) >> 1;\n     \
    \       return op(\n                prod_rec(nodes[node].lch, l, m, ql, qr),\n\
    \                prod_rec(nodes[node].rch, m, r, ql, qr)\n            );\n   \
    \     }\n    \n        // ver \u7248\u3092\u5143\u306B p \u756A\u76EE\u3092 x\
    \ \u306B\u5909\u66F4\u3057\u305F\u65B0\u3057\u3044\u7248\u3092\u672B\u5C3E\u306B\
    \u8FFD\u52A0\n        // ver = -1 \u306A\u3089\u6700\u65B0\u7248\u3092\u5143\u306B\
    \u3059\u308B\n        // \u8FD4\u308A\u5024\u306F\u65B0\u3057\u3044 version \u756A\
    \u53F7\n        int set(int p, const S& x, int ver = -1) {\n            assert(0\
    \ <= p && p < n);\n            ver = normalize_version(ver);\n            int\
    \ new_root = set_rec(roots[ver], 0, n, p, x);\n            roots.push_back(new_root);\n\
    \            return latest_version();\n        }\n    \n        S get(int p, int\
    \ ver = -1) const {\n            assert(0 <= p && p < n);\n            ver = normalize_version(ver);\n\
    \            return get_rec(roots[ver], 0, n, p);\n        }\n    \n        S\
    \ prod(int l, int r, int ver = -1) const {\n            assert(0 <= l && l <=\
    \ r && r <= n);\n            ver = normalize_version(ver);\n            if (n\
    \ == 0) return e();\n            return prod_rec(roots[ver], 0, n, l, r);\n  \
    \      }\n    \n        S all_prod(int ver = -1) const {\n            ver = normalize_version(ver);\n\
    \            if (n == 0) return e();\n            return nodes[roots[ver]].val;\n\
    \        }\n    };\n}\n#line 2 \"ds/potential_dsu.hpp\"\n\n#line 5 \"ds/potential_dsu.hpp\"\
    \n\nnamespace yesantikiss {\n    // ACL dsu \u98A8 + \u30DD\u30C6\u30F3\u30B7\u30E3\
    \u30EB(\u5DEE\u5206)\u7BA1\u7406\n    // \u7D04\u675F: merge(a,b,w) \u306F pot[b]\
    \ - pot[a] = w \u3092\u8FFD\u52A0\u3059\u308B\n    //      diff(a,b)    \u306F\
    \ pot[b] - pot[a] \u3092\u8FD4\u3059\uFF08\u540C\u4E00\u6210\u5206\u306E\u3068\
    \u304D\u306E\u307F\u547C\u3076\uFF09\n    template <class T>\n    struct potential_dsu\
    \ {\n        int n;\n        std::vector<int> parent_or_size; // root: -size,\
    \ else: parent\n        std::vector<T> diff_weight;      // diff_weight[v] = pot[v]\
    \ - pot[parent[v]] (root\u306F0)\n    \n        potential_dsu() : n(0) {}\n  \
    \      explicit potential_dsu(int n_) { init(n_); }\n    \n        void init(int\
    \ n_) {\n            n = n_;\n            parent_or_size.assign(n, -1);\n    \
    \        diff_weight.assign(n, T{}); // 0\n        }\n    \n        // leader\
    \ \u3092\u6C42\u3081\u3064\u3064\u3001diff_weight \u3092 root \u57FA\u6E96\u306B\
    \u7573\u307F\u8FBC\u3080\n        int leader(int a) {\n            if (parent_or_size[a]\
    \ < 0) return a;\n            int p = parent_or_size[a];\n            int r =\
    \ leader(p);\n            diff_weight[a] += diff_weight[p];\n            parent_or_size[a]\
    \ = r;\n            return r;\n        }\n    \n        bool same(int a, int b)\
    \ { return leader(a) == leader(b); }\n    \n        int size(int a) { return -parent_or_size[leader(a)];\
    \ }\n    \n        // pot[a] - pot[leader(a)]\n        T potential(int a) {\n\
    \            leader(a);\n            return diff_weight[a];\n        }\n    \n\
    \        // pot[b] - pot[a]\n        T diff(int a, int b) {\n            // \u547C\
    \u3073\u51FA\u3057\u5074\u3067 same(a,b) \u3092\u4FDD\u8A3C\uFF08ACL dsu \u3068\
    \u540C\u69D8\u306B\u672A\u5B9A\u7FA9\u6271\u3044\uFF09\n            return potential(b)\
    \ - potential(a);\n        }\n    \n        // pot[b] - pot[a] = w \u3092\u8FFD\
    \u52A0\u3057\u3066\u30DE\u30FC\u30B8\uFF08ACL dsu \u3068\u540C\u3058\u304F leader\
    \ \u3092\u8FD4\u3059\uFF09\n        int merge(int a, int b, T w) {\n         \
    \   w += potential(a);\n            w -= potential(b);\n            int x = leader(a),\
    \ y = leader(b);\n            if (x == y) return x;\n    \n            // union\
    \ by size (ACL dsu \u98A8)\n            if (-parent_or_size[x] < -parent_or_size[y])\
    \ {\n                std::swap(x, y);\n                w = -w;\n            }\n\
    \    \n            parent_or_size[x] += parent_or_size[y];\n            parent_or_size[y]\
    \ = x;\n            diff_weight[y] = w; // pot[y] - pot[x] = w\n            return\
    \ x;\n        }\n    \n        std::vector<std::vector<int>> groups() {\n    \
    \        std::vector<int> leader_buf(n), group_size(n);\n            for (int\
    \ i = 0; i < n; i++) {\n                leader_buf[i] = leader(i);\n         \
    \       group_size[leader_buf[i]]++;\n            }\n            std::vector<std::vector<int>>\
    \ result(n);\n            for (int i = 0; i < n; i++) result[i].reserve(group_size[i]);\n\
    \            for (int i = 0; i < n; i++) result[leader_buf[i]].push_back(i);\n\
    \            result.erase(std::remove_if(result.begin(), result.end(),\n     \
    \                              [](const auto& v) { return v.empty(); }),\n   \
    \                      result.end());\n            return result;\n        }\n\
    \    };\n}\n#line 2 \"math/factor.hpp\"\n\n#line 6 \"math/factor.hpp\"\n\nnamespace\
    \ yesantikiss {\n    // \u6700\u5C0F\u7D20\u56E0\u6570\u30C6\u30FC\u30D6\u30EB\
    \ (Least Prime Factor / LPF)\n    // 1..N \u3092 O(N) \u3067\u69CB\u7BC9\u3057\
    \u3066\u3001\u5404 x \u3092 O(\u7D20\u56E0\u6570\u306E\u500B\u6570) \u3067\u5206\
    \u89E3\u3067\u304D\u308B\n    struct Factor {\n        int N = 0;\n        std::vector<int>\
    \ lpf;     // lpf[x] = x \u306E\u6700\u5C0F\u7D20\u56E0\u6570 (x>=2), lpf[1]=1\n\
    \        std::vector<int> primes;  // \u7D20\u6570\u5217\uFF08\u304A\u307E\u3051\
    \uFF09\n    \n        Factor() {}\n        explicit Factor(int n) { build(n);\
    \ }\n    \n        void build(int n) {\n            assert(n >= 0);\n        \
    \    N = n;\n            lpf.assign(N + 1, 0);\n            primes.clear();\n\
    \            if (N >= 1) lpf[1] = 1;\n    \n            for (int i = 2; i <= N;\
    \ i++) {\n                if (lpf[i] == 0) {\n                    lpf[i] = i;\n\
    \                    primes.emplace_back(i);\n                }\n            \
    \    for (int p : primes) {\n                    long long v = 1LL * p * i;\n\
    \                    if (v > N) break;\n                    lpf[(int)v] = p;\n\
    \                    if (p == lpf[i]) break;\n                }\n            }\n\
    \        }\n    \n        // x \u3092\u7D20\u56E0\u6570\u5206\u89E3\u3057\u3066\
    \ (prime, exponent) \u3092\u8FD4\u3059\n        // \u4E8B\u524D\u306B build(maxA)\
    \ \u304C\u5FC5\u8981\u3002x==1 \u306F\u7A7A\u3092\u8FD4\u3059\u3002\n        std::vector<std::pair<int,int>>\
    \ factorize(int x) const {\n            assert(1 <= x && x <= N);\n          \
    \  std::vector<std::pair<int,int>> res;\n            while (x > 1) {\n       \
    \         int p = lpf[x];\n                int c = 0;\n                while (x\
    \ % p == 0) { x /= p; c++; }\n                res.push_back({p, c});\n       \
    \     }\n            return res;\n        }\n    \n        // (\u7D20\u56E0\u6570\
    \u3092\u5217\u6319\u3057\u305F\u3044\u3060\u3051) p,p,p,... \u306E\u5F62\u3067\
    \u8FD4\u3059\n        std::vector<int> factor_list(int x) const {\n          \
    \  assert(1 <= x && x <= N);\n            std::vector<int> res;\n            while\
    \ (x > 1) {\n                int p = lpf[x];\n                res.push_back(p);\n\
    \                x /= p;\n            }\n            return res;\n        }\n\
    \    \n        bool is_prime(int x) const {\n            assert(1 <= x && x <=\
    \ N);\n            return x >= 2 && lpf[x] == x;\n        }\n    };\n}\n#line\
    \ 2 \"string/aho_corasick.hpp\"\n\n#include <array>\n#line 5 \"string/aho_corasick.hpp\"\
    \n#include <queue>\n#line 8 \"string/aho_corasick.hpp\"\n\nnamespace yesantikiss\
    \ {\n    template<int SIGMA = 26, char BASE = 'a'>\n    struct AhoCorasick {\n\
    \        struct Node {\n            std::array<int, SIGMA> nxt;\n            int\
    \ link = 0;\n            int parent = -1;\n            int pch = -1;\n    \n \
    \           Node(int parent = -1, int pch = -1)\n                : parent(parent),\
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
    \        }\n    };\n}\n#line 2 \"string/rolling_hash.hpp\"\n\n#line 5 \"string/rolling_hash.hpp\"\
    \n#include <random>\n#line 8 \"string/rolling_hash.hpp\"\n\nnamespace yesantikiss\
    \ {\n    struct RollingHash {\n        using ull = unsigned long long;\n     \
    \   static constexpr ull MOD = (1ULL << 61) - 1;\n    \n        // \u5171\u6709\
    \u8CC7\u6E90\uFF08\u5168\u30A4\u30F3\u30B9\u30BF\u30F3\u30B9\u3067\u5171\u901A\
    \uFF09\n        inline static ull base = 0;\n        inline static std::vector<ull>\
    \ pow_base;\n    \n        std::vector<ull> hash;  // hash[i] = S[0..i) \u306E\
    \u30CF\u30C3\u30B7\u30E5\n        int n = 0;\n    \n        // 2^61-1 \u7528\u306E\
    \u6F14\u7B97\n        static inline ull add(ull a, ull b) {\n            ull c\
    \ = a + b;\n            if (c >= MOD) c -= MOD;\n            return c;\n     \
    \   }\n        static inline ull mul(ull a, ull b) {\n            unsigned __int128\
    \ t = (unsigned __int128)a * b;\n            ull res = (ull)(t >> 61) + ((ull)t\
    \ & MOD);\n            if (res >= MOD) res -= MOD;\n            return res;\n\
    \        }\n    \n        static void init_base() {\n            if (base != 0)\
    \ return;\n            std::mt19937_64 rng(std::random_device{}());\n        \
    \    std::uniform_int_distribution<ull> dist(1ULL, MOD - 1);\n            base\
    \ = dist(rng);\n            pow_base = {1};  // pow_base[0] = 1\n        }\n \
    \   \n        static void ensure_pow(int len) {\n            if ((int)pow_base.size()\
    \ >= len + 1) return;\n            int cur = (int)pow_base.size();\n         \
    \   pow_base.resize(len + 1);\n            for (int i = cur; i <= len; ++i) {\n\
    \                pow_base[i] = mul(pow_base[i - 1], base);\n            }\n  \
    \      }\n    \n        // hash(A + B) \u3092 hash(A), hash(B), |B| \u304B\u3089\
    \u6C42\u3081\u308B\n        static ull concat(ull h1, ull h2, int len2) {\n  \
    \          assert(len2 >= 0);\n            init_base();\n            ensure_pow(len2);\n\
    \            return add(mul(h1, pow_base[len2]), h2);\n        }\n\n        //\
    \ \u9577\u3055\u4ED8\u304D\u306E\u30CF\u30C3\u30B7\u30E5\u5024\u3002+ \u3067\u6587\
    \u5B57\u5217\u306E\u9023\u7D50\u306B\u5BFE\u5FDC\u3059\u308B\u30CF\u30C3\u30B7\
    \u30E5\u304C\u5F97\u3089\u308C\u308B\n        // \u65E2\u5B9A\u5024\u306F\u7A7A\
    \u6587\u5B57\u5217\uFF08+ \u306E\u5358\u4F4D\u5143\uFF09\n        struct Hash\
    \ {\n            ull val = 0;\n            int len = 0;\n\n            Hash()\
    \ = default;\n            Hash(ull val, int len) : val(val), len(len) {}\n   \
    \         // 1 \u6587\u5B57 / \u6587\u5B57\u5217\u5168\u4F53\u306E\u30CF\u30C3\
    \u30B7\u30E5\uFF08prefix hash \u3092\u6301\u305F\u305A\u306B\u6C42\u3081\u308B\
    \uFF09\n            explicit Hash(char c) : val((ull)(unsigned char)c + 1), len(1)\
    \ { init_base(); }\n            explicit Hash(const std::string &s) : len((int)s.size())\
    \ {\n                init_base();\n                for (char c : s) val = add(mul(val,\
    \ base), (ull)(unsigned char)c + 1);\n            }\n\n            friend Hash\
    \ operator+(const Hash &a, const Hash &b) {\n                return {concat(a.val,\
    \ b.val, b.len), a.len + b.len};\n            }\n            Hash &operator+=(const\
    \ Hash &o) { return *this = *this + o; }\n            friend bool operator==(const\
    \ Hash &a, const Hash &b) {\n                return a.val == b.val && a.len ==\
    \ b.len;\n            }\n            friend bool operator!=(const Hash &a, const\
    \ Hash &b) { return !(a == b); }\n        };\n\n        RollingHash() : n(0) {}\n\
    \    \n        RollingHash(const std::string &s) {\n            build(s);\n  \
    \      }\n    \n        void build(const std::string &s) {\n            init_base();\n\
    \            n = (int)s.size();\n            ensure_pow(n);\n            hash.assign(n\
    \ + 1, 0);\n            for (int i = 0; i < n; ++i) {\n                hash[i\
    \ + 1] = add(mul(hash[i], base), (ull)(unsigned char)s[i] + 1);\n            }\n\
    \        }\n    \n        // S[l..r) \u306E\u30CF\u30C3\u30B7\u30E5\u3092\u53D6\
    \u5F97\n        ull get(int l, int r) const {\n            assert(0 <= l && l\
    \ <= r && r <= n);\n            ull res = hash[r] + MOD - mul(hash[l], pow_base[r\
    \ - l]);\n            if (res >= MOD) res -= MOD;\n            return res;\n \
    \       }\n    \n        // S[l..r) \u306E\u9577\u3055\u4ED8\u304D\u30CF\u30C3\
    \u30B7\u30E5\u3092\u53D6\u5F97\uFF08+ \u3067\u9023\u7D50\u3067\u304D\u308B\uFF09\
    \n        Hash slice(int l, int r) const {\n            return {get(l, r), r -\
    \ l};\n        }\n\n        // \u540C\u3058\u6587\u5B57\u5217\u306E\u4E2D\u3067\
    \u90E8\u5206\u6587\u5B57\u5217\u304C\u7B49\u3057\u3044\u304B\n        bool equals(int\
    \ l1, int r1, int l2, int r2) const {\n            if (r1 - l1 != r2 - l2) return\
    \ false;\n            return get(l1, r1) == get(l2, r2);\n        }\n\n      \
    \  // a \u306E [l1, r1) \u3068 b \u306E [l2, r2) \u306E\u6700\u9577\u5171\u901A\
    \u63A5\u982D\u8F9E\u306E\u9577\u3055  O(log N)\n        static int lcp(const RollingHash\
    \ &a, int l1, int r1, const RollingHash &b, int l2, int r2) {\n            assert(0\
    \ <= l1 && l1 <= r1 && r1 <= a.n);\n            assert(0 <= l2 && l2 <= r2 &&\
    \ r2 <= b.n);\n            // get(l1, l1 + len) == get(l2, l2 + len) \u3092\u4E57\
    \u7B97 1 \u56DE\u3067\u5224\u5B9A\u3059\u308B\n            const ull diff = add(a.hash[l1],\
    \ MOD - b.hash[l2]);\n            auto same = [&](int len) {\n               \
    \ return add(a.hash[l1 + len], MOD - b.hash[l2 + len]) == mul(diff, pow_base[len]);\n\
    \            };\n            const int limit = std::min(r1 - l1, r2 - l2);\n \
    \           // \u7B54\u3048\u304C\u77ED\u3044\u5834\u5408\u306B\u901F\u3044\u3088\
    \u3046\u3001\u9577\u3055 32 \u307E\u3067\u306F\u500D\u3005\u3067\u78BA\u304B\u3081\
    \u3066\u304B\u3089\u4E8C\u5206\u63A2\u7D22\u3059\u308B\n            int ok = 0,\
    \ ng = 1;\n            while (true) {\n                if (ng > limit || !same(ng))\
    \ break;\n                ok = ng;\n                if (ng >= 32) {\n        \
    \            ng = limit + 1;\n                    break;\n                }\n\
    \                ng *= 2;\n            }\n            if (ng > limit + 1) ng =\
    \ limit + 1;\n            while (ng - ok > 1) {\n                int mid = ok\
    \ + (ng - ok) / 2;\n                if (same(mid)) ok = mid;\n               \
    \ else ng = mid;\n            }\n            return ok;\n        }\n        int\
    \ lcp(int l1, int r1, int l2, int r2) const {\n            return lcp(*this, l1,\
    \ r1, *this, l2, r2);\n        }\n\n        // a \u306E [l1, r1) \u3068 b \u306E\
    \ [l2, r2) \u3092\u8F9E\u66F8\u9806\u3067\u6BD4\u8F03  O(log N)\n        // \u8CA0\
    : a \u5074\u304C\u5C0F\u3055\u3044\u30010: \u7B49\u3057\u3044\u3001\u6B63: a \u5074\
    \u304C\u5927\u304D\u3044\uFF08std::string::compare \u3068\u540C\u3058\u9806\u5E8F\
    \uFF09\n        static int compare(const RollingHash &a, int l1, int r1, const\
    \ RollingHash &b, int l2, int r2) {\n            int len1 = r1 - l1, len2 = r2\
    \ - l2;\n            int k = lcp(a, l1, r1, b, l2, r2);\n            if (k ==\
    \ len1 || k == len2) return (len1 > len2) - (len1 < len2);\n            // \u9577\
    \u3055 1 \u306E\u30CF\u30C3\u30B7\u30E5\u306F \u6587\u5B57 + 1 \u305D\u306E\u3082\
    \u306E\n            ull c1 = a.get(l1 + k, l1 + k + 1), c2 = b.get(l2 + k, l2\
    \ + k + 1);\n            return (c1 > c2) - (c1 < c2);\n        }\n        int\
    \ compare(int l1, int r1, int l2, int r2) const {\n            return compare(*this,\
    \ l1, r1, *this, l2, r2);\n        }\n    };\n    \n}\n#line 2 \"tree/heavy_light_decomposition.hpp\"\
    \n\n#line 7 \"tree/heavy_light_decomposition.hpp\"\n\nnamespace yesantikiss {\n\
    \    struct HeavyLightDecomposition {\n        int n = 0;\n        int root =\
    \ -1;\n        std::vector<int> parent;\n        std::vector<int> depth;\n   \
    \     std::vector<int> size;\n        std::vector<int> in;\n        std::vector<int>\
    \ out;\n        std::vector<int> head;\n        std::vector<int> heavy;\n    \
    \    std::vector<int> vertex;\n\n        HeavyLightDecomposition() = default;\n\
    \n        explicit HeavyLightDecomposition(\n            const std::vector<std::vector<int>>&\
    \ graph, int root_ = 0) {\n            build(graph, root_);\n        }\n\n   \
    \     void build(const std::vector<std::vector<int>>& graph, int root_ = 0) {\n\
    \            init(static_cast<int>(graph.size()));\n            if (n == 0) return;\n\
    \            root = root_;\n\n            std::vector<int> order{root};\n    \
    \        parent[root] = root;\n            for (int i = 0; i < static_cast<int>(order.size());\
    \ ++i) {\n                int v = order[i];\n                for (int to : graph[v])\
    \ {\n                    if (parent[to] != -1) continue;\n                   \
    \ parent[to] = v;\n                    depth[to] = depth[v] + 1;\n           \
    \         order.push_back(to);\n                }\n            }\n\n         \
    \   for (int i = static_cast<int>(order.size()) - 1; i >= 0; --i) {\n        \
    \        int v = order[i];\n                int largest_size = 0;\n          \
    \      for (int to : graph[v]) {\n                    if (parent[to] != v) continue;\n\
    \                    size[v] += size[to];\n                    if (size[to] >\
    \ largest_size) {\n                        largest_size = size[to];\n        \
    \                heavy[v] = to;\n                    }\n                }\n  \
    \          }\n\n            int timer = 0;\n            std::vector<std::pair<int,\
    \ int>> pending{{root, root}};\n            while (!pending.empty()) {\n     \
    \           auto [v, chain_head] = pending.back();\n                pending.pop_back();\n\
    \n                for (; v != -1; v = heavy[v]) {\n                    head[v]\
    \ = chain_head;\n                    in[v] = timer;\n                    vertex[timer++]\
    \ = v;\n\n                    for (int to : graph[v]) {\n                    \
    \    if (parent[to] == v && to != heavy[v]) {\n                            pending.emplace_back(to,\
    \ to);\n                        }\n                    }\n                }\n\
    \            }\n\n            for (int v = 0; v < n; ++v) {\n                if\
    \ (in[v] != -1) out[v] = in[v] + size[v];\n            }\n        }\n\n      \
    \  int edge_vertex(int u, int v) const {\n            return depth[u] > depth[v]\
    \ ? u : v;\n        }\n\n        int lca(int u, int v) const {\n            while\
    \ (head[u] != head[v]) {\n                if (depth[head[u]] > depth[head[v]])\
    \ {\n                    u = parent[head[u]];\n                } else {\n    \
    \                v = parent[head[v]];\n                }\n            }\n    \
    \        return depth[u] < depth[v] ? u : v;\n        }\n\n        int dist(int\
    \ u, int v) const {\n            int ancestor = lca(u, v);\n            return\
    \ depth[u] + depth[v] - 2 * depth[ancestor];\n        }\n\n        bool is_ancestor(int\
    \ ancestor, int v) const {\n            return in[ancestor] <= in[v] && out[v]\
    \ <= out[ancestor];\n        }\n\n        std::pair<int, int> subtree_vertex(int\
    \ v) const {\n            return {in[v], out[v]};\n        }\n\n        // \u5404\
    \u8FBA\u3092\u6DF1\u3044\u65B9\u306E\u9802\u70B9\u306B\u5BFE\u5FDC\u3055\u305B\
    \u305F\u3068\u304D\u306E\u90E8\u5206\u6728\u5185\u306E\u8FBA\u3002\n        std::pair<int,\
    \ int> subtree_edge(int v) const {\n            return {in[v] + 1, out[v]};\n\
    \        }\n\n        // u -> v \u306E\u9806\u306B\u3001\u30D1\u30B9\u3092\u534A\
    \u958B\u533A\u9593\u3078\u5206\u89E3\u3059\u308B\u3002\n        // reverse=true\
    \ \u306E\u533A\u9593\u306F r-1, ..., l \u306E\u9806\u306B\u8AAD\u3080\u3002\n\
    \        template <class F>\n        void path_query(int u, int v, bool edge,\
    \ F&& callback) const {\n            std::vector<std::tuple<int, int, bool>> right;\n\
    \n            while (head[u] != head[v]) {\n                if (depth[head[u]]\
    \ > depth[head[v]]) {\n                    callback(in[head[u]], in[u] + 1, true);\n\
    \                    u = parent[head[u]];\n                } else {\n        \
    \            right.emplace_back(in[head[v]], in[v] + 1, false);\n            \
    \        v = parent[head[v]];\n                }\n            }\n\n          \
    \  if (depth[u] > depth[v]) {\n                int left = in[v] + (edge ? 1 :\
    \ 0);\n                int right_end = in[u] + 1;\n                if (left <\
    \ right_end) callback(left, right_end, true);\n            } else {\n        \
    \        int left = in[u] + (edge ? 1 : 0);\n                int right_end = in[v]\
    \ + 1;\n                if (left < right_end) callback(left, right_end, false);\n\
    \            }\n\n            std::reverse(right.begin(), right.end());\n    \
    \        for (auto [left, right_end, reverse] : right) {\n                callback(left,\
    \ right_end, reverse);\n            }\n        }\n\n        template <class S,\
    \ class Op, class Get>\n        S path_fold(int u, int v, bool edge, Op op, S\
    \ identity,\n                    Get get) const {\n            S result = identity;\n\
    \            path_query(u, v, edge,\n                       [&](int left, int\
    \ right, bool reverse) {\n                           result = op(result, get(left,\
    \ right, reverse));\n                       });\n            return result;\n\
    \        }\n\n    private:\n        void init(int size_) {\n            n = size_;\n\
    \            root = -1;\n            parent.assign(n, -1);\n            depth.assign(n,\
    \ 0);\n            size.assign(n, 1);\n            in.assign(n, -1);\n       \
    \     out.assign(n, -1);\n            head.assign(n, -1);\n            heavy.assign(n,\
    \ -1);\n            vertex.assign(n, -1);\n        }\n    };\n}\n#line 2 \"tree/lca_binary_lifting.hpp\"\
    \n\n#line 5 \"tree/lca_binary_lifting.hpp\"\n\nnamespace yesantikiss {\n    struct\
    \ BinaryLiftingLCA {\n        int n = 0;\n        int log = 1;\n        std::vector<int>\
    \ depth;\n        std::vector<int> parent;\n        std::vector<int> component;\n\
    \n        BinaryLiftingLCA() = default;\n\n        explicit BinaryLiftingLCA(\n\
    \            const std::vector<std::vector<int>>& graph, int root = 0) {\n   \
    \         build(graph, root);\n        }\n\n        void build(const std::vector<std::vector<int>>&\
    \ graph, int root = 0) {\n            init(static_cast<int>(graph.size()));\n\
    \            if (n == 0) return;\n\n            build_component(graph, root, 0);\n\
    \            build_table();\n        }\n\n        void build_forest(const std::vector<std::vector<int>>&\
    \ graph) {\n            init(static_cast<int>(graph.size()));\n\n            int\
    \ component_id = 0;\n            for (int root = 0; root < n; ++root) {\n    \
    \            if (parent[root] == -1) {\n                    build_component(graph,\
    \ root, component_id++);\n                }\n            }\n            build_table();\n\
    \        }\n\n        int kth_ancestor(int v, int k) const {\n            if (!contains(v)\
    \ || k < 0 || parent[v] == -1) return -1;\n            k = std::min(k, depth[v]);\n\
    \            for (int bit = 0; bit < log; ++bit) {\n                if ((k >>\
    \ bit) & 1) v = up_at(bit, v);\n            }\n            return v;\n       \
    \ }\n\n        int lca(int a, int b) const {\n            if (!same_component(a,\
    \ b)) return -1;\n            if (depth[a] < depth[b]) std::swap(a, b);\n\n  \
    \          a = kth_ancestor(a, depth[a] - depth[b]);\n            if (a == b)\
    \ return a;\n\n            for (int bit = log - 1; bit >= 0; --bit) {\n      \
    \          if (up_at(bit, a) != up_at(bit, b)) {\n                    a = up_at(bit,\
    \ a);\n                    b = up_at(bit, b);\n                }\n           \
    \ }\n            return parent[a];\n        }\n\n        int dist(int a, int b)\
    \ const {\n            int ancestor = lca(a, b);\n            if (ancestor ==\
    \ -1) return -1;\n            return depth[a] + depth[b] - 2 * depth[ancestor];\n\
    \        }\n\n        bool is_ancestor(int ancestor, int v) const {\n        \
    \    return same_component(ancestor, v) && lca(ancestor, v) == ancestor;\n   \
    \     }\n\n        // a -> b \u30D1\u30B9\u4E0A\u3067 a \u3092 0 \u756A\u76EE\u3068\
    \u3059\u308B k \u756A\u76EE\u306E\u9802\u70B9\u3092\u8FD4\u3059\u3002\n      \
    \  int jump(int a, int b, int k) const {\n            int ancestor = lca(a, b);\n\
    \            if (ancestor == -1 || k < 0) return -1;\n\n            int up_length\
    \ = depth[a] - depth[ancestor];\n            int down_length = depth[b] - depth[ancestor];\n\
    \            if (k > up_length + down_length) return -1;\n            if (k <=\
    \ up_length) return kth_ancestor(a, k);\n            return kth_ancestor(b, up_length\
    \ + down_length - k);\n        }\n\n    private:\n        std::vector<int> up;\n\
    \n        void init(int size) {\n            n = size;\n            log = 1;\n\
    \            while ((1LL << log) <= std::max(1, n)) ++log;\n            depth.assign(n,\
    \ 0);\n            parent.assign(n, -1);\n            component.assign(n, -1);\n\
    \            up.assign(log * n, 0);\n        }\n\n        bool contains(int v)\
    \ const { return 0 <= v && v < n; }\n\n        bool same_component(int a, int\
    \ b) const {\n            return contains(a) && contains(b) && component[a] !=\
    \ -1 &&\n                   component[a] == component[b];\n        }\n\n     \
    \   int& up_at(int bit, int v) { return up[bit * n + v]; }\n        int up_at(int\
    \ bit, int v) const { return up[bit * n + v]; }\n\n        void build_component(const\
    \ std::vector<std::vector<int>>& graph,\n                             int root,\
    \ int component_id) {\n            parent[root] = root;\n            depth[root]\
    \ = 0;\n            component[root] = component_id;\n\n            std::vector<int>\
    \ order{root};\n            for (int i = 0; i < static_cast<int>(order.size());\
    \ ++i) {\n                int v = order[i];\n                for (int to : graph[v])\
    \ {\n                    if (parent[to] != -1) continue;\n                   \
    \ parent[to] = v;\n                    depth[to] = depth[v] + 1;\n           \
    \         component[to] = component_id;\n                    order.push_back(to);\n\
    \                }\n            }\n        }\n\n        void build_table() {\n\
    \            for (int v = 0; v < n; ++v) {\n                if (parent[v] != -1)\
    \ up_at(0, v) = parent[v];\n            }\n            for (int bit = 1; bit <\
    \ log; ++bit) {\n                for (int v = 0; v < n; ++v) {\n             \
    \       if (parent[v] != -1) {\n                        up_at(bit, v) = up_at(bit\
    \ - 1, up_at(bit - 1, v));\n                    }\n                }\n       \
    \     }\n        }\n    };\n}\n#line 2 \"tree/lca_euler_tour.hpp\"\n\n#line 5\
    \ \"tree/lca_euler_tour.hpp\"\n\nnamespace yesantikiss {\n    struct EulerTourLCA\
    \ {\n        int n = 0;\n        std::vector<int> depth;\n        std::vector<int>\
    \ parent;\n        std::vector<int> component;\n        std::vector<int> tin;\n\
    \        std::vector<int> tout;\n\n        EulerTourLCA() = default;\n\n     \
    \   explicit EulerTourLCA(const std::vector<std::vector<int>>& graph,\n      \
    \                        int root = 0) {\n            build(graph, root);\n  \
    \      }\n\n        void build(const std::vector<std::vector<int>>& graph, int\
    \ root = 0) {\n            init(static_cast<int>(graph.size()));\n           \
    \ if (n == 0) return;\n\n            euler.reserve(2 * n - 1);\n            build_component(graph,\
    \ root, 0);\n            build_sparse_table();\n        }\n\n        void build_forest(const\
    \ std::vector<std::vector<int>>& graph) {\n            init(static_cast<int>(graph.size()));\n\
    \            euler.reserve(n == 0 ? 0 : 2 * n - 1);\n\n            int component_id\
    \ = 0;\n            for (int root = 0; root < n; ++root) {\n                if\
    \ (parent[root] == -1) {\n                    build_component(graph, root, component_id++);\n\
    \                }\n            }\n            build_sparse_table();\n       \
    \ }\n\n        int lca(int a, int b) const {\n            if (!same_component(a,\
    \ b)) return -1;\n            int left = first[a];\n            int right = first[b];\n\
    \            if (left > right) std::swap(left, right);\n\n            int length\
    \ = right - left + 1;\n            int level = lg[length];\n            return\
    \ better(st_at(level, left),\n                          st_at(level, right - (1\
    \ << level) + 1));\n        }\n\n        int dist(int a, int b) const {\n    \
    \        int ancestor = lca(a, b);\n            if (ancestor == -1) return -1;\n\
    \            return depth[a] + depth[b] - 2 * depth[ancestor];\n        }\n\n\
    \        bool is_ancestor(int ancestor, int v) const {\n            return same_component(ancestor,\
    \ v) && tin[ancestor] <= tin[v] &&\n                   tout[v] <= tout[ancestor];\n\
    \        }\n\n    private:\n        int timer = 0;\n        int euler_size = 0;\n\
    \        int levels = 0;\n        std::vector<int> first;\n        std::vector<int>\
    \ euler;\n        std::vector<int> lg;\n        std::vector<int> sparse_table;\n\
    \n        struct Frame {\n            int v;\n            int next_edge;\n   \
    \     };\n\n        void init(int size) {\n            n = size;\n           \
    \ timer = 0;\n            euler_size = 0;\n            levels = 0;\n         \
    \   depth.assign(n, 0);\n            parent.assign(n, -1);\n            component.assign(n,\
    \ -1);\n            tin.assign(n, -1);\n            tout.assign(n, -1);\n    \
    \        first.assign(n, -1);\n            euler.clear();\n            lg.clear();\n\
    \            sparse_table.clear();\n        }\n\n        bool contains(int v)\
    \ const { return 0 <= v && v < n; }\n\n        bool same_component(int a, int\
    \ b) const {\n            return contains(a) && contains(b) && component[a] !=\
    \ -1 &&\n                   component[a] == component[b];\n        }\n\n     \
    \   int& st_at(int level, int index) {\n            return sparse_table[level\
    \ * euler_size + index];\n        }\n\n        int st_at(int level, int index)\
    \ const {\n            return sparse_table[level * euler_size + index];\n    \
    \    }\n\n        int better(int a, int b) const {\n            return depth[a]\
    \ <= depth[b] ? a : b;\n        }\n\n        void enter(int v, int p, int component_id)\
    \ {\n            parent[v] = p;\n            component[v] = component_id;\n  \
    \          tin[v] = timer++;\n            first[v] = static_cast<int>(euler.size());\n\
    \            euler.push_back(v);\n        }\n\n        void build_component(const\
    \ std::vector<std::vector<int>>& graph,\n                             int root,\
    \ int component_id) {\n            depth[root] = 0;\n            enter(root, root,\
    \ component_id);\n            std::vector<Frame> stack{{root, 0}};\n\n       \
    \     while (!stack.empty()) {\n                Frame& frame = stack.back();\n\
    \                int v = frame.v;\n                if (frame.next_edge == static_cast<int>(graph[v].size()))\
    \ {\n                    tout[v] = timer;\n                    stack.pop_back();\n\
    \                    if (!stack.empty()) euler.push_back(stack.back().v);\n  \
    \                  continue;\n                }\n\n                int to = graph[v][frame.next_edge++];\n\
    \                if (parent[to] != -1) continue;\n                depth[to] =\
    \ depth[v] + 1;\n                enter(to, v, component_id);\n               \
    \ stack.push_back({to, 0});\n            }\n        }\n\n        void build_sparse_table()\
    \ {\n            euler_size = static_cast<int>(euler.size());\n            if\
    \ (euler_size == 0) return;\n\n            lg.assign(euler_size + 1, 0);\n   \
    \         for (int i = 2; i <= euler_size; ++i) lg[i] = lg[i / 2] + 1;\n\n   \
    \         levels = lg[euler_size] + 1;\n            sparse_table.assign(levels\
    \ * euler_size, 0);\n            for (int i = 0; i < euler_size; ++i) st_at(0,\
    \ i) = euler[i];\n\n            for (int level = 1; level < levels; ++level) {\n\
    \                int length = 1 << level;\n                int half = length /\
    \ 2;\n                for (int i = 0; i + length <= euler_size; ++i) {\n     \
    \               st_at(level, i) =\n                        better(st_at(level\
    \ - 1, i),\n                               st_at(level - 1, i + half));\n    \
    \            }\n            }\n        }\n    };\n}\n#line 2 \"utils/fraction.hpp\"\
    \n\n#line 4 \"utils/fraction.hpp\"\n#include <ios>\n#include <istream>\n#line\
    \ 8 \"utils/fraction.hpp\"\n#include <stdexcept>\n#line 11 \"utils/fraction.hpp\"\
    \n\nnamespace yesantikiss {\n    namespace fraction_detail {\n        using i128\
    \ = __int128;\n        using u128 = unsigned __int128;\n\n        template<class\
    \ T>\n        inline constexpr bool is_supported_integer_v =\n            (std::is_integral_v<T>\
    \ && std::is_signed_v<T> &&\n             !std::is_same_v<T, bool>) ||\n     \
    \       std::is_same_v<T, i128>;\n\n        struct u256 {\n            u128 hi\
    \ = 0;\n            u128 lo = 0;\n        };\n\n        inline bool is_zero(const\
    \ u256& x) {\n            return x.hi == 0 && x.lo == 0;\n        }\n\n      \
    \  inline int compare(const u256& a, const u256& b) {\n            if (a.hi !=\
    \ b.hi) return a.hi < b.hi ? -1 : 1;\n            if (a.lo != b.lo) return a.lo\
    \ < b.lo ? -1 : 1;\n            return 0;\n        }\n\n        inline u256 add(const\
    \ u256& a, const u256& b) {\n            u256 res;\n            res.lo = a.lo\
    \ + b.lo;\n            res.hi = a.hi + b.hi + (res.lo < a.lo);\n            return\
    \ res;\n        }\n\n        // a >= b \u3092\u4EEE\u5B9A\u3059\u308B\u3002\n\
    \        inline u256 subtract(const u256& a, const u256& b) {\n            u256\
    \ res;\n            res.lo = a.lo - b.lo;\n            res.hi = a.hi - b.hi -\
    \ (a.lo < b.lo);\n            return res;\n        }\n\n        inline u256 multiply(u128\
    \ a, u128 b) {\n            constexpr u128 mask64 = (u128(1) << 64) - 1;\n\n \
    \           u128 a0 = a & mask64;\n            u128 a1 = a >> 64;\n          \
    \  u128 b0 = b & mask64;\n            u128 b1 = b >> 64;\n\n            u128 p00\
    \ = a0 * b0;\n            u128 p01 = a0 * b1;\n            u128 p10 = a1 * b0;\n\
    \            u128 p11 = a1 * b1;\n\n            u128 lo = p00;\n            u128\
    \ x = p01 << 64;\n            u128 next = lo + x;\n            u128 carry = next\
    \ < lo;\n            lo = next;\n\n            x = p10 << 64;\n            next\
    \ = lo + x;\n            carry += next < lo;\n            lo = next;\n\n     \
    \       u128 hi = p11 + (p01 >> 64) + (p10 >> 64) + carry;\n            return\
    \ {hi, lo};\n        }\n\n        inline u256 from_u128(u128 x) {\n          \
    \  return {0, x};\n        }\n\n        struct div_result {\n            u256\
    \ quotient;\n            u128 remainder;\n        };\n\n        inline div_result\
    \ divide(const u256& value, u128 divisor) {\n            if (divisor == 0) {\n\
    \                throw std::domain_error(\"fraction: division by zero\");\n  \
    \          }\n            if (value.hi == 0) {\n                return {{0, value.lo\
    \ / divisor}, value.lo % divisor};\n            }\n\n            u256 quotient;\n\
    \            u128 remainder = 0;\n            for (int bit_index = 255; bit_index\
    \ >= 0; --bit_index) {\n                u128 bit;\n                if (bit_index\
    \ >= 128) {\n                    bit = (value.hi >> (bit_index - 128)) & 1;\n\
    \                } else {\n                    bit = (value.lo >> bit_index) &\
    \ 1;\n                }\n\n                bool carry = (remainder >> 127) !=\
    \ 0;\n                remainder = (remainder << 1) | bit;\n                if\
    \ (carry || remainder >= divisor) {\n                    remainder -= divisor;\n\
    \                    if (bit_index >= 128) {\n                        quotient.hi\
    \ |= u128(1) << (bit_index - 128);\n                    } else {\n           \
    \             quotient.lo |= u128(1) << bit_index;\n                    }\n  \
    \              }\n            }\n            return {quotient, remainder};\n \
    \       }\n\n        inline u128 modulo(const u256& value, u128 divisor) {\n \
    \           return divide(value, divisor).remainder;\n        }\n\n        inline\
    \ u256 divide_exact(const u256& value, u128 divisor) {\n            if (divisor\
    \ == 1) return value;\n            div_result result = divide(value, divisor);\n\
    \            if (result.remainder != 0) {\n                throw std::logic_error(\"\
    fraction: internal non-exact division\");\n            }\n            return result.quotient;\n\
    \        }\n\n        inline u128 gcd(u128 a, u128 b) {\n            while (b\
    \ != 0) {\n                u128 r = a % b;\n                a = b;\n         \
    \       b = r;\n            }\n            return a;\n        }\n\n        struct\
    \ signed_u256 {\n            bool negative = false;\n            u256 magnitude;\n\
    \        };\n\n        inline signed_u256 add(const signed_u256& a, const signed_u256&\
    \ b) {\n            if (a.negative == b.negative) {\n                signed_u256\
    \ res{a.negative, add(a.magnitude, b.magnitude)};\n                if (is_zero(res.magnitude))\
    \ res.negative = false;\n                return res;\n            }\n\n      \
    \      int cmp = compare(a.magnitude, b.magnitude);\n            if (cmp == 0)\
    \ return {};\n            if (cmp > 0) {\n                return {a.negative,\
    \ subtract(a.magnitude, b.magnitude)};\n            }\n            return {b.negative,\
    \ subtract(b.magnitude, a.magnitude)};\n        }\n    }\n\n    // T \u306F\u7B26\
    \u53F7\u4ED8\u304D\u6574\u6570\u578B\uFF08\u6700\u5927 __int128\uFF09\u3002\u5E38\
    \u306B\u65E2\u7D04\u304B\u3064 den > 0 \u306B\u4FDD\u3064\u3002\n    // \u6B63\
    \u898F\u5316\u5F8C\u306E\u5024\u304C T \u306B\u53CE\u307E\u3089\u306A\u3044\u6F14\
    \u7B97\u306F std::overflow_error \u3092\u9001\u51FA\u3059\u308B\u3002\n    template<class\
    \ T>\n    struct fraction {\n        static_assert(\n            fraction_detail::is_supported_integer_v<T>,\n\
    \            \"fraction<T>: T must be a signed integral type\");\n        static_assert(\n\
    \            sizeof(T) <= sizeof(fraction_detail::i128),\n            \"fraction<T>:\
    \ integers wider than 128 bits are not supported\");\n\n        using u128 = fraction_detail::u128;\n\
    \        using u256 = fraction_detail::u256;\n        using signed_u256 = fraction_detail::signed_u256;\n\
    \n        T num, den; // den > 0 \u3092\u5E38\u306B\u4FDD\u3064\n\n        fraction()\
    \ : num(0), den(1) {}\n        fraction(T n) : num(n), den(1) {}\n\n        fraction(T\
    \ n, T d) {\n            if (d == 0) {\n                throw std::invalid_argument(\n\
    \                    \"fraction: denominator must not be zero\");\n          \
    \  }\n            bool negative = (n < 0) != (d < 0);\n            assign_normalized(\n\
    \                negative, magnitude(n), magnitude(d));\n        }\n\n    private:\n\
    \        static constexpr u128 max_u128() {\n            return ~u128(0);\n  \
    \      }\n\n        static constexpr u128 max_magnitude() {\n            return\
    \ static_cast<u128>(std::numeric_limits<T>::max());\n        }\n\n        static\
    \ constexpr u128 min_magnitude() {\n            return max_magnitude() + 1;\n\
    \        }\n\n        static u128 magnitude(T x) {\n            u128 value = static_cast<u128>(x);\n\
    \            return x < 0 ? u128(0) - value : value;\n        }\n\n        static\
    \ bool fits(bool negative, u128 value) {\n            return value <= (negative\
    \ ? min_magnitude() : max_magnitude());\n        }\n\n        static T from_magnitude(bool\
    \ negative, u128 value) {\n            if (!fits(negative, value)) {\n       \
    \         throw std::overflow_error(\n                    \"fraction: value does\
    \ not fit the storage type\");\n            }\n            if (!negative) return\
    \ static_cast<T>(value);\n            if (value == min_magnitude()) {\n      \
    \          return std::numeric_limits<T>::min();\n            }\n            return\
    \ -static_cast<T>(value);\n        }\n\n        void assign_reduced(\n       \
    \     bool negative, const u256& numerator, const u256& denominator) {\n     \
    \       if (fraction_detail::is_zero(denominator)) {\n                throw std::invalid_argument(\n\
    \                    \"fraction: denominator must not be zero\");\n          \
    \  }\n            if (fraction_detail::is_zero(numerator)) {\n               \
    \ num = 0;\n                den = 1;\n                return;\n            }\n\
    \            if (numerator.hi != 0 || denominator.hi != 0 ||\n               \
    \ !fits(negative, numerator.lo) ||\n                denominator.lo > max_magnitude())\
    \ {\n                throw std::overflow_error(\n                    \"fraction:\
    \ result does not fit the storage type\");\n            }\n            num = from_magnitude(negative,\
    \ numerator.lo);\n            den = static_cast<T>(denominator.lo);\n        }\n\
    \n        bool try_assign_reduced(\n            bool negative, const u256& numerator,\
    \ const u256& denominator) {\n            if (fraction_detail::is_zero(denominator))\
    \ return false;\n            if (fraction_detail::is_zero(numerator)) {\n    \
    \            num = 0;\n                den = 1;\n                return true;\n\
    \            }\n            if (numerator.hi != 0 || denominator.hi != 0 ||\n\
    \                !fits(negative, numerator.lo) ||\n                denominator.lo\
    \ > max_magnitude()) {\n                return false;\n            }\n       \
    \     num = from_magnitude(negative, numerator.lo);\n            den = static_cast<T>(denominator.lo);\n\
    \            return true;\n        }\n\n        void assign_normalized(bool negative,\
    \ u128 numerator, u128 denominator) {\n            if (numerator == 0) {\n   \
    \             num = 0;\n                den = 1;\n                return;\n  \
    \          }\n            u128 g = fraction_detail::gcd(numerator, denominator);\n\
    \            assign_reduced(\n                negative,\n                fraction_detail::from_u128(numerator\
    \ / g),\n                fraction_detail::from_u128(denominator / g));\n     \
    \   }\n\n        bool try_assign_normalized(\n            bool negative, u128\
    \ numerator, u128 denominator) {\n            if (denominator == 0) return false;\n\
    \            if (numerator == 0) {\n                num = 0;\n               \
    \ den = 1;\n                return true;\n            }\n            u128 g =\
    \ fraction_detail::gcd(numerator, denominator);\n            return try_assign_reduced(\n\
    \                negative,\n                fraction_detail::from_u128(numerator\
    \ / g),\n                fraction_detail::from_u128(denominator / g));\n     \
    \   }\n\n        static signed_u256 signed_product(T value, u128 multiplier) {\n\
    \            u256 product =\n                fraction_detail::multiply(magnitude(value),\
    \ multiplier);\n            return {\n                value < 0 && !fraction_detail::is_zero(product),\n\
    \                product\n            };\n        }\n\n        fraction& add_or_subtract(const\
    \ fraction& other, bool subtract) {\n            u128 b = static_cast<u128>(den);\n\
    \            u128 d = static_cast<u128>(other.den);\n            u128 common =\
    \ fraction_detail::gcd(b, d);\n            u128 b_reduced = b / common;\n    \
    \        u128 d_reduced = d / common;\n\n            signed_u256 left = signed_product(num,\
    \ d_reduced);\n            signed_u256 right = signed_product(other.num, b_reduced);\n\
    \            if (subtract && !fraction_detail::is_zero(right.magnitude)) {\n \
    \               right.negative = !right.negative;\n            }\n           \
    \ signed_u256 numerator = fraction_detail::add(left, right);\n\n            if\
    \ (fraction_detail::is_zero(numerator.magnitude)) {\n                num = 0;\n\
    \                den = 1;\n                return *this;\n            }\n\n  \
    \          u128 remainder =\n                fraction_detail::modulo(numerator.magnitude,\
    \ common);\n            u128 reduction = fraction_detail::gcd(remainder, common);\n\
    \            u256 reduced_numerator =\n                fraction_detail::divide_exact(\n\
    \                    numerator.magnitude, reduction);\n            u256 reduced_denominator\
    \ =\n                fraction_detail::multiply(\n                    b_reduced,\
    \ d / reduction);\n\n            assign_reduced(\n                numerator.negative,\n\
    \                reduced_numerator,\n                reduced_denominator);\n \
    \           return *this;\n        }\n\n        static bool parse_unsigned(\n\
    \            const std::string& s, std::size_t first, std::size_t last,\n    \
    \        u128 limit, u128& out) {\n            if (first == last) return false;\n\
    \            u128 value = 0;\n            for (std::size_t i = first; i < last;\
    \ ++i) {\n                char c = s[i];\n                if (c < '0' || c > '9')\
    \ return false;\n                u128 digit = static_cast<unsigned>(c - '0');\n\
    \                if (digit > limit ||\n                    value > (limit - digit)\
    \ / 10) {\n                    return false;\n                }\n            \
    \    value = value * 10 + digit;\n            }\n            out = value;\n  \
    \          return true;\n        }\n\n        static bool pow10(std::size_t exponent,\
    \ u128& out) {\n            u128 value = 1;\n            for (std::size_t i =\
    \ 0; i < exponent; ++i) {\n                if (value > max_u128() / 10) return\
    \ false;\n                value *= 10;\n            }\n            out = value;\n\
    \            return true;\n        }\n\n        static std::ostream& write_integer(std::ostream&\
    \ os, T value) {\n            u128 x = magnitude(value);\n            if (value\
    \ < 0) os.put('-');\n\n            char digits[40];\n            int size = 0;\n\
    \            do {\n                digits[size++] = static_cast<char>('0' + x\
    \ % 10);\n                x /= 10;\n            } while (x != 0);\n          \
    \  while (size > 0) os.put(digits[--size]);\n            return os;\n        }\n\
    \n    public:\n        fraction operator-() const {\n            fraction result;\n\
    \            result.assign_reduced(\n                num >= 0,\n             \
    \   fraction_detail::from_u128(magnitude(num)),\n                fraction_detail::from_u128(\n\
    \                    static_cast<u128>(den)));\n            return result;\n \
    \       }\n\n        fraction inv() const {\n            if (num == 0) {\n   \
    \             throw std::domain_error(\n                    \"fraction: zero has\
    \ no reciprocal\");\n            }\n            fraction result;\n           \
    \ result.assign_normalized(\n                num < 0,\n                static_cast<u128>(den),\n\
    \                magnitude(num));\n            return result;\n        }\n\n \
    \       bool is_integer() const {\n            return den == 1;\n        }\n\n\
    \        long double to_ld() const {\n            return static_cast<long double>(num)\
    \ /\n                   static_cast<long double>(den);\n        }\n\n        double\
    \ to_double() const {\n            return static_cast<double>(num) /\n       \
    \            static_cast<double>(den);\n        }\n\n        T floor() const {\n\
    \            u128 n = magnitude(num);\n            u128 d = static_cast<u128>(den);\n\
    \            u128 quotient = n / d;\n            u128 remainder = n % d;\n   \
    \         if (num >= 0) return from_magnitude(false, quotient);\n            return\
    \ from_magnitude(true, quotient + (remainder != 0));\n        }\n\n        T ceil()\
    \ const {\n            u128 n = magnitude(num);\n            u128 d = static_cast<u128>(den);\n\
    \            u128 quotient = n / d;\n            u128 remainder = n % d;\n   \
    \         if (num >= 0) {\n                return from_magnitude(\n          \
    \          false, quotient + (remainder != 0));\n            }\n            return\
    \ from_magnitude(true, quotient);\n        }\n\n        fraction& operator+=(const\
    \ fraction& other) {\n            return add_or_subtract(other, false);\n    \
    \    }\n\n        fraction& operator-=(const fraction& other) {\n            return\
    \ add_or_subtract(other, true);\n        }\n\n        fraction& operator*=(const\
    \ fraction& other) {\n            if (num == 0 || other.num == 0) {\n        \
    \        num = 0;\n                den = 1;\n                return *this;\n \
    \           }\n\n            u128 a = magnitude(num);\n            u128 b = static_cast<u128>(den);\n\
    \            u128 c = magnitude(other.num);\n            u128 d = static_cast<u128>(other.den);\n\
    \            u128 left_reduction = fraction_detail::gcd(a, d);\n            u128\
    \ right_reduction = fraction_detail::gcd(c, b);\n\n            u256 numerator\
    \ = fraction_detail::multiply(\n                a / left_reduction, c / right_reduction);\n\
    \            u256 denominator = fraction_detail::multiply(\n                b\
    \ / right_reduction, d / left_reduction);\n            assign_reduced(\n     \
    \           (num < 0) != (other.num < 0),\n                numerator,\n      \
    \          denominator);\n            return *this;\n        }\n\n        fraction&\
    \ operator/=(const fraction& other) {\n            if (other.num == 0) {\n   \
    \             throw std::domain_error(\n                    \"fraction: division\
    \ by zero\");\n            }\n            if (num == 0) {\n                den\
    \ = 1;\n                return *this;\n            }\n\n            u128 a = magnitude(num);\n\
    \            u128 b = static_cast<u128>(den);\n            u128 c = magnitude(other.num);\n\
    \            u128 d = static_cast<u128>(other.den);\n            u128 numerator_reduction\
    \ = fraction_detail::gcd(a, c);\n            u128 denominator_reduction = fraction_detail::gcd(d,\
    \ b);\n\n            u256 numerator = fraction_detail::multiply(\n           \
    \     a / numerator_reduction,\n                d / denominator_reduction);\n\
    \            u256 denominator = fraction_detail::multiply(\n                b\
    \ / denominator_reduction,\n                c / numerator_reduction);\n      \
    \      assign_reduced(\n                (num < 0) != (other.num < 0),\n      \
    \          numerator,\n                denominator);\n            return *this;\n\
    \        }\n\n        friend fraction operator+(fraction a, const fraction& b)\
    \ {\n            a += b;\n            return a;\n        }\n\n        friend fraction\
    \ operator-(fraction a, const fraction& b) {\n            a -= b;\n          \
    \  return a;\n        }\n\n        friend fraction operator*(fraction a, const\
    \ fraction& b) {\n            a *= b;\n            return a;\n        }\n\n  \
    \      friend fraction operator/(fraction a, const fraction& b) {\n          \
    \  a /= b;\n            return a;\n        }\n\n        friend bool operator==(const\
    \ fraction& a, const fraction& b) {\n            return a.num == b.num && a.den\
    \ == b.den;\n        }\n\n        friend bool operator!=(const fraction& a, const\
    \ fraction& b) {\n            return !(a == b);\n        }\n\n        friend bool\
    \ operator<(const fraction& a, const fraction& b) {\n            if ((a.num <\
    \ 0) != (b.num < 0)) return a.num < 0;\n\n            u256 left = fraction_detail::multiply(\n\
    \                magnitude(a.num), static_cast<u128>(b.den));\n            u256\
    \ right = fraction_detail::multiply(\n                magnitude(b.num), static_cast<u128>(a.den));\n\
    \            int cmp = fraction_detail::compare(left, right);\n            return\
    \ a.num < 0 ? cmp > 0 : cmp < 0;\n        }\n\n        friend bool operator>(const\
    \ fraction& a, const fraction& b) {\n            return b < a;\n        }\n\n\
    \        friend bool operator<=(const fraction& a, const fraction& b) {\n    \
    \        return !(b < a);\n        }\n\n        friend bool operator>=(const fraction&\
    \ a, const fraction& b) {\n            return !(a < b);\n        }\n\n       \
    \ // \u5BFE\u5FDC\u5F62\u5F0F: 12, -7, 1.5, .5, 1., 3/4, -10/6\n        static\
    \ bool parse(const std::string& s, fraction& out) {\n            if (s.empty())\
    \ return false;\n\n            bool negative = false;\n            std::size_t\
    \ first = 0;\n            if (s[first] == '+') {\n                ++first;\n \
    \           } else if (s[first] == '-') {\n                negative = true;\n\
    \                ++first;\n            }\n            if (first == s.size()) return\
    \ false;\n\n            std::size_t slash = s.find('/', first);\n            if\
    \ (slash != std::string::npos) {\n                if (s.find('/', slash + 1) !=\
    \ std::string::npos) return false;\n\n                u128 numerator;\n      \
    \          u128 denominator;\n                if (!parse_unsigned(\n         \
    \               s, first, slash, max_u128(), numerator) ||\n                 \
    \   !parse_unsigned(\n                        s, slash + 1, s.size(),\n      \
    \                  max_u128(), denominator) ||\n                    denominator\
    \ == 0) {\n                    return false;\n                }\n\n          \
    \      fraction tmp;\n                if (!tmp.try_assign_normalized(\n      \
    \                  negative, numerator, denominator)) {\n                    return\
    \ false;\n                }\n                out = tmp;\n                return\
    \ true;\n            }\n\n            std::size_t dot = s.find('.', first);\n\
    \            if (dot == std::string::npos) {\n                u128 numerator;\n\
    \                if (!parse_unsigned(\n                        s, first, s.size(),\
    \ max_u128(), numerator)) {\n                    return false;\n             \
    \   }\n                fraction tmp;\n                if (!tmp.try_assign_normalized(\n\
    \                        negative, numerator, 1)) {\n                    return\
    \ false;\n                }\n                out = tmp;\n                return\
    \ true;\n            }\n            if (s.find('.', dot + 1) != std::string::npos)\
    \ return false;\n            if (first == dot && dot + 1 == s.size()) return false;\n\
    \n            std::size_t fractional_end = s.size();\n            while (fractional_end\
    \ > dot + 1 &&\n                   s[fractional_end - 1] == '0') {\n         \
    \       --fractional_end;\n            }\n\n            u128 integer_part = 0;\n\
    \            if (first != dot &&\n                !parse_unsigned(\n         \
    \           s, first, dot, max_u128(), integer_part)) {\n                return\
    \ false;\n            }\n\n            std::size_t fractional_digits = fractional_end\
    \ - (dot + 1);\n            u128 denominator;\n            if (!pow10(fractional_digits,\
    \ denominator)) return false;\n\n            u128 fractional_part = 0;\n     \
    \       if (fractional_digits != 0 &&\n                !parse_unsigned(\n    \
    \                s, dot + 1, fractional_end,\n                    denominator\
    \ - 1, fractional_part)) {\n                return false;\n            }\n\n \
    \           u256 numerator = fraction_detail::add(\n                fraction_detail::multiply(integer_part,\
    \ denominator),\n                fraction_detail::from_u128(fractional_part));\n\
    \            if (fraction_detail::is_zero(numerator)) {\n                out =\
    \ fraction();\n                return true;\n            }\n\n            u128\
    \ reduction = fraction_detail::gcd(\n                fraction_detail::modulo(numerator,\
    \ denominator),\n                denominator);\n            numerator =\n    \
    \            fraction_detail::divide_exact(numerator, reduction);\n          \
    \  u128 reduced_denominator = denominator / reduction;\n\n            fraction\
    \ tmp;\n            if (!tmp.try_assign_reduced(\n                    negative,\n\
    \                    numerator,\n                    fraction_detail::from_u128(reduced_denominator)))\
    \ {\n                return false;\n            }\n            out = tmp;\n  \
    \          return true;\n        }\n\n        friend std::ostream& operator<<(\n\
    \            std::ostream& os, const fraction& x) {\n            write_integer(os,\
    \ x.num);\n            if (x.den != 1) {\n                os.put('/');\n     \
    \           write_integer(os, x.den);\n            }\n            return os;\n\
    \        }\n\n        friend std::istream& operator>>(\n            std::istream&\
    \ is, fraction& x) {\n            std::string s;\n            is >> s;\n     \
    \       if (!is) return is;\n\n            fraction tmp;\n            if (!fraction::parse(s,\
    \ tmp)) {\n                is.setstate(std::ios::failbit);\n                return\
    \ is;\n            }\n            x = tmp;\n            return is;\n        }\n\
    \    };\n\n    template<class T>\n    fraction<T> abs(const fraction<T>& x) {\n\
    \        return x.num < 0 ? -x : x;\n    }\n\n    using fr = fraction<__int128>;\n\
    }\n#line 2 \"utils/hash.hpp\"\n\n#include <chrono>\n#line 5 \"utils/hash.hpp\"\
    \n#include <cstdint>\n#line 7 \"utils/hash.hpp\"\n#include <memory>\n#include\
    \ <unordered_map>\n#include <unordered_set>\n#line 11 \"utils/hash.hpp\"\n\nnamespace\
    \ yesantikiss {\n    namespace hash_detail {\n        inline std::uint64_t splitmix64(std::uint64_t\
    \ x) {\n            x += 0x9e3779b97f4a7c15ULL;\n            x = (x ^ (x >> 30))\
    \ * 0xbf58476d1ce4e5b9ULL;\n            x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;\n\
    \            return x ^ (x >> 31);\n        }\n\n        inline std::uint64_t\
    \ random_seed() {\n            static const std::uint64_t seed =\n           \
    \     static_cast<std::uint64_t>(\n                    std::chrono::steady_clock::now()\n\
    \                        .time_since_epoch()\n                        .count());\n\
    \            return seed;\n        }\n    }\n\n    struct custom_hash {\n    \
    \    template<class T>\n        std::size_t operator()(const T& value) const {\n\
    \            return static_cast<std::size_t>(hash_detail::splitmix64(\n      \
    \          static_cast<std::uint64_t>(std::hash<T>{}(value)) +\n             \
    \   hash_detail::random_seed()));\n        }\n\n        template<class T, class\
    \ U>\n        std::size_t operator()(const std::pair<T, U>& value) const {\n \
    \           std::uint64_t first =\n                static_cast<std::uint64_t>((*this)(value.first));\n\
    \            std::uint64_t second =\n                static_cast<std::uint64_t>((*this)(value.second));\n\
    \            return static_cast<std::size_t>(hash_detail::splitmix64(\n      \
    \          first ^ (second + 0x9e3779b97f4a7c15ULL +\n                       \
    \  (first << 6) + (first >> 2))));\n        }\n    };\n\n    template<\n     \
    \   class Key,\n        class T,\n        class Hash = custom_hash,\n        class\
    \ KeyEqual = std::equal_to<Key>,\n        class Allocator = std::allocator<std::pair<const\
    \ Key, T>>>\n    using umap =\n        std::unordered_map<Key, T, Hash, KeyEqual,\
    \ Allocator>;\n\n    template<\n        class Key,\n        class Hash = custom_hash,\n\
    \        class KeyEqual = std::equal_to<Key>,\n        class Allocator = std::allocator<Key>>\n\
    \    using uset =\n        std::unordered_set<Key, Hash, KeyEqual, Allocator>;\n\
    }\n#line 2 \"utils/int128.hpp\"\n\n#line 7 \"utils/int128.hpp\"\n\nnamespace yesantikiss\
    \ {\n    using i128 = __int128;\n    using u128 = unsigned __int128;\n    using\
    \ int128 = __int128;\n\n    namespace int128_detail {\n        inline std::string\
    \ to_string(u128 value) {\n            char digits[39];\n            int size\
    \ = 0;\n            do {\n                digits[size++] =\n                 \
    \   static_cast<char>('0' + static_cast<int>(value % 10));\n                value\
    \ /= 10;\n            } while (value != 0);\n\n            std::string result;\n\
    \            result.reserve(static_cast<std::size_t>(size));\n            while\
    \ (size > 0) result.push_back(digits[--size]);\n            return result;\n \
    \       }\n\n        inline bool parse_magnitude(\n            const std::string&\
    \ token, std::size_t first, u128 limit,\n            u128& result) {\n       \
    \     if (first == token.size()) return false;\n\n            u128 value = 0;\n\
    \            for (std::size_t i = first; i < token.size(); ++i) {\n          \
    \      char c = token[i];\n                if (c < '0' || c > '9') return false;\n\
    \                u128 digit = static_cast<unsigned>(c - '0');\n              \
    \  if (digit > limit || value > (limit - digit) / 10) {\n                    return\
    \ false;\n                }\n                value = value * 10 + digit;\n   \
    \         }\n            result = value;\n            return true;\n        }\n\
    \    }\n}\n\ninline std::ostream& operator<<(std::ostream& os, yesantikiss::i128\
    \ value) {\n    yesantikiss::u128 magnitude = static_cast<yesantikiss::u128>(value);\n\
    \    if (value < 0) {\n        magnitude = yesantikiss::u128(0) - magnitude;\n\
    \    }\n    std::string result =\n        yesantikiss::int128_detail::to_string(magnitude);\n\
    \    if (value < 0) result.insert(result.begin(), '-');\n    return os << result;\n\
    }\n\ninline std::ostream& operator<<(std::ostream& os, yesantikiss::u128 value)\
    \ {\n    return os << yesantikiss::int128_detail::to_string(value);\n}\n\ninline\
    \ std::istream& operator>>(std::istream& is, yesantikiss::i128& value) {\n   \
    \ std::string token;\n    if (!(is >> token)) return is;\n\n    std::size_t first\
    \ = 0;\n    bool negative = false;\n    if (token[first] == '+' || token[first]\
    \ == '-') {\n        negative = token[first] == '-';\n        ++first;\n    }\n\
    \n    constexpr yesantikiss::u128 min_magnitude =\n        yesantikiss::u128(1)\
    \ << 127;\n    constexpr yesantikiss::u128 max_magnitude = min_magnitude - 1;\n\
    \    yesantikiss::u128 magnitude;\n    if (!yesantikiss::int128_detail::parse_magnitude(\n\
    \            token, first,\n            negative ? min_magnitude : max_magnitude,\
    \ magnitude)) {\n        is.setstate(std::ios::failbit);\n        return is;\n\
    \    }\n\n    if (!negative) {\n        value = static_cast<yesantikiss::i128>(magnitude);\n\
    \    } else if (magnitude == min_magnitude) {\n        value = -static_cast<yesantikiss::i128>(magnitude\
    \ - 1) - 1;\n    } else {\n        value = -static_cast<yesantikiss::i128>(magnitude);\n\
    \    }\n    return is;\n}\n\ninline std::istream& operator>>(std::istream& is,\
    \ yesantikiss::u128& value) {\n    std::string token;\n    if (!(is >> token))\
    \ return is;\n\n    std::size_t first = 0;\n    if (token[first] == '+') ++first;\n\
    \    if (first == token.size() || token[first] == '-') {\n        is.setstate(std::ios::failbit);\n\
    \        return is;\n    }\n\n    constexpr yesantikiss::u128 max_value = ~yesantikiss::u128(0);\n\
    \    yesantikiss::u128 parsed;\n    if (!yesantikiss::int128_detail::parse_magnitude(\n\
    \            token, first, max_value, parsed)) {\n        is.setstate(std::ios::failbit);\n\
    \        return is;\n    }\n    value = parsed;\n    return is;\n}\n#line 27 \"\
    tests/test.cpp\"\n\nlong long op_sum(long long a, long long b) { return a + b;\
    \ }\nlong long e_sum() { return 0; }\n\nyesantikiss::RollingHash::ull rolling_hash_from_other_tu(const\
    \ std::string& s);\n\nint main() {\n    using namespace yesantikiss;\n\n    {\n\
    \        const std::vector<int> a{1, 2, 1, 3};\n        Mo mo((int)a.size());\n\
    \        mo.add_query(0, 3);\n        mo.add_query(1, 4);\n        std::vector<int>\
    \ count(4), answer(2);\n        int distinct = 0;\n        auto add = [&](int\
    \ i) { distinct += count[a[i]]++ == 0; };\n        auto del = [&](int i) { distinct\
    \ -= --count[a[i]] == 0; };\n        mo.solve(add, del, [&](int i) { answer[i]\
    \ = distinct; });\n        assert((answer == std::vector<int>{2, 3}));\n    }\n\
    \    {\n        PS2D<int> ps(3, 4);\n        ps.add_rect_imos(0, 1, 2, 3, 5);\n\
    \        ps.add_point_imos(1, 2, 2);\n        ps.build();\n        assert(ps.at(0,\
    \ 1) == 5 && ps[1][2] == 7);\n        assert(ps.sum(0, 0, 2, 4) == 22);\n    }\n\
    \    {\n        BinaryTrie<4> trie;\n        trie.insert(1);\n        trie.insert(4);\n\
    \        trie.insert(4);\n        assert(trie.size() == 3 && trie.count(4) ==\
    \ 2);\n        assert(trie.kth(1) == 4 && trie.min_element(7) == 3);\n       \
    \ assert(trie.erase(4) && trie.count(4) == 1);\n    }\n    {\n        CartesianTree<int>\
    \ tree({3, 1, 4, 2});\n        assert(tree.root == 1);\n        assert(tree.par[0]\
    \ == 1 && tree.par[3] == 1 && tree.par[2] == 3);\n    }\n    {\n        Compressor<int>\
    \ comp;\n        comp.add(10);\n        comp.add(3);\n        comp.add(10);\n\
    \        comp.build();\n        assert(comp.size() == 2 && comp.get(3) == 0 &&\
    \ comp.value(1) == 10);\n        assert((comp.map(std::vector<int>{10, 3}) ==\
    \ std::vector<int>{1, 0}));\n    }\n    {\n        dynamic_segtree<long long,\
    \ op_sum, e_sum> seg(8);\n        seg.set(2, 3);\n        seg.set(5, 7);\n   \
    \     seg.apply_point(2, 4);\n        assert(seg.get(2) == 7 && seg.prod(0, 6)\
    \ == 14);\n        assert(seg.max_right(0, [](long long x) { return x <= 7; })\
    \ == 5);\n        assert(seg.min_left(6, [](long long x) { return x <= 7; }) ==\
    \ 3);\n    }\n    {\n        IntervalMap<int, int> intervals(0, 10, 0);\n    \
    \    intervals.assign(2, 6, 1);\n        intervals.apply(4, 8, [](int x) { return\
    \ x + 2; });\n        assert(intervals.get_val(1) == 0);\n        assert(intervals.get_val(3)\
    \ == 1);\n        assert(intervals.get_val(5) == 3);\n        assert(intervals.get_val(7)\
    \ == 2);\n    }\n    {\n        persistent_segtree<long long, op_sum, e_sum> seg(\n\
    \            std::vector<long long>{1, 2, 3});\n        int version = seg.set(1,\
    \ 10);\n        assert(seg.prod(0, 3, 0) == 6);\n        assert(seg.prod(0, 3,\
    \ version) == 14);\n    }\n    {\n        potential_dsu<long long> dsu(4);\n \
    \       dsu.merge(0, 1, 3);\n        dsu.merge(1, 2, -1);\n        assert(dsu.same(0,\
    \ 2) && dsu.diff(0, 2) == 2);\n        assert(dsu.size(1) == 3 && dsu.groups().size()\
    \ == 2);\n    }\n    {\n        Factor factor(30);\n        assert(factor.is_prime(29)\
    \ && !factor.is_prime(1));\n        assert((factor.factorize(24) ==\n        \
    \        std::vector<std::pair<int, int>>{{2, 3}, {3, 1}}));\n    }\n    {\n \
    \       AhoCorasick<> ac;\n        int she = ac.add(\"she\");\n        int he\
    \ = ac.add(\"he\");\n        ac.build();\n        int state = 0;\n        for\
    \ (char c : std::string(\"she\")) state = ac.move(state, c);\n        assert(state\
    \ == she && ac.link(she) == he);\n    }\n    {\n        RollingHash hash(\"abracadabra\"\
    );\n        assert(hash.equals(0, 4, 7, 11));\n        assert(hash.get(0, 4) ==\
    \ rolling_hash_from_other_tu(\"abra\"));\n\n        using Hash = RollingHash::Hash;\n\
    \        const std::string s = \"abracadabra\";\n        for (int l = 0; l <=\
    \ (int)s.size(); ++l) {\n            for (int m = l; m <= (int)s.size(); ++m)\
    \ {\n                for (int r = m; r <= (int)s.size(); ++r) {\n            \
    \        assert(hash.slice(l, m) + hash.slice(m, r) == hash.slice(l, r));\n  \
    \                  assert(RollingHash::concat(hash.get(l, m), hash.get(m, r),\
    \ r - m) ==\n                           hash.get(l, r));\n                }\n\
    \            }\n        }\n        RollingHash other(\"cadabra\");\n        assert(hash.slice(0,\
    \ 4) + other.slice(0, 7) == hash.slice(0, 11));\n        assert(hash.slice(0,\
    \ 4) + other.slice(0, 3) != hash.slice(0, 4) + other.slice(1, 4));\n        assert(Hash(\"\
    abra\") + Hash(\"cad\") == hash.slice(0, 7));\n        assert(Hash(std::string(\"\
    abra\")).val == hash.get(0, 4));\n        Hash acc;\n        for (char c : s)\
    \ acc += Hash(c);\n        assert(acc == hash.slice(0, 11) && acc.len == 11);\n\
    \        assert(Hash() + acc == acc && acc + Hash() == acc);\n        const std::string\
    \ t = \"abracadabrb\";\n        RollingHash hash_t(t);\n        auto sign = [](int\
    \ x) { return (x > 0) - (x < 0); };\n        for (int l1 = 0; l1 <= (int)s.size();\
    \ ++l1) {\n            for (int r1 = l1; r1 <= (int)s.size(); ++r1) {\n      \
    \          for (int l2 = 0; l2 <= (int)t.size(); ++l2) {\n                   \
    \ for (int r2 = l2; r2 <= (int)t.size(); ++r2) {\n                        const\
    \ std::string x = s.substr(l1, r1 - l1), y = t.substr(l2, r2 - l2);\n        \
    \                int k = 0;\n                        while (k < (int)x.size()\
    \ && k < (int)y.size() && x[k] == y[k]) ++k;\n                        assert(RollingHash::lcp(hash,\
    \ l1, r1, hash_t, l2, r2) == k);\n                        assert(RollingHash::compare(hash,\
    \ l1, r1, hash_t, l2, r2) ==\n                               sign(x.compare(y)));\n\
    \                    }\n                }\n            }\n        }\n        assert(hash.lcp(0,\
    \ 11, 7, 11) == 4 && hash.compare(0, 11, 7, 11) > 0);\n        assert(hash.compare(0,\
    \ 4, 7, 11) == 0 && hash.compare(1, 4, 0, 4) > 0);\n        RollingHash high(std::string(\"\
    a\\xff\")), low(\"ab\");\n        assert(RollingHash::compare(high, 0, 2, low,\
    \ 0, 2) > 0);\n    }\n    {\n        std::vector<std::vector<int>> graph(7);\n\
    \        auto add_edge = [&](int u, int v) {\n            graph[u].push_back(v);\n\
    \            graph[v].push_back(u);\n        };\n        add_edge(0, 1);\n   \
    \     add_edge(0, 2);\n        add_edge(1, 3);\n        add_edge(1, 4);\n    \
    \    add_edge(2, 5);\n        add_edge(5, 6);\n\n        BinaryLiftingLCA doubling(graph);\n\
    \        EulerTourLCA sparse(graph);\n        assert(doubling.lca(3, 4) == 1);\n\
    \        assert(doubling.lca(3, 6) == 0);\n        assert(doubling.dist(3, 6)\
    \ == 5);\n        assert(doubling.is_ancestor(0, 6));\n        assert(sparse.lca(3,\
    \ 4) == 1);\n        assert(sparse.lca(3, 6) == 0);\n        assert(sparse.dist(3,\
    \ 6) == 5);\n        assert(sparse.is_ancestor(0, 6));\n        assert(doubling.kth_ancestor(6,\
    \ 100) == 0);\n        assert(doubling.jump(3, 6, 0) == 3);\n        assert(doubling.jump(3,\
    \ 6, 2) == 0);\n        assert(doubling.jump(3, 6, 5) == 6);\n        assert(doubling.jump(3,\
    \ 6, 6) == -1);\n\n        HeavyLightDecomposition hld(graph);\n        std::vector<int>\
    \ path;\n        hld.path_query(3, 6, false, [&](int l, int r, bool reverse) {\n\
    \            if (reverse) {\n                for (int i = r - 1; i >= l; --i)\
    \ path.push_back(hld.vertex[i]);\n            } else {\n                for (int\
    \ i = l; i < r; ++i) path.push_back(hld.vertex[i]);\n            }\n        });\n\
    \        assert((path == std::vector<int>{3, 1, 0, 2, 5, 6}));\n\n        path.clear();\n\
    \        hld.path_query(3, 6, true, [&](int l, int r, bool reverse) {\n      \
    \      if (reverse) {\n                for (int i = r - 1; i >= l; --i) path.push_back(hld.vertex[i]);\n\
    \            } else {\n                for (int i = l; i < r; ++i) path.push_back(hld.vertex[i]);\n\
    \            }\n        });\n        assert((path == std::vector<int>{3, 1, 2,\
    \ 5, 6}));\n\n        auto [left, right] = hld.subtree_vertex(2);\n        std::vector<int>\
    \ subtree(hld.vertex.begin() + left,\n                                 hld.vertex.begin()\
    \ + right);\n        std::sort(subtree.begin(), subtree.end());\n        assert((subtree\
    \ == std::vector<int>{2, 5, 6}));\n    }\n    {\n        std::vector<std::vector<int>>\
    \ forest{{1}, {0}, {3}, {2}};\n        BinaryLiftingLCA doubling;\n        EulerTourLCA\
    \ sparse;\n        doubling.build_forest(forest);\n        sparse.build_forest(forest);\n\
    \        assert(doubling.lca(0, 2) == -1);\n        assert(sparse.lca(0, 2) ==\
    \ -1);\n        assert(!doubling.is_ancestor(0, 2));\n        assert(!sparse.is_ancestor(0,\
    \ 2));\n    }\n    {\n        umap<long long, std::string> map;\n        map[1000000007LL]\
    \ = \"prime\";\n        assert(map.at(1000000007LL) == \"prime\");\n        assert(map.find(0)\
    \ == map.end());\n\n        uset<std::pair<int, int>> set;\n        set.insert({2,\
    \ 3});\n        set.insert({2, 3});\n        set.insert({3, 2});\n        assert(set.size()\
    \ == 2);\n        assert(set.count({2, 3}) == 1);\n    }\n    {\n        using\
    \ Fraction = fraction<long long>;\n\n        assert(Fraction(6, -8) == Fraction(-3,\
    \ 4));\n        assert(Fraction(-7, 3).floor() == -3);\n        assert(Fraction(-7,\
    \ 3).ceil() == -2);\n        assert(Fraction(std::numeric_limits<long long>::max(),\
    \ 2).ceil() ==\n               4611686018427387904LL);\n        assert(Fraction(std::numeric_limits<long\
    \ long>::min(), 1).floor() ==\n               std::numeric_limits<long long>::min());\n\
    \        assert(Fraction(2, std::numeric_limits<long long>::min()) ==\n      \
    \         Fraction(-1, 4611686018427387904LL));\n\n        Fraction small(1, 4000000000LL);\n\
    \        assert(small + small == Fraction(1, 2000000000LL));\n\n        Fraction\
    \ left(4000000000LL, 4000000001LL);\n        Fraction right(4000000001LL, 2000000000LL);\n\
    \        assert(left * right == Fraction(2));\n        assert((left * right) /\
    \ Fraction(4) == Fraction(1, 2));\n\n        Fraction parsed(7);\n        assert(Fraction::parse(\"\
    -10/6\", parsed));\n        assert(parsed == Fraction(-5, 3));\n        assert(Fraction::parse(\"\
    .500000000000000000000000000000\", parsed));\n        assert(parsed == Fraction(1,\
    \ 2));\n        assert(Fraction::parse(\".0\", parsed));\n        assert(parsed\
    \ == Fraction(0));\n\n        parsed = Fraction(7);\n        assert(!Fraction::parse(\"\
    9223372036854775808\", parsed));\n        assert(parsed == Fraction(7));\n   \
    \     assert(!Fraction::parse(\"-9223372036854775809\", parsed));\n        assert(parsed\
    \ == Fraction(7));\n\n        bool overflowed = false;\n        Fraction max_value(std::numeric_limits<long\
    \ long>::max());\n        try {\n            max_value += Fraction(1);\n     \
    \   } catch (const std::overflow_error&) {\n            overflowed = true;\n \
    \       }\n        assert(overflowed);\n        assert(max_value ==\n        \
    \       Fraction(std::numeric_limits<long long>::max()));\n\n        bool divided_by_zero\
    \ = false;\n        try {\n            max_value /= Fraction(0);\n        } catch\
    \ (const std::domain_error&) {\n            divided_by_zero = true;\n        }\n\
    \        assert(divided_by_zero);\n        assert(max_value ==\n             \
    \  Fraction(std::numeric_limits<long long>::max()));\n    }\n    {\n        using\
    \ Int128 = __int128;\n        Int128 large = Int128(1) << 70;\n\n        fr left(large,\
    \ large + 1);\n        fr right(large + 1, large / 2);\n        assert(left *\
    \ right == fr(2));\n        assert(fr(large, large - 1) > fr(large - 1, large));\n\
    \n        std::stringstream stream;\n        stream << fr(-large, 2);\n      \
    \  assert(stream.str() == \"-590295810358705651712\");\n\n        fr parsed;\n\
    \        assert(fr::parse(\n            \"170141183460469231731687303715884105727\"\
    , parsed));\n        std::stringstream max_stream;\n        max_stream << parsed;\n\
    \        assert(max_stream.str() ==\n               \"170141183460469231731687303715884105727\"\
    );\n        assert(!fr::parse(\n            \"170141183460469231731687303715884105728\"\
    , parsed));\n        assert(fr::parse(\n            \"-170141183460469231731687303715884105728\"\
    , parsed));\n        std::stringstream min_stream;\n        min_stream << parsed;\n\
    \        assert(min_stream.str() ==\n               \"-170141183460469231731687303715884105728\"\
    );\n    }\n    {\n        constexpr i128 i128_min = -(i128(1) << 126) * 2;\n \
    \       constexpr i128 i128_max =\n            static_cast<i128>((u128(1) << 127)\
    \ - 1);\n        constexpr u128 u128_max = ~u128(0);\n\n        std::stringstream\
    \ output;\n        output << i128(0) << ' ' << i128_min << ' ' << i128_max <<\
    \ ' '\n               << u128_max;\n        assert(output.str() ==\n         \
    \      \"0 -170141183460469231731687303715884105728 \"\n               \"170141183460469231731687303715884105727\
    \ \"\n               \"340282366920938463463374607431768211455\");\n\n       \
    \ i128 signed_value = 0;\n        u128 unsigned_value = 0;\n        std::stringstream\
    \ input(\n            \"  +170141183460469231731687303715884105727 \"\n      \
    \      \"-170141183460469231731687303715884105728 \"\n            \"340282366920938463463374607431768211455\"\
    );\n        input >> signed_value;\n        assert(signed_value == i128_max);\n\
    \        input >> signed_value;\n        assert(signed_value == i128_min);\n \
    \       input >> unsigned_value;\n        assert(unsigned_value == u128_max);\n\
    \n        signed_value = 42;\n        std::stringstream signed_overflow(\n   \
    \         \"170141183460469231731687303715884105728\");\n        signed_overflow\
    \ >> signed_value;\n        assert(signed_overflow.fail());\n        assert(signed_value\
    \ == 42);\n\n        unsigned_value = 42;\n        std::stringstream unsigned_overflow(\n\
    \            \"340282366920938463463374607431768211456\");\n        unsigned_overflow\
    \ >> unsigned_value;\n        assert(unsigned_overflow.fail());\n        assert(unsigned_value\
    \ == 42);\n\n        std::stringstream invalid(\"-1\");\n        invalid >> unsigned_value;\n\
    \        assert(invalid.fail());\n        assert(unsigned_value == 42);\n    }\n\
    }\n"
  code: "#include <algorithm>\n#include <cassert>\n#include <functional>\n#include\
    \ <limits>\n#include <sstream>\n#include <string>\n#include <vector>\n\n#include\
    \ \"algo/mo.hpp\"\n#include \"ds/2d_prefixsum.hpp\"\n#include \"ds/binary_trie.hpp\"\
    \n#include \"ds/cartesian_tree.hpp\"\n#include \"ds/compressor.hpp\"\n#include\
    \ \"ds/dynamic_segtree.hpp\"\n#include \"ds/interval_map.hpp\"\n#include \"ds/persistent_segtree.hpp\"\
    \n#include \"ds/potential_dsu.hpp\"\n#include \"math/factor.hpp\"\n#include \"\
    string/aho_corasick.hpp\"\n#include \"string/rolling_hash.hpp\"\n#include \"tree/heavy_light_decomposition.hpp\"\
    \n#include \"tree/lca_binary_lifting.hpp\"\n#include \"tree/lca_euler_tour.hpp\"\
    \n#include \"utils/fraction.hpp\"\n#include \"utils/hash.hpp\"\n#include \"utils/int128.hpp\"\
    \n\nlong long op_sum(long long a, long long b) { return a + b; }\nlong long e_sum()\
    \ { return 0; }\n\nyesantikiss::RollingHash::ull rolling_hash_from_other_tu(const\
    \ std::string& s);\n\nint main() {\n    using namespace yesantikiss;\n\n    {\n\
    \        const std::vector<int> a{1, 2, 1, 3};\n        Mo mo((int)a.size());\n\
    \        mo.add_query(0, 3);\n        mo.add_query(1, 4);\n        std::vector<int>\
    \ count(4), answer(2);\n        int distinct = 0;\n        auto add = [&](int\
    \ i) { distinct += count[a[i]]++ == 0; };\n        auto del = [&](int i) { distinct\
    \ -= --count[a[i]] == 0; };\n        mo.solve(add, del, [&](int i) { answer[i]\
    \ = distinct; });\n        assert((answer == std::vector<int>{2, 3}));\n    }\n\
    \    {\n        PS2D<int> ps(3, 4);\n        ps.add_rect_imos(0, 1, 2, 3, 5);\n\
    \        ps.add_point_imos(1, 2, 2);\n        ps.build();\n        assert(ps.at(0,\
    \ 1) == 5 && ps[1][2] == 7);\n        assert(ps.sum(0, 0, 2, 4) == 22);\n    }\n\
    \    {\n        BinaryTrie<4> trie;\n        trie.insert(1);\n        trie.insert(4);\n\
    \        trie.insert(4);\n        assert(trie.size() == 3 && trie.count(4) ==\
    \ 2);\n        assert(trie.kth(1) == 4 && trie.min_element(7) == 3);\n       \
    \ assert(trie.erase(4) && trie.count(4) == 1);\n    }\n    {\n        CartesianTree<int>\
    \ tree({3, 1, 4, 2});\n        assert(tree.root == 1);\n        assert(tree.par[0]\
    \ == 1 && tree.par[3] == 1 && tree.par[2] == 3);\n    }\n    {\n        Compressor<int>\
    \ comp;\n        comp.add(10);\n        comp.add(3);\n        comp.add(10);\n\
    \        comp.build();\n        assert(comp.size() == 2 && comp.get(3) == 0 &&\
    \ comp.value(1) == 10);\n        assert((comp.map(std::vector<int>{10, 3}) ==\
    \ std::vector<int>{1, 0}));\n    }\n    {\n        dynamic_segtree<long long,\
    \ op_sum, e_sum> seg(8);\n        seg.set(2, 3);\n        seg.set(5, 7);\n   \
    \     seg.apply_point(2, 4);\n        assert(seg.get(2) == 7 && seg.prod(0, 6)\
    \ == 14);\n        assert(seg.max_right(0, [](long long x) { return x <= 7; })\
    \ == 5);\n        assert(seg.min_left(6, [](long long x) { return x <= 7; }) ==\
    \ 3);\n    }\n    {\n        IntervalMap<int, int> intervals(0, 10, 0);\n    \
    \    intervals.assign(2, 6, 1);\n        intervals.apply(4, 8, [](int x) { return\
    \ x + 2; });\n        assert(intervals.get_val(1) == 0);\n        assert(intervals.get_val(3)\
    \ == 1);\n        assert(intervals.get_val(5) == 3);\n        assert(intervals.get_val(7)\
    \ == 2);\n    }\n    {\n        persistent_segtree<long long, op_sum, e_sum> seg(\n\
    \            std::vector<long long>{1, 2, 3});\n        int version = seg.set(1,\
    \ 10);\n        assert(seg.prod(0, 3, 0) == 6);\n        assert(seg.prod(0, 3,\
    \ version) == 14);\n    }\n    {\n        potential_dsu<long long> dsu(4);\n \
    \       dsu.merge(0, 1, 3);\n        dsu.merge(1, 2, -1);\n        assert(dsu.same(0,\
    \ 2) && dsu.diff(0, 2) == 2);\n        assert(dsu.size(1) == 3 && dsu.groups().size()\
    \ == 2);\n    }\n    {\n        Factor factor(30);\n        assert(factor.is_prime(29)\
    \ && !factor.is_prime(1));\n        assert((factor.factorize(24) ==\n        \
    \        std::vector<std::pair<int, int>>{{2, 3}, {3, 1}}));\n    }\n    {\n \
    \       AhoCorasick<> ac;\n        int she = ac.add(\"she\");\n        int he\
    \ = ac.add(\"he\");\n        ac.build();\n        int state = 0;\n        for\
    \ (char c : std::string(\"she\")) state = ac.move(state, c);\n        assert(state\
    \ == she && ac.link(she) == he);\n    }\n    {\n        RollingHash hash(\"abracadabra\"\
    );\n        assert(hash.equals(0, 4, 7, 11));\n        assert(hash.get(0, 4) ==\
    \ rolling_hash_from_other_tu(\"abra\"));\n\n        using Hash = RollingHash::Hash;\n\
    \        const std::string s = \"abracadabra\";\n        for (int l = 0; l <=\
    \ (int)s.size(); ++l) {\n            for (int m = l; m <= (int)s.size(); ++m)\
    \ {\n                for (int r = m; r <= (int)s.size(); ++r) {\n            \
    \        assert(hash.slice(l, m) + hash.slice(m, r) == hash.slice(l, r));\n  \
    \                  assert(RollingHash::concat(hash.get(l, m), hash.get(m, r),\
    \ r - m) ==\n                           hash.get(l, r));\n                }\n\
    \            }\n        }\n        RollingHash other(\"cadabra\");\n        assert(hash.slice(0,\
    \ 4) + other.slice(0, 7) == hash.slice(0, 11));\n        assert(hash.slice(0,\
    \ 4) + other.slice(0, 3) != hash.slice(0, 4) + other.slice(1, 4));\n        assert(Hash(\"\
    abra\") + Hash(\"cad\") == hash.slice(0, 7));\n        assert(Hash(std::string(\"\
    abra\")).val == hash.get(0, 4));\n        Hash acc;\n        for (char c : s)\
    \ acc += Hash(c);\n        assert(acc == hash.slice(0, 11) && acc.len == 11);\n\
    \        assert(Hash() + acc == acc && acc + Hash() == acc);\n        const std::string\
    \ t = \"abracadabrb\";\n        RollingHash hash_t(t);\n        auto sign = [](int\
    \ x) { return (x > 0) - (x < 0); };\n        for (int l1 = 0; l1 <= (int)s.size();\
    \ ++l1) {\n            for (int r1 = l1; r1 <= (int)s.size(); ++r1) {\n      \
    \          for (int l2 = 0; l2 <= (int)t.size(); ++l2) {\n                   \
    \ for (int r2 = l2; r2 <= (int)t.size(); ++r2) {\n                        const\
    \ std::string x = s.substr(l1, r1 - l1), y = t.substr(l2, r2 - l2);\n        \
    \                int k = 0;\n                        while (k < (int)x.size()\
    \ && k < (int)y.size() && x[k] == y[k]) ++k;\n                        assert(RollingHash::lcp(hash,\
    \ l1, r1, hash_t, l2, r2) == k);\n                        assert(RollingHash::compare(hash,\
    \ l1, r1, hash_t, l2, r2) ==\n                               sign(x.compare(y)));\n\
    \                    }\n                }\n            }\n        }\n        assert(hash.lcp(0,\
    \ 11, 7, 11) == 4 && hash.compare(0, 11, 7, 11) > 0);\n        assert(hash.compare(0,\
    \ 4, 7, 11) == 0 && hash.compare(1, 4, 0, 4) > 0);\n        RollingHash high(std::string(\"\
    a\\xff\")), low(\"ab\");\n        assert(RollingHash::compare(high, 0, 2, low,\
    \ 0, 2) > 0);\n    }\n    {\n        std::vector<std::vector<int>> graph(7);\n\
    \        auto add_edge = [&](int u, int v) {\n            graph[u].push_back(v);\n\
    \            graph[v].push_back(u);\n        };\n        add_edge(0, 1);\n   \
    \     add_edge(0, 2);\n        add_edge(1, 3);\n        add_edge(1, 4);\n    \
    \    add_edge(2, 5);\n        add_edge(5, 6);\n\n        BinaryLiftingLCA doubling(graph);\n\
    \        EulerTourLCA sparse(graph);\n        assert(doubling.lca(3, 4) == 1);\n\
    \        assert(doubling.lca(3, 6) == 0);\n        assert(doubling.dist(3, 6)\
    \ == 5);\n        assert(doubling.is_ancestor(0, 6));\n        assert(sparse.lca(3,\
    \ 4) == 1);\n        assert(sparse.lca(3, 6) == 0);\n        assert(sparse.dist(3,\
    \ 6) == 5);\n        assert(sparse.is_ancestor(0, 6));\n        assert(doubling.kth_ancestor(6,\
    \ 100) == 0);\n        assert(doubling.jump(3, 6, 0) == 3);\n        assert(doubling.jump(3,\
    \ 6, 2) == 0);\n        assert(doubling.jump(3, 6, 5) == 6);\n        assert(doubling.jump(3,\
    \ 6, 6) == -1);\n\n        HeavyLightDecomposition hld(graph);\n        std::vector<int>\
    \ path;\n        hld.path_query(3, 6, false, [&](int l, int r, bool reverse) {\n\
    \            if (reverse) {\n                for (int i = r - 1; i >= l; --i)\
    \ path.push_back(hld.vertex[i]);\n            } else {\n                for (int\
    \ i = l; i < r; ++i) path.push_back(hld.vertex[i]);\n            }\n        });\n\
    \        assert((path == std::vector<int>{3, 1, 0, 2, 5, 6}));\n\n        path.clear();\n\
    \        hld.path_query(3, 6, true, [&](int l, int r, bool reverse) {\n      \
    \      if (reverse) {\n                for (int i = r - 1; i >= l; --i) path.push_back(hld.vertex[i]);\n\
    \            } else {\n                for (int i = l; i < r; ++i) path.push_back(hld.vertex[i]);\n\
    \            }\n        });\n        assert((path == std::vector<int>{3, 1, 2,\
    \ 5, 6}));\n\n        auto [left, right] = hld.subtree_vertex(2);\n        std::vector<int>\
    \ subtree(hld.vertex.begin() + left,\n                                 hld.vertex.begin()\
    \ + right);\n        std::sort(subtree.begin(), subtree.end());\n        assert((subtree\
    \ == std::vector<int>{2, 5, 6}));\n    }\n    {\n        std::vector<std::vector<int>>\
    \ forest{{1}, {0}, {3}, {2}};\n        BinaryLiftingLCA doubling;\n        EulerTourLCA\
    \ sparse;\n        doubling.build_forest(forest);\n        sparse.build_forest(forest);\n\
    \        assert(doubling.lca(0, 2) == -1);\n        assert(sparse.lca(0, 2) ==\
    \ -1);\n        assert(!doubling.is_ancestor(0, 2));\n        assert(!sparse.is_ancestor(0,\
    \ 2));\n    }\n    {\n        umap<long long, std::string> map;\n        map[1000000007LL]\
    \ = \"prime\";\n        assert(map.at(1000000007LL) == \"prime\");\n        assert(map.find(0)\
    \ == map.end());\n\n        uset<std::pair<int, int>> set;\n        set.insert({2,\
    \ 3});\n        set.insert({2, 3});\n        set.insert({3, 2});\n        assert(set.size()\
    \ == 2);\n        assert(set.count({2, 3}) == 1);\n    }\n    {\n        using\
    \ Fraction = fraction<long long>;\n\n        assert(Fraction(6, -8) == Fraction(-3,\
    \ 4));\n        assert(Fraction(-7, 3).floor() == -3);\n        assert(Fraction(-7,\
    \ 3).ceil() == -2);\n        assert(Fraction(std::numeric_limits<long long>::max(),\
    \ 2).ceil() ==\n               4611686018427387904LL);\n        assert(Fraction(std::numeric_limits<long\
    \ long>::min(), 1).floor() ==\n               std::numeric_limits<long long>::min());\n\
    \        assert(Fraction(2, std::numeric_limits<long long>::min()) ==\n      \
    \         Fraction(-1, 4611686018427387904LL));\n\n        Fraction small(1, 4000000000LL);\n\
    \        assert(small + small == Fraction(1, 2000000000LL));\n\n        Fraction\
    \ left(4000000000LL, 4000000001LL);\n        Fraction right(4000000001LL, 2000000000LL);\n\
    \        assert(left * right == Fraction(2));\n        assert((left * right) /\
    \ Fraction(4) == Fraction(1, 2));\n\n        Fraction parsed(7);\n        assert(Fraction::parse(\"\
    -10/6\", parsed));\n        assert(parsed == Fraction(-5, 3));\n        assert(Fraction::parse(\"\
    .500000000000000000000000000000\", parsed));\n        assert(parsed == Fraction(1,\
    \ 2));\n        assert(Fraction::parse(\".0\", parsed));\n        assert(parsed\
    \ == Fraction(0));\n\n        parsed = Fraction(7);\n        assert(!Fraction::parse(\"\
    9223372036854775808\", parsed));\n        assert(parsed == Fraction(7));\n   \
    \     assert(!Fraction::parse(\"-9223372036854775809\", parsed));\n        assert(parsed\
    \ == Fraction(7));\n\n        bool overflowed = false;\n        Fraction max_value(std::numeric_limits<long\
    \ long>::max());\n        try {\n            max_value += Fraction(1);\n     \
    \   } catch (const std::overflow_error&) {\n            overflowed = true;\n \
    \       }\n        assert(overflowed);\n        assert(max_value ==\n        \
    \       Fraction(std::numeric_limits<long long>::max()));\n\n        bool divided_by_zero\
    \ = false;\n        try {\n            max_value /= Fraction(0);\n        } catch\
    \ (const std::domain_error&) {\n            divided_by_zero = true;\n        }\n\
    \        assert(divided_by_zero);\n        assert(max_value ==\n             \
    \  Fraction(std::numeric_limits<long long>::max()));\n    }\n    {\n        using\
    \ Int128 = __int128;\n        Int128 large = Int128(1) << 70;\n\n        fr left(large,\
    \ large + 1);\n        fr right(large + 1, large / 2);\n        assert(left *\
    \ right == fr(2));\n        assert(fr(large, large - 1) > fr(large - 1, large));\n\
    \n        std::stringstream stream;\n        stream << fr(-large, 2);\n      \
    \  assert(stream.str() == \"-590295810358705651712\");\n\n        fr parsed;\n\
    \        assert(fr::parse(\n            \"170141183460469231731687303715884105727\"\
    , parsed));\n        std::stringstream max_stream;\n        max_stream << parsed;\n\
    \        assert(max_stream.str() ==\n               \"170141183460469231731687303715884105727\"\
    );\n        assert(!fr::parse(\n            \"170141183460469231731687303715884105728\"\
    , parsed));\n        assert(fr::parse(\n            \"-170141183460469231731687303715884105728\"\
    , parsed));\n        std::stringstream min_stream;\n        min_stream << parsed;\n\
    \        assert(min_stream.str() ==\n               \"-170141183460469231731687303715884105728\"\
    );\n    }\n    {\n        constexpr i128 i128_min = -(i128(1) << 126) * 2;\n \
    \       constexpr i128 i128_max =\n            static_cast<i128>((u128(1) << 127)\
    \ - 1);\n        constexpr u128 u128_max = ~u128(0);\n\n        std::stringstream\
    \ output;\n        output << i128(0) << ' ' << i128_min << ' ' << i128_max <<\
    \ ' '\n               << u128_max;\n        assert(output.str() ==\n         \
    \      \"0 -170141183460469231731687303715884105728 \"\n               \"170141183460469231731687303715884105727\
    \ \"\n               \"340282366920938463463374607431768211455\");\n\n       \
    \ i128 signed_value = 0;\n        u128 unsigned_value = 0;\n        std::stringstream\
    \ input(\n            \"  +170141183460469231731687303715884105727 \"\n      \
    \      \"-170141183460469231731687303715884105728 \"\n            \"340282366920938463463374607431768211455\"\
    );\n        input >> signed_value;\n        assert(signed_value == i128_max);\n\
    \        input >> signed_value;\n        assert(signed_value == i128_min);\n \
    \       input >> unsigned_value;\n        assert(unsigned_value == u128_max);\n\
    \n        signed_value = 42;\n        std::stringstream signed_overflow(\n   \
    \         \"170141183460469231731687303715884105728\");\n        signed_overflow\
    \ >> signed_value;\n        assert(signed_overflow.fail());\n        assert(signed_value\
    \ == 42);\n\n        unsigned_value = 42;\n        std::stringstream unsigned_overflow(\n\
    \            \"340282366920938463463374607431768211456\");\n        unsigned_overflow\
    \ >> unsigned_value;\n        assert(unsigned_overflow.fail());\n        assert(unsigned_value\
    \ == 42);\n\n        std::stringstream invalid(\"-1\");\n        invalid >> unsigned_value;\n\
    \        assert(invalid.fail());\n        assert(unsigned_value == 42);\n    }\n\
    }\n"
  dependsOn:
  - algo/mo.hpp
  - ds/2d_prefixsum.hpp
  - ds/binary_trie.hpp
  - ds/cartesian_tree.hpp
  - ds/compressor.hpp
  - ds/dynamic_segtree.hpp
  - ds/interval_map.hpp
  - ds/persistent_segtree.hpp
  - ds/potential_dsu.hpp
  - math/factor.hpp
  - string/aho_corasick.hpp
  - string/rolling_hash.hpp
  - tree/heavy_light_decomposition.hpp
  - tree/lca_binary_lifting.hpp
  - tree/lca_euler_tour.hpp
  - utils/fraction.hpp
  - utils/hash.hpp
  - utils/int128.hpp
  isVerificationFile: false
  path: tests/test.cpp
  requiredBy: []
  timestamp: '2026-10-08 13:39:00+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tests/test.cpp
layout: document
redirect_from:
- /library/tests/test.cpp
- /library/tests/test.cpp.html
title: tests/test.cpp
---
