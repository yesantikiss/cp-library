---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: tests/test.cpp
    title: tests/test.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/associative_array.test.cpp
    title: verify/associative_array.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utils/hash.hpp\"\n\n#include <chrono>\n#include <cstddef>\n\
    #include <cstdint>\n#include <functional>\n#include <memory>\n#include <unordered_map>\n\
    #include <unordered_set>\n#include <utility>\n\nnamespace yesantikiss {\n    namespace\
    \ hash_detail {\n        inline std::uint64_t splitmix64(std::uint64_t x) {\n\
    \            x += 0x9e3779b97f4a7c15ULL;\n            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;\n\
    \            x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;\n            return\
    \ x ^ (x >> 31);\n        }\n\n        inline std::uint64_t random_seed() {\n\
    \            static const std::uint64_t seed =\n                static_cast<std::uint64_t>(\n\
    \                    std::chrono::steady_clock::now()\n                      \
    \  .time_since_epoch()\n                        .count());\n            return\
    \ seed;\n        }\n    }\n\n    struct custom_hash {\n        template<class\
    \ T>\n        std::size_t operator()(const T& value) const {\n            return\
    \ static_cast<std::size_t>(hash_detail::splitmix64(\n                static_cast<std::uint64_t>(std::hash<T>{}(value))\
    \ +\n                hash_detail::random_seed()));\n        }\n\n        template<class\
    \ T, class U>\n        std::size_t operator()(const std::pair<T, U>& value) const\
    \ {\n            std::uint64_t first =\n                static_cast<std::uint64_t>((*this)(value.first));\n\
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
    }\n"
  code: "#pragma once\n\n#include <chrono>\n#include <cstddef>\n#include <cstdint>\n\
    #include <functional>\n#include <memory>\n#include <unordered_map>\n#include <unordered_set>\n\
    #include <utility>\n\nnamespace yesantikiss {\n    namespace hash_detail {\n \
    \       inline std::uint64_t splitmix64(std::uint64_t x) {\n            x += 0x9e3779b97f4a7c15ULL;\n\
    \            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;\n            x = (x\
    \ ^ (x >> 27)) * 0x94d049bb133111ebULL;\n            return x ^ (x >> 31);\n \
    \       }\n\n        inline std::uint64_t random_seed() {\n            static\
    \ const std::uint64_t seed =\n                static_cast<std::uint64_t>(\n  \
    \                  std::chrono::steady_clock::now()\n                        .time_since_epoch()\n\
    \                        .count());\n            return seed;\n        }\n   \
    \ }\n\n    struct custom_hash {\n        template<class T>\n        std::size_t\
    \ operator()(const T& value) const {\n            return static_cast<std::size_t>(hash_detail::splitmix64(\n\
    \                static_cast<std::uint64_t>(std::hash<T>{}(value)) +\n       \
    \         hash_detail::random_seed()));\n        }\n\n        template<class T,\
    \ class U>\n        std::size_t operator()(const std::pair<T, U>& value) const\
    \ {\n            std::uint64_t first =\n                static_cast<std::uint64_t>((*this)(value.first));\n\
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
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/hash.hpp
  requiredBy:
  - tests/test.cpp
  timestamp: '2026-08-25 15:58:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/associative_array.test.cpp
documentation_of: utils/hash.hpp
layout: document
title: "\u4E71\u6570\u5316\u30CF\u30C3\u30B7\u30E5\u30B3\u30F3\u30C6\u30CA"
---

## 概要

SplitMix64 と実行ごとに変わる salt を使う `yesantikiss::custom_hash`、および
それを既定ハッシュにした `yesantikiss::umap` と `yesantikiss::uset` を提供します。

## API

- `custom_hash`: 単一値と `std::pair` に対応するハッシュ関数オブジェクトです。
- `umap<Key, T>`: `std::unordered_map<Key, T, custom_hash>` 相当です。
- `uset<Key>`: `std::unordered_set<Key, custom_hash>` 相当です。

標準コンテナと同様、ハッシュ関数、等値比較、アロケータは追加のテンプレート
引数で差し替えられます。

## 要件・注意

- キー型には `std::hash<Key>` が必要です。`std::pair` の各要素も同じ要件を
  満たす必要があります。
- salt はプロセス内で共通です。暗号学的ハッシュではなく、衝突耐性を保証する
  ものではありません。
- iterator の無効化などの規則は対応する標準 unordered コンテナと同じです。

## 計算量

検索・挿入・削除は期待 `O(1)`、最悪 `O(N)` です。メモリは `O(N)` です。
