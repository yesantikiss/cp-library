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

## `grid_rotate.hpp`

二次元配列を時計回りに回転した新しい配列を返します。`std::vector<std::vector<T>>` と `std::vector<std::string>` の両方に対応します。

- `rotate90(a)`, `rotate180(a)`, `rotate270(a)`
- `rotate(a, k)`: 時計回りに `90k°`。`k` は負でもよい
- 計算量: `O(HW)`

## `fraction.hpp`

符号付き整数 `T` を分子・分母に使う有理数型 `yesantikiss::fraction<T>` です。値は常に既約で、分母は正です。`fraction<__int128>` の別名 `yesantikiss::fr` もあります。

- 四則演算、複合代入、比較、ストリーム入出力
- `inv()`, `abs(x)`, `is_integer()`, `floor()`, `ceil()`, `to_ld()`, `to_double()`
- `parse(s, out)`: 整数・小数・分数の文字列を解析
- 結果が `T` に収まらない演算は `std::overflow_error` を送出
- 各演算の時間はほぼ gcd で決まり、値が 64 bit に収まる範囲なら 64 bit の binary gcd で計算
