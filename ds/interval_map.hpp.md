---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: tests/test.cpp
    title: tests/test.cpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"ds/interval_map.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <functional>\n#include <iterator>\n#include <ostream>\n\
    #include <set>\n#include <tuple>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\nnamespace yesantikiss {\n    using std::distance;\n    using\
    \ std::max;\n    using std::min;\n    using std::next;\n    using std::ostream;\n\
    \    using std::prev;\n    using std::set;\n    using std::vector;\n    /*\n \
    \     IntervalMap\uFF08\u533A\u9593 map / \u533A\u9593 set \u7BA1\u7406\uFF1A\u5B8C\
    \u6210\u5F62\uFF09\n      ==============================================\n   \
    \   \u534A\u958B\u533A\u9593 [l, r) \u3092 set \u3067\u7BA1\u7406\u3057\u3001\u5404\
    \u533A\u9593\u306B\u5024 v \u3092\u6301\u305F\u305B\u308B\u3002\n    \n      \u25A0\
    \ \u4E0D\u5909\u91CF\uFF08\u3053\u308C\u304C\u5D29\u308C\u306A\u3044\u3088\u3046\
    \u306B\u5B9F\u88C5\u3059\u308B\uFF09\n      ----------------------------------------\n\
    \      1) \u533A\u9593\u306F\u4E92\u3044\u306B\u4EA4\u5DEE\u3057\u306A\u3044\n\
    \      2) \u5E38\u306B [L, R) \u3092\u5B8C\u5168\u306B\u88AB\u8986\u3057\u3066\
    \u3044\u308B\uFF08init \u3067 1 \u672C\u5165\u308C\u3066\u958B\u59CB\uFF09\n \
    \     3) \u96A3\u63A5\u3057\u3066\u5024\u304C\u540C\u3058\u533A\u9593\u306F\u5B58\
    \u5728\u3057\u306A\u3044\uFF08\u81EA\u52D5\u30DE\u30FC\u30B8\u3067\u6F70\u3059\
    \uFF09\n    \n      \u25A0 \u4E3B\u8981 API\n      ----------\n      - locate(x)\
    \        : x \u3092\u542B\u3080\u533A\u9593\u306E iterator \u3092\u8FD4\u3059\uFF08\
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
    \ nd.v << \" \";\n            }\n            return os;\n        }\n    };\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <functional>\n\
    #include <iterator>\n#include <ostream>\n#include <set>\n#include <tuple>\n#include\
    \ <type_traits>\n#include <utility>\n#include <vector>\n\nnamespace yesantikiss\
    \ {\n    using std::distance;\n    using std::max;\n    using std::min;\n    using\
    \ std::next;\n    using std::ostream;\n    using std::prev;\n    using std::set;\n\
    \    using std::vector;\n    /*\n      IntervalMap\uFF08\u533A\u9593 map / \u533A\
    \u9593 set \u7BA1\u7406\uFF1A\u5B8C\u6210\u5F62\uFF09\n      ==============================================\n\
    \      \u534A\u958B\u533A\u9593 [l, r) \u3092 set \u3067\u7BA1\u7406\u3057\u3001\
    \u5404\u533A\u9593\u306B\u5024 v \u3092\u6301\u305F\u305B\u308B\u3002\n    \n\
    \      \u25A0 \u4E0D\u5909\u91CF\uFF08\u3053\u308C\u304C\u5D29\u308C\u306A\u3044\
    \u3088\u3046\u306B\u5B9F\u88C5\u3059\u308B\uFF09\n      ----------------------------------------\n\
    \      1) \u533A\u9593\u306F\u4E92\u3044\u306B\u4EA4\u5DEE\u3057\u306A\u3044\n\
    \      2) \u5E38\u306B [L, R) \u3092\u5B8C\u5168\u306B\u88AB\u8986\u3057\u3066\
    \u3044\u308B\uFF08init \u3067 1 \u672C\u5165\u308C\u3066\u958B\u59CB\uFF09\n \
    \     3) \u96A3\u63A5\u3057\u3066\u5024\u304C\u540C\u3058\u533A\u9593\u306F\u5B58\
    \u5728\u3057\u306A\u3044\uFF08\u81EA\u52D5\u30DE\u30FC\u30B8\u3067\u6F70\u3059\
    \uFF09\n    \n      \u25A0 \u4E3B\u8981 API\n      ----------\n      - locate(x)\
    \        : x \u3092\u542B\u3080\u533A\u9593\u306E iterator \u3092\u8FD4\u3059\uFF08\
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
    \ nd.v << \" \";\n            }\n            return os;\n        }\n    };\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/interval_map.hpp
  requiredBy:
  - tests/test.cpp
  timestamp: '2026-08-04 23:10:17+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: ds/interval_map.hpp
layout: document
title: "\u533A\u9593 map"
---

## 概要

`yesantikiss::IntervalMap<T, V>` は `[L, R)` を値付き半開区間の集合として
管理します。管理区間を常に完全被覆し、隣接する同値区間を自動で併合します。

## API

- `IntervalMap(L, R, init)`: 全区間を値 `init` で初期化します。
- `locate(x)`: `x` を含む区間の iterator を返します。
- `get_val(x)`: 点 `x` の値を返します。
- `assign(l, r, v)`: `[l, r)` を `v` に置き換えます。
- `apply(l, r, f)`: 各交差区間の値を `f` で変換します。`f(v)` と
  `f(l, r, v)` の両形式を利用できます。
- `enumerate_cut(l, r, f)`: `[l, r)` の端で切り揃えて各区間を列挙します。
- `segments_cut(l, r)`: 列挙結果を `std::vector<Node>` で返します。

`assign`、`apply`、`enumerate_cut` には `add(l, r, v)` と `del(l, r, v)` を
受け取る版もあり、区間ごとの外部集計を同期できます。

## 要件・注意

- 構築時に `L < R` が必要です。`locate` と `get_val` は `L <= x < R` に限ります。
- 更新・列挙の区間は `[L, R)` との共通部分へ自動的に切り詰められます。
- `T` は順序付けと区間端の比較、`V` は等値比較に対応する必要があります。
- 更新により iterator が無効になるため、更新後は `locate` などで取り直してください。
- コールバック版の構築時には初期区間への `add` は呼ばれません。外部集計には
  初期区間の寄与をあらかじめ入れてください。
- `enumerate_cut` も内部では一時的に分割・併合するため、コールバックが
  呼ばれることがあります。

## 計算量

現在の区間数を `M`、処理対象の区間数を `K` とすると、代表的な操作は
`O(log M + K log M)` 程度です。保持メモリは `O(M)` です。
