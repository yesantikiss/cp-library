#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace yesantikiss {
    // ACL dsu 風 + ロールバック
    // 経路圧縮をせず union by size だけで併合するので、merge を新しい順に
    // 取り消せる。merge は同じ成分どうしでも履歴を 1 件積むので、merge 1 回と
    // undo 1 回が必ず対応する。
    struct rollback_dsu {
        rollback_dsu() : rollback_dsu(0) {}
        explicit rollback_dsu(int n_)
            : n(n_), components(n_), parent_or_size(n_, -1) {}

        int leader(int a) const {
            assert(0 <= a && a < n);
            while (parent_or_size[a] >= 0) a = parent_or_size[a];
            return a;
        }

        bool same(int a, int b) const { return leader(a) == leader(b); }

        int size(int a) const { return -parent_or_size[leader(a)]; }

        // 連結成分の個数
        int count() const { return components; }

        // ACL dsu と同じく、併合後の leader を返す
        int merge(int a, int b) {
            int x = leader(a), y = leader(b);
            if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
            history.push_back({x, y, parent_or_size[x], parent_or_size[y]});
            if (x == y) return x;
            parent_or_size[x] += parent_or_size[y];
            parent_or_size[y] = x;
            components--;
            return x;
        }

        // 直前の merge を 1 回取り消す
        void undo() {
            assert(!history.empty());
            const record& last = history.back();
            parent_or_size[last.x] = last.old_x;
            parent_or_size[last.y] = last.old_y;
            if (last.x != last.y) components++;
            history.pop_back();
        }

        // これまでに取り消されずに残っている merge の回数
        int snapshot() const { return (int)history.size(); }

        // snapshot() が state を返した時点まで戻す
        void rollback(int state) {
            assert(0 <= state && state <= (int)history.size());
            while ((int)history.size() > state) undo();
        }

        // 各頂点の leader を一時配列にメモしながら求めるので O(N)
        std::vector<std::vector<int>> groups() const {
            std::vector<int> leader_buf(n, -1), group_size(n), path;
            for (int i = 0; i < n; i++) {
                int v = i;
                while (leader_buf[v] < 0 && parent_or_size[v] >= 0) {
                    path.push_back(v);
                    v = parent_or_size[v];
                }
                int r = leader_buf[v] < 0 ? v : leader_buf[v];
                leader_buf[v] = r;
                for (int u : path) leader_buf[u] = r;
                path.clear();
                group_size[r]++;
            }
            std::vector<std::vector<int>> result(n);
            for (int i = 0; i < n; i++) result[i].reserve(group_size[i]);
            for (int i = 0; i < n; i++) result[leader_buf[i]].push_back(i);
            result.erase(std::remove_if(result.begin(), result.end(),
                                        [](const auto& v) { return v.empty(); }),
                         result.end());
            return result;
        }

      private:
        struct record {
            int x, y, old_x, old_y;
        };
        int n;
        int components;
        std::vector<int> parent_or_size; // root: -size, else: parent
        std::vector<record> history;
    };
}
