// 素朴な実装と突き合わせるランダムテストを通してから A + B を解く。
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "utils/grid_rotate.hpp"

int main() {
    std::mt19937 random(20261110);
    using yesantikiss::rotate;
    using yesantikiss::rotate180;
    using yesantikiss::rotate270;
    using yesantikiss::rotate90;

    {
        // 向きを取り違えていないか、手で書いた例で確かめる (時計回り)
        std::vector<std::string> a{"ab", "cd", "ef"};
        assert((rotate90(a) == std::vector<std::string>{"eca", "fdb"}));
        assert((rotate180(a) == std::vector<std::string>{"fe", "dc", "ba"}));
        assert((rotate270(a) == std::vector<std::string>{"bdf", "ace"}));

        std::vector<std::string> empty;
        assert(rotate90(empty).empty() && rotate180(empty).empty());
        assert(rotate270(empty).empty() && rotate(empty, 5).empty());
    }

    for (int trial = 0; trial < 2000; ++trial) {
        int H = 1 + static_cast<int>(random() % 7);
        int W = 1 + static_cast<int>(random() % 7);
        std::vector<std::vector<int>> a(H, std::vector<int>(W));
        std::vector<std::string> s(H, std::string(W, '.'));
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                a[i][j] = static_cast<int>(random() % 1000);
                s[i][j] = static_cast<char>('a' + random() % 26);
            }
        }

        // 定義どおりの添字で比べる
        auto r90 = rotate90(a);
        auto r180 = rotate180(a);
        auto r270 = rotate270(a);
        auto s90 = rotate90(s);
        auto s180 = rotate180(s);
        auto s270 = rotate270(s);
        assert(static_cast<int>(r90.size()) == W);
        assert(static_cast<int>(r180.size()) == H);
        assert(static_cast<int>(r270.size()) == W);
        for (int i = 0; i < W; ++i) {
            assert(static_cast<int>(r90[i].size()) == H);
            assert(static_cast<int>(r270[i].size()) == H);
            for (int j = 0; j < H; ++j) {
                assert(r90[i][j] == a[H - 1 - j][i]);
                assert(r270[i][j] == a[j][W - 1 - i]);
                assert(s90[i][j] == s[H - 1 - j][i]);
                assert(s270[i][j] == s[j][W - 1 - i]);
            }
        }
        for (int i = 0; i < H; ++i) {
            assert(static_cast<int>(r180[i].size()) == W);
            for (int j = 0; j < W; ++j) {
                assert(r180[i][j] == a[H - 1 - i][W - 1 - j]);
                assert(s180[i][j] == s[H - 1 - i][W - 1 - j]);
            }
        }

        // rotate(a, k) は 90 度を k 回まわしたものと同じ (k は負でもよい)
        std::vector<std::vector<int>> turned = a;
        for (int k = 0; k <= 9; ++k) {
            assert(rotate(a, k) == turned);
            assert(rotate(a, k - 12) == turned);
            assert(rotate(rotate(a, k), -k) == a);
            turned = rotate90(turned);
        }
    }

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
