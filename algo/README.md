# Algorithm

[トップへ戻る](../README.md)

## `binary_search.hpp`

整数区間上の単調な述語の境界を求める二分探索です。

- `binary_search_min_left(left, right, f)`: `false ... true` で `f(x)` が真となる最小の `x`。見つからなければ `right`
- `binary_search_max_right(left, right, f)`: `true ... false` で `f(x)` が真となる最大の `x`。見つからなければ `left`
- `left`, `right` は番兵で、`f(left)`, `f(right)` は評価しない
- 計算量: `O(F log(right - left))`

## `mo.hpp`

複数の静的な区間クエリを、クエリの処理順を並べ替えて処理する Mo's algorithm です。

- 型: `yesantikiss::Mo`
- 区間: 0-indexed、半開区間 `[l, r)`
- `add_query(l, r)`: クエリを追加
- `solve(add, del, out)`: 左右で共通の追加・削除処理を使用
- `solve(addL, addR, delL, delR, out)`: 左右で異なる追加・削除処理を使用
- `out(i)`: 元の追加順におけるクエリ番号 `i` の答えを記録

`add` と `del` が定数時間なら、典型的な計算量はおおよそ `O((N + Q)√Q)` です。
