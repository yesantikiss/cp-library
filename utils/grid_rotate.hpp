#pragma once

#include <cassert>
#include <vector>

namespace yesantikiss {
    // 二次元配列の回転（すべて時計回り）
    // Row は std::vector<T> でも std::string でもよい
    // H×W の a を 90° 回すと W×H になる: res[i][j] = a[H-1-j][i]
    template <class Row>
    std::vector<Row> rotate90(const std::vector<Row>& a) {
        const int H = (int)a.size();
        if (H == 0) return {};
        const int W = (int)a[0].size();
        std::vector<Row> res(W, Row(H, typename Row::value_type()));
        for (int i = 0; i < H; ++i) {
            assert((int)a[i].size() == W);
            for (int j = 0; j < W; ++j) res[j][H - 1 - i] = a[i][j];
        }
        return res;
    }

    // 180°: res[i][j] = a[H-1-i][W-1-j]
    template <class Row>
    std::vector<Row> rotate180(const std::vector<Row>& a) {
        std::vector<Row> res(a.rbegin(), a.rend());
        for (auto& row : res) {
            assert(row.size() == a[0].size());
            row = Row(row.rbegin(), row.rend());
        }
        return res;
    }

    // 270°（反時計回りに 90°）: res[i][j] = a[j][W-1-i]
    template <class Row>
    std::vector<Row> rotate270(const std::vector<Row>& a) {
        const int H = (int)a.size();
        if (H == 0) return {};
        const int W = (int)a[0].size();
        std::vector<Row> res(W, Row(H, typename Row::value_type()));
        for (int i = 0; i < H; ++i) {
            assert((int)a[i].size() == W);
            for (int j = 0; j < W; ++j) res[W - 1 - j][i] = a[i][j];
        }
        return res;
    }

    // 時計回りに 90k°（k は負でもよい）
    template <class Row>
    std::vector<Row> rotate(const std::vector<Row>& a, int k) {
        k = (k % 4 + 4) % 4;
        if (k == 1) return rotate90(a);
        if (k == 2) return rotate180(a);
        if (k == 3) return rotate270(a);
        return a;
    }
}
