#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

// 版を頂点とする木を作り、DFS で潜るときに merge、戻るときに undo する。
#include <iostream>
#include <utility>
#include <vector>

#include "ds/rollback_dsu.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    // 頂点 0 が初期状態、頂点 i + 1 がクエリ i の後の版
    std::vector<int> type(q + 1, -1), u(q + 1), v(q + 1);
    std::vector<std::vector<int>> children(q + 1);
    for (int i = 1; i <= q; i++) {
        int k;
        std::cin >> type[i] >> k >> u[i] >> v[i];
        children[k + 1].push_back(i);
    }

    yesantikiss::rollback_dsu dsu(n);
    std::vector<int> answer(q + 1, -1);
    // 非負なら入る頂点、負なら ~頂点 から出る
    std::vector<int> stack{0};
    while (!stack.empty()) {
        int x = stack.back();
        stack.pop_back();
        if (x < 0) {
            if (type[~x] == 0) dsu.undo();
            continue;
        }
        if (type[x] == 0) dsu.merge(u[x], v[x]);
        if (type[x] == 1) answer[x] = dsu.same(u[x], v[x]);
        stack.push_back(~x);
        for (int c : children[x]) stack.push_back(c);
    }

    for (int i = 1; i <= q; i++) {
        if (type[i] == 1) std::cout << answer[i] << '\n';
    }
}
