# Algorithm

[トップへ戻る](../README.md)

## `mo.hpp`

複数の静的な区間クエリを、クエリの処理順を並べ替えて処理する Mo's algorithm です。

- 型: `yesantikiss::Mo`
- 区間: 0-indexed、半開区間 `[l, r)`
- `add_query(l, r)`: クエリを追加
- `solve(add, del, out)`: 左右で共通の追加・削除処理を使用
- `solve(addL, addR, delL, delR, out)`: 左右で異なる追加・削除処理を使用
- `out(i)`: 元の追加順におけるクエリ番号 `i` の答えを記録

`add` と `del` が定数時間なら、典型的な計算量はおおよそ `O((N + Q)√Q)` です。
