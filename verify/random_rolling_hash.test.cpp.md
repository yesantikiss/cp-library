---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash.hpp
    title: Rolling Hash
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
  bundledCode: "#line 1 \"verify/random_rolling_hash.test.cpp\"\n// \u7D20\u6734\u306A\
    \u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\u30E9\u30F3\u30C0\u30E0\
    \u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089 A + B \u3092\u89E3\u304F\
    \u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <cstdlib>\n#include <iostream>\n#include\
    \ <random>\n#include <string>\n#include <vector>\n\n#line 2 \"string/rolling_hash.hpp\"\
    \n\n#line 7 \"string/rolling_hash.hpp\"\n#include <type_traits>\n#line 9 \"string/rolling_hash.hpp\"\
    \n\nnamespace yesantikiss {\n    struct RollingHash {\n        using ull = unsigned\
    \ long long;\n        static constexpr ull MOD = (1ULL << 61) - 1;\n    \n   \
    \     // \u5171\u6709\u8CC7\u6E90\uFF08\u5168\u30A4\u30F3\u30B9\u30BF\u30F3\u30B9\
    \u3067\u5171\u901A\uFF09\n        inline static ull base = 0;\n        inline\
    \ static std::vector<ull> pow_base;\n    \n        std::vector<ull> hash;  //\
    \ hash[i] = S[0..i) \u306E\u30CF\u30C3\u30B7\u30E5\n        int n = 0;\n    \n\
    \        // 2^61-1 \u7528\u306E\u6F14\u7B97\n        static inline ull add(ull\
    \ a, ull b) {\n            ull c = a + b;\n            if (c >= MOD) c -= MOD;\n\
    \            return c;\n        }\n        static inline ull mul(ull a, ull b)\
    \ {\n            unsigned __int128 t = (unsigned __int128)a * b;\n           \
    \ ull res = (ull)(t >> 61) + ((ull)t & MOD);\n            if (res >= MOD) res\
    \ -= MOD;\n            return res;\n        }\n    \n        static void init_base()\
    \ {\n            if (base != 0) return;\n            std::mt19937_64 rng(std::random_device{}());\n\
    \            std::uniform_int_distribution<ull> dist(1ULL, MOD - 1);\n       \
    \     base = dist(rng);\n            pow_base = {1};  // pow_base[0] = 1\n   \
    \     }\n    \n        static void ensure_pow(int len) {\n            if ((int)pow_base.size()\
    \ >= len + 1) return;\n            int cur = (int)pow_base.size();\n         \
    \   pow_base.resize(len + 1);\n            for (int i = cur; i <= len; ++i) {\n\
    \                pow_base[i] = mul(pow_base[i - 1], base);\n            }\n  \
    \      }\n    \n        // base^len\u3002\u30C6\u30FC\u30D6\u30EB\u306B\u3042\u308C\
    \u3070\u5F15\u304D\u3001\u306A\u3051\u308C\u3070\u7E70\u308A\u8FD4\u3057\u4E8C\
    \u4E57\u6CD5\u3067\u6C42\u3081\u308B\uFF08\u30C6\u30FC\u30D6\u30EB\u306F\u4F38\
    \u3070\u3055\u306A\u3044\uFF09\n        static ull pow_of(long long len) {\n \
    \           assert(len >= 0);\n            if (len < (long long)pow_base.size())\
    \ return pow_base[len];\n            ull res = 1, x = base;\n            for (ull\
    \ e = (ull)len; e > 0; e >>= 1) {\n                if (e & 1) res = mul(res, x);\n\
    \                x = mul(x, x);\n            }\n            return res;\n    \
    \    }\n\n        // \u8981\u7D20\u3092 [1, MOD) \u306E\u5024\u306B\u5909\u63DB\
    \u3059\u308B\u3002\u5358\u5C04\u3067\u5927\u5C0F\u306E\u9806\u3092\u4FDD\u3064\
    \n        // \u6587\u5B57\u306F (unsigned char)c + 1\n        static ull code(char\
    \ c) { return (ull)(unsigned char)c + 1; }\n        // \u6574\u6570\u306F x +\
    \ 2^60\u3002|x| <= 2^60 - 2 \u304C\u5FC5\u8981\n        static constexpr long\
    \ long INT_LIMIT = (1LL << 60) - 2;\n        template <class T, std::enable_if_t<std::is_integral_v<T>\
    \ && !std::is_same_v<T, char>,\n                                            std::nullptr_t>\
    \ = nullptr>\n        static ull code(T x) {\n            if constexpr (std::is_signed_v<T>)\
    \ {\n                assert(-INT_LIMIT <= (long long)x && (long long)x <= INT_LIMIT);\n\
    \            } else {\n                assert((unsigned long long)x <= (unsigned\
    \ long long)INT_LIMIT);\n            }\n            return (ull)((long long)x\
    \ + (1LL << 60));\n        }\n\n        // hash(A + B) \u3092 hash(A), hash(B),\
    \ |B| \u304B\u3089\u6C42\u3081\u308B\n        // \u30C6\u30FC\u30D6\u30EB\u3092\
    \u4F38\u3070\u3059\u306E\u306F build \u3060\u3051\u306A\u306E\u3067\u3001\u9577\
    \u3044\u30CF\u30C3\u30B7\u30E5\u3092\u7D44\u307F\u7ACB\u3066\u3066\u3082\u30E1\
    \u30E2\u30EA\u306F\u5897\u3048\u306A\u3044\n        static ull concat(ull h1,\
    \ ull h2, long long len2) {\n            assert(len2 >= 0);\n            init_base();\n\
    \            return add(mul(h1, pow_of(len2)), h2);\n        }\n\n        // \u9577\
    \u3055\u4ED8\u304D\u306E\u30CF\u30C3\u30B7\u30E5\u5024\u3002+ \u3067\u6587\u5B57\
    \u5217\u306E\u9023\u7D50\u306B\u5BFE\u5FDC\u3059\u308B\u30CF\u30C3\u30B7\u30E5\
    \u304C\u5F97\u3089\u308C\u308B\n        // \u65E2\u5B9A\u5024\u306F\u7A7A\u6587\
    \u5B57\u5217\uFF08+ \u306E\u5358\u4F4D\u5143\uFF09\n        struct Hash {\n  \
    \          ull val = 0;\n            long long len = 0;  // \u7E70\u308A\u8FD4\
    \u3057\u4E8C\u4E57\u6CD5\u3067\u9023\u7D50\u3059\u308C\u3070 10^18 \u7A0B\u5EA6\
    \u306E\u9577\u3055\u3082\u6271\u3048\u308B\n\n            Hash() = default;\n\
    \            Hash(ull val, long long len) : val(val), len(len) {}\n          \
    \  // 1 \u8981\u7D20 / \u5217\u5168\u4F53\u306E\u30CF\u30C3\u30B7\u30E5\uFF08\
    prefix hash \u3092\u6301\u305F\u305A\u306B\u6C42\u3081\u308B\uFF09\n         \
    \   explicit Hash(char c) : val(code(c)), len(1) { init_base(); }\n          \
    \  template <class T, std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T,\
    \ char>,\n                                                std::nullptr_t> = nullptr>\n\
    \            explicit Hash(T x) : val(code(x)), len(1) { init_base(); }\n    \
    \        explicit Hash(const std::string &s) { assign(s); }\n            template\
    \ <class T>\n            explicit Hash(const std::vector<T> &s) { assign(s); }\n\
    \n          private:\n            template <class Seq>\n            void assign(const\
    \ Seq &s) {\n                init_base();\n                len = (long long)s.size();\n\
    \                for (size_t i = 0; i < s.size(); ++i) {\n                   \
    \ val = add(mul(val, base), code((typename Seq::value_type)s[i]));\n         \
    \       }\n            }\n\n          public:\n\n            friend Hash operator+(const\
    \ Hash &a, const Hash &b) {\n                return {concat(a.val, b.val, b.len),\
    \ a.len + b.len};\n            }\n            Hash &operator+=(const Hash &o)\
    \ { return *this = *this + o; }\n            friend bool operator==(const Hash\
    \ &a, const Hash &b) {\n                return a.val == b.val && a.len == b.len;\n\
    \            }\n            friend bool operator!=(const Hash &a, const Hash &b)\
    \ { return !(a == b); }\n        };\n\n        RollingHash() : n(0) {}\n    \n\
    \        RollingHash(const std::string &s) {\n            build(s);\n        }\n\
    \        // \u6574\u6570\u306E\u5217\u3002\u5404\u8981\u7D20\u306F |x| <= 2^60\
    \ - 2\n        template <class T>\n        RollingHash(const std::vector<T> &s)\
    \ {\n            build(s);\n        }\n    \n        void build(const std::string\
    \ &s) { build_impl(s); }\n        template <class T>\n        void build(const\
    \ std::vector<T> &s) { build_impl(s); }\n    \n        template <class Seq>\n\
    \        void build_impl(const Seq &s) {\n            init_base();\n         \
    \   n = (int)s.size();\n            ensure_pow(n);\n            hash.assign(n\
    \ + 1, 0);\n            for (int i = 0; i < n; ++i) {\n                hash[i\
    \ + 1] = add(mul(hash[i], base), code((typename Seq::value_type)s[i]));\n    \
    \        }\n        }\n\n        // S[l..r) \u306E\u30CF\u30C3\u30B7\u30E5\u3092\
    \u53D6\u5F97\n        ull get(int l, int r) const {\n            assert(0 <= l\
    \ && l <= r && r <= n);\n            ull res = hash[r] + MOD - mul(hash[l], pow_base[r\
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
    \u304C\u5927\u304D\u3044\uFF08std::string::compare, std::vector \u306E < \u3068\
    \u540C\u3058\u9806\u5E8F\uFF09\n        static int compare(const RollingHash &a,\
    \ int l1, int r1, const RollingHash &b, int l2, int r2) {\n            int len1\
    \ = r1 - l1, len2 = r2 - l2;\n            int k = lcp(a, l1, r1, b, l2, r2);\n\
    \            if (k == len1 || k == len2) return (len1 > len2) - (len1 < len2);\n\
    \            // \u9577\u3055 1 \u306E\u30CF\u30C3\u30B7\u30E5\u306F code(\u8981\
    \u7D20) \u305D\u306E\u3082\u306E\n            ull c1 = a.get(l1 + k, l1 + k +\
    \ 1), c2 = b.get(l2 + k, l2 + k + 1);\n            return (c1 > c2) - (c1 < c2);\n\
    \        }\n        int compare(int l1, int r1, int l2, int r2) const {\n    \
    \        return compare(*this, l1, r1, *this, l2, r2);\n        }\n    };\n  \
    \  \n}\n#line 13 \"verify/random_rolling_hash.test.cpp\"\n\nnamespace {\n    using\
    \ yesantikiss::RollingHash;\n    using Hash = RollingHash::Hash;\n    using ull\
    \ = RollingHash::ull;\n\n    std::mt19937_64 random_engine(20261112);\n\n    int\
    \ random_int(int lo, int hi) {\n        return std::uniform_int_distribution<int>(lo,\
    \ hi)(random_engine);\n    }\n\n    long long random_ll(long long lo, long long\
    \ hi) {\n        return std::uniform_int_distribution<long long>(lo, hi)(random_engine);\n\
    \    }\n\n    // h \u3092 k \u56DE\u7E70\u308A\u8FD4\u3057\u305F\u30CF\u30C3\u30B7\
    \u30E5\uFF08\u7E70\u308A\u8FD4\u3057\u4E8C\u4E57\u6CD5\u3067\u9023\u7D50\u3059\
    \u308B\uFF09\n    Hash repeat(Hash h, long long k) {\n        Hash res;\n    \
    \    for (; k > 0; k >>= 1, h = h + h) {\n            if (k & 1) res = res + h;\n\
    \        }\n        return res;\n    }\n\n    std::string random_string(int n,\
    \ int sigma) {\n        std::string s(n, 'a');\n        for (char &c : s) c =\
    \ char('a' + random_int(0, sigma - 1));\n        return s;\n    }\n\n    ull naive_pow(int\
    \ len) {\n        ull res = 1;\n        for (int i = 0; i < len; ++i) res = RollingHash::mul(res,\
    \ RollingHash::base);\n        return res;\n    }\n\n    // \u30C6\u30FC\u30D6\
    \u30EB\u5916\u306E\u7D2F\u4E57\u306F\u7D20\u6734\u306A\u639B\u3051\u7B97\u3068\
    \u4E00\u81F4\u3059\u308B\n    void test_pow_of() {\n        RollingHash::init_base();\n\
    \        for (int len = 0; len <= 3000; ++len) assert(RollingHash::pow_of(len)\
    \ == naive_pow(len));\n        for (int iter = 0; iter < 200; ++iter) {\n    \
    \        long long a = random_ll(0, 1LL << 61), b = random_ll(0, 1LL << 61);\n\
    \            assert(RollingHash::pow_of(a + b) ==\n                   RollingHash::mul(RollingHash::pow_of(a),\
    \ RollingHash::pow_of(b)));\n        }\n    }\n\n    // \u5B9F\u969B\u306E\u6587\
    \u5B57\u5217\u3092\u9023\u7D50\u3057\u305F\u30CF\u30C3\u30B7\u30E5\u3068\u4E00\
    \u81F4\u3059\u308B\uFF08\u30C6\u30FC\u30D6\u30EB\u3088\u308A\u9577\u3044\u53F3\
    \u5074\u3092\u542B\u3080\uFF09\n    void test_concat_matches_string() {\n    \
    \    for (int iter = 0; iter < 300; ++iter) {\n            int k = random_int(1,\
    \ 6);\n            std::vector<std::string> parts(k);\n            Hash acc;\n\
    \            std::string whole;\n            for (auto &p : parts) {\n       \
    \         p = random_string(random_int(0, 2000), random_int(1, 3));\n        \
    \        acc += Hash(p);\n                whole += p;\n            }\n       \
    \     assert(acc == Hash(whole));\n            RollingHash rh(whole);\n      \
    \      assert(acc == rh.slice(0, (int)whole.size()));\n            // build \u6E08\
    \u307F\u306E\u30C6\u30FC\u30D6\u30EB\u3092\u4F7F\u3046 slice \u3068\u306E\u9023\
    \u7D50\u3082\u4E00\u81F4\u3059\u308B\n            int l = random_int(0, (int)whole.size()),\
    \ r = random_int(l, (int)whole.size());\n            int m = random_int(l, r);\n\
    \            assert(rh.slice(l, m) + rh.slice(m, r) == rh.slice(l, r));\n    \
    \        assert(rh.slice(l, m) + Hash(whole.substr(m, r - m)) == rh.slice(l, r));\n\
    \        }\n    }\n\n    // \u9577\u3044\u30CF\u30C3\u30B7\u30E5\u306E\u7D44\u307F\
    \u7ACB\u3066\u3067\u30C6\u30FC\u30D6\u30EB\u304C\u4F38\u3073\u305A\u3001\u7D50\
    \u5408\u6CD5\u5247\u304C\u6210\u308A\u7ACB\u3064\n    void test_long_concat_memory()\
    \ {\n        RollingHash rh(random_string(100, 26));\n        const size_t table\
    \ = RollingHash::pow_base.size();\n        Hash h('a');\n        for (int i =\
    \ 0; i < 29; ++i) h = h + h;  // \u9577\u3055 2^29\n        assert(h.len == 1\
    \ << 29);\n        assert(RollingHash::pow_base.size() == table);\n\n        std::vector<Hash>\
    \ pieces = {Hash('x'), h, Hash(std::string(\"abc\")), rh.slice(3, 50)};\n    \
    \    for (int i = 0; i < 6; ++i) pieces.push_back(pieces[random_int(0, (int)pieces.size()\
    \ - 1)] + Hash('q'));\n        for (int iter = 0; iter < 2000; ++iter) {\n   \
    \         const Hash &a = pieces[random_int(0, (int)pieces.size() - 1)];\n   \
    \         const Hash &b = pieces[random_int(0, (int)pieces.size() - 1)];\n   \
    \         const Hash &c = pieces[random_int(0, (int)pieces.size() - 1)];\n   \
    \         if ((long long)a.len + b.len + c.len > (1 << 30)) continue;\n      \
    \      assert((a + b) + c == a + (b + c));\n        }\n        // 2^29 \u500B\u306E\
    \ 'a' \u3092 2 \u9032\u6570\u306E\u5404\u6841\u306E\u9577\u3055\u306B\u5206\u3051\
    \u3066\u4F5C\u3063\u3066\u3082\u4E00\u81F4\u3059\u308B\n        Hash g, p('a');\n\
    \        for (int bit = 0; bit < 30; ++bit, p = p + p) {\n            if (((1\
    \ << 29) - 1) >> bit & 1) g = g + p;\n        }\n        assert(g + Hash('a')\
    \ == h);\n        // \u6587\u5B57\u5217\u304B\u3089\u4F5C\u3063\u305F\u9577\u3055\
    \ 2^20 \u306E\u30CF\u30C3\u30B7\u30E5\u3068\u3082\u4E00\u81F4\u3059\u308B\n  \
    \      Hash x('a');\n        for (int i = 0; i < 20; ++i) x = x + x;\n       \
    \ assert(x == Hash(std::string(1 << 20, 'a')));\n        assert(RollingHash::pow_base.size()\
    \ == table);\n    }\n\n    // 10^18 \u8FD1\u304F\u306E\u9577\u3055\u3067\u3082\
    \u9023\u7D50\u304C\u6574\u5408\u3057\u3001\u30C6\u30FC\u30D6\u30EB\u306F\u4F38\
    \u3073\u306A\u3044\n    void test_huge_repeat() {\n        const size_t table\
    \ = RollingHash::pow_base.size();\n        for (int iter = 0; iter < 300; ++iter)\
    \ {\n            std::string s = random_string(random_int(1, 5), random_int(1,\
    \ 2));\n            Hash hs(s);\n            long long a = random_ll(0, 100000000000000000LL),\
    \ b = random_ll(0, 100000000000000000LL);\n            Hash ra = repeat(hs, a),\
    \ rb = repeat(hs, b);\n            assert(ra.len == a * (long long)s.size());\n\
    \            assert(ra + rb == repeat(hs, a + b));\n            assert(ra + rb\
    \ == rb + ra);\n            // (s \u3092 2 \u56DE\u4E26\u3079\u305F\u3082\u306E\
    ) \u3092 k \u56DE == s \u3092 2k \u56DE\n            long long k = random_ll(0,\
    \ 100000000000000000LL);\n            assert(repeat(Hash(s + s), k) == repeat(hs,\
    \ 2 * k));\n            // \u77ED\u3044\u5834\u5408\u306F\u5B9F\u969B\u306E\u6587\
    \u5B57\u5217\u3068\u4E00\u81F4\u3059\u308B\n            int c = random_int(0,\
    \ 300);\n            std::string rep;\n            for (int i = 0; i < c; ++i)\
    \ rep += s;\n            assert(repeat(hs, c) == Hash(rep));\n            // 1\
    \ \u6587\u5B57\u9055\u3044\u306E\u6587\u5B57\u5217\u3092\u7E70\u308A\u8FD4\u3059\
    \u3068\u4E00\u81F4\u3057\u306A\u3044\n            std::string t = s;\n       \
    \     t[random_int(0, (int)t.size() - 1)] ^= 1;\n            long long m = random_ll(1,\
    \ 100000000000000000LL);\n            assert(repeat(hs, m) != repeat(Hash(t),\
    \ m));\n        }\n        assert(RollingHash::pow_base.size() == table);\n  \
    \  }\n\n    constexpr long long LIM = RollingHash::INT_LIMIT;\n\n    // \u5024\
    \u306E\u7A2E\u985E\u304C\u5C11\u306A\u3044\u5217\u3068\u3001\u5883\u754C\u4ED8\
    \u8FD1\u306E\u5024\u3092\u542B\u3080\u5217\u3092\u4F5C\u308B\n    std::vector<long\
    \ long> random_ll_vector(int n) {\n        std::vector<long long> pool;\n    \
    \    int kind = random_int(0, 3);\n        if (kind == 0) pool = {0};\n      \
    \  else if (kind == 1) pool = {-1, 0, 7};  // \u7D20\u6734\u306B ull \u306B\u3059\
    \u308B\u3068\u885D\u7A81\u3059\u308B\u7D44\n        else if (kind == 2) pool =\
    \ {-LIM, -LIM + 1, LIM - 1, LIM, 0};\n        else for (int i = 0; i < 3; ++i)\
    \ pool.push_back(random_ll(-LIM, LIM));\n        std::vector<long long> a(n);\n\
    \        for (auto &x : a) x = pool[random_int(0, (int)pool.size() - 1)];\n  \
    \      return a;\n    }\n\n    int naive_compare(const std::vector<long long>\
    \ &x, const std::vector<long long> &y) {\n        return (y < x) - (x < y);\n\
    \    }\n\n    // \u6574\u6570\u5217\u306E\u4E00\u81F4\u30FBlcp\u30FB\u8F9E\u66F8\
    \u9806\u6BD4\u8F03\u304C\u7D20\u6734\u306A\u6BD4\u8F03\u3068\u4E00\u81F4\u3059\
    \u308B\n    void test_vector_matches_naive() {\n        for (int iter = 0; iter\
    \ < 300; ++iter) {\n            std::vector<long long> a = random_ll_vector(random_int(0,\
    \ 30));\n            std::vector<long long> b = random_int(0, 1) ? a : random_ll_vector(random_int(0,\
    \ 30));\n            if (!b.empty() && random_int(0, 1)) b[random_int(0, (int)b.size()\
    \ - 1)] = random_ll(-LIM, LIM);\n            RollingHash ra(a), rb(b);\n     \
    \       const int n = (int)a.size(), m = (int)b.size();\n            for (int\
    \ q = 0; q < 300; ++q) {\n                int l1 = random_int(0, n), r1 = random_int(l1,\
    \ n);\n                int l2 = random_int(0, m), r2 = random_int(l2, m);\n  \
    \              std::vector<long long> x(a.begin() + l1, a.begin() + r1), y(b.begin()\
    \ + l2, b.begin() + r2);\n                int k = 0;\n                while (k\
    \ < (int)x.size() && k < (int)y.size() && x[k] == y[k]) ++k;\n               \
    \ assert(RollingHash::lcp(ra, l1, r1, rb, l2, r2) == k);\n                assert(RollingHash::compare(ra,\
    \ l1, r1, rb, l2, r2) == naive_compare(x, y));\n                assert((ra.slice(l1,\
    \ r1) == rb.slice(l2, r2)) == (x == y));\n                assert(ra.slice(l1,\
    \ r1) == Hash(x));\n                int l3 = random_int(0, n), r3 = random_int(l3,\
    \ n);\n                std::vector<long long> z(a.begin() + l3, a.begin() + r3);\n\
    \                assert(ra.equals(l1, r1, l3, r3) == (x == z));\n            }\n\
    \            Hash acc;\n            for (long long x : a) acc += Hash(x);\n  \
    \          assert(acc == Hash(a) && acc == ra.slice(0, n));\n        }\n    }\n\
    \n    // 0 \u3060\u3051\u306E\u5217\u306F\u9577\u3055\u3067\u533A\u5225\u3067\u304D\
    \u3001\u578B\u304C\u9055\u3063\u3066\u3082\u540C\u3058\u5024\u306A\u3089\u540C\
    \u3058\u30CF\u30C3\u30B7\u30E5\u306B\u306A\u308B\n    void test_vector_types()\
    \ {\n        for (int len = 0; len <= 50; ++len) {\n            RollingHash z(std::vector<int>(len,\
    \ 0));\n            for (int len2 = 0; len2 < len; ++len2) {\n               \
    \ assert(z.get(0, len) != z.get(0, len2));\n                assert(Hash(std::vector<int>(len,\
    \ 0)) != Hash(std::vector<int>(len2, 0)));\n            }\n        }\n       \
    \ for (int iter = 0; iter < 300; ++iter) {\n            int n = random_int(0,\
    \ 20);\n            std::vector<int> vi(n);\n            for (int &x : vi) x =\
    \ random_int(-1000000000, 1000000000);\n            std::vector<long long> vl(vi.begin(),\
    \ vi.end());\n            std::vector<short> vs(n);\n            for (int i =\
    \ 0; i < n; ++i) vs[i] = (short)(vi[i] % 30000);\n            std::vector<long\
    \ long> vsl(vs.begin(), vs.end());\n            assert(Hash(vi) == Hash(vl));\n\
    \            assert(RollingHash(vi).get(0, n) == RollingHash(vl).get(0, n));\n\
    \            assert(Hash(vs) == Hash(vsl));\n            std::vector<unsigned>\
    \ vu(n);\n            for (int i = 0; i < n; ++i) vu[i] = (unsigned)std::abs(vi[i]);\n\
    \            std::vector<long long> vul(vu.begin(), vu.end());\n            assert(Hash(vu)\
    \ == Hash(vul));\n            std::vector<unsigned long long> vull(vu.begin(),\
    \ vu.end());\n            assert(RollingHash(vull).get(0, n) == RollingHash(vul).get(0,\
    \ n));\n            std::vector<bool> vb(n);\n            std::vector<int> vbi(n);\n\
    \            for (int i = 0; i < n; ++i) vbi[i] = vb[i] = random_int(0, 1);\n\
    \            assert(Hash(vb) == Hash(vbi) && RollingHash(vb).slice(0, n) == Hash(vbi));\n\
    \            // vector<char> \u306F string \u3068\u540C\u3058\n            std::string\
    \ s = random_string(n, 26);\n            std::vector<char> vc(s.begin(), s.end());\n\
    \            assert(Hash(vc) == Hash(s) && RollingHash(vc).get(0, n) == RollingHash(s).get(0,\
    \ n));\n        }\n        // \u5883\u754C\u306E\u5024\u3068\u3001\u7D20\u6734\
    \u306B ull \u306B\u3059\u308B\u3068\u885D\u7A81\u3059\u308B\u7D44\n        std::vector<long\
    \ long> v = {-LIM, -LIM + 1, -1, 0, 7, LIM - 1, LIM};\n        RollingHash rv(v);\n\
    \        for (int i = 0; i < (int)v.size(); ++i) {\n            for (int j = 0;\
    \ j < (int)v.size(); ++j) {\n                assert((rv.get(i, i + 1) == rv.get(j,\
    \ j + 1)) == (i == j));\n                assert(rv.compare(i, i + 1, j, j + 1)\
    \ == (i > j) - (i < j));\n            }\n        }\n    }\n}  // namespace\n\n\
    int main() {\n    test_pow_of();\n    test_concat_matches_string();\n    test_long_concat_memory();\n\
    \    test_huge_repeat();\n    test_vector_matches_naive();\n    test_vector_types();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "// \u7D20\u6734\u306A\u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\
    \u30E9\u30F3\u30C0\u30E0\u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089\
    \ A + B \u3092\u89E3\u304F\u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cstdlib>\n#include <iostream>\n\
    #include <random>\n#include <string>\n#include <vector>\n\n#include \"string/rolling_hash.hpp\"\
    \n\nnamespace {\n    using yesantikiss::RollingHash;\n    using Hash = RollingHash::Hash;\n\
    \    using ull = RollingHash::ull;\n\n    std::mt19937_64 random_engine(20261112);\n\
    \n    int random_int(int lo, int hi) {\n        return std::uniform_int_distribution<int>(lo,\
    \ hi)(random_engine);\n    }\n\n    long long random_ll(long long lo, long long\
    \ hi) {\n        return std::uniform_int_distribution<long long>(lo, hi)(random_engine);\n\
    \    }\n\n    // h \u3092 k \u56DE\u7E70\u308A\u8FD4\u3057\u305F\u30CF\u30C3\u30B7\
    \u30E5\uFF08\u7E70\u308A\u8FD4\u3057\u4E8C\u4E57\u6CD5\u3067\u9023\u7D50\u3059\
    \u308B\uFF09\n    Hash repeat(Hash h, long long k) {\n        Hash res;\n    \
    \    for (; k > 0; k >>= 1, h = h + h) {\n            if (k & 1) res = res + h;\n\
    \        }\n        return res;\n    }\n\n    std::string random_string(int n,\
    \ int sigma) {\n        std::string s(n, 'a');\n        for (char &c : s) c =\
    \ char('a' + random_int(0, sigma - 1));\n        return s;\n    }\n\n    ull naive_pow(int\
    \ len) {\n        ull res = 1;\n        for (int i = 0; i < len; ++i) res = RollingHash::mul(res,\
    \ RollingHash::base);\n        return res;\n    }\n\n    // \u30C6\u30FC\u30D6\
    \u30EB\u5916\u306E\u7D2F\u4E57\u306F\u7D20\u6734\u306A\u639B\u3051\u7B97\u3068\
    \u4E00\u81F4\u3059\u308B\n    void test_pow_of() {\n        RollingHash::init_base();\n\
    \        for (int len = 0; len <= 3000; ++len) assert(RollingHash::pow_of(len)\
    \ == naive_pow(len));\n        for (int iter = 0; iter < 200; ++iter) {\n    \
    \        long long a = random_ll(0, 1LL << 61), b = random_ll(0, 1LL << 61);\n\
    \            assert(RollingHash::pow_of(a + b) ==\n                   RollingHash::mul(RollingHash::pow_of(a),\
    \ RollingHash::pow_of(b)));\n        }\n    }\n\n    // \u5B9F\u969B\u306E\u6587\
    \u5B57\u5217\u3092\u9023\u7D50\u3057\u305F\u30CF\u30C3\u30B7\u30E5\u3068\u4E00\
    \u81F4\u3059\u308B\uFF08\u30C6\u30FC\u30D6\u30EB\u3088\u308A\u9577\u3044\u53F3\
    \u5074\u3092\u542B\u3080\uFF09\n    void test_concat_matches_string() {\n    \
    \    for (int iter = 0; iter < 300; ++iter) {\n            int k = random_int(1,\
    \ 6);\n            std::vector<std::string> parts(k);\n            Hash acc;\n\
    \            std::string whole;\n            for (auto &p : parts) {\n       \
    \         p = random_string(random_int(0, 2000), random_int(1, 3));\n        \
    \        acc += Hash(p);\n                whole += p;\n            }\n       \
    \     assert(acc == Hash(whole));\n            RollingHash rh(whole);\n      \
    \      assert(acc == rh.slice(0, (int)whole.size()));\n            // build \u6E08\
    \u307F\u306E\u30C6\u30FC\u30D6\u30EB\u3092\u4F7F\u3046 slice \u3068\u306E\u9023\
    \u7D50\u3082\u4E00\u81F4\u3059\u308B\n            int l = random_int(0, (int)whole.size()),\
    \ r = random_int(l, (int)whole.size());\n            int m = random_int(l, r);\n\
    \            assert(rh.slice(l, m) + rh.slice(m, r) == rh.slice(l, r));\n    \
    \        assert(rh.slice(l, m) + Hash(whole.substr(m, r - m)) == rh.slice(l, r));\n\
    \        }\n    }\n\n    // \u9577\u3044\u30CF\u30C3\u30B7\u30E5\u306E\u7D44\u307F\
    \u7ACB\u3066\u3067\u30C6\u30FC\u30D6\u30EB\u304C\u4F38\u3073\u305A\u3001\u7D50\
    \u5408\u6CD5\u5247\u304C\u6210\u308A\u7ACB\u3064\n    void test_long_concat_memory()\
    \ {\n        RollingHash rh(random_string(100, 26));\n        const size_t table\
    \ = RollingHash::pow_base.size();\n        Hash h('a');\n        for (int i =\
    \ 0; i < 29; ++i) h = h + h;  // \u9577\u3055 2^29\n        assert(h.len == 1\
    \ << 29);\n        assert(RollingHash::pow_base.size() == table);\n\n        std::vector<Hash>\
    \ pieces = {Hash('x'), h, Hash(std::string(\"abc\")), rh.slice(3, 50)};\n    \
    \    for (int i = 0; i < 6; ++i) pieces.push_back(pieces[random_int(0, (int)pieces.size()\
    \ - 1)] + Hash('q'));\n        for (int iter = 0; iter < 2000; ++iter) {\n   \
    \         const Hash &a = pieces[random_int(0, (int)pieces.size() - 1)];\n   \
    \         const Hash &b = pieces[random_int(0, (int)pieces.size() - 1)];\n   \
    \         const Hash &c = pieces[random_int(0, (int)pieces.size() - 1)];\n   \
    \         if ((long long)a.len + b.len + c.len > (1 << 30)) continue;\n      \
    \      assert((a + b) + c == a + (b + c));\n        }\n        // 2^29 \u500B\u306E\
    \ 'a' \u3092 2 \u9032\u6570\u306E\u5404\u6841\u306E\u9577\u3055\u306B\u5206\u3051\
    \u3066\u4F5C\u3063\u3066\u3082\u4E00\u81F4\u3059\u308B\n        Hash g, p('a');\n\
    \        for (int bit = 0; bit < 30; ++bit, p = p + p) {\n            if (((1\
    \ << 29) - 1) >> bit & 1) g = g + p;\n        }\n        assert(g + Hash('a')\
    \ == h);\n        // \u6587\u5B57\u5217\u304B\u3089\u4F5C\u3063\u305F\u9577\u3055\
    \ 2^20 \u306E\u30CF\u30C3\u30B7\u30E5\u3068\u3082\u4E00\u81F4\u3059\u308B\n  \
    \      Hash x('a');\n        for (int i = 0; i < 20; ++i) x = x + x;\n       \
    \ assert(x == Hash(std::string(1 << 20, 'a')));\n        assert(RollingHash::pow_base.size()\
    \ == table);\n    }\n\n    // 10^18 \u8FD1\u304F\u306E\u9577\u3055\u3067\u3082\
    \u9023\u7D50\u304C\u6574\u5408\u3057\u3001\u30C6\u30FC\u30D6\u30EB\u306F\u4F38\
    \u3073\u306A\u3044\n    void test_huge_repeat() {\n        const size_t table\
    \ = RollingHash::pow_base.size();\n        for (int iter = 0; iter < 300; ++iter)\
    \ {\n            std::string s = random_string(random_int(1, 5), random_int(1,\
    \ 2));\n            Hash hs(s);\n            long long a = random_ll(0, 100000000000000000LL),\
    \ b = random_ll(0, 100000000000000000LL);\n            Hash ra = repeat(hs, a),\
    \ rb = repeat(hs, b);\n            assert(ra.len == a * (long long)s.size());\n\
    \            assert(ra + rb == repeat(hs, a + b));\n            assert(ra + rb\
    \ == rb + ra);\n            // (s \u3092 2 \u56DE\u4E26\u3079\u305F\u3082\u306E\
    ) \u3092 k \u56DE == s \u3092 2k \u56DE\n            long long k = random_ll(0,\
    \ 100000000000000000LL);\n            assert(repeat(Hash(s + s), k) == repeat(hs,\
    \ 2 * k));\n            // \u77ED\u3044\u5834\u5408\u306F\u5B9F\u969B\u306E\u6587\
    \u5B57\u5217\u3068\u4E00\u81F4\u3059\u308B\n            int c = random_int(0,\
    \ 300);\n            std::string rep;\n            for (int i = 0; i < c; ++i)\
    \ rep += s;\n            assert(repeat(hs, c) == Hash(rep));\n            // 1\
    \ \u6587\u5B57\u9055\u3044\u306E\u6587\u5B57\u5217\u3092\u7E70\u308A\u8FD4\u3059\
    \u3068\u4E00\u81F4\u3057\u306A\u3044\n            std::string t = s;\n       \
    \     t[random_int(0, (int)t.size() - 1)] ^= 1;\n            long long m = random_ll(1,\
    \ 100000000000000000LL);\n            assert(repeat(hs, m) != repeat(Hash(t),\
    \ m));\n        }\n        assert(RollingHash::pow_base.size() == table);\n  \
    \  }\n\n    constexpr long long LIM = RollingHash::INT_LIMIT;\n\n    // \u5024\
    \u306E\u7A2E\u985E\u304C\u5C11\u306A\u3044\u5217\u3068\u3001\u5883\u754C\u4ED8\
    \u8FD1\u306E\u5024\u3092\u542B\u3080\u5217\u3092\u4F5C\u308B\n    std::vector<long\
    \ long> random_ll_vector(int n) {\n        std::vector<long long> pool;\n    \
    \    int kind = random_int(0, 3);\n        if (kind == 0) pool = {0};\n      \
    \  else if (kind == 1) pool = {-1, 0, 7};  // \u7D20\u6734\u306B ull \u306B\u3059\
    \u308B\u3068\u885D\u7A81\u3059\u308B\u7D44\n        else if (kind == 2) pool =\
    \ {-LIM, -LIM + 1, LIM - 1, LIM, 0};\n        else for (int i = 0; i < 3; ++i)\
    \ pool.push_back(random_ll(-LIM, LIM));\n        std::vector<long long> a(n);\n\
    \        for (auto &x : a) x = pool[random_int(0, (int)pool.size() - 1)];\n  \
    \      return a;\n    }\n\n    int naive_compare(const std::vector<long long>\
    \ &x, const std::vector<long long> &y) {\n        return (y < x) - (x < y);\n\
    \    }\n\n    // \u6574\u6570\u5217\u306E\u4E00\u81F4\u30FBlcp\u30FB\u8F9E\u66F8\
    \u9806\u6BD4\u8F03\u304C\u7D20\u6734\u306A\u6BD4\u8F03\u3068\u4E00\u81F4\u3059\
    \u308B\n    void test_vector_matches_naive() {\n        for (int iter = 0; iter\
    \ < 300; ++iter) {\n            std::vector<long long> a = random_ll_vector(random_int(0,\
    \ 30));\n            std::vector<long long> b = random_int(0, 1) ? a : random_ll_vector(random_int(0,\
    \ 30));\n            if (!b.empty() && random_int(0, 1)) b[random_int(0, (int)b.size()\
    \ - 1)] = random_ll(-LIM, LIM);\n            RollingHash ra(a), rb(b);\n     \
    \       const int n = (int)a.size(), m = (int)b.size();\n            for (int\
    \ q = 0; q < 300; ++q) {\n                int l1 = random_int(0, n), r1 = random_int(l1,\
    \ n);\n                int l2 = random_int(0, m), r2 = random_int(l2, m);\n  \
    \              std::vector<long long> x(a.begin() + l1, a.begin() + r1), y(b.begin()\
    \ + l2, b.begin() + r2);\n                int k = 0;\n                while (k\
    \ < (int)x.size() && k < (int)y.size() && x[k] == y[k]) ++k;\n               \
    \ assert(RollingHash::lcp(ra, l1, r1, rb, l2, r2) == k);\n                assert(RollingHash::compare(ra,\
    \ l1, r1, rb, l2, r2) == naive_compare(x, y));\n                assert((ra.slice(l1,\
    \ r1) == rb.slice(l2, r2)) == (x == y));\n                assert(ra.slice(l1,\
    \ r1) == Hash(x));\n                int l3 = random_int(0, n), r3 = random_int(l3,\
    \ n);\n                std::vector<long long> z(a.begin() + l3, a.begin() + r3);\n\
    \                assert(ra.equals(l1, r1, l3, r3) == (x == z));\n            }\n\
    \            Hash acc;\n            for (long long x : a) acc += Hash(x);\n  \
    \          assert(acc == Hash(a) && acc == ra.slice(0, n));\n        }\n    }\n\
    \n    // 0 \u3060\u3051\u306E\u5217\u306F\u9577\u3055\u3067\u533A\u5225\u3067\u304D\
    \u3001\u578B\u304C\u9055\u3063\u3066\u3082\u540C\u3058\u5024\u306A\u3089\u540C\
    \u3058\u30CF\u30C3\u30B7\u30E5\u306B\u306A\u308B\n    void test_vector_types()\
    \ {\n        for (int len = 0; len <= 50; ++len) {\n            RollingHash z(std::vector<int>(len,\
    \ 0));\n            for (int len2 = 0; len2 < len; ++len2) {\n               \
    \ assert(z.get(0, len) != z.get(0, len2));\n                assert(Hash(std::vector<int>(len,\
    \ 0)) != Hash(std::vector<int>(len2, 0)));\n            }\n        }\n       \
    \ for (int iter = 0; iter < 300; ++iter) {\n            int n = random_int(0,\
    \ 20);\n            std::vector<int> vi(n);\n            for (int &x : vi) x =\
    \ random_int(-1000000000, 1000000000);\n            std::vector<long long> vl(vi.begin(),\
    \ vi.end());\n            std::vector<short> vs(n);\n            for (int i =\
    \ 0; i < n; ++i) vs[i] = (short)(vi[i] % 30000);\n            std::vector<long\
    \ long> vsl(vs.begin(), vs.end());\n            assert(Hash(vi) == Hash(vl));\n\
    \            assert(RollingHash(vi).get(0, n) == RollingHash(vl).get(0, n));\n\
    \            assert(Hash(vs) == Hash(vsl));\n            std::vector<unsigned>\
    \ vu(n);\n            for (int i = 0; i < n; ++i) vu[i] = (unsigned)std::abs(vi[i]);\n\
    \            std::vector<long long> vul(vu.begin(), vu.end());\n            assert(Hash(vu)\
    \ == Hash(vul));\n            std::vector<unsigned long long> vull(vu.begin(),\
    \ vu.end());\n            assert(RollingHash(vull).get(0, n) == RollingHash(vul).get(0,\
    \ n));\n            std::vector<bool> vb(n);\n            std::vector<int> vbi(n);\n\
    \            for (int i = 0; i < n; ++i) vbi[i] = vb[i] = random_int(0, 1);\n\
    \            assert(Hash(vb) == Hash(vbi) && RollingHash(vb).slice(0, n) == Hash(vbi));\n\
    \            // vector<char> \u306F string \u3068\u540C\u3058\n            std::string\
    \ s = random_string(n, 26);\n            std::vector<char> vc(s.begin(), s.end());\n\
    \            assert(Hash(vc) == Hash(s) && RollingHash(vc).get(0, n) == RollingHash(s).get(0,\
    \ n));\n        }\n        // \u5883\u754C\u306E\u5024\u3068\u3001\u7D20\u6734\
    \u306B ull \u306B\u3059\u308B\u3068\u885D\u7A81\u3059\u308B\u7D44\n        std::vector<long\
    \ long> v = {-LIM, -LIM + 1, -1, 0, 7, LIM - 1, LIM};\n        RollingHash rv(v);\n\
    \        for (int i = 0; i < (int)v.size(); ++i) {\n            for (int j = 0;\
    \ j < (int)v.size(); ++j) {\n                assert((rv.get(i, i + 1) == rv.get(j,\
    \ j + 1)) == (i == j));\n                assert(rv.compare(i, i + 1, j, j + 1)\
    \ == (i > j) - (i < j));\n            }\n        }\n    }\n}  // namespace\n\n\
    int main() {\n    test_pow_of();\n    test_concat_matches_string();\n    test_long_concat_memory();\n\
    \    test_huge_repeat();\n    test_vector_matches_naive();\n    test_vector_types();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - string/rolling_hash.hpp
  isVerificationFile: true
  path: verify/random_rolling_hash.test.cpp
  requiredBy: []
  timestamp: '2026-11-15 11:23:52+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/random_rolling_hash.test.cpp
layout: document
redirect_from:
- /verify/verify/random_rolling_hash.test.cpp
- /verify/verify/random_rolling_hash.test.cpp.html
title: verify/random_rolling_hash.test.cpp
---
