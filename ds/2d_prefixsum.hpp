#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace yesantikiss {
    // 2D Prefix/Imos (single diff, single O(HW) build)
    // 仕様: 0-index, 半開区間 [y1,y2)×[x1,x2)
    // 使い分け: set_pointのみ→SETモード / add_rect_imosのみ→IMOSモード（併用禁止）
    template<class T>
    struct PS2D {
        enum Mode { EMPTY, SET_MODE, IMOS_MODE };
    
        int H, W;
        Mode mode = EMPTY;
        std::vector<std::vector<T>> buf;   // SET: 値行列としてH×Wのみ使用 / IMOS: 差分として(H+1)×(W+1)全面使用
        std::vector<std::vector<T>> grid;  // build後の完成グリッド H×W
        std::vector<std::vector<T>> pref;  // 2D累積和 (H+1)×(W+1)
        bool built = false;
    
        PS2D(int H, int W): H(H), W(W),
            buf(H+1, std::vector<T>(W+1, T())),
            grid(H, std::vector<T>(W, T())),
            pref(H+1, std::vector<T>(W+1, T())) {}
    
        // 単点上書き: SETモード専用
        void set_point(int y, int x, T v) {
            assert(0 <= y && y < H && 0 <= x && x < W);
            assert(mode == EMPTY || mode == SET_MODE);
            mode = SET_MODE;
            buf[y][x] = v;   // bufは値行列として使用（H×W領域）
            built = false;
        }
    
        // 長方形加算: IMOSモード専用
        void add_rect_imos(int y1, int x1, int y2, int x2, T v) {
            assert(0 <= y1 && y1 <= y2 && y2 <= H);
            assert(0 <= x1 && x1 <= x2 && x2 <= W);
            assert(mode == EMPTY || mode == IMOS_MODE);
            mode = IMOS_MODE;
            // bufは差分として使用（(H+1)×(W+1)）
            buf[y1][x1] += v;
            buf[y1][x2] -= v;
            buf[y2][x1] -= v;
            buf[y2][x2] += v;
            built = false;
        }
    
        // 点加算(imos)
        void add_point_imos(int y, int x, T v) { add_rect_imos(y, x, y+1, x+1, v); }
    
        // クリア
        void clear_all() {
            for (int y = 0; y <= H; ++y) std::fill(buf[y].begin(), buf[y].end(), T());
            built = false;
            mode = EMPTY;
        }
    
        // 構築: 常にO(HW) 1回で grid と pref を同時に生成
        void build() {
            for (int y = 0; y <= H; ++y) std::fill(pref[y].begin(), pref[y].end(), T());
    
            if (mode == SET_MODE) {
                // buf[y][x] を値としてそのまま累積
                for (int y = 0; y < H; ++y) {
                    T row_sum = T();
                    for (int x = 0; x < W; ++x) {
                        T v = buf[y][x];
                        grid[y][x] = v;
                        row_sum += v;
                        pref[y+1][x+1] = pref[y][x+1] + row_sum;
                    }
                }
            } else {
                // IMOS_MODE または EMPTY（EMPTYは全0）
                // bufは差分。gridにimosを累積しつつprefも同時に作る
                for (int y = 0; y < H; ++y) {
                    for (int x = 0; x < W; ++x) {
                        T v = buf[y][x];
                        if (y) v += grid[y-1][x];
                        if (x) v += grid[y][x-1];
                        if (y && x) v -= grid[y-1][x-1];
                        grid[y][x] = v;
    
                        pref[y+1][x+1] = pref[y][x+1] + pref[y+1][x] - pref[y][x] + v;
                    }
                }
            }
            built = true;
        }
    
        // 単点取得 O(1)
        T at(int y, int x) const {
            assert(built);
            assert(0 <= y && y < H && 0 <= x && x < W);
            return grid[y][x];
        }
        T operator()(int y, int x) const { return at(y, x); }
    
        struct RowProxy {
            const PS2D* p; int y;
            T operator[](int x) const {
                assert(p->built); assert(0 <= x && x < p->W);
                return p->grid[y][x];
            }
        };
        RowProxy operator[](int y) const { assert(built); return RowProxy{this, y}; }
    
        // 長方形和 O(1)  [y1,y2)×[x1,x2)
        T sum(int y1, int x1, int y2, int x2) const {
            assert(built);
            assert(0 <= y1 && y1 <= y2 && y2 <= H);
            assert(0 <= x1 && x1 <= x2 && x2 <= W);
            return pref[y2][x2] - pref[y1][x2] - pref[y2][x1] + pref[y1][x1];
        }
    
        // 全体和
        T sum_all() const { assert(built); return pref[H][W]; }
    };
}
