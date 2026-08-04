#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"

#include <iostream>

#include "ds/binary_trie.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    yesantikiss::BinaryTrie<30> values;
    while (q--) {
        int type;
        unsigned long long x;
        std::cin >> type >> x;

        if (type == 0) {
            if (!values.contains(x)) values.insert(x);
        } else if (type == 1) {
            values.erase(x);
        } else {
            std::cout << values.min_element(x) << '\n';
        }
    }
}
