#pragma once

#include <cassert>
#include <utility>
#include <vector>

namespace yesantikiss {
    // 最小素因数テーブル (Least Prime Factor / LPF)
    // 1..N を O(N) で構築して、各 x を O(素因数の個数) で分解できる
    struct Factor {
        int N = 0;
        std::vector<int> lpf;     // lpf[x] = x の最小素因数 (x>=2), lpf[1]=1
        std::vector<int> primes;  // 素数列（おまけ）
    
        Factor() {}
        explicit Factor(int n) { build(n); }
    
        void build(int n) {
            assert(n >= 0);
            N = n;
            lpf.assign(N + 1, 0);
            primes.clear();
            if (N >= 1) lpf[1] = 1;
    
            for (int i = 2; i <= N; i++) {
                if (lpf[i] == 0) {
                    lpf[i] = i;
                    primes.emplace_back(i);
                }
                for (int p : primes) {
                    long long v = 1LL * p * i;
                    if (v > N) break;
                    lpf[(int)v] = p;
                    if (p == lpf[i]) break;
                }
            }
        }
    
        // x を素因数分解して (prime, exponent) を返す
        // 事前に build(maxA) が必要。x==1 は空を返す。
        std::vector<std::pair<int,int>> factorize(int x) const {
            assert(1 <= x && x <= N);
            std::vector<std::pair<int,int>> res;
            while (x > 1) {
                int p = lpf[x];
                int c = 0;
                while (x % p == 0) { x /= p; c++; }
                res.push_back({p, c});
            }
            return res;
        }
    
        // (素因数を列挙したいだけ) p,p,p,... の形で返す
        std::vector<int> factor_list(int x) const {
            assert(1 <= x && x <= N);
            std::vector<int> res;
            while (x > 1) {
                int p = lpf[x];
                res.push_back(p);
                x /= p;
            }
            return res;
        }
    
        bool is_prime(int x) const {
            assert(1 <= x && x <= N);
            return x >= 2 && lpf[x] == x;
        }
    };
}
