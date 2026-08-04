# Utilities

[トップへ戻る](../README.md)

## `int128.hpp`

GCC・Clang の拡張整数型 `yesantikiss::i128`（`__int128`）と
`yesantikiss::u128`（`unsigned __int128`）を定義し、10進数での
ストリーム入出力に対応します。

```cpp
#include <iostream>

#include "utils/int128.hpp"

int main() {
    yesantikiss::i128 x;
    std::cin >> x;
    std::cout << x << '\n';
}
```

- 先頭の `+`・`-` に対応（`u128` では `-` を受け付けません）
- 型の範囲外の入力や不正な文字列では `failbit` を設定し、値を変更しません
- 入出力の計算量: 桁数を `D` として `O(D)`

## `hash.hpp`

`std::unordered_map` と `std::unordered_set` を、実行ごとに変わる salt と
SplitMix64 を用いた `yesantikiss::custom_hash` で利用するための
`yesantikiss::umap`、`yesantikiss::uset` です。

- `umap<Key, T>`: `std::unordered_map<Key, T, custom_hash>`
- `uset<Key>`: `std::unordered_set<Key, custom_hash>`
- 標準でハッシュ可能な型と、それらを要素に持つ `std::pair` をキーに利用可能
- 検索・挿入・削除の期待計算量: `O(1)`

標準のコンテナと同様に、必要に応じてハッシュ関数、等値比較、アロケータを
追加のテンプレート引数で指定できます。
