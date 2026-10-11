#pragma once

#include <cassert>
#include <vector>

namespace yesantikiss {
    // 二次元累積和 + 二次元いもす法
    // 仕様: 0-index, 半開区間 [y1,y2)×[x1,x2)
    // 更新はすべて差分配列への加算なので、点加算と長方形加算は自由に混ぜてよい
    template <class T>
    struct PS2D {
        int H, W;
        std::vector<std::vector<T>> diff;  // 差分 (H+1)×(W+1)
        std::vector<std::vector<T>> pref;  // 完成グリッドの累積和 (H+1)×(W+1)
        bool built = false;

        PS2D(int H, int W)
            : H(H), W(W),
              diff(H + 1, std::vector<T>(W + 1, T())),
              pref(H + 1, std::vector<T>(W + 1, T())) {}

        // 初期グリッドから構築済みの状態で作る: O(HW)
        explicit PS2D(const std::vector<std::vector<T>>& a)
            : PS2D((int)a.size(), a.empty() ? 0 : (int)a[0].size()) {
            for (int y = 0; y < H; ++y) {
                assert((int)a[y].size() == W);
                for (int x = 0; x < W; ++x) add(y, x, a[y][x]);
            }
            build();
        }

        // 長方形加算: O(1)
        void add_rect(int y1, int x1, int y2, int x2, const T& v) {
            assert(0 <= y1 && y1 <= y2 && y2 <= H);
            assert(0 <= x1 && x1 <= x2 && x2 <= W);
            diff[y1][x1] += v;
            diff[y1][x2] -= v;
            diff[y2][x1] -= v;
            diff[y2][x2] += v;
            built = false;
        }

        // 点加算: O(1)
        void add(int y, int x, const T& v) { add_rect(y, x, y + 1, x + 1, v); }

        // 差分を2回累積して pref を作る: O(HW)
        void build() {
            for (int y = 0; y < H; ++y) {
                for (int x = 0; x < W; ++x) pref[y + 1][x + 1] = diff[y][x];
            }
            for (int k = 0; k < 2; ++k) {  // 1回目で完成グリッド、2回目で累積和
                for (int y = 1; y <= H; ++y) {
                    for (int x = 1; x <= W; ++x) {
                        pref[y][x] += pref[y - 1][x] + pref[y][x - 1] - pref[y - 1][x - 1];
                    }
                }
            }
            built = true;
        }

        // 長方形和: O(1)
        T sum(int y1, int x1, int y2, int x2) const {
            assert(built);
            assert(0 <= y1 && y1 <= y2 && y2 <= H);
            assert(0 <= x1 && x1 <= x2 && x2 <= W);
            return pref[y2][x2] - pref[y1][x2] - pref[y2][x1] + pref[y1][x1];
        }

        // 全体和: O(1)
        T sum() const { return sum(0, 0, H, W); }

        // 点取得: O(1)
        T get(int y, int x) const {
            assert(0 <= y && y < H && 0 <= x && x < W);
            return sum(y, x, y + 1, x + 1);
        }

        // 更新をすべて消去: O(HW)
        void clear() {
            for (auto& row : diff) row.assign(W + 1, T());
            built = false;
        }
    };
}
