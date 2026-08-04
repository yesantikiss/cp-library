#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <iterator>
#include <ostream>
#include <set>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace yesantikiss {
    using std::distance;
    using std::max;
    using std::min;
    using std::next;
    using std::ostream;
    using std::prev;
    using std::set;
    using std::vector;
    /*
      IntervalMap（区間 map / 区間 set 管理：完成形）
      ==============================================
      半開区間 [l, r) を set で管理し、各区間に値 v を持たせる。
    
      ■ 不変量（これが崩れないように実装する）
      ----------------------------------------
      1) 区間は互いに交差しない
      2) 常に [L, R) を完全に被覆している（init で 1 本入れて開始）
      3) 隣接して値が同じ区間は存在しない（自動マージで潰す）
    
      ■ 主要 API
      ----------
      - locate(x)        : x を含む区間の iterator を返す（走査・ジャンプ用）
      - get_val(x)       : 点 x の値
      - assign(l,r,v)    : [l,r) を v に「代入」（split + erase + insert + merge）
      - apply(l,r,f)     : [l,r) にかかる各区間の値を f で変換
          f は以下どちらでもOK:
            (A) V f(const V&)
            (B) V f(T l, T r, const V&)
      - enumerate_cut(l,r,f) : [l,r) にかかる区間を「必ず [l,r) に切った形」で列挙
      - segments_cut(l,r)    : enumerate_cut の vector 版（デバッグ・回答生成用）
    
      ■ add/del コールバック
      --------------------------------------
      split / assign / apply / merge が内部で区間を消したり作ったりするので、
      「区間が増減したときの寄与更新」を外から渡せるようにする。
    
        add(l,r,v): 区間 [l,r) の値 v が “追加” された
        del(l,r,v): 区間 [l,r) の値 v が “削除” された
    
      例：値ごとの総長 len[v] を維持したい
        add: len[v] += (r-l)
        del: len[v] -= (r-l)
    
      ■ 超重要な注意
      --------------
      assign/apply/enumerate_cut は内部で erase/insert を行うため、
      それ以前に取った iterator は無効化され得る。
      → 更新後に iterator を使い回さず、locate などで取り直す。
    */
    
    template <class T, class V>
    struct IntervalMap {
        struct Node {
            T l, r;
            V v;
        };
    
        // set は l の昇順。transparent comparator にして lower_bound(x) を直接使えるようにする。
        struct Cmp {
            using is_transparent = void;
            bool operator()(const Node& a, const Node& b) const { return a.l < b.l; }
            bool operator()(const Node& a, const T& x)   const { return a.l < x; }
            bool operator()(const T& x, const Node& a)   const { return x < a.l; }
        };
    
        T L, R;
        set<Node, Cmp> s;
    
        IntervalMap() = default;
    
        // [L, R) を init で完全被覆してスタート（番兵を兼ねる）
        IntervalMap(T L_, T R_, V init) : L(L_), R(R_) {
            assert(L < R);
            s.insert(Node{L, R, init});
        }
    
        auto begin() { return s.begin(); }
        auto end()   { return s.end(); }
        auto begin() const { return s.begin(); }
        auto end()   const { return s.end(); }
    
        // x を含む区間の iterator を返す（L <= x < R を前提）
        auto locate(T x) {
            assert(L <= x && x < R);
            auto it = s.upper_bound(x); // l > x となる最初
            --it;                       // その1つ前が必ず x を含む（完全被覆なので）
            return it;
        }
        auto locate(T x) const {
            assert(L <= x && x < R);
            auto it = s.upper_bound(x);
            --it;
            return it;
        }
    
        // 点の値
        V get_val(T x) const {
            return locate(x)->v;
        }
    
    private:
        // f を呼ぶ：f(v) または f(l,r,v) に対応
        template <class F>
        static V call_f(F& f, T l, T r, const V& v) {
            if constexpr (std::is_invocable_r_v<V, F, const V&>) {
                return f(v);
            } else {
                static_assert(std::is_invocable_r_v<V, F, T, T, const V&>,
                              "apply: f must be V(const V&) or V(T,T,const V&)");
                return f(l, r, v);
            }
        }
    
        // split(x): x を境に区間を割って「x から始まる区間」の iterator を返す
        // split も区間構造を変えるので add/del を呼んで集計の整合を保つ。
        template <class ADD, class DEL>
        auto split(T x, ADD add, DEL del) {
            if (x <= L) return s.begin();
            if (x >= R) return s.end();
    
            auto it = locate(x);
            if (it->l == x) return it; // すでに境界がある
    
            Node cur = *it;
    
            // 元区間の寄与を消してから分割
            del(cur.l, cur.r, cur.v);
            s.erase(it);
    
            auto itL = s.insert(Node{cur.l, x, cur.v}).first;
            auto itR = s.insert(Node{x, cur.r, cur.v}).first;
            add(itL->l, itL->r, itL->v);
            add(itR->l, itR->r, itR->v);
    
            return itR;
        }
    
        // it の左右を見て「隣接かつ同値」を可能な限りマージ
        template <class ADD, class DEL>
        auto merge_around(typename set<Node, Cmp>::iterator it, ADD add, DEL del) {
            bool changed = true;
            while (changed) {
                changed = false;
    
                // 左とマージ
                if (it != s.begin()) {
                    auto pv = prev(it);
                    if (pv->r == it->l && pv->v == it->v) {
                        Node a = *pv, b = *it;
                        del(a.l, a.r, a.v);
                        del(b.l, b.r, b.v);
                        s.erase(pv);
                        s.erase(it);
                        it = s.insert(Node{a.l, b.r, a.v}).first;
                        add(it->l, it->r, it->v);
                        changed = true;
                        continue;
                    }
                }
    
                // 右とマージ
                auto nx = next(it);
                if (nx != s.end()) {
                    if (it->r == nx->l && it->v == nx->v) {
                        Node a = *it, b = *nx;
                        del(a.l, a.r, a.v);
                        del(b.l, b.r, b.v);
                        s.erase(it);
                        s.erase(nx);
                        it = s.insert(Node{a.l, b.r, a.v}).first;
                        add(it->l, it->r, it->v);
                        changed = true;
                        continue;
                    }
                }
            }
            return it;
        }
    
        // ある近傍だけ「隣接同値」を潰す（apply/enumerate_cut で split したあとに使う）
        template <class ADD, class DEL>
        void normalize_window(T l, T r, ADD add, DEL del) {
            auto it = s.lower_bound(l);
            if (it != s.begin()) it = prev(it);
    
            while (it != s.end()) {
                auto nx = next(it);
                if (nx == s.end()) break;
    
                if (it->r == nx->l && it->v == nx->v) {
                    Node a = *it, b = *nx;
                    del(a.l, a.r, a.v);
                    del(b.l, b.r, b.v);
                    s.erase(it);
                    s.erase(nx);
                    it = s.insert(Node{a.l, b.r, a.v}).first;
                    add(it->l, it->r, it->v);
                    if (it != s.begin()) it = prev(it);
                } else {
                    // 触った範囲より十分右に来たら打ち切り（保守的）
                    if (it->l >= r && nx->l >= r) break;
                    it = nx;
                }
            }
        }
    
    public:
        // assign: [l,r) を v に代入（add/del 付き）
        template <class ADD, class DEL>
        void assign(T l, T r, const V& v, ADD add, DEL del) {
            l = max(l, L);
            r = min(r, R);
            if (l >= r) return;
    
            auto itr = split(r, add, del);
            auto itl = split(l, add, del);
    
            for (auto it = itl; it != itr; ) {
                del(it->l, it->r, it->v);
                it = s.erase(it);
            }
    
            auto it = s.insert(Node{l, r, v}).first;
            add(l, r, v);
    
            merge_around(it, add, del);
        }
    
        // assign: コールバックなし
        void assign(T l, T r, const V& v) {
            assign(l, r, v,
                   [](T, T, const V&) {},
                   [](T, T, const V&) {});
        }
    
        // apply: [l,r) にかかる各区間の値を f で変換（add/del 付き）
        template <class F, class ADD, class DEL>
        void apply(T l, T r, F f, ADD add, DEL del) {
            l = max(l, L);
            r = min(r, R);
            if (l >= r) return;
    
            auto itr = split(r, add, del);
            auto itl = split(l, add, del);
    
            // set をいじりながら変換すると壊れやすいので、一旦退避してから入れ直す
            vector<Node> segs;
            segs.reserve(distance(itl, itr));
    
            for (auto it = itl; it != itr; ++it) {
                Node nd = *it;
                del(nd.l, nd.r, nd.v);
                nd.v = call_f(f, nd.l, nd.r, nd.v);
                segs.push_back(nd);
            }
    
            for (auto it = itl; it != itr; ) it = s.erase(it);
    
            for (auto &nd : segs) {
                s.insert(nd);
                add(nd.l, nd.r, nd.v);
            }
    
            // split の結果生まれた同値隣接を潰す
            normalize_window(l, r, add, del);
        }
    
        // apply: コールバックなし
        template <class F>
        void apply(T l, T r, F f) {
            apply(l, r, f,
                  [](T, T, const V&) {},
                  [](T, T, const V&) {});
        }
    
        /*
          enumerate_cut(l, r, f):
          ----------------------
          [l,r) にかかる区間を「必ず [l,r) に切った形」で列挙する。
    
          例：
            元が [0,10)=A で enumerate_cut(3,7) を呼ぶと、
            split により [0,3)=A [3,7)=A [7,10)=A の形に一旦なり、
            f(3,7,A) が呼ばれる。
    
          計算量（目安）: O(log M + k)
            - split が高々2回: O(log M)（M=区間数）
            - 交差区間を k 個列挙: O(k)
            - normalize は触った周辺だけ（定数倍が少し増える程度）
        */
        template <class F, class ADD, class DEL>
        void enumerate_cut(T l, T r, F f, ADD add, DEL del) {
            l = max(l, L);
            r = min(r, R);
            if (l >= r) return;
    
            auto itr = split(r, add, del);
            auto itl = split(l, add, del);
    
            for (auto it = itl; it != itr; ++it) {
                f(it->l, it->r, it->v);
            }
    
            // splitで同値隣接が生まれた可能性があるので戻す
            normalize_window(l, r, add, del);
        }
    
        template <class F>
        void enumerate_cut(T l, T r, F f) {
            enumerate_cut(l, r, f,
                          [](T, T, const V&) {},
                          [](T, T, const V&) {});
        }
    
        // vector で欲しい場合（デバッグや「区間列を材料に答えを作る」用途）
        vector<Node> segments_cut(T l, T r) {
            vector<Node> res;
            enumerate_cut(l, r, [&](T a, T b, const V& v) {
                res.push_back(Node{a, b, v});
            });
            return res;
        }
    
        // デバッグ：全区間を出力
        friend ostream& operator<<(ostream& os, const IntervalMap& im) {
            for (auto &nd : im.s) {
                os << "[" << nd.l << "," << nd.r << ")=" << nd.v << " ";
            }
            return os;
        }
    };
}
