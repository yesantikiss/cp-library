#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include <cstdint>
#include <iostream>

#include "utils/hash.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    yesantikiss::umap<std::uint64_t, std::uint64_t> values;
    values.reserve(q);

    while (q--) {
        int type;
        std::uint64_t key;
        std::cin >> type >> key;

        if (type == 0) {
            std::uint64_t value;
            std::cin >> value;
            values[key] = value;
        } else {
            auto it = values.find(key);
            std::cout << (it == values.end() ? 0 : it->second) << '\n';
        }
    }
}
