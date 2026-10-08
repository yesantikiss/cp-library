---
title: Rolling Hash
documentation_of: ./rolling_hash.hpp
---

## 概要

`yesantikiss::RollingHash` は法 `2^61 - 1` の文字列用ローリングハッシュです。
基数はプロセスごとにランダムに選ばれ、全インスタンスで共有されます。

## API

- `RollingHash(s)`, `build(s)`: 文字列の prefix hash を構築します。
- `get(l, r)`: 半開区間 `s[l, r)` のハッシュを返します。
- `equals(l1, r1, l2, r2)`: 同じ構築元文字列内の二つの部分文字列を比較します。

### 辞書順比較

- `lcp(l1, r1, l2, r2)`: `s[l1, r1)` と `s[l2, r2)` の最長共通接頭辞の長さを返します。
- `compare(l1, r1, l2, r2)`: 辞書順で比較し、負・0・正を返します（`std::string::compare` と同じ順序）。
- `RollingHash::lcp(a, l1, r1, b, l2, r2)`, `RollingHash::compare(a, l1, r1, b, l2, r2)`:
  別インスタンス `a`, `b` の部分文字列どうしで同じことをします。

```cpp
RollingHash rh(s);
// 接尾辞のソート
std::sort(idx.begin(), idx.end(), [&](int i, int j) { return rh.compare(i, n, j, n) < 0; });
```

### 連結

`get` は `unsigned long long` を返すので、連結には長さの情報が別途必要です。
長さを一緒に持つ `RollingHash::Hash`（`val`, `len`）を使うと `+` で連結できます。

- `slice(l, r)`: `s[l, r)` の `Hash` を返します。
- `a + b`, `a += b`: 連結した文字列の `Hash` を返します。既定構築の `Hash()` は空文字列で、`+` の単位元です。
- `==`, `!=`: 比較。`map` / `set` のキーにしたいときは `get` の値を使ってください。
- `Hash(c)`, `Hash(s)`: 1 文字・文字列全体の `Hash` を prefix hash を持たずに求めます（`explicit`）。
- `Hash(val, len)`: ハッシュ値と長さから直接作ります。
- `RollingHash::concat(h1, h2, len2)`: `get` の値のまま連結する版です。`len2` は後ろ側の長さです。

```cpp
RollingHash a("abra"), b("cadabra"), c("abracadabra");
assert(a.slice(0, 4) + b.slice(0, 7) == c.slice(0, 11));
```

`Hash` は `+` と `Hash()` でモノイドになるので、そのままセグメント木に載せられます。

```cpp
using Hash = yesantikiss::RollingHash::Hash;
Hash op(Hash a, Hash b) { return a + b; }
Hash e() { return Hash(); }

atcoder::segtree<Hash, op, e> seg(n);
for (int i = 0; i < n; i++) seg.set(i, Hash(s[i]));
bool same = seg.prod(l1, r1) == seg.prod(l2, r2);
```

逆向きのハッシュ（回文判定など）は `op` を `b + a` にしたセグメント木を別に持ちます。

## 要件・注意

- 既定構築した場合は、取得前に `build(s)` を呼んでください。
- 各区間は `0 <= l <= r <= s.size()` を満たす必要があります。
- ハッシュが一致しても文字列が等しいとは限らず、衝突の可能性はゼロではありません。
- 基数を共有するため、異なるインスタンスの同じ内容・長さの部分文字列も
  ハッシュ値で比較できます。ただし API の `equals` は同一インスタンス内用です。

## 計算量

構築は `O(N)` 時間・メモリ、部分文字列ハッシュと比較は `O(1)` です。
`lcp`, `compare` は `O(log N)` です。
連結は、基数の累乗テーブルが足りていれば `O(1)`（足りない分は初回のみ伸長）、`Hash(s)` は `O(|s|)` です。
