# Tree

[トップへ戻る](../README.md)

## `lca_binary_lifting.hpp`

ダブリングによる `yesantikiss::BinaryLiftingLCA` です。

- `lca(u, v)`: 最小共通祖先
- `dist(u, v)`: パスの辺数
- `kth_ancestor(v, k)`: `v` の `k` 個上の祖先
- `jump(u, v, k)`: `u` から `v` へのパス上の `k` 番目の頂点
- 構築: `O(N log N)`、各クエリ: `O(log N)`

## `lca_euler_tour.hpp`

Euler TourとSparse Tableによる `yesantikiss::EulerTourLCA` です。

- `lca(u, v)`: 最小共通祖先
- `dist(u, v)`: パスの辺数
- `is_ancestor(u, v)`: `u` が `v` の祖先か判定
- 構築: `O(N log N)`、各クエリ: `O(1)`

## `heavy_light_decomposition.hpp`

Heavy-Light Decompositionを行う
`yesantikiss::HeavyLightDecomposition` です。

- `path_query(u, v, edge, callback)`: パスを向き付き区間へ分解
- `subtree_vertex(v)`, `subtree_edge(v)`: 部分木に対応する区間
- `lca(u, v)`, `dist(u, v)`, `is_ancestor(u, v)`
- 構築: `O(N)`、パス分解・LCA: `O(log N)`
