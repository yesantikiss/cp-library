#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace yesantikiss {
    template <class T>
    struct Compressor {
        std::vector<T> xs;   // 追加された値（重複あり）
        std::vector<T> v;    // ソート済みユニーク列
        bool built = false;
    
        // 値を追加: 平均 O(1)
        void add(const T& x) {
            xs.push_back(x);
        }
    
        // 範囲追加: O(k)
        template <class It>
        void add_range(It first, It last) {
            xs.insert(xs.end(), first, last);
        }
    
        // 構築: O(n log n)  n = add された総数
        void build() {
            v = xs;
            std::sort(v.begin(), v.end());
            v.erase(std::unique(v.begin(), v.end()), v.end());
            built = true;
        }
    
        // 圧縮後の要素数: O(1)
        int size() const {
            return (int)v.size();
        }
    
        // x の圧縮後インデックスを返す。存在しなければ -1: O(log n)
        int get(const T& x) const {
            assert(built);
            auto it = std::lower_bound(v.begin(), v.end(), x);
            if (it == v.end() || *it != x) return -1;
            return (int)(it - v.begin());
        }
    
        // x が存在するか: O(log n)
        bool has(const T& x) const {
            return get(x) != -1;
        }
    
        // v[i] >= x となる最小 i を返す。全て < x なら size(): O(log n)
        int lower_bound(const T& x) const {
            assert(built);
            return (int)(std::lower_bound(v.begin(), v.end(), x) - v.begin());
        }
    
        // v[i] > x となる最小 i を返す。全て <= x なら size(): O(log n)
        int upper_bound(const T& x) const {
            assert(built);
            return (int)(std::upper_bound(v.begin(), v.end(), x) - v.begin());
        }
    
        // 圧縮値 → 元の値: O(1)
        const T& value(int idx) const {
            assert(built);
            return v[idx];
        }
    
        // 配列を圧縮インデックス列に変換して返す（存在しない値は -1）: O(k log n)
        std::vector<int> map(const std::vector<T>& a) const {
            assert(built);
            std::vector<int> res; res.reserve(a.size());
            for (auto& x : a) res.push_back(get(x));
            return res;
        }
    };
}
