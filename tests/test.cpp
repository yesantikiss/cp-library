#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "algo/mo.hpp"
#include "ds/2d_prefixsum.hpp"
#include "ds/binary_trie.hpp"
#include "ds/cartesian_tree.hpp"
#include "ds/compressor.hpp"
#include "ds/dynamic_segtree.hpp"
#include "ds/interval_map.hpp"
#include "ds/persistent_segtree.hpp"
#include "ds/potential_dsu.hpp"
#include "math/factor.hpp"
#include "string/aho_corasick.hpp"
#include "string/rolling_hash.hpp"
#include "utils/fraction.hpp"
#include "utils/hash.hpp"
#include "utils/int128.hpp"

long long op_sum(long long a, long long b) { return a + b; }
long long e_sum() { return 0; }

yesantikiss::RollingHash::ull rolling_hash_from_other_tu(const std::string& s);

int main() {
    using namespace yesantikiss;

    {
        const std::vector<int> a{1, 2, 1, 3};
        Mo mo((int)a.size());
        mo.add_query(0, 3);
        mo.add_query(1, 4);
        std::vector<int> count(4), answer(2);
        int distinct = 0;
        auto add = [&](int i) { distinct += count[a[i]]++ == 0; };
        auto del = [&](int i) { distinct -= --count[a[i]] == 0; };
        mo.solve(add, del, [&](int i) { answer[i] = distinct; });
        assert((answer == std::vector<int>{2, 3}));
    }
    {
        PS2D<int> ps(3, 4);
        ps.add_rect_imos(0, 1, 2, 3, 5);
        ps.add_point_imos(1, 2, 2);
        ps.build();
        assert(ps.at(0, 1) == 5 && ps[1][2] == 7);
        assert(ps.sum(0, 0, 2, 4) == 22);
    }
    {
        BinaryTrie<4> trie;
        trie.insert(1);
        trie.insert(4);
        trie.insert(4);
        assert(trie.size() == 3 && trie.count(4) == 2);
        assert(trie.kth(1) == 4 && trie.min_element(7) == 3);
        assert(trie.erase(4) && trie.count(4) == 1);
    }
    {
        CartesianTree<int> tree({3, 1, 4, 2});
        assert(tree.root == 1);
        assert(tree.par[0] == 1 && tree.par[3] == 1 && tree.par[2] == 3);
    }
    {
        Compressor<int> comp;
        comp.add(10);
        comp.add(3);
        comp.add(10);
        comp.build();
        assert(comp.size() == 2 && comp.get(3) == 0 && comp.value(1) == 10);
        assert((comp.map(std::vector<int>{10, 3}) == std::vector<int>{1, 0}));
    }
    {
        dynamic_segtree<long long, op_sum, e_sum> seg(8);
        seg.set(2, 3);
        seg.set(5, 7);
        seg.apply_point(2, 4);
        assert(seg.get(2) == 7 && seg.prod(0, 6) == 14);
        assert(seg.max_right(0, [](long long x) { return x <= 7; }) == 5);
        assert(seg.min_left(6, [](long long x) { return x <= 7; }) == 3);
    }
    {
        IntervalMap<int, int> intervals(0, 10, 0);
        intervals.assign(2, 6, 1);
        intervals.apply(4, 8, [](int x) { return x + 2; });
        assert(intervals.get_val(1) == 0);
        assert(intervals.get_val(3) == 1);
        assert(intervals.get_val(5) == 3);
        assert(intervals.get_val(7) == 2);
    }
    {
        persistent_segtree<long long, op_sum, e_sum> seg(
            std::vector<long long>{1, 2, 3});
        int version = seg.set(1, 10);
        assert(seg.prod(0, 3, 0) == 6);
        assert(seg.prod(0, 3, version) == 14);
    }
    {
        potential_dsu<long long> dsu(4);
        dsu.merge(0, 1, 3);
        dsu.merge(1, 2, -1);
        assert(dsu.same(0, 2) && dsu.diff(0, 2) == 2);
        assert(dsu.size(1) == 3 && dsu.groups().size() == 2);
    }
    {
        Factor factor(30);
        assert(factor.is_prime(29) && !factor.is_prime(1));
        assert((factor.factorize(24) ==
                std::vector<std::pair<int, int>>{{2, 3}, {3, 1}}));
    }
    {
        AhoCorasick<> ac;
        int she = ac.add("she");
        int he = ac.add("he");
        ac.build();
        int state = 0;
        for (char c : std::string("she")) state = ac.move(state, c);
        assert(state == she && ac.link(she) == he);
    }
    {
        RollingHash hash("abracadabra");
        assert(hash.equals(0, 4, 7, 11));
        assert(hash.get(0, 4) == rolling_hash_from_other_tu("abra"));
    }
    {
        umap<long long, std::string> map;
        map[1000000007LL] = "prime";
        assert(map.at(1000000007LL) == "prime");
        assert(map.find(0) == map.end());

        uset<std::pair<int, int>> set;
        set.insert({2, 3});
        set.insert({2, 3});
        set.insert({3, 2});
        assert(set.size() == 2);
        assert(set.count({2, 3}) == 1);
    }
    {
        using Fraction = fraction<long long>;

        assert(Fraction(6, -8) == Fraction(-3, 4));
        assert(Fraction(-7, 3).floor() == -3);
        assert(Fraction(-7, 3).ceil() == -2);
        assert(Fraction(std::numeric_limits<long long>::max(), 2).ceil() ==
               4611686018427387904LL);
        assert(Fraction(std::numeric_limits<long long>::min(), 1).floor() ==
               std::numeric_limits<long long>::min());
        assert(Fraction(2, std::numeric_limits<long long>::min()) ==
               Fraction(-1, 4611686018427387904LL));

        Fraction small(1, 4000000000LL);
        assert(small + small == Fraction(1, 2000000000LL));

        Fraction left(4000000000LL, 4000000001LL);
        Fraction right(4000000001LL, 2000000000LL);
        assert(left * right == Fraction(2));
        assert((left * right) / Fraction(4) == Fraction(1, 2));

        Fraction parsed(7);
        assert(Fraction::parse("-10/6", parsed));
        assert(parsed == Fraction(-5, 3));
        assert(Fraction::parse(".500000000000000000000000000000", parsed));
        assert(parsed == Fraction(1, 2));
        assert(Fraction::parse(".0", parsed));
        assert(parsed == Fraction(0));

        parsed = Fraction(7);
        assert(!Fraction::parse("9223372036854775808", parsed));
        assert(parsed == Fraction(7));
        assert(!Fraction::parse("-9223372036854775809", parsed));
        assert(parsed == Fraction(7));

        bool overflowed = false;
        Fraction max_value(std::numeric_limits<long long>::max());
        try {
            max_value += Fraction(1);
        } catch (const std::overflow_error&) {
            overflowed = true;
        }
        assert(overflowed);
        assert(max_value ==
               Fraction(std::numeric_limits<long long>::max()));

        bool divided_by_zero = false;
        try {
            max_value /= Fraction(0);
        } catch (const std::domain_error&) {
            divided_by_zero = true;
        }
        assert(divided_by_zero);
        assert(max_value ==
               Fraction(std::numeric_limits<long long>::max()));
    }
    {
        using Int128 = __int128;
        Int128 large = Int128(1) << 70;

        fr left(large, large + 1);
        fr right(large + 1, large / 2);
        assert(left * right == fr(2));
        assert(fr(large, large - 1) > fr(large - 1, large));

        std::stringstream stream;
        stream << fr(-large, 2);
        assert(stream.str() == "-590295810358705651712");

        fr parsed;
        assert(fr::parse(
            "170141183460469231731687303715884105727", parsed));
        std::stringstream max_stream;
        max_stream << parsed;
        assert(max_stream.str() ==
               "170141183460469231731687303715884105727");
        assert(!fr::parse(
            "170141183460469231731687303715884105728", parsed));
        assert(fr::parse(
            "-170141183460469231731687303715884105728", parsed));
        std::stringstream min_stream;
        min_stream << parsed;
        assert(min_stream.str() ==
               "-170141183460469231731687303715884105728");
    }
    {
        constexpr i128 i128_min = -(i128(1) << 126) * 2;
        constexpr i128 i128_max =
            static_cast<i128>((u128(1) << 127) - 1);
        constexpr u128 u128_max = ~u128(0);

        std::stringstream output;
        output << i128(0) << ' ' << i128_min << ' ' << i128_max << ' '
               << u128_max;
        assert(output.str() ==
               "0 -170141183460469231731687303715884105728 "
               "170141183460469231731687303715884105727 "
               "340282366920938463463374607431768211455");

        i128 signed_value = 0;
        u128 unsigned_value = 0;
        std::stringstream input(
            "  +170141183460469231731687303715884105727 "
            "-170141183460469231731687303715884105728 "
            "340282366920938463463374607431768211455");
        input >> signed_value;
        assert(signed_value == i128_max);
        input >> signed_value;
        assert(signed_value == i128_min);
        input >> unsigned_value;
        assert(unsigned_value == u128_max);

        signed_value = 42;
        std::stringstream signed_overflow(
            "170141183460469231731687303715884105728");
        signed_overflow >> signed_value;
        assert(signed_overflow.fail());
        assert(signed_value == 42);

        unsigned_value = 42;
        std::stringstream unsigned_overflow(
            "340282366920938463463374607431768211456");
        unsigned_overflow >> unsigned_value;
        assert(unsigned_overflow.fail());
        assert(unsigned_value == 42);

        std::stringstream invalid("-1");
        invalid >> unsigned_value;
        assert(invalid.fail());
        assert(unsigned_value == 42);
    }
}
