---
title: Aho-Corasick automaton
documentation_of: ./aho_corasick.hpp
---

## 概要

`yesantikiss::AhoCorasick<SIGMA, BASE>` は、複数パターンの文字列照合に使う
Aho-Corasick オートマトンです。既定では `'a'` から始まる英小文字 26 文字を
扱います。

## API

- `add(s)`: パターンを Trie に追加し、その終端ノード番号を返します。
- `build()`: failure link と全遷移を構築します。
- `move(v, c)`, `move(v, ch)`: 状態 `v` から遷移します。
- `link(v)`: failure link、`parent(v)`: Trie 上の親を返します。
- `size()`: ノード数を返します。
- `order`: 根から始まる BFS 順のノード列です。failure link を使った集計に
  利用できます。

## 要件・注意

- すべてのパターンを `add` してから `build()` を一度呼んでください。
  構築後の追加や再構築には対応していません。
- 文字 `ch` は `BASE <= ch < BASE + SIGMA` を満たす必要があります。
- 遷移を使う前に `build()` が必要です。
- パターンの終端情報は利用側で `add` の返り値として保持してください。

## 計算量

パターン総長を `L`、ノード数を `V` とすると、追加は合計 `O(L)`、構築は
`O(V * SIGMA)`、一文字の遷移は `O(1)` です。メモリは `O(V * SIGMA)` です。
