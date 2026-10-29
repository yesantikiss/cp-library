#include <cassert>
#include <functional>
#include <random>
#include <vector>

#include "ds/dynamic_li_chao_tree.hpp"

template <class Compare, class U>
void run(std::mt19937_64& random, long long max_coord, long long max_a,
         long long max_b) {
    auto uniform = [&](long long lo, long long hi) {
        return std::uniform_int_distribution<long long>(lo, hi)(random);
    };

    struct Segment {
        __int128 a, b;
        long long l, r;
    };

    for (int trial = 0; trial < 200; ++trial) {
        long long lo = uniform(-max_coord, max_coord);
        long long hi = lo + uniform(1, max_coord);
        yesantikiss::DynamicLiChaoTree<long long, Compare, U> tree(lo, hi);
        std::vector<Segment> segments;

        for (int step = 0; step < 300; ++step) {
            int type = static_cast<int>(random() % 4);
            if (type == 0) {
                long long a = uniform(-max_a, max_a);
                long long b = uniform(-max_b, max_b);
                tree.add_line(a, b);
                segments.push_back({a, b, lo, hi});
            } else if (type == 1) {
                long long a = uniform(-max_a, max_a);
                long long b = uniform(-max_b, max_b);
                long long l = uniform(lo, hi);
                long long r = uniform(lo, hi);
                if (l > r) std::swap(l, r);
                tree.add_segment(a, b, l, r);
                segments.push_back({a, b, l, r});
            } else if (type == 2 && step % 8 == 0) {
                long long p = uniform(-max_a, max_a);
                long long q = uniform(-max_b, max_b);
                tree.add_all(p, q);
                for (Segment& s : segments) {
                    s.a += p;
                    s.b += q;
                }
            } else {
                long long x = uniform(lo, hi - 1);
                bool found = false;
                __int128 best = 0;
                for (const Segment& s : segments) {
                    if (x < s.l || s.r <= x) continue;
                    __int128 y = s.a * x + s.b;
                    if (!found || Compare{}(y, best)) best = y;
                    found = true;
                }
                assert(tree.has_line(x) == found);
                if (found) assert(static_cast<__int128>(tree.get(x)) == best);
            }
        }
    }
}

int main() {
    std::mt19937_64 random(987654321);
    run<std::less<>, long long>(random, 50, 10, 100);
    run<std::greater<>, long long>(random, 50, 10, 100);
    run<std::less<>, long long>(random, 1000000, 1000, 1000000);
    run<std::less<>, __int128>(random, 1000000000, 1000000000,
                               1000000000000000000);
    run<std::greater<>, __int128>(random, 1000000000, 1000000000,
                                  1000000000000000000);
}
