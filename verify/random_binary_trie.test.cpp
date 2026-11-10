// 素朴な実装と突き合わせるランダムテストを通してから A + B を解く。
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <set>
#include <vector>

#include "ds/binary_trie.hpp"

namespace {
    using ull = unsigned long long;

    template <int B>
    void run(std::mt19937_64& random, int trials, ull value_mask) {
        for (int trial = 0; trial < trials; ++trial) {
            yesantikiss::BinaryTrie<B> trie;
            std::multiset<ull> values;
            std::vector<ull> pool;
            auto value = [&]() {
                // 同じ値が何度も出るように、既出の値を半分の確率で使う
                if (!pool.empty() && random() % 2 == 0) {
                    return pool[random() % pool.size()];
                }
                ull x = random() & value_mask;
                pool.push_back(x);
                return x;
            };
            assert(trie.empty() && trie.size() == 0);

            for (int query = 0; query < 80; ++query) {
                ull x = value();
                ull mask = random() % 4 == 0 ? 0 : random() & value_mask;
                int type = static_cast<int>(random() % 4);
                if (type == 0) {
                    trie.insert(x);
                    values.insert(x);
                } else if (type == 1) {
                    bool exists = values.count(x) > 0;
                    assert(trie.erase(x) == exists);
                    if (exists) values.erase(values.find(x));
                } else if (type == 2 && !values.empty()) {
                    std::vector<ull> sorted;
                    for (ull y : values) sorted.push_back(y ^ mask);
                    std::sort(sorted.begin(), sorted.end());
                    long long k = static_cast<long long>(
                        random() % sorted.size());
                    assert(trie.kth(k, mask) == sorted[k]);
                    assert(trie.min_element(mask) == sorted.front());
                    assert(trie.max_element(mask) == sorted.back());
                } else {
                    // count(v, T) は {x xor T} の中の v の個数
                    assert(trie.count(x, mask) ==
                           static_cast<long long>(values.count(x ^ mask)));
                    assert(trie.contains(x, mask) ==
                           (values.count(x ^ mask) > 0));
                }
                assert(trie.size() == static_cast<long long>(values.size()));
                assert(trie.empty() == values.empty());
            }
        }
    }
}

int main() {
    std::mt19937_64 random(20261110);
    run<1>(random, 300, 1);
    run<5>(random, 2000, 31);
    run<30>(random, 500, (1ULL << 30) - 1);
    run<63>(random, 500, (1ULL << 63) - 1);

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
