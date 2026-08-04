#define PROBLEM "https://judge.yosupo.jp/problem/static_range_count_distinct"

#include <iostream>
#include <vector>

#include "algo/mo.hpp"
#include "ds/compressor.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> values(n);
    yesantikiss::Compressor<int> compressor;
    for (int& value : values) {
        std::cin >> value;
        compressor.add(value);
    }
    compressor.build();
    values = compressor.map(values);

    yesantikiss::Mo mo(n);
    for (int i = 0; i < q; ++i) {
        int left, right;
        std::cin >> left >> right;
        mo.add_query(left, right);
    }

    std::vector<int> frequency(compressor.size());
    std::vector<int> answer(q);
    int distinct = 0;
    auto add = [&](int index) {
        if (frequency[values[index]]++ == 0) ++distinct;
    };
    auto erase = [&](int index) {
        if (--frequency[values[index]] == 0) --distinct;
    };
    mo.solve(add, erase, [&](int query) {
        answer[query] = distinct;
    });

    for (int value : answer) std::cout << value << '\n';
}
