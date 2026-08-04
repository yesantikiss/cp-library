# String

[トップへ戻る](../README.md)

## `aho_corasick.hpp`

複数パターンの文字列照合に使う `yesantikiss::AhoCorasick<SIGMA, BASE>` です。デフォルトでは英小文字26文字を扱います。

- `add(s)`: パターンを追加し、終端ノードを返す
- `build()`: failure link と遷移を構築
- `move(v, c)`: 状態 `v` から文字または文字番号 `c` で遷移
- `link(v)`, `parent(v)`: failure link・Trie上の親を取得
- `order`: BFS順のノード列

全パターンの長さの合計を `L`、ノード数を `V` とすると、追加は合計 `O(L)`、構築は `O(V × SIGMA)` です。

## `rolling_hash.hpp`

法 `2^61 - 1` の `yesantikiss::RollingHash` です。基数はプロセスごとにランダムに選択され、全インスタンスで共有されます。

- `build(s)`: 文字列のハッシュを `O(N)` で構築
- `get(l, r)`: 半開区間 `s[l, r)` のハッシュを `O(1)` で取得
- `equals(l1, r1, l2, r2)`: 同一文字列内の部分文字列を比較

ハッシュ衝突の可能性はゼロではありません。
