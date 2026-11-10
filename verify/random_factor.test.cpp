// 素朴な実装と突き合わせるランダムテストを通してから A + B を解く。
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

#include "math/factor.hpp"

int main() {
    {
        yesantikiss::Factor empty(0);
        assert(empty.primes.empty());
        yesantikiss::Factor one(1);
        assert(one.primes.empty() && !one.is_prime(1));
        assert(one.factorize(1).empty() && one.factor_list(1).empty());
    }

    // 試し割りの結果と、N 以下のすべての数で比べる。
    for (int n : {2, 3, 4, 10, 97, 100, 30000}) {
        yesantikiss::Factor factor(n);
        std::vector<int> primes;
        for (int x = 1; x <= n; ++x) {
            std::vector<std::pair<int, int>> expected;
            std::vector<int> expected_list;
            int rest = x;
            for (int p = 2; p * p <= rest; ++p) {
                if (rest % p != 0) continue;
                int count = 0;
                while (rest % p == 0) {
                    rest /= p;
                    ++count;
                    expected_list.push_back(p);
                }
                expected.emplace_back(p, count);
            }
            if (rest > 1) {
                expected.emplace_back(rest, 1);
                expected_list.push_back(rest);
            }

            bool prime = x >= 2 && expected.size() == 1 &&
                         expected[0].second == 1;
            if (prime) primes.push_back(x);
            assert(factor.is_prime(x) == prime);
            assert(factor.factorize(x) == expected);
            assert(factor.factor_list(x) == expected_list);
            assert(factor.lpf[x] == (x == 1 ? 1 : expected[0].first));
        }
        assert(factor.primes == primes);

        // build し直しても前の結果が残らない
        factor.build(n / 2);
        assert(factor.N == n / 2);
        assert(static_cast<int>(factor.lpf.size()) == n / 2 + 1);
        for (int p : factor.primes) assert(p <= n / 2);
    }

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
