// 素朴な実装と突き合わせるランダムテストを通してから A + B を解く。
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>

#include "utils/fraction.hpp"

namespace {
    using i128 = __int128;
    using u128 = unsigned __int128;
    using yesantikiss::fraction;

    std::mt19937_64 random_engine(20261110);

    template <class T>
    T max_of() {
        return static_cast<T>((u128(1) << (8 * sizeof(T) - 1)) - 1);
    }

    template <class T>
    T min_of() {
        return static_cast<T>(-max_of<T>() - 1);
    }

    i128 gcd(i128 a, i128 b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b != 0) {
            i128 r = a % b;
            a = b;
            b = r;
        }
        return a;
    }

    std::string to_string(i128 x) {
        if (x == 0) return "0";
        bool negative = x < 0;
        u128 magnitude = negative ? u128(0) - static_cast<u128>(x)
                                  : static_cast<u128>(x);
        std::string digits;
        while (magnitude != 0) {
            digits.insert(digits.begin(),
                          static_cast<char>('0' + static_cast<int>(magnitude % 10)));
            magnitude /= 10;
        }
        return negative ? "-" + digits : digits;
    }

    // 素朴な有理数。分子・分母を __int128 で持ち、あふれない範囲でだけ使う。
    struct Exact {
        i128 num = 0, den = 1;
        bool defined = true;
    };

    Exact normalize(i128 num, i128 den) {
        if (den == 0) return {0, 1, false};
        if (den < 0) {
            num = -num;
            den = -den;
        }
        i128 g = gcd(num, den);
        return {num / g, den / g, true};
    }

    template <class T>
    bool fits(const Exact& x) {
        return min_of<T>() <= x.num && x.num <= max_of<T>() &&
               x.den <= max_of<T>();
    }

    template <class T>
    bool same(const fraction<T>& x, const Exact& expected) {
        return static_cast<i128>(x.num) == expected.num &&
               static_cast<i128>(x.den) == expected.den;
    }

    // 絶対値が limit 以下の値。端の値と小さい値が出やすいようにする。
    i128 random_value(i128 limit, bool allow_min) {
        int kind = static_cast<int>(random_engine() % 8);
        if (kind == 0) return 0;
        if (kind == 1) return limit;
        if (kind == 2) return allow_min ? -limit - 1 : -limit;
        if (kind == 3) {
            return static_cast<i128>(random_engine() % 7) - 3;
        }
        // 桁数を一様に選ぶ
        int bits = 0;
        while ((limit >> bits) > 1) ++bits;
        int use = 1 + static_cast<int>(random_engine() % (bits + 1));
        u128 raw = (static_cast<u128>(random_engine()) << 64) | random_engine();
        i128 value = static_cast<i128>(raw % (u128(1) << use));
        if (value > limit) value = limit;
        return random_engine() % 2 == 0 ? value : -value;
    }

    // f を実行し、期待値が T に収まるなら一致、収まらないなら
    // overflow_error、未定義なら domain_error になることを確かめる。
    template <class T, class F>
    void check(const Exact& expected, F f) {
        try {
            fraction<T> result = f();
            assert(expected.defined && fits<T>(expected));
            assert(same(result, expected));
        } catch (const std::overflow_error&) {
            assert(expected.defined && !fits<T>(expected));
        } catch (const std::domain_error&) {
            assert(!expected.defined);
        }
    }

    // T の全範囲を使い、あふれの境界も含めて素朴解と比べる。
    // limit は素朴解の途中計算が __int128 に収まる上限。
    template <class T>
    void test_against_exact(int trials, i128 limit, bool allow_min) {
        using F = fraction<T>;
        for (int trial = 0; trial < trials; ++trial) {
            i128 a = random_value(limit, allow_min);
            i128 b = random_value(limit, allow_min);
            i128 c = random_value(limit, allow_min);
            i128 d = random_value(limit, allow_min);
            if (b == 0) b = 1;
            if (d == 0) d = 1;

            Exact ex = normalize(a, b), ey = normalize(c, d);
            check<T>(ex, [&] { return F(static_cast<T>(a), static_cast<T>(b)); });
            if (!fits<T>(ex) || !fits<T>(ey)) continue;

            const F x(static_cast<T>(a), static_cast<T>(b));
            const F y(static_cast<T>(c), static_cast<T>(d));
            assert(same(x, ex) && same(y, ey));
            assert(x.is_integer() == (ex.den == 1));

            // 四則演算
            Exact sum = normalize(ex.num * ey.den + ey.num * ex.den,
                                  ex.den * ey.den);
            Exact difference = normalize(
                ex.num * ey.den - ey.num * ex.den, ex.den * ey.den);
            Exact product = normalize(ex.num * ey.num, ex.den * ey.den);
            Exact quotient = normalize(ex.num * ey.den, ex.den * ey.num);
            check<T>(sum, [&] { return x + y; });
            check<T>(difference, [&] { return x - y; });
            check<T>(product, [&] { return x * y; });
            check<T>(quotient, [&] { return x / y; });

            // 複合代入は、例外を投げたときに元の値を壊さない
            for (int op = 0; op < 4; ++op) {
                F z = x;
                try {
                    if (op == 0) z += y;
                    if (op == 1) z -= y;
                    if (op == 2) z *= y;
                    if (op == 3) z /= y;
                    const Exact& expected = op == 0   ? sum
                                            : op == 1 ? difference
                                            : op == 2 ? product
                                                      : quotient;
                    assert(same(z, expected));
                } catch (const std::overflow_error&) {
                    assert(z == x);
                } catch (const std::domain_error&) {
                    assert(z == x && op == 3 && ey.num == 0);
                }
            }

            // 単項演算
            check<T>(normalize(-ex.num, ex.den), [&] { return -x; });
            check<T>(normalize(ex.num < 0 ? -ex.num : ex.num, ex.den),
                     [&] { return abs(x); });
            check<T>(normalize(ex.den, ex.num), [&] { return x.inv(); });

            // 比較
            i128 left = ex.num * ey.den, right = ey.num * ex.den;
            assert((x < y) == (left < right));
            assert((x > y) == (left > right));
            assert((x <= y) == (left <= right));
            assert((x >= y) == (left >= right));
            assert((x == y) == (left == right));
            assert((x != y) == (left != right));

            // floor / ceil
            i128 floor = ex.num / ex.den, ceil = ex.num / ex.den;
            if (ex.num % ex.den != 0) {
                if (ex.num < 0) --floor;
                else ++ceil;
            }
            assert(static_cast<i128>(x.floor()) == floor);
            assert(static_cast<i128>(x.ceil()) == ceil);

            // 出力した文字列を読み直すと元に戻る
            std::ostringstream os;
            os << x;
            std::string text = to_string(ex.num);
            if (ex.den != 1) text += "/" + to_string(ex.den);
            assert(os.str() == text);
            F parsed(1);
            assert(F::parse(text, parsed) && parsed == x);

            // 既約でない a/b の形。収まらないなら false で、out は変えない
            if (b > 0) {
                parsed = F(1);
                bool ok = F::parse(to_string(a) + "/" + to_string(b), parsed);
                assert(ok && parsed == x);
            }
        }
    }

    // 小数の文字列を読む。
    template <class T>
    void test_parse_decimal(int trials, int max_digits) {
        using F = fraction<T>;
        for (int trial = 0; trial < trials; ++trial) {
            int integer_digits =
                static_cast<int>(random_engine() % (max_digits + 1));
            int fraction_digits =
                static_cast<int>(random_engine() % (max_digits + 1));
            std::string integer_part, fraction_part;
            i128 numerator = 0, denominator = 1;
            for (int i = 0; i < integer_digits; ++i) {
                int digit = static_cast<int>(random_engine() % 10);
                integer_part += static_cast<char>('0' + digit);
                numerator = numerator * 10 + digit;
            }
            for (int i = 0; i < fraction_digits; ++i) {
                // 末尾の 0 が続く場合も試す
                int digit = random_engine() % 3 == 0
                                ? 0
                                : static_cast<int>(random_engine() % 10);
                fraction_part += static_cast<char>('0' + digit);
                numerator = numerator * 10 + digit;
                denominator *= 10;
            }
            int sign = static_cast<int>(random_engine() % 3);
            std::string text = sign == 0 ? "" : sign == 1 ? "+" : "-";
            text += integer_part;
            bool has_dot = fraction_digits > 0 || random_engine() % 2 == 0;
            if (has_dot) text += "." + fraction_part;

            Exact expected =
                normalize(sign == 2 ? -numerator : numerator, denominator);
            bool valid = integer_digits + fraction_digits > 0;
            F parsed(7);
            bool ok = F::parse(text, parsed);
            assert(ok == (valid && fits<T>(expected)));
            if (ok) assert(same(parsed, expected));
            else assert(parsed == F(7));
        }
    }

    template <class T>
    void test_parse_fixed() {
        using F = fraction<T>;
        for (const char* text :
             {"", "+", "-", ".", "-.", "+.", "1/0", "0/0", "1//2", "1/2/3",
              "/2", "1/", "a", "1a", "1.2.3", "1/-2", "1/+2", "--1", "+-1",
              " 1", "1 ", "1e5", "0x1", "1/ 2", "1./2", "1/2.", "1.5/2"}) {
            F parsed(7);
            assert(!F::parse(text, parsed));
            assert(parsed == F(7));
        }
        F parsed;
        assert(F::parse("1.", parsed) && parsed == F(1));
        assert(F::parse(".5", parsed) && parsed == F(1, 2));
        assert(F::parse("-.25", parsed) && parsed == F(-1, 4));
        assert(F::parse("-0", parsed) && parsed == F(0));
        assert(F::parse("-0.000", parsed) && parsed == F(0));
        assert(F::parse("+3/6", parsed) && parsed == F(1, 2));
        assert(F::parse("0/5", parsed) && parsed == F(0));
        assert(F::parse("007", parsed) && parsed == F(7));
        assert(F::parse("-10/4", parsed) && parsed == F(-5, 2));

        // ストリームからの読み込み。失敗したら failbit が立ち、値は変わらない
        std::istringstream is("3/4 -1.25 x 5");
        F p, q, r(7);
        is >> p >> q;
        assert(is && p == F(3, 4) && q == F(-5, 4));
        is >> r;
        assert(is.fail() && r == F(7));
        std::istringstream empty("");
        empty >> r;
        assert(empty.fail() && r == F(7));

        // ゼロ除算
        bool thrown = false;
        try {
            F zero_denominator(1, 0);
        } catch (const std::invalid_argument&) {
            thrown = true;
        }
        assert(thrown);
    }

    // 内部の gcd と 256ビット ÷ 128ビットの割り算を、素朴な計算と比べる。
    void test_detail() {
        namespace detail = yesantikiss::fraction_detail;
        auto random_bits = [&](int bits) {
            u128 raw =
                (static_cast<u128>(random_engine()) << 64) | random_engine();
            return bits == 128 ? raw : raw % (u128(1) << bits);
        };
        auto naive_gcd = [](u128 a, u128 b) {
            while (b != 0) {
                u128 r = a % b;
                a = b;
                b = r;
            }
            return a;
        };
        for (int trial = 0; trial < 20000; ++trial) {
            // 桁数をばらばらに選び、共通因数も持たせる
            u128 a = random_bits(static_cast<int>(random_engine() % 129));
            u128 b = random_bits(static_cast<int>(random_engine() % 129));
            if (trial % 3 == 0) {
                u128 g = random_bits(static_cast<int>(random_engine() % 70));
                a = (a >> 70) * g;
                b = (b >> 70) * g;
            }
            if (trial % 11 == 0) b = a;
            if (trial % 13 == 0) a <<= random_engine() % 40;
            if (trial % 7 == 0) {
                // 下位64ビットがすべて 0 の値
                a = (a >> 100 | 1) << (64 + random_engine() % 36);
                b = (b >> 100 | 1) << (64 + random_engine() % 36);
            }
            u128 expected = naive_gcd(a, b);
            assert(detail::gcd(a, b) == expected);
            assert(detail::gcd(b, a) == expected);
            if ((a >> 64) == 0 && (b >> 64) == 0) {
                assert(detail::gcd64(static_cast<unsigned long long>(a),
                                     static_cast<unsigned long long>(b)) ==
                       expected);
            }
        }
        assert(detail::gcd(0, 0) == 0 && detail::gcd64(0, 0) == 0);
        assert(detail::gcd(0, 7) == 7 && detail::gcd(~u128(0), 0) == ~u128(0));
        assert(detail::gcd(~u128(0), ~u128(0)) == ~u128(0));
        assert(detail::gcd(u128(1) << 127, u128(1) << 100) == u128(1) << 100);

        for (int trial = 0; trial < 6000; ++trial) {
            // value = quotient * divisor + remainder を作ってから割り直す。
            // 割る数が64ビット以下の近道と、それより大きい場合の両方を通す。
            u128 divisor =
                random_bits(1 + static_cast<int>(random_engine() % 128)) + 1;
            if (divisor == 0) divisor = 1;
            u128 quotient =
                random_bits(static_cast<int>(random_engine() % 129));
            u128 remainder = random_bits(128) % divisor;
            detail::u256 value = detail::add(
                detail::multiply(quotient, divisor),
                detail::from_u128(remainder));
            detail::div_result result = detail::divide(value, divisor);
            assert(result.quotient.hi == 0 && result.quotient.lo == quotient);
            assert(result.remainder == remainder);
            assert(detail::modulo(value, divisor) == remainder);
        }
        // 商が128ビットを超える場合: (2^256 - 1) / 3 = 0x5555...
        detail::div_result all = detail::divide({~u128(0), ~u128(0)}, 3);
        assert(all.remainder == 0);
        assert(all.quotient.hi == ~u128(0) / 3 && all.quotient.lo == ~u128(0) / 3);
        all = detail::divide({~u128(0), ~u128(0)}, (u128(1) << 64) + 1);
        assert(detail::compare(
                   detail::add(detail::add(
                                   detail::multiply(all.quotient.lo,
                                                    (u128(1) << 64) + 1),
                                   detail::u256{
                                       all.quotient.hi * ((u128(1) << 64) + 1),
                                       0}),
                               detail::from_u128(all.remainder)),
                   detail::u256{~u128(0), ~u128(0)}) == 0);
    }

    // __int128 で、64ビットに収まるときの近道と通常の経路の切り替わり
    // (2^63 と 2^64 の前後) を、素朴解が __int128 に収まる組み合わせで試す。
    void test_boundary() {
        using F = fraction<i128>;
        auto small = [&]() {
            return static_cast<i128>(random_engine() % 2000001) - 1000000;
        };
        auto near = [&](bool allow_64) {
            i128 pivot = i128(1) << (allow_64 && random_engine() % 2 ? 64 : 63);
            i128 value = pivot + static_cast<i128>(random_engine() % 7) - 3;
            return random_engine() % 2 == 0 ? value : -value;
        };
        for (int trial = 0; trial < 20000; ++trial) {
            i128 a, b, c, d;
            if (trial % 2 == 0) {
                // 分子が境界の近く、分母は小さい
                a = random_engine() % 4 == 0 ? small() : near(true);
                c = random_engine() % 4 == 0 ? small() : near(true);
                b = small();
                d = small();
            } else {
                // 分母が境界の近く、分子は小さい
                a = small();
                c = small();
                b = random_engine() % 4 == 0 ? small() : near(false);
                d = random_engine() % 4 == 0 ? small() : near(false);
            }
            if (b == 0) b = 1;
            if (d == 0) d = 1;
            Exact ex = normalize(a, b), ey = normalize(c, d);
            const F x(a, b), y(c, d);
            assert(same(x, ex) && same(y, ey));

            check<i128>(normalize(ex.num * ey.den + ey.num * ex.den,
                                  ex.den * ey.den),
                        [&] { return x + y; });
            check<i128>(normalize(ex.num * ey.den - ey.num * ex.den,
                                  ex.den * ey.den),
                        [&] { return x - y; });
            // 積と商は、素朴解の途中計算が収まる向きだけ確かめる
            if (trial % 2 == 0) {
                check<i128>(normalize(ex.num * ey.den, ex.den * ey.num),
                            [&] { return x / y; });
            } else {
                check<i128>(normalize(ex.num * ey.num, ex.den * ey.den),
                            [&] { return x * y; });
            }
            i128 left = ex.num * ey.den, right = ey.num * ex.den;
            assert((x < y) == (left < right));
            assert((y < x) == (right < left));
            assert((x == y) == (left == right));
        }
    }

    // __int128 で、途中の積が128ビットを超える経路を通す。
    // 答えが分かる形に値を組み立てて比べる。
    void test_wide() {
        using F = fraction<i128>;
        auto random_bits = [&](int bits) {
            u128 raw =
                (static_cast<u128>(random_engine()) << 64) | random_engine();
            return static_cast<i128>(raw % (u128(1) << bits)) + 1;
        };
        int wide_sums = 0;
        for (int trial = 0; trial < 2000; ++trial) {
            // 同じ分母 m: p/m ± q/m = (p ± q)/m
            {
                i128 m = random_bits(40 + static_cast<int>(random_engine() % 80));
                i128 p = random_bits(125), q = random_bits(125);
                if (random_engine() % 2 == 0) p = -p;
                if (random_engine() % 2 == 0) q = -q;
                F x(p, m), y(q, m);
                assert(same(x, normalize(p, m)) && same(y, normalize(q, m)));
                // 約分後の分母どうしの積が大きいと、途中で128ビットを超える
                if (x.den > (i128(1) << 64) && y.den > (i128(1) << 64)) {
                    ++wide_sums;
                }
                assert(same(x + y, normalize(p + q, m)));
                assert(same(x - y, normalize(p - q, m)));
                assert((x < y) == (p < q));
                assert((x == y) == (p == q));
            }
            // 互いに約分される積: (p*s)/(q*t) * (q*u)/(p*v) = (s*u)/(t*v)
            {
                i128 p = random_bits(62), q = random_bits(62);
                i128 s = random_bits(60), t = random_bits(60);
                i128 u = random_bits(60), v = random_bits(60);
                F x(p * s, q * t), y(q * u, p * v);
                if (random_engine() % 2 == 0) x = -x;
                Exact expected = normalize(s * u, t * v);
                if (x.num < 0) expected.num = -expected.num;
                assert(same(x * y, expected));
                // x / (1/y) も同じ値
                assert(same(x / y.inv(), expected));
            }
            // 大きい値どうしの比較: p/q と (p+1)/q、p/q と p/(q+1)
            {
                i128 p = random_bits(126), q = random_bits(126);
                assert(F(p, q) < F(p + 1, q) && F(p, q + 1) < F(p, q));
                assert(F(-p - 1, q) < F(-p, q) && F(-p, q) < F(-p, q + 1));
                assert(!(F(p, q) < F(p, q)) && F(p, q) <= F(p, q));
                assert(F(-p, q) < F(p, q + 1));
            }
            // 足して引くと元に戻る (あふれたら例外で、元の値は変わらない)
            {
                F x(random_bits(100), random_bits(60));
                F y(random_bits(100), random_bits(60));
                try {
                    F z = x + y;
                    assert(z - y == x && z - x == y);
                } catch (const std::overflow_error&) {
                }
                try {
                    F z = x * y;
                    assert(z / y == x && z / x == y);
                } catch (const std::overflow_error&) {
                }
            }
        }
        assert(wide_sums > 100);

        // 型の端の値
        const i128 max = max_of<i128>(), min = min_of<i128>();
        assert(same(F(max, 3) - F(max - 1, 3), normalize(1, 3)));
        assert(F(min, min) == F(1) && F(max, max) == F(1));
        assert(F(min, 2) < F(max, 2) && F(min) < F(min + 1));
        assert(F(max, max - 1) * F(max - 1, max) == F(1));
        assert(F(min).floor() == min && F(max).ceil() == max);
        bool thrown = false;
        try {
            (void)-F(min);
        } catch (const std::overflow_error&) {
            thrown = true;
        }
        assert(thrown);
        thrown = false;
        try {
            (void)(F(max) + F(1));
        } catch (const std::overflow_error&) {
            thrown = true;
        }
        assert(thrown);

        std::ostringstream os;
        os << F(min) << ' ' << F(max, 2);
        assert(os.str() == to_string(min) + " " + to_string(max) + "/2");
        F parsed;
        assert(F::parse(to_string(min), parsed) && parsed == F(min));
        assert(!F::parse(to_string(max) + "0", parsed));
    }
}

int main() {
    // verify ではテストケースごとに実行されるので、回数は1秒以内に収まる
    // 程度にしている。
    // 8ビットでは全範囲を使い、あふれの境界を集中的に試す。
    test_against_exact<signed char>(20000, max_of<signed char>(), true);
    test_against_exact<short>(8000, max_of<short>(), true);
    test_against_exact<int>(12000, max_of<int>(), true);
    // 素朴解の途中計算が __int128 に収まるよう、絶対値は 2^62 まで
    test_against_exact<long long>(12000, i128(1) << 62, false);
    test_against_exact<i128>(12000, i128(1) << 62, false);

    test_parse_decimal<signed char>(20000, 4);
    test_parse_decimal<int>(20000, 11);
    test_parse_decimal<long long>(20000, 18);
    test_parse_decimal<i128>(20000, 18);
    test_parse_fixed<int>();
    test_parse_fixed<long long>();
    test_parse_fixed<i128>();

    test_detail();
    test_boundary();
    test_wide();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
