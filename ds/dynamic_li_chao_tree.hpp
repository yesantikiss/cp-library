#pragma once

#include <cassert>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <utility>
#include <vector>

namespace yesantikiss {
    // 動的 Li Chao Tree
    // - 座標範囲 [lo, hi) の整数点で直線・線分の最小値（最大値）を扱う
    // - 直線が入った経路だけノード生成
    // - add_all で全直線に一次関数を一括加算
    // - T: 座標の型（整数型のみ）, U: 係数と評価に使う型（オーバーフローするなら __int128）
    // - Compare: std::less<> なら最小値、std::greater<> なら最大値

    template <class T, class Compare = std::less<>, class U = T>
    struct DynamicLiChaoTree {
        static_assert(std::is_integral_v<T> || std::is_same_v<T, __int128>,
                      "T must be an integer type");

    private:
        struct Line {
            U a, b;
            U eval(T x) const { return a * U(x) + b; }
        };

        struct Node {
            Line line{U(0), U(0)};
            bool has = false;
            int l = -1, r = -1;
        };

        T lo_ = 0, hi_ = 1;
        U add_a_ = 0, add_b_ = 0;
        int root_ = -1;
        std::vector<Node> pool_;

        static bool better(const Line& f, const Line& g, T x) {
            return Compare{}(f.eval(x), g.eval(x));
        }

        int new_node() {
            pool_.emplace_back();
            return (int)pool_.size() - 1;
        }

        int child(int v, bool right) {
            int c = right ? pool_[v].r : pool_[v].l;
            if (c == -1) {
                c = new_node();
                (right ? pool_[v].r : pool_[v].l) = c;
            }
            return c;
        }

        // ノード v（担当区間 [l, r)）以下に直線 f を入れる
        void insert_line(int v, T l, T r, Line f) {
            while (true) {
                Node& nd = pool_[v];
                if (!nd.has) {
                    nd.line = f;
                    nd.has = true;
                    return;
                }
                bool left_better = better(f, nd.line, l);
                bool right_better = better(f, nd.line, r - 1);
                // 区間の両端で負けるなら全体で負け、両端で勝つなら全体で勝ち
                if (!left_better && !right_better) return;
                if (left_better && right_better) {
                    nd.line = f;
                    return;
                }
                T m = l + (r - l) / 2;
                bool mid_better = better(f, nd.line, m);
                if (mid_better) std::swap(nd.line, f);
                if (r - l == 1) return;
                if (left_better != mid_better) {
                    v = child(v, false);
                    r = m;
                } else {
                    v = child(v, true);
                    l = m;
                }
            }
        }

        void insert_segment(int v, T nl, T nr, T l, T r, const Line& f) {
            if (r <= nl || nr <= l) return;
            if (l <= nl && nr <= r) {
                insert_line(v, nl, nr, f);
                return;
            }
            T m = nl + (nr - nl) / 2;
            if (l < m) insert_segment(child(v, false), nl, m, l, r, f);
            if (m < r) insert_segment(child(v, true), m, nr, l, r, f);
        }

        // x を通る経路上の最良値。直線がなければ first = false
        std::pair<bool, U> query(T x) const {
            assert(lo_ <= x && x < hi_);
            bool found = false;
            U best = 0;
            int v = root_;
            T l = lo_, r = hi_;
            while (v != -1) {
                const Node& nd = pool_[v];
                if (nd.has) {
                    U y = nd.line.eval(x);
                    if (!found || Compare{}(y, best)) best = y;
                    found = true;
                }
                if (r - l == 1) break;
                T m = l + (r - l) / 2;
                if (x < m) {
                    v = nd.l;
                    r = m;
                } else {
                    v = nd.r;
                    l = m;
                }
            }
            return {found, best};
        }

    public:
        DynamicLiChaoTree() = default;
        DynamicLiChaoTree(T lo, T hi) { init(lo, hi); }

        void init(T lo, T hi) {
            assert(lo < hi);
            lo_ = lo;
            hi_ = hi;
            add_a_ = add_b_ = 0;
            root_ = -1;
            pool_.clear();
        }

        void reserve_nodes(std::size_t m) { pool_.reserve(m); }

        // 直線 ax + b を全域に追加
        void add_line(U a, U b) {
            if (root_ == -1) root_ = new_node();
            insert_line(root_, lo_, hi_, Line{a - add_a_, b - add_b_});
        }

        // 線分 ax + b を [l, r) にだけ追加
        void add_segment(U a, U b, T l, T r) {
            assert(lo_ <= l && l <= r && r <= hi_);
            if (l == r) return;
            if (root_ == -1) root_ = new_node();
            insert_segment(root_, lo_, hi_, l, r,
                           Line{a - add_a_, b - add_b_});
        }

        // 追加済みのすべての直線に px + q を加算
        void add_all(U p, U q) {
            add_a_ += p;
            add_b_ += q;
        }

        bool has_line(T x) const { return query(x).first; }

        // x での最小値（std::greater<> なら最大値）。x に直線がある必要あり
        U get(T x) const {
            std::pair<bool, U> res = query(x);
            assert(res.first);
            return res.second + add_a_ * U(x) + add_b_;
        }
    };
}
