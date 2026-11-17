// 素朴な実装と突き合わせるランダムテストを通してから A + B を解く。
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "ds/rollback_dsu.hpp"

namespace {
    // 張った辺の列から、各頂点の成分番号 (成分内で最小の頂点) を求める。
    std::vector<int> naive_labels(int n,
                                  const std::vector<std::pair<int, int>>& edges) {
        std::vector<int> label(n);
        for (int i = 0; i < n; i++) label[i] = i;
        bool changed = true;
        while (changed) {
            changed = false;
            for (auto [a, b] : edges) {
                int m = std::min(label[a], label[b]);
                if (label[a] != m || label[b] != m) {
                    label[a] = label[b] = m;
                    changed = true;
                }
            }
        }
        return label;
    }

    void check(const yesantikiss::rollback_dsu& dsu, int n,
               const std::vector<std::pair<int, int>>& edges) {
        std::vector<int> label = naive_labels(n, edges);
        std::vector<int> naive_size(n);
        int naive_count = 0;
        for (int i = 0; i < n; i++) {
            naive_size[label[i]]++;
            if (label[i] == i) naive_count++;
        }
        assert(dsu.count() == naive_count);
        assert(dsu.snapshot() == (int)edges.size());
        for (int a = 0; a < n; a++) {
            int r = dsu.leader(a);
            assert(0 <= r && r < n && label[r] == label[a]);
            assert(dsu.size(a) == naive_size[label[a]]);
            for (int b = 0; b < n; b++) {
                assert(dsu.same(a, b) == (label[a] == label[b]));
            }
        }

        std::vector<std::vector<int>> expected(n);
        for (int i = 0; i < n; i++) expected[label[i]].push_back(i);
        expected.erase(std::remove_if(expected.begin(), expected.end(),
                                      [](const auto& g) { return g.empty(); }),
                       expected.end());
        auto actual = dsu.groups();
        for (auto& g : actual) std::sort(g.begin(), g.end());
        std::sort(actual.begin(), actual.end());
        assert(actual == expected);
    }
}

int main() {
    std::mt19937 random(20261117);
    auto uniform = [&](int low, int high) {
        return std::uniform_int_distribution<int>(low, high)(random);
    };

    {
        yesantikiss::rollback_dsu empty;
        assert(empty.count() == 0 && empty.snapshot() == 0);
        assert(empty.groups().empty());
        empty.rollback(0);
    }

    for (int trial = 0; trial < 3000; ++trial) {
        int n = uniform(1, 12);
        yesantikiss::rollback_dsu dsu(n);
        // 同じ成分どうしの merge も 1 件として積む
        std::vector<std::pair<int, int>> edges;
        std::vector<int> snapshots;
        check(dsu, n, edges);

        for (int query = 0; query < 60; ++query) {
            int type = uniform(0, 9);
            if (type <= 4) {
                int a = uniform(0, n - 1), b = uniform(0, n - 1);
                int ra = dsu.leader(a), rb = dsu.leader(b);
                int size_a = dsu.size(a), size_b = dsu.size(b);
                int r = dsu.merge(a, b);
                assert(r == dsu.leader(a) && r == dsu.leader(b));
                // union by size: 大きい方の leader が残る
                assert(r == ra || r == rb);
                if (size_a > size_b) assert(r == ra);
                if (size_a < size_b) assert(r == rb);
                edges.emplace_back(a, b);
            } else if (type <= 6) {
                if (edges.empty()) continue;
                dsu.undo();
                edges.pop_back();
                // 取り消した merge より後の snapshot は使えなくなる
                while (!snapshots.empty() &&
                       snapshots.back() > (int)edges.size()) {
                    snapshots.pop_back();
                }
            } else if (type == 7) {
                snapshots.push_back(dsu.snapshot());
            } else {
                // 入れ子の snapshot のどれかへ戻す
                if (snapshots.empty()) continue;
                int i = uniform(0, (int)snapshots.size() - 1);
                int state = snapshots[i];
                snapshots.resize(i + 1);
                dsu.rollback(state);
                edges.resize(state);
                if (uniform(0, 1)) dsu.rollback(state); // 同じ時点へは何もしない
            }
            check(dsu, n, edges);
        }
        dsu.rollback(0);
        edges.clear();
        check(dsu, n, edges);
    }

    // 大きめの n で、まとめて巻き戻したあとの状態と groups を確かめる。
    {
        const int n = 1 << 12;
        yesantikiss::rollback_dsu dsu(n);
        for (int step = 1; step < n; step *= 2) {
            for (int i = 0; i + step < n; i += 2 * step) {
                dsu.merge(i + step, i);
            }
        }
        assert(dsu.count() == 1 && dsu.size(0) == n);
        int state = dsu.snapshot();
        for (int i = 0; i < 1000; i++) {
            dsu.merge(uniform(0, n - 1), uniform(0, n - 1));
        }
        assert(dsu.snapshot() == state + 1000 && dsu.count() == 1);
        dsu.rollback(state);
        dsu.rollback(0);
        assert(dsu.count() == n && dsu.size(n - 1) == 1);
        assert((int)dsu.groups().size() == n);

        // union by size がなければ深さ N の鎖になる併合順
        for (int i = 1; i < n; i++) dsu.merge(i, i - 1);
        assert(dsu.count() == 1);
        auto groups = dsu.groups();
        assert(groups.size() == 1 && (int)groups[0].size() == n);
    }

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
