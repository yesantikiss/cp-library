#pragma once

#include <cstddef>
#include <ios>
#include <istream>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace yesantikiss {
    namespace fraction_detail {
        using i128 = __int128;
        using u128 = unsigned __int128;

        template<class T>
        inline constexpr bool is_supported_integer_v =
            (std::is_integral_v<T> && std::is_signed_v<T> &&
             !std::is_same_v<T, bool>) ||
            std::is_same_v<T, i128>;

        struct u256 {
            u128 hi = 0;
            u128 lo = 0;
        };

        inline bool is_zero(const u256& x) {
            return x.hi == 0 && x.lo == 0;
        }

        inline int compare(const u256& a, const u256& b) {
            if (a.hi != b.hi) return a.hi < b.hi ? -1 : 1;
            if (a.lo != b.lo) return a.lo < b.lo ? -1 : 1;
            return 0;
        }

        inline u256 add(const u256& a, const u256& b) {
            u256 res;
            res.lo = a.lo + b.lo;
            res.hi = a.hi + b.hi + (res.lo < a.lo);
            return res;
        }

        // a >= b を仮定する。
        inline u256 subtract(const u256& a, const u256& b) {
            u256 res;
            res.lo = a.lo - b.lo;
            res.hi = a.hi - b.hi - (a.lo < b.lo);
            return res;
        }

        inline u256 multiply(u128 a, u128 b) {
            constexpr u128 mask64 = (u128(1) << 64) - 1;

            u128 a0 = a & mask64;
            u128 a1 = a >> 64;
            u128 b0 = b & mask64;
            u128 b1 = b >> 64;

            u128 p00 = a0 * b0;
            u128 p01 = a0 * b1;
            u128 p10 = a1 * b0;
            u128 p11 = a1 * b1;

            u128 lo = p00;
            u128 x = p01 << 64;
            u128 next = lo + x;
            u128 carry = next < lo;
            lo = next;

            x = p10 << 64;
            next = lo + x;
            carry += next < lo;
            lo = next;

            u128 hi = p11 + (p01 >> 64) + (p10 >> 64) + carry;
            return {hi, lo};
        }

        inline u256 from_u128(u128 x) {
            return {0, x};
        }

        struct div_result {
            u256 quotient;
            u128 remainder;
        };

        inline div_result divide(const u256& value, u128 divisor) {
            if (divisor == 0) {
                throw std::domain_error("fraction: division by zero");
            }
            if (value.hi == 0) {
                return {{0, value.lo / divisor}, value.lo % divisor};
            }

            u256 quotient;
            u128 remainder = 0;
            for (int bit_index = 255; bit_index >= 0; --bit_index) {
                u128 bit;
                if (bit_index >= 128) {
                    bit = (value.hi >> (bit_index - 128)) & 1;
                } else {
                    bit = (value.lo >> bit_index) & 1;
                }

                bool carry = (remainder >> 127) != 0;
                remainder = (remainder << 1) | bit;
                if (carry || remainder >= divisor) {
                    remainder -= divisor;
                    if (bit_index >= 128) {
                        quotient.hi |= u128(1) << (bit_index - 128);
                    } else {
                        quotient.lo |= u128(1) << bit_index;
                    }
                }
            }
            return {quotient, remainder};
        }

        inline u128 modulo(const u256& value, u128 divisor) {
            return divide(value, divisor).remainder;
        }

        inline u256 divide_exact(const u256& value, u128 divisor) {
            if (divisor == 1) return value;
            div_result result = divide(value, divisor);
            if (result.remainder != 0) {
                throw std::logic_error("fraction: internal non-exact division");
            }
            return result.quotient;
        }

        inline u128 gcd(u128 a, u128 b) {
            while (b != 0) {
                u128 r = a % b;
                a = b;
                b = r;
            }
            return a;
        }

        struct signed_u256 {
            bool negative = false;
            u256 magnitude;
        };

        inline signed_u256 add(const signed_u256& a, const signed_u256& b) {
            if (a.negative == b.negative) {
                signed_u256 res{a.negative, add(a.magnitude, b.magnitude)};
                if (is_zero(res.magnitude)) res.negative = false;
                return res;
            }

            int cmp = compare(a.magnitude, b.magnitude);
            if (cmp == 0) return {};
            if (cmp > 0) {
                return {a.negative, subtract(a.magnitude, b.magnitude)};
            }
            return {b.negative, subtract(b.magnitude, a.magnitude)};
        }
    }

    // T は符号付き整数型（最大 __int128）。常に既約かつ den > 0 に保つ。
    // 正規化後の値が T に収まらない演算は std::overflow_error を送出する。
    template<class T>
    struct fraction {
        static_assert(
            fraction_detail::is_supported_integer_v<T>,
            "fraction<T>: T must be a signed integral type");
        static_assert(
            sizeof(T) <= sizeof(fraction_detail::i128),
            "fraction<T>: integers wider than 128 bits are not supported");

        using u128 = fraction_detail::u128;
        using u256 = fraction_detail::u256;
        using signed_u256 = fraction_detail::signed_u256;

        T num, den; // den > 0 を常に保つ

        fraction() : num(0), den(1) {}
        fraction(T n) : num(n), den(1) {}

        fraction(T n, T d) {
            if (d == 0) {
                throw std::invalid_argument(
                    "fraction: denominator must not be zero");
            }
            bool negative = (n < 0) != (d < 0);
            assign_normalized(
                negative, magnitude(n), magnitude(d));
        }

    private:
        static constexpr u128 max_u128() {
            return ~u128(0);
        }

        static constexpr u128 max_magnitude() {
            return static_cast<u128>(std::numeric_limits<T>::max());
        }

        static constexpr u128 min_magnitude() {
            return max_magnitude() + 1;
        }

        static u128 magnitude(T x) {
            u128 value = static_cast<u128>(x);
            return x < 0 ? u128(0) - value : value;
        }

        static bool fits(bool negative, u128 value) {
            return value <= (negative ? min_magnitude() : max_magnitude());
        }

        static T from_magnitude(bool negative, u128 value) {
            if (!fits(negative, value)) {
                throw std::overflow_error(
                    "fraction: value does not fit the storage type");
            }
            if (!negative) return static_cast<T>(value);
            if (value == min_magnitude()) {
                return std::numeric_limits<T>::min();
            }
            return -static_cast<T>(value);
        }

        void assign_reduced(
            bool negative, const u256& numerator, const u256& denominator) {
            if (fraction_detail::is_zero(denominator)) {
                throw std::invalid_argument(
                    "fraction: denominator must not be zero");
            }
            if (fraction_detail::is_zero(numerator)) {
                num = 0;
                den = 1;
                return;
            }
            if (numerator.hi != 0 || denominator.hi != 0 ||
                !fits(negative, numerator.lo) ||
                denominator.lo > max_magnitude()) {
                throw std::overflow_error(
                    "fraction: result does not fit the storage type");
            }
            num = from_magnitude(negative, numerator.lo);
            den = static_cast<T>(denominator.lo);
        }

        bool try_assign_reduced(
            bool negative, const u256& numerator, const u256& denominator) {
            if (fraction_detail::is_zero(denominator)) return false;
            if (fraction_detail::is_zero(numerator)) {
                num = 0;
                den = 1;
                return true;
            }
            if (numerator.hi != 0 || denominator.hi != 0 ||
                !fits(negative, numerator.lo) ||
                denominator.lo > max_magnitude()) {
                return false;
            }
            num = from_magnitude(negative, numerator.lo);
            den = static_cast<T>(denominator.lo);
            return true;
        }

        void assign_normalized(bool negative, u128 numerator, u128 denominator) {
            if (numerator == 0) {
                num = 0;
                den = 1;
                return;
            }
            u128 g = fraction_detail::gcd(numerator, denominator);
            assign_reduced(
                negative,
                fraction_detail::from_u128(numerator / g),
                fraction_detail::from_u128(denominator / g));
        }

        bool try_assign_normalized(
            bool negative, u128 numerator, u128 denominator) {
            if (denominator == 0) return false;
            if (numerator == 0) {
                num = 0;
                den = 1;
                return true;
            }
            u128 g = fraction_detail::gcd(numerator, denominator);
            return try_assign_reduced(
                negative,
                fraction_detail::from_u128(numerator / g),
                fraction_detail::from_u128(denominator / g));
        }

        static signed_u256 signed_product(T value, u128 multiplier) {
            u256 product =
                fraction_detail::multiply(magnitude(value), multiplier);
            return {
                value < 0 && !fraction_detail::is_zero(product),
                product
            };
        }

        fraction& add_or_subtract(const fraction& other, bool subtract) {
            u128 b = static_cast<u128>(den);
            u128 d = static_cast<u128>(other.den);
            u128 common = fraction_detail::gcd(b, d);
            u128 b_reduced = b / common;
            u128 d_reduced = d / common;

            signed_u256 left = signed_product(num, d_reduced);
            signed_u256 right = signed_product(other.num, b_reduced);
            if (subtract && !fraction_detail::is_zero(right.magnitude)) {
                right.negative = !right.negative;
            }
            signed_u256 numerator = fraction_detail::add(left, right);

            if (fraction_detail::is_zero(numerator.magnitude)) {
                num = 0;
                den = 1;
                return *this;
            }

            u128 remainder =
                fraction_detail::modulo(numerator.magnitude, common);
            u128 reduction = fraction_detail::gcd(remainder, common);
            u256 reduced_numerator =
                fraction_detail::divide_exact(
                    numerator.magnitude, reduction);
            u256 reduced_denominator =
                fraction_detail::multiply(
                    b_reduced, d / reduction);

            assign_reduced(
                numerator.negative,
                reduced_numerator,
                reduced_denominator);
            return *this;
        }

        static bool parse_unsigned(
            const std::string& s, std::size_t first, std::size_t last,
            u128 limit, u128& out) {
            if (first == last) return false;
            u128 value = 0;
            for (std::size_t i = first; i < last; ++i) {
                char c = s[i];
                if (c < '0' || c > '9') return false;
                u128 digit = static_cast<unsigned>(c - '0');
                if (digit > limit ||
                    value > (limit - digit) / 10) {
                    return false;
                }
                value = value * 10 + digit;
            }
            out = value;
            return true;
        }

        static bool pow10(std::size_t exponent, u128& out) {
            u128 value = 1;
            for (std::size_t i = 0; i < exponent; ++i) {
                if (value > max_u128() / 10) return false;
                value *= 10;
            }
            out = value;
            return true;
        }

        static std::ostream& write_integer(std::ostream& os, T value) {
            u128 x = magnitude(value);
            if (value < 0) os.put('-');

            char digits[40];
            int size = 0;
            do {
                digits[size++] = static_cast<char>('0' + x % 10);
                x /= 10;
            } while (x != 0);
            while (size > 0) os.put(digits[--size]);
            return os;
        }

    public:
        fraction operator-() const {
            fraction result;
            result.assign_reduced(
                num >= 0,
                fraction_detail::from_u128(magnitude(num)),
                fraction_detail::from_u128(
                    static_cast<u128>(den)));
            return result;
        }

        fraction inv() const {
            if (num == 0) {
                throw std::domain_error(
                    "fraction: zero has no reciprocal");
            }
            fraction result;
            result.assign_normalized(
                num < 0,
                static_cast<u128>(den),
                magnitude(num));
            return result;
        }

        bool is_integer() const {
            return den == 1;
        }

        long double to_ld() const {
            return static_cast<long double>(num) /
                   static_cast<long double>(den);
        }

        double to_double() const {
            return static_cast<double>(num) /
                   static_cast<double>(den);
        }

        T floor() const {
            u128 n = magnitude(num);
            u128 d = static_cast<u128>(den);
            u128 quotient = n / d;
            u128 remainder = n % d;
            if (num >= 0) return from_magnitude(false, quotient);
            return from_magnitude(true, quotient + (remainder != 0));
        }

        T ceil() const {
            u128 n = magnitude(num);
            u128 d = static_cast<u128>(den);
            u128 quotient = n / d;
            u128 remainder = n % d;
            if (num >= 0) {
                return from_magnitude(
                    false, quotient + (remainder != 0));
            }
            return from_magnitude(true, quotient);
        }

        fraction& operator+=(const fraction& other) {
            return add_or_subtract(other, false);
        }

        fraction& operator-=(const fraction& other) {
            return add_or_subtract(other, true);
        }

        fraction& operator*=(const fraction& other) {
            if (num == 0 || other.num == 0) {
                num = 0;
                den = 1;
                return *this;
            }

            u128 a = magnitude(num);
            u128 b = static_cast<u128>(den);
            u128 c = magnitude(other.num);
            u128 d = static_cast<u128>(other.den);
            u128 left_reduction = fraction_detail::gcd(a, d);
            u128 right_reduction = fraction_detail::gcd(c, b);

            u256 numerator = fraction_detail::multiply(
                a / left_reduction, c / right_reduction);
            u256 denominator = fraction_detail::multiply(
                b / right_reduction, d / left_reduction);
            assign_reduced(
                (num < 0) != (other.num < 0),
                numerator,
                denominator);
            return *this;
        }

        fraction& operator/=(const fraction& other) {
            if (other.num == 0) {
                throw std::domain_error(
                    "fraction: division by zero");
            }
            if (num == 0) {
                den = 1;
                return *this;
            }

            u128 a = magnitude(num);
            u128 b = static_cast<u128>(den);
            u128 c = magnitude(other.num);
            u128 d = static_cast<u128>(other.den);
            u128 numerator_reduction = fraction_detail::gcd(a, c);
            u128 denominator_reduction = fraction_detail::gcd(d, b);

            u256 numerator = fraction_detail::multiply(
                a / numerator_reduction,
                d / denominator_reduction);
            u256 denominator = fraction_detail::multiply(
                b / denominator_reduction,
                c / numerator_reduction);
            assign_reduced(
                (num < 0) != (other.num < 0),
                numerator,
                denominator);
            return *this;
        }

        friend fraction operator+(fraction a, const fraction& b) {
            a += b;
            return a;
        }

        friend fraction operator-(fraction a, const fraction& b) {
            a -= b;
            return a;
        }

        friend fraction operator*(fraction a, const fraction& b) {
            a *= b;
            return a;
        }

        friend fraction operator/(fraction a, const fraction& b) {
            a /= b;
            return a;
        }

        friend bool operator==(const fraction& a, const fraction& b) {
            return a.num == b.num && a.den == b.den;
        }

        friend bool operator!=(const fraction& a, const fraction& b) {
            return !(a == b);
        }

        friend bool operator<(const fraction& a, const fraction& b) {
            if ((a.num < 0) != (b.num < 0)) return a.num < 0;

            u256 left = fraction_detail::multiply(
                magnitude(a.num), static_cast<u128>(b.den));
            u256 right = fraction_detail::multiply(
                magnitude(b.num), static_cast<u128>(a.den));
            int cmp = fraction_detail::compare(left, right);
            return a.num < 0 ? cmp > 0 : cmp < 0;
        }

        friend bool operator>(const fraction& a, const fraction& b) {
            return b < a;
        }

        friend bool operator<=(const fraction& a, const fraction& b) {
            return !(b < a);
        }

        friend bool operator>=(const fraction& a, const fraction& b) {
            return !(a < b);
        }

        // 対応形式: 12, -7, 1.5, .5, 1., 3/4, -10/6
        static bool parse(const std::string& s, fraction& out) {
            if (s.empty()) return false;

            bool negative = false;
            std::size_t first = 0;
            if (s[first] == '+') {
                ++first;
            } else if (s[first] == '-') {
                negative = true;
                ++first;
            }
            if (first == s.size()) return false;

            std::size_t slash = s.find('/', first);
            if (slash != std::string::npos) {
                if (s.find('/', slash + 1) != std::string::npos) return false;

                u128 numerator;
                u128 denominator;
                if (!parse_unsigned(
                        s, first, slash, max_u128(), numerator) ||
                    !parse_unsigned(
                        s, slash + 1, s.size(),
                        max_u128(), denominator) ||
                    denominator == 0) {
                    return false;
                }

                fraction tmp;
                if (!tmp.try_assign_normalized(
                        negative, numerator, denominator)) {
                    return false;
                }
                out = tmp;
                return true;
            }

            std::size_t dot = s.find('.', first);
            if (dot == std::string::npos) {
                u128 numerator;
                if (!parse_unsigned(
                        s, first, s.size(), max_u128(), numerator)) {
                    return false;
                }
                fraction tmp;
                if (!tmp.try_assign_normalized(
                        negative, numerator, 1)) {
                    return false;
                }
                out = tmp;
                return true;
            }
            if (s.find('.', dot + 1) != std::string::npos) return false;
            if (first == dot && dot + 1 == s.size()) return false;

            std::size_t fractional_end = s.size();
            while (fractional_end > dot + 1 &&
                   s[fractional_end - 1] == '0') {
                --fractional_end;
            }

            u128 integer_part = 0;
            if (first != dot &&
                !parse_unsigned(
                    s, first, dot, max_u128(), integer_part)) {
                return false;
            }

            std::size_t fractional_digits = fractional_end - (dot + 1);
            u128 denominator;
            if (!pow10(fractional_digits, denominator)) return false;

            u128 fractional_part = 0;
            if (fractional_digits != 0 &&
                !parse_unsigned(
                    s, dot + 1, fractional_end,
                    denominator - 1, fractional_part)) {
                return false;
            }

            u256 numerator = fraction_detail::add(
                fraction_detail::multiply(integer_part, denominator),
                fraction_detail::from_u128(fractional_part));
            if (fraction_detail::is_zero(numerator)) {
                out = fraction();
                return true;
            }

            u128 reduction = fraction_detail::gcd(
                fraction_detail::modulo(numerator, denominator),
                denominator);
            numerator =
                fraction_detail::divide_exact(numerator, reduction);
            u128 reduced_denominator = denominator / reduction;

            fraction tmp;
            if (!tmp.try_assign_reduced(
                    negative,
                    numerator,
                    fraction_detail::from_u128(reduced_denominator))) {
                return false;
            }
            out = tmp;
            return true;
        }

        friend std::ostream& operator<<(
            std::ostream& os, const fraction& x) {
            write_integer(os, x.num);
            if (x.den != 1) {
                os.put('/');
                write_integer(os, x.den);
            }
            return os;
        }

        friend std::istream& operator>>(
            std::istream& is, fraction& x) {
            std::string s;
            is >> s;
            if (!is) return is;

            fraction tmp;
            if (!fraction::parse(s, tmp)) {
                is.setstate(std::ios::failbit);
                return is;
            }
            x = tmp;
            return is;
        }
    };

    template<class T>
    fraction<T> abs(const fraction<T>& x) {
        return x.num < 0 ? -x : x;
    }

    using fr = fraction<__int128>;
}
