#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

// 動的（implicit）セグメント木
// - 区間 [0, n) を扱う
// - 更新が入った経路だけノード生成
// - ACL segtree 風インタフェース

namespace yesantikiss {
    // 動的（implicit）セグメント木
    // - 区間 [0, n) を扱う
    // - 更新が入った経路だけノード生成
    // - ACL segtree 風インタフェース
    
    template <class S, S (*op)(S, S), S (*e)()>
    struct dynamic_segtree {
    private:
        struct Node {
            int l = -1, r = -1;
            S val;
            Node() : val(e()) {}
        };
    
        long long n_ = 0;
        unsigned long long size_ = 1;
        int root_ = -1;
        std::vector<Node> pool_;
    
        static unsigned long long ceil_pow2_ull(unsigned long long x) {
            unsigned long long p = 1;
            while (p < x) p <<= 1;
            return p;
        }
    
        int new_node() {
            pool_.emplace_back();
            return (int)pool_.size() - 1;
        }
    
        S node_val(int idx) const {
            return (idx == -1) ? e() : pool_[idx].val;
        }
    
        S prod_rec(int idx,
                   unsigned long long segL, unsigned long long segR,
                   unsigned long long ql, unsigned long long qr) const {
            if (idx == -1) return e();
            if (qr <= segL || segR <= ql) return e();
            if (ql <= segL && segR <= qr) return pool_[idx].val;
            unsigned long long mid = (segL + segR) >> 1;
            S left = prod_rec(pool_[idx].l, segL, mid, ql, qr);
            S right = prod_rec(pool_[idx].r, mid, segR, ql, qr);
            return op(left, right);
        }
    
        template <class F>
        long long max_right_rec(int idx,
                                unsigned long long segL, unsigned long long segR,
                                unsigned long long ql,
                                F& f, S& sm) const {
            if (segR <= ql) return (long long)ql;
            S segVal = (idx == -1) ? e() : pool_[idx].val;
            if (segL >= ql) {
                S nxt = op(sm, segVal);
                if (f(nxt)) {
                    sm = nxt;
                    return (long long)segR;
                }
                if (segR - segL == 1) return (long long)segL;
            }
            unsigned long long mid = (segL + segR) >> 1;
            int lch = (idx == -1) ? -1 : pool_[idx].l;
            int rch = (idx == -1) ? -1 : pool_[idx].r;
            long long resL = max_right_rec(lch, segL, mid, ql, f, sm);
            if ((unsigned long long)resL < mid) return resL;
            return max_right_rec(rch, mid, segR, ql, f, sm);
        }
    
        template <class F>
        long long min_left_rec(int idx,
                               unsigned long long segL, unsigned long long segR,
                               unsigned long long qr,
                               F& f, S& sm) const {
            if (qr <= segL) return (long long)qr;
            S segVal = (idx == -1) ? e() : pool_[idx].val;
            if (segR <= qr) {
                S nxt = op(segVal, sm);
                if (f(nxt)) {
                    sm = nxt;
                    return (long long)segL;
                }
                if (segR - segL == 1) return (long long)segR;
            }
            unsigned long long mid = (segL + segR) >> 1;
            int lch = (idx == -1) ? -1 : pool_[idx].l;
            int rch = (idx == -1) ? -1 : pool_[idx].r;
            long long resR = min_left_rec(rch, mid, segR, qr, f, sm);
            if ((unsigned long long)resR > mid) return resR;
            return min_left_rec(lch, segL, mid, qr, f, sm);
        }
    
        template <bool APPLY>
        void point_update(long long p, const S& x) {
            assert(0 <= p && p < n_);
            if (root_ == -1) root_ = new_node();
            int idx = root_;
            unsigned long long segL = 0, segR = size_;
            int path[70];
            int psz = 0;
            path[psz++] = idx;
            while (segR - segL > 1) {
                unsigned long long mid = (segL + segR) >> 1;
                if ((unsigned long long)p < mid) {
                    if (pool_[idx].l == -1) {
                        int child = new_node();
                        pool_[idx].l = child;
                    }
                    idx = pool_[idx].l;
                    segR = mid;
                } else {
                    if (pool_[idx].r == -1) {
                        int child = new_node();
                        pool_[idx].r = child;
                    }
                    idx = pool_[idx].r;
                    segL = mid;
                }
                path[psz++] = idx;
            }
            if constexpr (APPLY) {
                pool_[idx].val = op(pool_[idx].val, x);
            } else {
                pool_[idx].val = x;
            }
            for (int i = psz - 2; i >= 0; --i) {
                int v = path[i];
                pool_[v].val = op(node_val(pool_[v].l), node_val(pool_[v].r));
            }
        }
    
    public:
        dynamic_segtree() = default;
        explicit dynamic_segtree(long long n) { init(n); }
    
        void init(long long n) {
            assert(n >= 0);
            n_ = n;
            size_ = ceil_pow2_ull((unsigned long long)std::max(1LL, n_));
            root_ = -1;
            pool_.clear();
        }
    
        void reserve_nodes(std::size_t m) { pool_.reserve(m); }
    
        long long size() const { return n_; }
    
        S all_prod() const {
            return (root_ == -1) ? e() : pool_[root_].val;
        }
    
        S get(long long p) const {
            assert(0 <= p && p < n_);
            int idx = root_;
            if (idx == -1) return e();
            unsigned long long segL = 0, segR = size_;
            while (segR - segL > 1 && idx != -1) {
                unsigned long long mid = (segL + segR) >> 1;
                if ((unsigned long long)p < mid) {
                    idx = pool_[idx].l;
                    segR = mid;
                } else {
                    idx = pool_[idx].r;
                    segL = mid;
                }
            }
            return (idx == -1) ? e() : pool_[idx].val;
        }
    
        void set(long long p, S x) { point_update<false>(p, x); }
        void apply_point(long long p, S x) { point_update<true>(p, x); }
    
        S prod(long long l, long long r) const {
            assert(0 <= l && l <= r && r <= n_);
            if (l == r) return e();
            if (root_ == -1) return e();
            return prod_rec(root_, 0, size_,
                            (unsigned long long)l, (unsigned long long)r);
        }
    
        template <class F>
        long long max_right(long long l, F f) const {
            assert(0 <= l && l <= n_);
            assert(f(e()));
            if (l == n_) return n_;
            S sm = e();
            F ff = f;
            long long res = max_right_rec(root_, 0, size_, (unsigned long long)l, ff, sm);
            if (res > n_) res = n_;
            return res;
        }
    
        template <class F>
        long long min_left(long long r, F f) const {
            assert(0 <= r && r <= n_);
            assert(f(e()));
            if (r == 0) return 0;
            S sm = e();
            F ff = f;
            long long res = min_left_rec(root_, 0, size_, (unsigned long long)r, ff, sm);
            if (res < 0) res = 0;
            if (res > r) res = r;
            return res;
        }
    };
}
