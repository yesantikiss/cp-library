#pragma once

#include <algorithm>
#include <vector>

namespace yesantikiss {
    // ACL dsu 風 + ポテンシャル(差分)管理
    // 約束: merge(a,b,w) は pot[b] - pot[a] = w を追加する
    //      diff(a,b)    は pot[b] - pot[a] を返す（同一成分のときのみ呼ぶ）
    template <class T>
    struct potential_dsu {
        int n;
        std::vector<int> parent_or_size; // root: -size, else: parent
        std::vector<T> diff_weight;      // diff_weight[v] = pot[v] - pot[parent[v]] (rootは0)
    
        potential_dsu() : n(0) {}
        explicit potential_dsu(int n_) { init(n_); }
    
        void init(int n_) {
            n = n_;
            parent_or_size.assign(n, -1);
            diff_weight.assign(n, T{}); // 0
        }
    
        // leader を求めつつ、diff_weight を root 基準に畳み込む
        int leader(int a) {
            if (parent_or_size[a] < 0) return a;
            int p = parent_or_size[a];
            int r = leader(p);
            diff_weight[a] += diff_weight[p];
            parent_or_size[a] = r;
            return r;
        }
    
        bool same(int a, int b) { return leader(a) == leader(b); }
    
        int size(int a) { return -parent_or_size[leader(a)]; }
    
        // pot[a] - pot[leader(a)]
        T potential(int a) {
            leader(a);
            return diff_weight[a];
        }
    
        // pot[b] - pot[a]
        T diff(int a, int b) {
            // 呼び出し側で same(a,b) を保証（ACL dsu と同様に未定義扱い）
            return potential(b) - potential(a);
        }
    
        // pot[b] - pot[a] = w を追加してマージ（ACL dsu と同じく leader を返す）
        int merge(int a, int b, T w) {
            w += potential(a);
            w -= potential(b);
            int x = leader(a), y = leader(b);
            if (x == y) return x;
    
            // union by size (ACL dsu 風)
            if (-parent_or_size[x] < -parent_or_size[y]) {
                std::swap(x, y);
                w = -w;
            }
    
            parent_or_size[x] += parent_or_size[y];
            parent_or_size[y] = x;
            diff_weight[y] = w; // pot[y] - pot[x] = w
            return x;
        }
    
        std::vector<std::vector<int>> groups() {
            std::vector<int> leader_buf(n), group_size(n);
            for (int i = 0; i < n; i++) {
                leader_buf[i] = leader(i);
                group_size[leader_buf[i]]++;
            }
            std::vector<std::vector<int>> result(n);
            for (int i = 0; i < n; i++) result[i].reserve(group_size[i]);
            for (int i = 0; i < n; i++) result[leader_buf[i]].push_back(i);
            result.erase(std::remove_if(result.begin(), result.end(),
                                   [](const auto& v) { return v.empty(); }),
                         result.end());
            return result;
        }
    };
}
