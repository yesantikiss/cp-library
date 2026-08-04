# Data Structure

[トップへ戻る](../README.md)

## `2d_prefixsum.hpp`

二次元累積和と二次元いもす法を扱う `yesantikiss::PS2D<T>` です。

- 座標: 0-indexed
- 長方形: 半開区間 `[y1, y2) × [x1, x2)`
- `set_point(y, x, v)`: 点を設定する SET モード
- `add_rect_imos(y1, x1, y2, x2, v)`: 長方形加算を登録する IMOS モード
- `build()`: グリッドと累積和を `O(HW)` で構築
- `at(y, x)`: 構築後の点取得 `O(1)`
- `sum(y1, x1, y2, x2)`: 構築後の長方形和 `O(1)`

SET モードと IMOS モードは併用できません。

## `binary_trie.hpp`

多重集合を管理する `yesantikiss::BinaryTrie<B>` です。値全体に XOR を適用したとみなして、順序統計を取得できます。

- `insert(x)`, `erase(x)`, `count(x)`, `contains(x)`
- `kth(k, T)`: `{x xor T}` を昇順に並べた `k` 番目を取得
- `min_element(T)`, `max_element(T)`
- 各操作: `O(B)`

`B` は `1` 以上 `63` 以下です。

## `cartesian_tree.hpp`

配列から `yesantikiss::CartesianTree<T, Compare>` を `O(N)` で構築します。

- `std::less<T>`: min Cartesian Tree
- `std::greater<T>`: max Cartesian Tree
- `root`: 根の添字
- `par`, `left`, `right`: 各頂点の親・左の子・右の子。存在しない場合は `-1`

## `compressor.hpp`

座標圧縮を行う `yesantikiss::Compressor<T>` です。

- `add(x)`, `add_range(first, last)`: 値を登録
- `build()`: ソート済みユニーク列を `O(N log N)` で構築
- `get(x)`: 登録済みの値の圧縮後添字を取得。未登録なら `-1`
- `lower_bound(x)`, `upper_bound(x)`: 境界の圧縮後添字を取得
- `value(i)`: 圧縮後添字から元の値を取得
- `map(a)`: 配列全体を圧縮後添字へ変換

## `dynamic_segtree.hpp`

必要な経路だけノードを生成する動的セグメント木 `yesantikiss::dynamic_segtree<S, op, e>` です。

- 対象区間: `[0, n)`
- `set(p, x)`: 点 `p` を `x` に更新
- `apply_point(p, x)`: 点 `p` を `op(get(p), x)` に更新
- `get(p)`, `prod(l, r)`, `all_prod()`
- `max_right(l, f)`, `min_left(r, f)`: ACL の segtree に近い境界探索
- 点操作・区間積・境界探索: `O(log n)`

生成ノード数は点更新1回につき `O(log n)` です。

## `interval_map.hpp`

区間を値ごとにまとめて管理する `yesantikiss::IntervalMap<T, V>` です。初期化時に指定した `[L, R)` を常に完全被覆し、隣接する同値区間を自動的に併合します。

- `get_val(x)`: 点 `x` の値
- `assign(l, r, v)`: `[l, r)` を `v` に代入
- `apply(l, r, f)`: 交差する各区間の値を変換
- `enumerate_cut(l, r, f)`: `[l, r)` で切り揃えて区間を列挙
- `segments_cut(l, r)`: 列挙結果を `std::vector<Node>` で取得
- 更新コールバック版では、区間の追加・削除に合わせて外部の集計も更新可能

区間数を `M`、処理対象の区間数を `K` とすると、代表的な操作は `O(log M + K log M)` 程度です。

## `persistent_segtree.hpp`

一点更新ごとに新しい版を作る永続セグメント木 `yesantikiss::persistent_segtree<S, op, e>` です。

- `set(p, x, ver)`: `ver` 版から新しい版を作り、その版番号を返す
- `get(p, ver)`, `prod(l, r, ver)`, `all_prod(ver)`
- `ver = -1`: 最新版を指定
- 構築: `O(N)`
- 一点更新・区間積: `O(log N)`
- 一点更新ごとの追加ノード数: `O(log N)`

## `potential_dsu.hpp`

頂点間のポテンシャル差を管理する `yesantikiss::potential_dsu<T>` です。

- `merge(a, b, w)`: 制約 `pot[b] - pot[a] = w` を追加
- `diff(a, b)`: `pot[b] - pot[a]` を取得。同一連結成分である必要あり
- `potential(a)`: `pot[a] - pot[leader(a)]`
- `leader(a)`, `same(a, b)`, `size(a)`, `groups()`
- `groups()` 以外の償却計算量: `O(α(N))`
