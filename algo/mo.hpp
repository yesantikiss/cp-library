#pragma once

#include <algorithm>
#include <cmath>
#include <numeric>
#include <utility>
#include <vector>

namespace yesantikiss {
    struct Mo {
        int n;
        std::vector<std::pair<int, int>> queries; // [l, r)
    
        explicit Mo(int n) : n(n) {}
        void add_query(int l, int r) { queries.emplace_back(l, r); }
    
        // add(i), del(i) しか要らないケース（互換）
        template <class Add, class Del, class Out>
        void solve(const Add& add, const Del& del, const Out& out) {
            solve(add, add, del, del, out); // 左右同じ関数として扱う
        }
    
        // 左右で add/del を分けたいケース
        // addL: 左に伸ばすときに追加 (l--)
        // addR: 右に伸ばすときに追加 (r++)
        // delL: 左を縮めるときに削除 (l++)
        // delR: 右を縮めるときに削除 (r--)
        template <class AddL, class AddR, class DelL, class DelR, class Out>
        void solve(const AddL& addL, const AddR& addR, const DelL& delL, const DelR& delR, const Out& out) {
            int q = (int)queries.size();
            if (q == 0) return;
    
            int bs = std::max(1, (int)(n / std::sqrt((double)q)));
            std::vector<int> ord(q);
            std::iota(ord.begin(), ord.end(), 0);
    
            std::sort(ord.begin(), ord.end(), [&](int a, int b) {
                int ab = queries[a].first / bs, bb = queries[b].first / bs;
                if (ab != bb) return ab < bb;
                return (ab & 1) ? queries[a].second > queries[b].second
                                : queries[a].second < queries[b].second;
            });
    
            int l = 0, r = 0;
            for (int idx : ord) {
                auto [ql, qr] = queries[idx];
    
                while (l > ql) addL(--l);
                while (r < qr) addR(r++);
                while (l < ql) delL(l++);
                while (r > qr) delR(--r);
    
                out(idx);
            }
        }
    };
    
}
