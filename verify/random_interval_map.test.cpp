// 素朴な実装と突き合わせるランダムテストを通してから A + B を解く。
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <random>
#include <vector>

#include "ds/interval_map.hpp"

int main() {
    std::mt19937 random(20261110);
    auto uniform = [&](int low, int high) {
        return std::uniform_int_distribution<int>(low, high)(random);
    };

    for (int trial = 0; trial < 3000; ++trial) {
        int L = uniform(-5, 0), R = uniform(1, 25);
        int initial = uniform(0, 3);
        yesantikiss::IntervalMap<int, int> intervals(L, R, initial);
        std::vector<int> a(R - L, initial);

        // add / del の呼び出しだけで、値ごとの総長を保てるか確かめる。
        std::map<int, long long> length;
        length[initial] = R - L;
        auto add = [&](int l, int r, const int& v) {
            assert(l < r);
            length[v] += r - l;
        };
        auto del = [&](int l, int r, const int& v) {
            assert(l < r);
            length[v] -= r - l;
        };

        for (int query = 0; query < 40; ++query) {
            // 範囲外や空の区間も渡す
            int l = uniform(L - 2, R + 2), r = uniform(L - 2, R + 2);
            int clipped_l = std::max(l, L), clipped_r = std::min(r, R);
            int type = uniform(0, 4);
            bool with_callbacks = uniform(0, 3) != 0;
            if (!with_callbacks && type <= 3) {
                // コールバックなしの版は総長の検査と両立しないので別に試す
                yesantikiss::IntervalMap<int, int> copy = intervals;
                std::vector<int> b = a;
                if (type == 0) {
                    int v = uniform(0, 3);
                    copy.assign(l, r, v);
                    for (int i = clipped_l; i < clipped_r; ++i) b[i - L] = v;
                } else if (type == 1) {
                    copy.apply(l, r, [](const int& v) { return (v + 1) % 4; });
                    for (int i = clipped_l; i < clipped_r; ++i) {
                        b[i - L] = (b[i - L] + 1) % 4;
                    }
                } else {
                    auto segments = copy.segments_cut(l, r);
                    int next = clipped_l;
                    for (const auto& segment : segments) {
                        assert(segment.l == next && segment.l < segment.r);
                        for (int i = segment.l; i < segment.r; ++i) {
                            assert(b[i - L] == segment.v);
                        }
                        next = segment.r;
                    }
                    if (clipped_l < clipped_r) assert(next == clipped_r);
                    else assert(segments.empty());
                }
                for (int i = L; i < R; ++i) {
                    assert(copy.get_val(i) == b[i - L]);
                }
                continue;
            }

            if (type == 0) {
                int v = uniform(0, 3);
                intervals.assign(l, r, v, add, del);
                for (int i = clipped_l; i < clipped_r; ++i) a[i - L] = v;
            } else if (type == 1) {
                int d = uniform(0, 2);
                intervals.apply(
                    l, r, [&](const int& v) { return (v + d) % 4; }, add,
                    del);
                for (int i = clipped_l; i < clipped_r; ++i) {
                    a[i - L] = (a[i - L] + d) % 4;
                }
            } else if (type == 2) {
                // f(l, r, v) の形: 区間の位置で値を決める
                intervals.apply(
                    l, r,
                    [&](int x, int y, const int& v) {
                        assert(clipped_l <= x && x < y && y <= clipped_r);
                        for (int i = x; i < y; ++i) assert(a[i - L] == v);
                        return (v + x + 100) % 4;
                    },
                    add, del);
                // 素朴解: 変換前の値が同じで連続している範囲ごとに適用
                std::vector<int> b = a;
                for (int i = clipped_l; i < clipped_r;) {
                    int j = i;
                    while (j < clipped_r && a[j - L] == a[i - L]) ++j;
                    // 区間の左端は、範囲外へ続く同じ値の区間でも clipped_l
                    for (int k = i; k < j; ++k) {
                        b[k - L] = (a[i - L] + i + 100) % 4;
                    }
                    i = j;
                }
                a = b;
            } else {
                std::vector<int> seen;
                intervals.enumerate_cut(
                    l, r,
                    [&](int x, int y, const int& v) {
                        assert(clipped_l <= x && x < y && y <= clipped_r);
                        for (int i = x; i < y; ++i) {
                            assert(a[i - L] == v);
                            seen.push_back(i);
                        }
                    },
                    add, del);
                std::vector<int> expected;
                for (int i = clipped_l; i < clipped_r; ++i) {
                    expected.push_back(i);
                }
                assert(seen == expected);
            }

            // 不変量: すき間なく被覆し、隣り合う区間は値が違う
            int previous_r = L, previous_v = -1;
            bool first = true;
            std::map<int, long long> actual_length;
            for (const auto& node : intervals) {
                assert(node.l == previous_r && node.l < node.r);
                if (!first) assert(node.v != previous_v);
                first = false;
                previous_r = node.r;
                previous_v = node.v;
                actual_length[node.v] += node.r - node.l;
                for (int i = node.l; i < node.r; ++i) {
                    assert(a[i - L] == node.v);
                }
            }
            assert(previous_r == R);
            for (const auto& [value, total] : length) {
                assert(actual_length[value] == total);
            }
            for (int i = L; i < R; ++i) {
                assert(intervals.get_val(i) == a[i - L]);
                auto it = intervals.locate(i);
                assert(it->l <= i && i < it->r);
            }
        }
    }

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
