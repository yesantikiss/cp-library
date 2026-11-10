// 素朴な実装と突き合わせるランダムテストを通してから A + B を解く。
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "ds/persistent_segtree.hpp"

namespace {
    // 非可換な演算で、左右の順序を取り違えていないか確かめる。
    std::string op_concat(std::string a, std::string b) { return a + b; }
    std::string e_concat() { return ""; }
}

int main() {
    std::mt19937 random(20261110);
    auto uniform = [&](int low, int high) {
        return std::uniform_int_distribution<int>(low, high)(random);
    };
    using Segtree =
        yesantikiss::persistent_segtree<std::string, op_concat, e_concat>;

    {
        Segtree empty(0);
        assert(empty.versions() == 1 && empty.latest_version() == 0);
        assert(empty.prod(0, 0) == "" && empty.all_prod() == "");
        Segtree identity(3);
        assert(identity.all_prod() == "" && identity.get(1) == "");
    }

    for (int trial = 0; trial < 2000; ++trial) {
        int n = uniform(1, 20);
        std::vector<std::string> initial(n);
        for (std::string& s : initial) {
            s = std::string(1, static_cast<char>('a' + uniform(0, 25)));
        }
        Segtree seg(initial);
        // versions[i] は i 番目の版の配列そのもの
        std::vector<std::vector<std::string>> versions{initial};

        for (int query = 0; query < 40; ++query) {
            // -1 は最新版を指す
            int version = uniform(-1, static_cast<int>(versions.size()) - 1);
            int actual_version =
                version == -1 ? static_cast<int>(versions.size()) - 1
                              : version;
            if (uniform(0, 1) == 0) {
                int p = uniform(0, n - 1);
                std::string x(1, static_cast<char>('a' + uniform(0, 25)));
                std::vector<std::string> next = versions[actual_version];
                next[p] = x;
                int created = seg.set(p, x, version);
                assert(created == static_cast<int>(versions.size()));
                versions.push_back(next);
                assert(seg.versions() == static_cast<int>(versions.size()));
                assert(seg.latest_version() == created);
            } else {
                const std::vector<std::string>& a = versions[actual_version];
                int l = uniform(0, n);
                int r = uniform(l, n);
                std::string expected, all;
                for (int i = l; i < r; ++i) expected += a[i];
                for (int i = 0; i < n; ++i) all += a[i];
                assert(seg.prod(l, r, version) == expected);
                assert(seg.all_prod(version) == all);
                int p = uniform(0, n - 1);
                assert(seg.get(p, version) == a[p]);
            }
        }

        // 古い版が後の更新で壊れていないか、最後に全部確かめる。
        for (int version = 0; version < static_cast<int>(versions.size());
             ++version) {
            for (int p = 0; p < n; ++p) {
                assert(seg.get(p, version) == versions[version][p]);
            }
        }
    }

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
