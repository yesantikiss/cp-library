---
title: 木の中心で根付け
documentation_of: ./centered_tree.hpp
---

## 概要

木を中心で根付けします。中心が2点 `u, v` のときは、その間に仮想頂点 `N`
を置いて根にします。`dist2[x]` は中心点からの距離の2倍で、各辺に頂点を
はさんだ木で中心から測った深さと一致します。頂点を倍にしなくても、
中心が1点か2点かで場合分けせずに木DPが書けます。

```cpp
// 直径の本数 (距離が直径に等しい頂点対の数) を数える例
yesantikiss::CenteredTree tree(graph);
std::vector<long long> endpoints(tree.n + 1);
long long answer = 0;
// 葉から根へ
for (int i = static_cast<int>(tree.order.size()) - 1; i >= 0; --i) {
    int v = tree.order[i];
    if (tree.is_diameter_endpoint(v)) endpoints[v] = 1;
    for (int to : tree.children[v]) {
        // 根では、別々の子の部分木にある端点どうしが直径になる
        if (v == tree.root) answer += endpoints[v] * endpoints[to];
        endpoints[v] += endpoints[to];
    }
}
```

中心が2点 `u, v` のとき、`u` と `v` は元の `graph` では隣り合っていますが、
根付き木ではどちらも仮想頂点 `N` の子です。`graph[v]` を
`to != parent[v]` で絞ると `u` の子に `v` が入ってしまうので、子は必ず
`children[v]` でたどってください。

## API

- `CenteredTree(graph)`: 構築します。
- `build(graph)`: 同じインスタンスを再構築します。
- `n`: 元の木の頂点数です。仮想頂点の番号は `n` です。
- `root`: 根です。中心が1点ならその頂点、2点なら `n` です。
- `diameter`: 直径の辺数です。
- `parent[v]`: 根付き木での親です。`parent[root] = -1` です。
- `order`: 根からの BFS 順です。中心が1点のときは `n` を含みません。
- `children[v]`: 根付き木での子です。仮想頂点が根のとき、
  `children[n]` は中心の2点です。
- `dist2[v]`: 中心点からの距離の2倍です。根では `0`、使わない仮想頂点では
  `-1` です。
- `is_virtual(v)`: `v` が仮想頂点か判定します。
- `has_virtual_root()`: 中心が2点 (直径が奇数) か判定します。
- `radius()`: 半径 `(diameter + 1) / 2` を返します。
- `is_diameter_endpoint(v)`: `v` がある直径の端点か判定します。
  `dist2[v] == diameter` と同じです。
- `eccentricity(v)`: 元の木で `v` から最も遠い頂点までの距離
  `(dist2[v] + diameter) / 2` を返します。

`parent`, `dist2`, `children` のサイズは常に `n + 1` です。

## 要件・計算量

入力は重みなしの無向の木で、頂点番号は `0` 以上 `N` 未満とします。
`N = 0` のときは `root = -1` で `order` は空です。BFS を3回行うので
`O(N)` 時間です。
