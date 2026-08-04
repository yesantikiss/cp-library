---
title: 乱数化ハッシュコンテナ
documentation_of: ./hash.hpp
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
