---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utils/hash.hpp
    title: "\u4E71\u6570\u5316\u30CF\u30C3\u30B7\u30E5\u30B3\u30F3\u30C6\u30CA"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/associative_array
    links:
    - https://judge.yosupo.jp/problem/associative_array
  bundledCode: "#line 1 \"verify/associative_array.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/associative_array\"\n\n#include <cstdint>\n#include\
    \ <iostream>\n\n#line 2 \"utils/hash.hpp\"\n\n#include <chrono>\n#include <cstddef>\n\
    #line 6 \"utils/hash.hpp\"\n#include <functional>\n#include <memory>\n#include\
    \ <unordered_map>\n#include <unordered_set>\n#include <utility>\n\nnamespace yesantikiss\
    \ {\n    namespace hash_detail {\n        inline std::uint64_t splitmix64(std::uint64_t\
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
    }\n#line 7 \"verify/associative_array.test.cpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int q;\n    std::cin >> q;\n\n    yesantikiss::umap<std::uint64_t,\
    \ std::uint64_t> values;\n    values.reserve(q);\n\n    while (q--) {\n      \
    \  int type;\n        std::uint64_t key;\n        std::cin >> type >> key;\n\n\
    \        if (type == 0) {\n            std::uint64_t value;\n            std::cin\
    \ >> value;\n            values[key] = value;\n        } else {\n            auto\
    \ it = values.find(key);\n            std::cout << (it == values.end() ? 0 : it->second)\
    \ << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/associative_array\"\n\n\
    #include <cstdint>\n#include <iostream>\n\n#include \"utils/hash.hpp\"\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int q;\n    std::cin >> q;\n\n    yesantikiss::umap<std::uint64_t, std::uint64_t>\
    \ values;\n    values.reserve(q);\n\n    while (q--) {\n        int type;\n  \
    \      std::uint64_t key;\n        std::cin >> type >> key;\n\n        if (type\
    \ == 0) {\n            std::uint64_t value;\n            std::cin >> value;\n\
    \            values[key] = value;\n        } else {\n            auto it = values.find(key);\n\
    \            std::cout << (it == values.end() ? 0 : it->second) << '\\n';\n  \
    \      }\n    }\n}\n"
  dependsOn:
  - utils/hash.hpp
  isVerificationFile: true
  path: verify/associative_array.test.cpp
  requiredBy: []
  timestamp: '2026-08-25 15:58:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/associative_array.test.cpp
layout: document
redirect_from:
- /verify/verify/associative_array.test.cpp
- /verify/verify/associative_array.test.cpp.html
title: verify/associative_array.test.cpp
---
