#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace yesantikiss {
    template<class S, S (*op)(S, S), S (*e)()>
    struct persistent_segtree {
        struct Node {
            S val;
            int lch, rch;
        };
    
        int n = 0;
        std::vector<Node> nodes;
        std::vector<int> roots; // roots[version] = その版の根ノード index
    
        persistent_segtree() = default;
    
        explicit persistent_segtree(const std::vector<S>& a) {
            init(a);
        }
    
        explicit persistent_segtree(int n_) {
            init(std::vector<S>(n_, e()));
        }
    
        int new_node(const S& val, int lch = -1, int rch = -1) {
            nodes.push_back({val, lch, rch});
            return (int)nodes.size() - 1;
        }
    
        int build(int l, int r, const std::vector<S>& a) {
            if (r - l == 1) {
                return new_node(a[l]);
            }
            int m = (l + r) >> 1;
            int lc = build(l, m, a);
            int rc = build(m, r, a);
            return new_node(op(nodes[lc].val, nodes[rc].val), lc, rc);
        }
    
        void init(const std::vector<S>& a) {
            n = (int)a.size();
            nodes.clear();
            roots.clear();
    
            nodes.reserve(std::max(1, 2 * n));
    
            if (n == 0) {
                roots.push_back(-1); // version 0 は空配列版
                return;
            }
    
            int root0 = build(0, n, a);
            roots.push_back(root0); // 初期版の version は 0
        }
    
        int versions() const {
            return (int)roots.size();
        }
    
        int latest_version() const {
            return (int)roots.size() - 1;
        }
    
        int normalize_version(int ver) const {
            if (ver == -1) return latest_version();
            assert(0 <= ver && ver < (int)roots.size());
            return ver;
        }
    
        int set_rec(int node, int l, int r, int p, const S& x) {
            if (r - l == 1) {
                return new_node(x);
            }
    
            int m = (l + r) >> 1;
            int lc = nodes[node].lch;
            int rc = nodes[node].rch;
    
            if (p < m) {
                lc = set_rec(lc, l, m, p, x);
            } else {
                rc = set_rec(rc, m, r, p, x);
            }
    
            return new_node(op(nodes[lc].val, nodes[rc].val), lc, rc);
        }
    
        S get_rec(int node, int l, int r, int p) const {
            if (r - l == 1) {
                return nodes[node].val;
            }
    
            int m = (l + r) >> 1;
            if (p < m) return get_rec(nodes[node].lch, l, m, p);
            return get_rec(nodes[node].rch, m, r, p);
        }
    
        S prod_rec(int node, int l, int r, int ql, int qr) const {
            if (qr <= l || r <= ql) return e();
            if (ql <= l && r <= qr) return nodes[node].val;
    
            int m = (l + r) >> 1;
            return op(
                prod_rec(nodes[node].lch, l, m, ql, qr),
                prod_rec(nodes[node].rch, m, r, ql, qr)
            );
        }
    
        // ver 版を元に p 番目を x に変更した新しい版を末尾に追加
        // ver = -1 なら最新版を元にする
        // 返り値は新しい version 番号
        int set(int p, const S& x, int ver = -1) {
            assert(0 <= p && p < n);
            ver = normalize_version(ver);
            int new_root = set_rec(roots[ver], 0, n, p, x);
            roots.push_back(new_root);
            return latest_version();
        }
    
        S get(int p, int ver = -1) const {
            assert(0 <= p && p < n);
            ver = normalize_version(ver);
            return get_rec(roots[ver], 0, n, p);
        }
    
        S prod(int l, int r, int ver = -1) const {
            assert(0 <= l && l <= r && r <= n);
            ver = normalize_version(ver);
            if (n == 0) return e();
            return prod_rec(roots[ver], 0, n, l, r);
        }
    
        S all_prod(int ver = -1) const {
            ver = normalize_version(ver);
            if (n == 0) return e();
            return nodes[roots[ver]].val;
        }
    };
}
