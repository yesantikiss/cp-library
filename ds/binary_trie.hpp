#pragma once

#include <cassert>
#include <vector>

namespace yesantikiss {
    template<int B>
    struct BinaryTrie {
        static_assert(0 < B && B <= 63);
        using ull = unsigned long long;
    
        struct Node {
            int ch[2];
            long long cnt; // subtree size (with multiplicity)
            long long end; // exact value count at leaf
            Node() : ch{-1, -1}, cnt(0), end(0) {}
        };
    
        std::vector<Node> tr;
        BinaryTrie() { tr.emplace_back(); }
    
        long long size() const { return tr[0].cnt; }
        bool empty() const { return size() == 0; }
    
        void insert(ull x) { add_raw(x, +1); }
    
        // erase one occurrence; returns false if not present
        bool erase(ull x) {
            if (count_raw(x) == 0) return false;
            add_raw(x, -1);
            return true;
        }
    
        // count/contains in {v xor T} multiset (T=0 => normal)
        long long count(ull v, ull T = 0) const { return count_raw(v ^ T); }
        bool contains(ull v, ull T = 0) const { return count(v, T) > 0; }
    
        // kth (0-index) in sorted {x xor T}
        ull kth(long long k, ull T = 0) const {
            assert(0 <= k && k < size());
            int v = 0;
            ull y = 0;
    
            for (int b = B - 1; b >= 0; --b) {
                int tb = (T >> b) & 1ULL;
                int pref = tb;      // ybit=0 needs xbit=tb
                int other = tb ^ 1;
    
                int vp = tr[v].ch[pref];
                long long cnt_pref = (vp == -1 ? 0 : tr[vp].cnt);
    
                if (k < cnt_pref) {
                    v = vp; // ybit=0
                    assert(v != -1);
                } else {
                    k -= cnt_pref;
                    v = tr[v].ch[other]; // ybit=1
                    assert(v != -1);
                    y |= (1ULL << b);
                }
            }
            return y;
        }
    
        ull min_element(ull T = 0) const {
            assert(!empty());
            return kth(0, T);
        }
    
        ull max_element(ull T = 0) const {
            assert(!empty());
            return kth(size() - 1, T);
        }
    
    private:
        void add_raw(ull x, long long delta) {
            int v = 0;
            tr[v].cnt += delta;
            for (int b = B - 1; b >= 0; --b) {
                int bit = (x >> b) & 1ULL;
                if (tr[v].ch[bit] == -1) {
                    tr[v].ch[bit] = (int)tr.size();
                    tr.emplace_back();
                }
                v = tr[v].ch[bit];
                tr[v].cnt += delta;
            }
            tr[v].end += delta;
        }
    
        long long count_raw(ull x) const {
            int v = 0;
            for (int b = B - 1; b >= 0; --b) {
                int bit = (x >> b) & 1ULL;
                v = tr[v].ch[bit];
                if (v == -1) return 0;
            }
            return tr[v].end;
        }
    };
    
    // usage example:
    // using BT = BinaryTrie<30>; // for [0, 1e9]
    
}
