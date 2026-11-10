// 素朴な実装と突き合わせるランダムテストを通してから A + B を解く。
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

#include "ds/dynamic_segtree.hpp"

namespace {
    using ll = long long;

    ll op_sum(ll a, ll b) { return a + b; }
    ll e_sum() { return 0; }
    ll op_max(ll a, ll b) { return std::max(a, b); }
    ll e_max() { return std::numeric_limits<ll>::min(); }
    // 非可換な演算で、左右の順序を取り違えていないか確かめる。
    std::string op_concat(std::string a, std::string b) { return a + b; }
    std::string e_concat() { return ""; }

    std::mt19937_64 random_engine(20261110);

    ll uniform(ll low, ll high) {
        return std::uniform_int_distribution<ll>(low, high)(random_engine);
    }

    void test_small() {
        for (int trial = 0; trial < 2000; ++trial) {
            int n = static_cast<int>(uniform(0, 40));
            yesantikiss::dynamic_segtree<ll, op_sum, e_sum> sum(n);
            yesantikiss::dynamic_segtree<ll, op_max, e_max> max(n);
            yesantikiss::dynamic_segtree<std::string, op_concat, e_concat>
                concat(n);
            std::vector<ll> a(n, 0), b(n, e_max());
            std::vector<std::string> c(n);
            assert(sum.size() == n);

            for (int query = 0; query < 60; ++query) {
                if (n == 0) {
                    assert(sum.all_prod() == 0 && sum.prod(0, 0) == 0);
                    assert(sum.max_right(0, [](ll) { return true; }) == 0);
                    assert(sum.min_left(0, [](ll) { return true; }) == 0);
                    break;
                }
                int type = static_cast<int>(uniform(0, 5));
                if (type == 0) {
                    int p = static_cast<int>(uniform(0, n - 1));
                    ll x = uniform(0, 9);
                    sum.set(p, x);
                    max.set(p, x);
                    a[p] = b[p] = x;
                    c[p] = std::string(1, static_cast<char>('a' + x));
                    concat.set(p, c[p]);
                } else if (type == 1) {
                    int p = static_cast<int>(uniform(0, n - 1));
                    ll x = uniform(0, 9);
                    sum.apply_point(p, x);
                    a[p] += x;
                    std::string s(1, static_cast<char>('a' + x));
                    concat.apply_point(p, s);
                    c[p] += s;
                } else if (type == 2) {
                    int l = static_cast<int>(uniform(0, n));
                    int r = static_cast<int>(uniform(l, n));
                    ll expected_sum = 0, expected_max = e_max();
                    std::string expected_concat;
                    for (int i = l; i < r; ++i) {
                        expected_sum += a[i];
                        expected_max = std::max(expected_max, b[i]);
                        expected_concat += c[i];
                    }
                    assert(sum.prod(l, r) == expected_sum);
                    assert(max.prod(l, r) == expected_max);
                    assert(concat.prod(l, r) == expected_concat);
                } else if (type == 3) {
                    int l = static_cast<int>(uniform(0, n));
                    ll limit = uniform(0, 30);
                    int r = l;
                    ll total = 0;
                    while (r < n && total + a[r] <= limit) total += a[r++];
                    assert(sum.max_right(
                               l, [&](ll x) { return x <= limit; }) == r);

                    ll bound = uniform(-1, 9);
                    r = l;
                    while (r < n && b[r] <= bound) ++r;
                    assert(max.max_right(
                               l, [&](ll x) { return x <= bound; }) == r);

                    // 非可換: l から先をつなげた文字列の接頭辞になっているか
                    std::string rest;
                    for (int i = l; i < n; ++i) rest += c[i];
                    std::size_t length = static_cast<std::size_t>(limit) / 3;
                    r = l;
                    std::size_t used = 0;
                    while (r < n && used + c[r].size() <= length) {
                        used += c[r++].size();
                    }
                    assert(concat.max_right(l, [&](const std::string& x) {
                        return x.size() <= length &&
                               rest.compare(0, x.size(), x) == 0;
                    }) == r);
                } else if (type == 4) {
                    int r = static_cast<int>(uniform(0, n));
                    ll limit = uniform(0, 30);
                    int l = r;
                    ll total = 0;
                    while (l > 0 && total + a[l - 1] <= limit) total += a[--l];
                    assert(sum.min_left(
                               r, [&](ll x) { return x <= limit; }) == l);

                    ll bound = uniform(-1, 9);
                    l = r;
                    while (l > 0 && b[l - 1] <= bound) --l;
                    assert(max.min_left(
                               r, [&](ll x) { return x <= bound; }) == l);

                    // 非可換: r より前をつなげた文字列の接尾辞になっているか
                    std::string before;
                    for (int i = 0; i < r; ++i) before += c[i];
                    std::size_t length = static_cast<std::size_t>(limit) / 3;
                    l = r;
                    std::size_t used = 0;
                    while (l > 0 && used + c[l - 1].size() <= length) {
                        used += c[--l].size();
                    }
                    assert(concat.min_left(r, [&](const std::string& x) {
                        return x.size() <= length &&
                               before.compare(before.size() - x.size(),
                                              x.size(), x) == 0;
                    }) == l);
                } else {
                    int p = static_cast<int>(uniform(0, n - 1));
                    assert(sum.get(p) == a[p]);
                    assert(max.get(p) == b[p]);
                    assert(concat.get(p) == c[p]);
                }
                ll expected_all = 0;
                for (ll x : a) expected_all += x;
                assert(sum.all_prod() == expected_all);
            }
        }
    }

    // 添字が大きいときは、値の入った位置だけを覚えた素朴解と比べる。
    void test_huge() {
        for (int trial = 0; trial < 200; ++trial) {
            ll n = trial % 2 == 0 ? 4000000000000000000LL
                                  : uniform(1, 4000000000000000000LL);
            yesantikiss::dynamic_segtree<ll, op_sum, e_sum> sum(n);
            std::vector<std::pair<ll, ll>> points;
            auto position = [&]() {
                int kind = static_cast<int>(uniform(0, 3));
                if (kind == 0) return uniform(0, std::min<ll>(n - 1, 5));
                if (kind == 1) return n - 1 - uniform(0, std::min<ll>(n - 1, 5));
                if (kind == 2 && !points.empty()) {
                    return points[uniform(0, static_cast<ll>(points.size()) - 1)]
                        .first;
                }
                return uniform(0, n - 1);
            };
            auto range_sum = [&](ll l, ll r) {
                ll total = 0;
                for (auto [p, x] : points) {
                    if (l <= p && p < r) total += x;
                }
                return total;
            };
            for (int query = 0; query < 40; ++query) {
                int type = static_cast<int>(uniform(0, 3));
                if (type == 0) {
                    ll p = position(), x = uniform(1, 9);
                    sum.set(p, x);
                    bool found = false;
                    for (auto& point : points) {
                        if (point.first == p) {
                            point.second = x;
                            found = true;
                        }
                    }
                    if (!found) points.emplace_back(p, x);
                } else if (type == 1) {
                    ll l = position(), r = position() + 1;
                    if (l > r) std::swap(l, r);
                    assert(sum.prod(l, r) == range_sum(l, r));
                } else if (type == 2) {
                    ll l = position(), limit = uniform(0, 20);
                    // 和が limit を超える最初の位置を素朴に探す
                    std::vector<std::pair<ll, ll>> sorted = points;
                    std::sort(sorted.begin(), sorted.end());
                    ll expected = n, total = 0;
                    for (auto [p, x] : sorted) {
                        if (p < l) continue;
                        total += x;
                        if (total > limit) {
                            expected = p;
                            break;
                        }
                    }
                    assert(sum.max_right(
                               l, [&](ll x) { return x <= limit; }) ==
                           expected);
                } else {
                    ll r = position() + 1, limit = uniform(0, 20);
                    std::vector<std::pair<ll, ll>> sorted = points;
                    std::sort(sorted.rbegin(), sorted.rend());
                    ll expected = 0, total = 0;
                    for (auto [p, x] : sorted) {
                        if (p >= r) continue;
                        total += x;
                        if (total > limit) {
                            expected = p + 1;
                            break;
                        }
                    }
                    assert(sum.min_left(
                               r, [&](ll x) { return x <= limit; }) ==
                           expected);
                }
            }
        }
    }
}

int main() {
    test_small();
    test_huge();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
