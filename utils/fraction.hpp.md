---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: tests/test.cpp
    title: tests/test.cpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utils/fraction.hpp\"\n\n#include <cstddef>\n#include <ios>\n\
    #include <istream>\n#include <limits>\n#include <ostream>\n#include <stdexcept>\n\
    #include <string>\n#include <type_traits>\n\nnamespace yesantikiss {\n    namespace\
    \ fraction_detail {\n        using i128 = __int128;\n        using u128 = unsigned\
    \ __int128;\n\n        template<class T>\n        inline constexpr bool is_supported_integer_v\
    \ =\n            (std::is_integral_v<T> && std::is_signed_v<T> &&\n          \
    \   !std::is_same_v<T, bool>) ||\n            std::is_same_v<T, i128>;\n\n   \
    \     struct u256 {\n            u128 hi = 0;\n            u128 lo = 0;\n    \
    \    };\n\n        inline bool is_zero(const u256& x) {\n            return x.hi\
    \ == 0 && x.lo == 0;\n        }\n\n        inline int compare(const u256& a, const\
    \ u256& b) {\n            if (a.hi != b.hi) return a.hi < b.hi ? -1 : 1;\n   \
    \         if (a.lo != b.lo) return a.lo < b.lo ? -1 : 1;\n            return 0;\n\
    \        }\n\n        inline u256 add(const u256& a, const u256& b) {\n      \
    \      u256 res;\n            res.lo = a.lo + b.lo;\n            res.hi = a.hi\
    \ + b.hi + (res.lo < a.lo);\n            return res;\n        }\n\n        //\
    \ a >= b \u3092\u4EEE\u5B9A\u3059\u308B\u3002\n        inline u256 subtract(const\
    \ u256& a, const u256& b) {\n            u256 res;\n            res.lo = a.lo\
    \ - b.lo;\n            res.hi = a.hi - b.hi - (a.lo < b.lo);\n            return\
    \ res;\n        }\n\n        inline u256 multiply(u128 a, u128 b) {\n        \
    \    constexpr u128 mask64 = (u128(1) << 64) - 1;\n\n            u128 a0 = a &\
    \ mask64;\n            u128 a1 = a >> 64;\n            u128 b0 = b & mask64;\n\
    \            u128 b1 = b >> 64;\n\n            u128 p00 = a0 * b0;\n         \
    \   u128 p01 = a0 * b1;\n            u128 p10 = a1 * b0;\n            u128 p11\
    \ = a1 * b1;\n\n            u128 lo = p00;\n            u128 x = p01 << 64;\n\
    \            u128 next = lo + x;\n            u128 carry = next < lo;\n      \
    \      lo = next;\n\n            x = p10 << 64;\n            next = lo + x;\n\
    \            carry += next < lo;\n            lo = next;\n\n            u128 hi\
    \ = p11 + (p01 >> 64) + (p10 >> 64) + carry;\n            return {hi, lo};\n \
    \       }\n\n        inline u256 from_u128(u128 x) {\n            return {0, x};\n\
    \        }\n\n        struct div_result {\n            u256 quotient;\n      \
    \      u128 remainder;\n        };\n\n        inline div_result divide(const u256&\
    \ value, u128 divisor) {\n            if (divisor == 0) {\n                throw\
    \ std::domain_error(\"fraction: division by zero\");\n            }\n        \
    \    if (value.hi == 0) {\n                return {{0, value.lo / divisor}, value.lo\
    \ % divisor};\n            }\n\n            u256 quotient;\n            u128 remainder\
    \ = 0;\n            for (int bit_index = 255; bit_index >= 0; --bit_index) {\n\
    \                u128 bit;\n                if (bit_index >= 128) {\n        \
    \            bit = (value.hi >> (bit_index - 128)) & 1;\n                } else\
    \ {\n                    bit = (value.lo >> bit_index) & 1;\n                }\n\
    \n                bool carry = (remainder >> 127) != 0;\n                remainder\
    \ = (remainder << 1) | bit;\n                if (carry || remainder >= divisor)\
    \ {\n                    remainder -= divisor;\n                    if (bit_index\
    \ >= 128) {\n                        quotient.hi |= u128(1) << (bit_index - 128);\n\
    \                    } else {\n                        quotient.lo |= u128(1)\
    \ << bit_index;\n                    }\n                }\n            }\n   \
    \         return {quotient, remainder};\n        }\n\n        inline u128 modulo(const\
    \ u256& value, u128 divisor) {\n            return divide(value, divisor).remainder;\n\
    \        }\n\n        inline u256 divide_exact(const u256& value, u128 divisor)\
    \ {\n            if (divisor == 1) return value;\n            div_result result\
    \ = divide(value, divisor);\n            if (result.remainder != 0) {\n      \
    \          throw std::logic_error(\"fraction: internal non-exact division\");\n\
    \            }\n            return result.quotient;\n        }\n\n        inline\
    \ u128 gcd(u128 a, u128 b) {\n            while (b != 0) {\n                u128\
    \ r = a % b;\n                a = b;\n                b = r;\n            }\n\
    \            return a;\n        }\n\n        struct signed_u256 {\n          \
    \  bool negative = false;\n            u256 magnitude;\n        };\n\n       \
    \ inline signed_u256 add(const signed_u256& a, const signed_u256& b) {\n     \
    \       if (a.negative == b.negative) {\n                signed_u256 res{a.negative,\
    \ add(a.magnitude, b.magnitude)};\n                if (is_zero(res.magnitude))\
    \ res.negative = false;\n                return res;\n            }\n\n      \
    \      int cmp = compare(a.magnitude, b.magnitude);\n            if (cmp == 0)\
    \ return {};\n            if (cmp > 0) {\n                return {a.negative,\
    \ subtract(a.magnitude, b.magnitude)};\n            }\n            return {b.negative,\
    \ subtract(b.magnitude, a.magnitude)};\n        }\n    }\n\n    // T \u306F\u7B26\
    \u53F7\u4ED8\u304D\u6574\u6570\u578B\uFF08\u6700\u5927 __int128\uFF09\u3002\u5E38\
    \u306B\u65E2\u7D04\u304B\u3064 den > 0 \u306B\u4FDD\u3064\u3002\n    // \u6B63\
    \u898F\u5316\u5F8C\u306E\u5024\u304C T \u306B\u53CE\u307E\u3089\u306A\u3044\u6F14\
    \u7B97\u306F std::overflow_error \u3092\u9001\u51FA\u3059\u308B\u3002\n    template<class\
    \ T>\n    struct fraction {\n        static_assert(\n            fraction_detail::is_supported_integer_v<T>,\n\
    \            \"fraction<T>: T must be a signed integral type\");\n        static_assert(\n\
    \            sizeof(T) <= sizeof(fraction_detail::i128),\n            \"fraction<T>:\
    \ integers wider than 128 bits are not supported\");\n\n        using u128 = fraction_detail::u128;\n\
    \        using u256 = fraction_detail::u256;\n        using signed_u256 = fraction_detail::signed_u256;\n\
    \n        T num, den; // den > 0 \u3092\u5E38\u306B\u4FDD\u3064\n\n        fraction()\
    \ : num(0), den(1) {}\n        fraction(T n) : num(n), den(1) {}\n\n        fraction(T\
    \ n, T d) {\n            if (d == 0) {\n                throw std::invalid_argument(\n\
    \                    \"fraction: denominator must not be zero\");\n          \
    \  }\n            bool negative = (n < 0) != (d < 0);\n            assign_normalized(\n\
    \                negative, magnitude(n), magnitude(d));\n        }\n\n    private:\n\
    \        static constexpr u128 max_u128() {\n            return ~u128(0);\n  \
    \      }\n\n        static constexpr u128 max_magnitude() {\n            return\
    \ static_cast<u128>(std::numeric_limits<T>::max());\n        }\n\n        static\
    \ constexpr u128 min_magnitude() {\n            return max_magnitude() + 1;\n\
    \        }\n\n        static u128 magnitude(T x) {\n            u128 value = static_cast<u128>(x);\n\
    \            return x < 0 ? u128(0) - value : value;\n        }\n\n        static\
    \ bool fits(bool negative, u128 value) {\n            return value <= (negative\
    \ ? min_magnitude() : max_magnitude());\n        }\n\n        static T from_magnitude(bool\
    \ negative, u128 value) {\n            if (!fits(negative, value)) {\n       \
    \         throw std::overflow_error(\n                    \"fraction: value does\
    \ not fit the storage type\");\n            }\n            if (!negative) return\
    \ static_cast<T>(value);\n            if (value == min_magnitude()) {\n      \
    \          return std::numeric_limits<T>::min();\n            }\n            return\
    \ -static_cast<T>(value);\n        }\n\n        void assign_reduced(\n       \
    \     bool negative, const u256& numerator, const u256& denominator) {\n     \
    \       if (fraction_detail::is_zero(denominator)) {\n                throw std::invalid_argument(\n\
    \                    \"fraction: denominator must not be zero\");\n          \
    \  }\n            if (fraction_detail::is_zero(numerator)) {\n               \
    \ num = 0;\n                den = 1;\n                return;\n            }\n\
    \            if (numerator.hi != 0 || denominator.hi != 0 ||\n               \
    \ !fits(negative, numerator.lo) ||\n                denominator.lo > max_magnitude())\
    \ {\n                throw std::overflow_error(\n                    \"fraction:\
    \ result does not fit the storage type\");\n            }\n            num = from_magnitude(negative,\
    \ numerator.lo);\n            den = static_cast<T>(denominator.lo);\n        }\n\
    \n        bool try_assign_reduced(\n            bool negative, const u256& numerator,\
    \ const u256& denominator) {\n            if (fraction_detail::is_zero(denominator))\
    \ return false;\n            if (fraction_detail::is_zero(numerator)) {\n    \
    \            num = 0;\n                den = 1;\n                return true;\n\
    \            }\n            if (numerator.hi != 0 || denominator.hi != 0 ||\n\
    \                !fits(negative, numerator.lo) ||\n                denominator.lo\
    \ > max_magnitude()) {\n                return false;\n            }\n       \
    \     num = from_magnitude(negative, numerator.lo);\n            den = static_cast<T>(denominator.lo);\n\
    \            return true;\n        }\n\n        void assign_normalized(bool negative,\
    \ u128 numerator, u128 denominator) {\n            if (numerator == 0) {\n   \
    \             num = 0;\n                den = 1;\n                return;\n  \
    \          }\n            u128 g = fraction_detail::gcd(numerator, denominator);\n\
    \            assign_reduced(\n                negative,\n                fraction_detail::from_u128(numerator\
    \ / g),\n                fraction_detail::from_u128(denominator / g));\n     \
    \   }\n\n        bool try_assign_normalized(\n            bool negative, u128\
    \ numerator, u128 denominator) {\n            if (denominator == 0) return false;\n\
    \            if (numerator == 0) {\n                num = 0;\n               \
    \ den = 1;\n                return true;\n            }\n            u128 g =\
    \ fraction_detail::gcd(numerator, denominator);\n            return try_assign_reduced(\n\
    \                negative,\n                fraction_detail::from_u128(numerator\
    \ / g),\n                fraction_detail::from_u128(denominator / g));\n     \
    \   }\n\n        static signed_u256 signed_product(T value, u128 multiplier) {\n\
    \            u256 product =\n                fraction_detail::multiply(magnitude(value),\
    \ multiplier);\n            return {\n                value < 0 && !fraction_detail::is_zero(product),\n\
    \                product\n            };\n        }\n\n        fraction& add_or_subtract(const\
    \ fraction& other, bool subtract) {\n            u128 b = static_cast<u128>(den);\n\
    \            u128 d = static_cast<u128>(other.den);\n            u128 common =\
    \ fraction_detail::gcd(b, d);\n            u128 b_reduced = b / common;\n    \
    \        u128 d_reduced = d / common;\n\n            signed_u256 left = signed_product(num,\
    \ d_reduced);\n            signed_u256 right = signed_product(other.num, b_reduced);\n\
    \            if (subtract && !fraction_detail::is_zero(right.magnitude)) {\n \
    \               right.negative = !right.negative;\n            }\n           \
    \ signed_u256 numerator = fraction_detail::add(left, right);\n\n            if\
    \ (fraction_detail::is_zero(numerator.magnitude)) {\n                num = 0;\n\
    \                den = 1;\n                return *this;\n            }\n\n  \
    \          u128 remainder =\n                fraction_detail::modulo(numerator.magnitude,\
    \ common);\n            u128 reduction = fraction_detail::gcd(remainder, common);\n\
    \            u256 reduced_numerator =\n                fraction_detail::divide_exact(\n\
    \                    numerator.magnitude, reduction);\n            u256 reduced_denominator\
    \ =\n                fraction_detail::multiply(\n                    b_reduced,\
    \ d / reduction);\n\n            assign_reduced(\n                numerator.negative,\n\
    \                reduced_numerator,\n                reduced_denominator);\n \
    \           return *this;\n        }\n\n        static bool parse_unsigned(\n\
    \            const std::string& s, std::size_t first, std::size_t last,\n    \
    \        u128 limit, u128& out) {\n            if (first == last) return false;\n\
    \            u128 value = 0;\n            for (std::size_t i = first; i < last;\
    \ ++i) {\n                char c = s[i];\n                if (c < '0' || c > '9')\
    \ return false;\n                u128 digit = static_cast<unsigned>(c - '0');\n\
    \                if (digit > limit ||\n                    value > (limit - digit)\
    \ / 10) {\n                    return false;\n                }\n            \
    \    value = value * 10 + digit;\n            }\n            out = value;\n  \
    \          return true;\n        }\n\n        static bool pow10(std::size_t exponent,\
    \ u128& out) {\n            u128 value = 1;\n            for (std::size_t i =\
    \ 0; i < exponent; ++i) {\n                if (value > max_u128() / 10) return\
    \ false;\n                value *= 10;\n            }\n            out = value;\n\
    \            return true;\n        }\n\n        static std::ostream& write_integer(std::ostream&\
    \ os, T value) {\n            u128 x = magnitude(value);\n            if (value\
    \ < 0) os.put('-');\n\n            char digits[40];\n            int size = 0;\n\
    \            do {\n                digits[size++] = static_cast<char>('0' + x\
    \ % 10);\n                x /= 10;\n            } while (x != 0);\n          \
    \  while (size > 0) os.put(digits[--size]);\n            return os;\n        }\n\
    \n    public:\n        fraction operator-() const {\n            fraction result;\n\
    \            result.assign_reduced(\n                num >= 0,\n             \
    \   fraction_detail::from_u128(magnitude(num)),\n                fraction_detail::from_u128(\n\
    \                    static_cast<u128>(den)));\n            return result;\n \
    \       }\n\n        fraction inv() const {\n            if (num == 0) {\n   \
    \             throw std::domain_error(\n                    \"fraction: zero has\
    \ no reciprocal\");\n            }\n            fraction result;\n           \
    \ result.assign_normalized(\n                num < 0,\n                static_cast<u128>(den),\n\
    \                magnitude(num));\n            return result;\n        }\n\n \
    \       bool is_integer() const {\n            return den == 1;\n        }\n\n\
    \        long double to_ld() const {\n            return static_cast<long double>(num)\
    \ /\n                   static_cast<long double>(den);\n        }\n\n        double\
    \ to_double() const {\n            return static_cast<double>(num) /\n       \
    \            static_cast<double>(den);\n        }\n\n        T floor() const {\n\
    \            u128 n = magnitude(num);\n            u128 d = static_cast<u128>(den);\n\
    \            u128 quotient = n / d;\n            u128 remainder = n % d;\n   \
    \         if (num >= 0) return from_magnitude(false, quotient);\n            return\
    \ from_magnitude(true, quotient + (remainder != 0));\n        }\n\n        T ceil()\
    \ const {\n            u128 n = magnitude(num);\n            u128 d = static_cast<u128>(den);\n\
    \            u128 quotient = n / d;\n            u128 remainder = n % d;\n   \
    \         if (num >= 0) {\n                return from_magnitude(\n          \
    \          false, quotient + (remainder != 0));\n            }\n            return\
    \ from_magnitude(true, quotient);\n        }\n\n        fraction& operator+=(const\
    \ fraction& other) {\n            return add_or_subtract(other, false);\n    \
    \    }\n\n        fraction& operator-=(const fraction& other) {\n            return\
    \ add_or_subtract(other, true);\n        }\n\n        fraction& operator*=(const\
    \ fraction& other) {\n            if (num == 0 || other.num == 0) {\n        \
    \        num = 0;\n                den = 1;\n                return *this;\n \
    \           }\n\n            u128 a = magnitude(num);\n            u128 b = static_cast<u128>(den);\n\
    \            u128 c = magnitude(other.num);\n            u128 d = static_cast<u128>(other.den);\n\
    \            u128 left_reduction = fraction_detail::gcd(a, d);\n            u128\
    \ right_reduction = fraction_detail::gcd(c, b);\n\n            u256 numerator\
    \ = fraction_detail::multiply(\n                a / left_reduction, c / right_reduction);\n\
    \            u256 denominator = fraction_detail::multiply(\n                b\
    \ / right_reduction, d / left_reduction);\n            assign_reduced(\n     \
    \           (num < 0) != (other.num < 0),\n                numerator,\n      \
    \          denominator);\n            return *this;\n        }\n\n        fraction&\
    \ operator/=(const fraction& other) {\n            if (other.num == 0) {\n   \
    \             throw std::domain_error(\n                    \"fraction: division\
    \ by zero\");\n            }\n            if (num == 0) {\n                den\
    \ = 1;\n                return *this;\n            }\n\n            u128 a = magnitude(num);\n\
    \            u128 b = static_cast<u128>(den);\n            u128 c = magnitude(other.num);\n\
    \            u128 d = static_cast<u128>(other.den);\n            u128 numerator_reduction\
    \ = fraction_detail::gcd(a, c);\n            u128 denominator_reduction = fraction_detail::gcd(d,\
    \ b);\n\n            u256 numerator = fraction_detail::multiply(\n           \
    \     a / numerator_reduction,\n                d / denominator_reduction);\n\
    \            u256 denominator = fraction_detail::multiply(\n                b\
    \ / denominator_reduction,\n                c / numerator_reduction);\n      \
    \      assign_reduced(\n                (num < 0) != (other.num < 0),\n      \
    \          numerator,\n                denominator);\n            return *this;\n\
    \        }\n\n        friend fraction operator+(fraction a, const fraction& b)\
    \ {\n            a += b;\n            return a;\n        }\n\n        friend fraction\
    \ operator-(fraction a, const fraction& b) {\n            a -= b;\n          \
    \  return a;\n        }\n\n        friend fraction operator*(fraction a, const\
    \ fraction& b) {\n            a *= b;\n            return a;\n        }\n\n  \
    \      friend fraction operator/(fraction a, const fraction& b) {\n          \
    \  a /= b;\n            return a;\n        }\n\n        friend bool operator==(const\
    \ fraction& a, const fraction& b) {\n            return a.num == b.num && a.den\
    \ == b.den;\n        }\n\n        friend bool operator!=(const fraction& a, const\
    \ fraction& b) {\n            return !(a == b);\n        }\n\n        friend bool\
    \ operator<(const fraction& a, const fraction& b) {\n            if ((a.num <\
    \ 0) != (b.num < 0)) return a.num < 0;\n\n            u256 left = fraction_detail::multiply(\n\
    \                magnitude(a.num), static_cast<u128>(b.den));\n            u256\
    \ right = fraction_detail::multiply(\n                magnitude(b.num), static_cast<u128>(a.den));\n\
    \            int cmp = fraction_detail::compare(left, right);\n            return\
    \ a.num < 0 ? cmp > 0 : cmp < 0;\n        }\n\n        friend bool operator>(const\
    \ fraction& a, const fraction& b) {\n            return b < a;\n        }\n\n\
    \        friend bool operator<=(const fraction& a, const fraction& b) {\n    \
    \        return !(b < a);\n        }\n\n        friend bool operator>=(const fraction&\
    \ a, const fraction& b) {\n            return !(a < b);\n        }\n\n       \
    \ // \u5BFE\u5FDC\u5F62\u5F0F: 12, -7, 1.5, .5, 1., 3/4, -10/6\n        static\
    \ bool parse(const std::string& s, fraction& out) {\n            if (s.empty())\
    \ return false;\n\n            bool negative = false;\n            std::size_t\
    \ first = 0;\n            if (s[first] == '+') {\n                ++first;\n \
    \           } else if (s[first] == '-') {\n                negative = true;\n\
    \                ++first;\n            }\n            if (first == s.size()) return\
    \ false;\n\n            std::size_t slash = s.find('/', first);\n            if\
    \ (slash != std::string::npos) {\n                if (s.find('/', slash + 1) !=\
    \ std::string::npos) return false;\n\n                u128 numerator;\n      \
    \          u128 denominator;\n                if (!parse_unsigned(\n         \
    \               s, first, slash, max_u128(), numerator) ||\n                 \
    \   !parse_unsigned(\n                        s, slash + 1, s.size(),\n      \
    \                  max_u128(), denominator) ||\n                    denominator\
    \ == 0) {\n                    return false;\n                }\n\n          \
    \      fraction tmp;\n                if (!tmp.try_assign_normalized(\n      \
    \                  negative, numerator, denominator)) {\n                    return\
    \ false;\n                }\n                out = tmp;\n                return\
    \ true;\n            }\n\n            std::size_t dot = s.find('.', first);\n\
    \            if (dot == std::string::npos) {\n                u128 numerator;\n\
    \                if (!parse_unsigned(\n                        s, first, s.size(),\
    \ max_u128(), numerator)) {\n                    return false;\n             \
    \   }\n                fraction tmp;\n                if (!tmp.try_assign_normalized(\n\
    \                        negative, numerator, 1)) {\n                    return\
    \ false;\n                }\n                out = tmp;\n                return\
    \ true;\n            }\n            if (s.find('.', dot + 1) != std::string::npos)\
    \ return false;\n            if (first == dot && dot + 1 == s.size()) return false;\n\
    \n            std::size_t fractional_end = s.size();\n            while (fractional_end\
    \ > dot + 1 &&\n                   s[fractional_end - 1] == '0') {\n         \
    \       --fractional_end;\n            }\n\n            u128 integer_part = 0;\n\
    \            if (first != dot &&\n                !parse_unsigned(\n         \
    \           s, first, dot, max_u128(), integer_part)) {\n                return\
    \ false;\n            }\n\n            std::size_t fractional_digits = fractional_end\
    \ - (dot + 1);\n            u128 denominator;\n            if (!pow10(fractional_digits,\
    \ denominator)) return false;\n\n            u128 fractional_part = 0;\n     \
    \       if (fractional_digits != 0 &&\n                !parse_unsigned(\n    \
    \                s, dot + 1, fractional_end,\n                    denominator\
    \ - 1, fractional_part)) {\n                return false;\n            }\n\n \
    \           u256 numerator = fraction_detail::add(\n                fraction_detail::multiply(integer_part,\
    \ denominator),\n                fraction_detail::from_u128(fractional_part));\n\
    \            if (fraction_detail::is_zero(numerator)) {\n                out =\
    \ fraction();\n                return true;\n            }\n\n            u128\
    \ reduction = fraction_detail::gcd(\n                fraction_detail::modulo(numerator,\
    \ denominator),\n                denominator);\n            numerator =\n    \
    \            fraction_detail::divide_exact(numerator, reduction);\n          \
    \  u128 reduced_denominator = denominator / reduction;\n\n            fraction\
    \ tmp;\n            if (!tmp.try_assign_reduced(\n                    negative,\n\
    \                    numerator,\n                    fraction_detail::from_u128(reduced_denominator)))\
    \ {\n                return false;\n            }\n            out = tmp;\n  \
    \          return true;\n        }\n\n        friend std::ostream& operator<<(\n\
    \            std::ostream& os, const fraction& x) {\n            write_integer(os,\
    \ x.num);\n            if (x.den != 1) {\n                os.put('/');\n     \
    \           write_integer(os, x.den);\n            }\n            return os;\n\
    \        }\n\n        friend std::istream& operator>>(\n            std::istream&\
    \ is, fraction& x) {\n            std::string s;\n            is >> s;\n     \
    \       if (!is) return is;\n\n            fraction tmp;\n            if (!fraction::parse(s,\
    \ tmp)) {\n                is.setstate(std::ios::failbit);\n                return\
    \ is;\n            }\n            x = tmp;\n            return is;\n        }\n\
    \    };\n\n    template<class T>\n    fraction<T> abs(const fraction<T>& x) {\n\
    \        return x.num < 0 ? -x : x;\n    }\n\n    using fr = fraction<__int128>;\n\
    }\n"
  code: "#pragma once\n\n#include <cstddef>\n#include <ios>\n#include <istream>\n\
    #include <limits>\n#include <ostream>\n#include <stdexcept>\n#include <string>\n\
    #include <type_traits>\n\nnamespace yesantikiss {\n    namespace fraction_detail\
    \ {\n        using i128 = __int128;\n        using u128 = unsigned __int128;\n\
    \n        template<class T>\n        inline constexpr bool is_supported_integer_v\
    \ =\n            (std::is_integral_v<T> && std::is_signed_v<T> &&\n          \
    \   !std::is_same_v<T, bool>) ||\n            std::is_same_v<T, i128>;\n\n   \
    \     struct u256 {\n            u128 hi = 0;\n            u128 lo = 0;\n    \
    \    };\n\n        inline bool is_zero(const u256& x) {\n            return x.hi\
    \ == 0 && x.lo == 0;\n        }\n\n        inline int compare(const u256& a, const\
    \ u256& b) {\n            if (a.hi != b.hi) return a.hi < b.hi ? -1 : 1;\n   \
    \         if (a.lo != b.lo) return a.lo < b.lo ? -1 : 1;\n            return 0;\n\
    \        }\n\n        inline u256 add(const u256& a, const u256& b) {\n      \
    \      u256 res;\n            res.lo = a.lo + b.lo;\n            res.hi = a.hi\
    \ + b.hi + (res.lo < a.lo);\n            return res;\n        }\n\n        //\
    \ a >= b \u3092\u4EEE\u5B9A\u3059\u308B\u3002\n        inline u256 subtract(const\
    \ u256& a, const u256& b) {\n            u256 res;\n            res.lo = a.lo\
    \ - b.lo;\n            res.hi = a.hi - b.hi - (a.lo < b.lo);\n            return\
    \ res;\n        }\n\n        inline u256 multiply(u128 a, u128 b) {\n        \
    \    constexpr u128 mask64 = (u128(1) << 64) - 1;\n\n            u128 a0 = a &\
    \ mask64;\n            u128 a1 = a >> 64;\n            u128 b0 = b & mask64;\n\
    \            u128 b1 = b >> 64;\n\n            u128 p00 = a0 * b0;\n         \
    \   u128 p01 = a0 * b1;\n            u128 p10 = a1 * b0;\n            u128 p11\
    \ = a1 * b1;\n\n            u128 lo = p00;\n            u128 x = p01 << 64;\n\
    \            u128 next = lo + x;\n            u128 carry = next < lo;\n      \
    \      lo = next;\n\n            x = p10 << 64;\n            next = lo + x;\n\
    \            carry += next < lo;\n            lo = next;\n\n            u128 hi\
    \ = p11 + (p01 >> 64) + (p10 >> 64) + carry;\n            return {hi, lo};\n \
    \       }\n\n        inline u256 from_u128(u128 x) {\n            return {0, x};\n\
    \        }\n\n        struct div_result {\n            u256 quotient;\n      \
    \      u128 remainder;\n        };\n\n        inline div_result divide(const u256&\
    \ value, u128 divisor) {\n            if (divisor == 0) {\n                throw\
    \ std::domain_error(\"fraction: division by zero\");\n            }\n        \
    \    if (value.hi == 0) {\n                return {{0, value.lo / divisor}, value.lo\
    \ % divisor};\n            }\n\n            u256 quotient;\n            u128 remainder\
    \ = 0;\n            for (int bit_index = 255; bit_index >= 0; --bit_index) {\n\
    \                u128 bit;\n                if (bit_index >= 128) {\n        \
    \            bit = (value.hi >> (bit_index - 128)) & 1;\n                } else\
    \ {\n                    bit = (value.lo >> bit_index) & 1;\n                }\n\
    \n                bool carry = (remainder >> 127) != 0;\n                remainder\
    \ = (remainder << 1) | bit;\n                if (carry || remainder >= divisor)\
    \ {\n                    remainder -= divisor;\n                    if (bit_index\
    \ >= 128) {\n                        quotient.hi |= u128(1) << (bit_index - 128);\n\
    \                    } else {\n                        quotient.lo |= u128(1)\
    \ << bit_index;\n                    }\n                }\n            }\n   \
    \         return {quotient, remainder};\n        }\n\n        inline u128 modulo(const\
    \ u256& value, u128 divisor) {\n            return divide(value, divisor).remainder;\n\
    \        }\n\n        inline u256 divide_exact(const u256& value, u128 divisor)\
    \ {\n            if (divisor == 1) return value;\n            div_result result\
    \ = divide(value, divisor);\n            if (result.remainder != 0) {\n      \
    \          throw std::logic_error(\"fraction: internal non-exact division\");\n\
    \            }\n            return result.quotient;\n        }\n\n        inline\
    \ u128 gcd(u128 a, u128 b) {\n            while (b != 0) {\n                u128\
    \ r = a % b;\n                a = b;\n                b = r;\n            }\n\
    \            return a;\n        }\n\n        struct signed_u256 {\n          \
    \  bool negative = false;\n            u256 magnitude;\n        };\n\n       \
    \ inline signed_u256 add(const signed_u256& a, const signed_u256& b) {\n     \
    \       if (a.negative == b.negative) {\n                signed_u256 res{a.negative,\
    \ add(a.magnitude, b.magnitude)};\n                if (is_zero(res.magnitude))\
    \ res.negative = false;\n                return res;\n            }\n\n      \
    \      int cmp = compare(a.magnitude, b.magnitude);\n            if (cmp == 0)\
    \ return {};\n            if (cmp > 0) {\n                return {a.negative,\
    \ subtract(a.magnitude, b.magnitude)};\n            }\n            return {b.negative,\
    \ subtract(b.magnitude, a.magnitude)};\n        }\n    }\n\n    // T \u306F\u7B26\
    \u53F7\u4ED8\u304D\u6574\u6570\u578B\uFF08\u6700\u5927 __int128\uFF09\u3002\u5E38\
    \u306B\u65E2\u7D04\u304B\u3064 den > 0 \u306B\u4FDD\u3064\u3002\n    // \u6B63\
    \u898F\u5316\u5F8C\u306E\u5024\u304C T \u306B\u53CE\u307E\u3089\u306A\u3044\u6F14\
    \u7B97\u306F std::overflow_error \u3092\u9001\u51FA\u3059\u308B\u3002\n    template<class\
    \ T>\n    struct fraction {\n        static_assert(\n            fraction_detail::is_supported_integer_v<T>,\n\
    \            \"fraction<T>: T must be a signed integral type\");\n        static_assert(\n\
    \            sizeof(T) <= sizeof(fraction_detail::i128),\n            \"fraction<T>:\
    \ integers wider than 128 bits are not supported\");\n\n        using u128 = fraction_detail::u128;\n\
    \        using u256 = fraction_detail::u256;\n        using signed_u256 = fraction_detail::signed_u256;\n\
    \n        T num, den; // den > 0 \u3092\u5E38\u306B\u4FDD\u3064\n\n        fraction()\
    \ : num(0), den(1) {}\n        fraction(T n) : num(n), den(1) {}\n\n        fraction(T\
    \ n, T d) {\n            if (d == 0) {\n                throw std::invalid_argument(\n\
    \                    \"fraction: denominator must not be zero\");\n          \
    \  }\n            bool negative = (n < 0) != (d < 0);\n            assign_normalized(\n\
    \                negative, magnitude(n), magnitude(d));\n        }\n\n    private:\n\
    \        static constexpr u128 max_u128() {\n            return ~u128(0);\n  \
    \      }\n\n        static constexpr u128 max_magnitude() {\n            return\
    \ static_cast<u128>(std::numeric_limits<T>::max());\n        }\n\n        static\
    \ constexpr u128 min_magnitude() {\n            return max_magnitude() + 1;\n\
    \        }\n\n        static u128 magnitude(T x) {\n            u128 value = static_cast<u128>(x);\n\
    \            return x < 0 ? u128(0) - value : value;\n        }\n\n        static\
    \ bool fits(bool negative, u128 value) {\n            return value <= (negative\
    \ ? min_magnitude() : max_magnitude());\n        }\n\n        static T from_magnitude(bool\
    \ negative, u128 value) {\n            if (!fits(negative, value)) {\n       \
    \         throw std::overflow_error(\n                    \"fraction: value does\
    \ not fit the storage type\");\n            }\n            if (!negative) return\
    \ static_cast<T>(value);\n            if (value == min_magnitude()) {\n      \
    \          return std::numeric_limits<T>::min();\n            }\n            return\
    \ -static_cast<T>(value);\n        }\n\n        void assign_reduced(\n       \
    \     bool negative, const u256& numerator, const u256& denominator) {\n     \
    \       if (fraction_detail::is_zero(denominator)) {\n                throw std::invalid_argument(\n\
    \                    \"fraction: denominator must not be zero\");\n          \
    \  }\n            if (fraction_detail::is_zero(numerator)) {\n               \
    \ num = 0;\n                den = 1;\n                return;\n            }\n\
    \            if (numerator.hi != 0 || denominator.hi != 0 ||\n               \
    \ !fits(negative, numerator.lo) ||\n                denominator.lo > max_magnitude())\
    \ {\n                throw std::overflow_error(\n                    \"fraction:\
    \ result does not fit the storage type\");\n            }\n            num = from_magnitude(negative,\
    \ numerator.lo);\n            den = static_cast<T>(denominator.lo);\n        }\n\
    \n        bool try_assign_reduced(\n            bool negative, const u256& numerator,\
    \ const u256& denominator) {\n            if (fraction_detail::is_zero(denominator))\
    \ return false;\n            if (fraction_detail::is_zero(numerator)) {\n    \
    \            num = 0;\n                den = 1;\n                return true;\n\
    \            }\n            if (numerator.hi != 0 || denominator.hi != 0 ||\n\
    \                !fits(negative, numerator.lo) ||\n                denominator.lo\
    \ > max_magnitude()) {\n                return false;\n            }\n       \
    \     num = from_magnitude(negative, numerator.lo);\n            den = static_cast<T>(denominator.lo);\n\
    \            return true;\n        }\n\n        void assign_normalized(bool negative,\
    \ u128 numerator, u128 denominator) {\n            if (numerator == 0) {\n   \
    \             num = 0;\n                den = 1;\n                return;\n  \
    \          }\n            u128 g = fraction_detail::gcd(numerator, denominator);\n\
    \            assign_reduced(\n                negative,\n                fraction_detail::from_u128(numerator\
    \ / g),\n                fraction_detail::from_u128(denominator / g));\n     \
    \   }\n\n        bool try_assign_normalized(\n            bool negative, u128\
    \ numerator, u128 denominator) {\n            if (denominator == 0) return false;\n\
    \            if (numerator == 0) {\n                num = 0;\n               \
    \ den = 1;\n                return true;\n            }\n            u128 g =\
    \ fraction_detail::gcd(numerator, denominator);\n            return try_assign_reduced(\n\
    \                negative,\n                fraction_detail::from_u128(numerator\
    \ / g),\n                fraction_detail::from_u128(denominator / g));\n     \
    \   }\n\n        static signed_u256 signed_product(T value, u128 multiplier) {\n\
    \            u256 product =\n                fraction_detail::multiply(magnitude(value),\
    \ multiplier);\n            return {\n                value < 0 && !fraction_detail::is_zero(product),\n\
    \                product\n            };\n        }\n\n        fraction& add_or_subtract(const\
    \ fraction& other, bool subtract) {\n            u128 b = static_cast<u128>(den);\n\
    \            u128 d = static_cast<u128>(other.den);\n            u128 common =\
    \ fraction_detail::gcd(b, d);\n            u128 b_reduced = b / common;\n    \
    \        u128 d_reduced = d / common;\n\n            signed_u256 left = signed_product(num,\
    \ d_reduced);\n            signed_u256 right = signed_product(other.num, b_reduced);\n\
    \            if (subtract && !fraction_detail::is_zero(right.magnitude)) {\n \
    \               right.negative = !right.negative;\n            }\n           \
    \ signed_u256 numerator = fraction_detail::add(left, right);\n\n            if\
    \ (fraction_detail::is_zero(numerator.magnitude)) {\n                num = 0;\n\
    \                den = 1;\n                return *this;\n            }\n\n  \
    \          u128 remainder =\n                fraction_detail::modulo(numerator.magnitude,\
    \ common);\n            u128 reduction = fraction_detail::gcd(remainder, common);\n\
    \            u256 reduced_numerator =\n                fraction_detail::divide_exact(\n\
    \                    numerator.magnitude, reduction);\n            u256 reduced_denominator\
    \ =\n                fraction_detail::multiply(\n                    b_reduced,\
    \ d / reduction);\n\n            assign_reduced(\n                numerator.negative,\n\
    \                reduced_numerator,\n                reduced_denominator);\n \
    \           return *this;\n        }\n\n        static bool parse_unsigned(\n\
    \            const std::string& s, std::size_t first, std::size_t last,\n    \
    \        u128 limit, u128& out) {\n            if (first == last) return false;\n\
    \            u128 value = 0;\n            for (std::size_t i = first; i < last;\
    \ ++i) {\n                char c = s[i];\n                if (c < '0' || c > '9')\
    \ return false;\n                u128 digit = static_cast<unsigned>(c - '0');\n\
    \                if (digit > limit ||\n                    value > (limit - digit)\
    \ / 10) {\n                    return false;\n                }\n            \
    \    value = value * 10 + digit;\n            }\n            out = value;\n  \
    \          return true;\n        }\n\n        static bool pow10(std::size_t exponent,\
    \ u128& out) {\n            u128 value = 1;\n            for (std::size_t i =\
    \ 0; i < exponent; ++i) {\n                if (value > max_u128() / 10) return\
    \ false;\n                value *= 10;\n            }\n            out = value;\n\
    \            return true;\n        }\n\n        static std::ostream& write_integer(std::ostream&\
    \ os, T value) {\n            u128 x = magnitude(value);\n            if (value\
    \ < 0) os.put('-');\n\n            char digits[40];\n            int size = 0;\n\
    \            do {\n                digits[size++] = static_cast<char>('0' + x\
    \ % 10);\n                x /= 10;\n            } while (x != 0);\n          \
    \  while (size > 0) os.put(digits[--size]);\n            return os;\n        }\n\
    \n    public:\n        fraction operator-() const {\n            fraction result;\n\
    \            result.assign_reduced(\n                num >= 0,\n             \
    \   fraction_detail::from_u128(magnitude(num)),\n                fraction_detail::from_u128(\n\
    \                    static_cast<u128>(den)));\n            return result;\n \
    \       }\n\n        fraction inv() const {\n            if (num == 0) {\n   \
    \             throw std::domain_error(\n                    \"fraction: zero has\
    \ no reciprocal\");\n            }\n            fraction result;\n           \
    \ result.assign_normalized(\n                num < 0,\n                static_cast<u128>(den),\n\
    \                magnitude(num));\n            return result;\n        }\n\n \
    \       bool is_integer() const {\n            return den == 1;\n        }\n\n\
    \        long double to_ld() const {\n            return static_cast<long double>(num)\
    \ /\n                   static_cast<long double>(den);\n        }\n\n        double\
    \ to_double() const {\n            return static_cast<double>(num) /\n       \
    \            static_cast<double>(den);\n        }\n\n        T floor() const {\n\
    \            u128 n = magnitude(num);\n            u128 d = static_cast<u128>(den);\n\
    \            u128 quotient = n / d;\n            u128 remainder = n % d;\n   \
    \         if (num >= 0) return from_magnitude(false, quotient);\n            return\
    \ from_magnitude(true, quotient + (remainder != 0));\n        }\n\n        T ceil()\
    \ const {\n            u128 n = magnitude(num);\n            u128 d = static_cast<u128>(den);\n\
    \            u128 quotient = n / d;\n            u128 remainder = n % d;\n   \
    \         if (num >= 0) {\n                return from_magnitude(\n          \
    \          false, quotient + (remainder != 0));\n            }\n            return\
    \ from_magnitude(true, quotient);\n        }\n\n        fraction& operator+=(const\
    \ fraction& other) {\n            return add_or_subtract(other, false);\n    \
    \    }\n\n        fraction& operator-=(const fraction& other) {\n            return\
    \ add_or_subtract(other, true);\n        }\n\n        fraction& operator*=(const\
    \ fraction& other) {\n            if (num == 0 || other.num == 0) {\n        \
    \        num = 0;\n                den = 1;\n                return *this;\n \
    \           }\n\n            u128 a = magnitude(num);\n            u128 b = static_cast<u128>(den);\n\
    \            u128 c = magnitude(other.num);\n            u128 d = static_cast<u128>(other.den);\n\
    \            u128 left_reduction = fraction_detail::gcd(a, d);\n            u128\
    \ right_reduction = fraction_detail::gcd(c, b);\n\n            u256 numerator\
    \ = fraction_detail::multiply(\n                a / left_reduction, c / right_reduction);\n\
    \            u256 denominator = fraction_detail::multiply(\n                b\
    \ / right_reduction, d / left_reduction);\n            assign_reduced(\n     \
    \           (num < 0) != (other.num < 0),\n                numerator,\n      \
    \          denominator);\n            return *this;\n        }\n\n        fraction&\
    \ operator/=(const fraction& other) {\n            if (other.num == 0) {\n   \
    \             throw std::domain_error(\n                    \"fraction: division\
    \ by zero\");\n            }\n            if (num == 0) {\n                den\
    \ = 1;\n                return *this;\n            }\n\n            u128 a = magnitude(num);\n\
    \            u128 b = static_cast<u128>(den);\n            u128 c = magnitude(other.num);\n\
    \            u128 d = static_cast<u128>(other.den);\n            u128 numerator_reduction\
    \ = fraction_detail::gcd(a, c);\n            u128 denominator_reduction = fraction_detail::gcd(d,\
    \ b);\n\n            u256 numerator = fraction_detail::multiply(\n           \
    \     a / numerator_reduction,\n                d / denominator_reduction);\n\
    \            u256 denominator = fraction_detail::multiply(\n                b\
    \ / denominator_reduction,\n                c / numerator_reduction);\n      \
    \      assign_reduced(\n                (num < 0) != (other.num < 0),\n      \
    \          numerator,\n                denominator);\n            return *this;\n\
    \        }\n\n        friend fraction operator+(fraction a, const fraction& b)\
    \ {\n            a += b;\n            return a;\n        }\n\n        friend fraction\
    \ operator-(fraction a, const fraction& b) {\n            a -= b;\n          \
    \  return a;\n        }\n\n        friend fraction operator*(fraction a, const\
    \ fraction& b) {\n            a *= b;\n            return a;\n        }\n\n  \
    \      friend fraction operator/(fraction a, const fraction& b) {\n          \
    \  a /= b;\n            return a;\n        }\n\n        friend bool operator==(const\
    \ fraction& a, const fraction& b) {\n            return a.num == b.num && a.den\
    \ == b.den;\n        }\n\n        friend bool operator!=(const fraction& a, const\
    \ fraction& b) {\n            return !(a == b);\n        }\n\n        friend bool\
    \ operator<(const fraction& a, const fraction& b) {\n            if ((a.num <\
    \ 0) != (b.num < 0)) return a.num < 0;\n\n            u256 left = fraction_detail::multiply(\n\
    \                magnitude(a.num), static_cast<u128>(b.den));\n            u256\
    \ right = fraction_detail::multiply(\n                magnitude(b.num), static_cast<u128>(a.den));\n\
    \            int cmp = fraction_detail::compare(left, right);\n            return\
    \ a.num < 0 ? cmp > 0 : cmp < 0;\n        }\n\n        friend bool operator>(const\
    \ fraction& a, const fraction& b) {\n            return b < a;\n        }\n\n\
    \        friend bool operator<=(const fraction& a, const fraction& b) {\n    \
    \        return !(b < a);\n        }\n\n        friend bool operator>=(const fraction&\
    \ a, const fraction& b) {\n            return !(a < b);\n        }\n\n       \
    \ // \u5BFE\u5FDC\u5F62\u5F0F: 12, -7, 1.5, .5, 1., 3/4, -10/6\n        static\
    \ bool parse(const std::string& s, fraction& out) {\n            if (s.empty())\
    \ return false;\n\n            bool negative = false;\n            std::size_t\
    \ first = 0;\n            if (s[first] == '+') {\n                ++first;\n \
    \           } else if (s[first] == '-') {\n                negative = true;\n\
    \                ++first;\n            }\n            if (first == s.size()) return\
    \ false;\n\n            std::size_t slash = s.find('/', first);\n            if\
    \ (slash != std::string::npos) {\n                if (s.find('/', slash + 1) !=\
    \ std::string::npos) return false;\n\n                u128 numerator;\n      \
    \          u128 denominator;\n                if (!parse_unsigned(\n         \
    \               s, first, slash, max_u128(), numerator) ||\n                 \
    \   !parse_unsigned(\n                        s, slash + 1, s.size(),\n      \
    \                  max_u128(), denominator) ||\n                    denominator\
    \ == 0) {\n                    return false;\n                }\n\n          \
    \      fraction tmp;\n                if (!tmp.try_assign_normalized(\n      \
    \                  negative, numerator, denominator)) {\n                    return\
    \ false;\n                }\n                out = tmp;\n                return\
    \ true;\n            }\n\n            std::size_t dot = s.find('.', first);\n\
    \            if (dot == std::string::npos) {\n                u128 numerator;\n\
    \                if (!parse_unsigned(\n                        s, first, s.size(),\
    \ max_u128(), numerator)) {\n                    return false;\n             \
    \   }\n                fraction tmp;\n                if (!tmp.try_assign_normalized(\n\
    \                        negative, numerator, 1)) {\n                    return\
    \ false;\n                }\n                out = tmp;\n                return\
    \ true;\n            }\n            if (s.find('.', dot + 1) != std::string::npos)\
    \ return false;\n            if (first == dot && dot + 1 == s.size()) return false;\n\
    \n            std::size_t fractional_end = s.size();\n            while (fractional_end\
    \ > dot + 1 &&\n                   s[fractional_end - 1] == '0') {\n         \
    \       --fractional_end;\n            }\n\n            u128 integer_part = 0;\n\
    \            if (first != dot &&\n                !parse_unsigned(\n         \
    \           s, first, dot, max_u128(), integer_part)) {\n                return\
    \ false;\n            }\n\n            std::size_t fractional_digits = fractional_end\
    \ - (dot + 1);\n            u128 denominator;\n            if (!pow10(fractional_digits,\
    \ denominator)) return false;\n\n            u128 fractional_part = 0;\n     \
    \       if (fractional_digits != 0 &&\n                !parse_unsigned(\n    \
    \                s, dot + 1, fractional_end,\n                    denominator\
    \ - 1, fractional_part)) {\n                return false;\n            }\n\n \
    \           u256 numerator = fraction_detail::add(\n                fraction_detail::multiply(integer_part,\
    \ denominator),\n                fraction_detail::from_u128(fractional_part));\n\
    \            if (fraction_detail::is_zero(numerator)) {\n                out =\
    \ fraction();\n                return true;\n            }\n\n            u128\
    \ reduction = fraction_detail::gcd(\n                fraction_detail::modulo(numerator,\
    \ denominator),\n                denominator);\n            numerator =\n    \
    \            fraction_detail::divide_exact(numerator, reduction);\n          \
    \  u128 reduced_denominator = denominator / reduction;\n\n            fraction\
    \ tmp;\n            if (!tmp.try_assign_reduced(\n                    negative,\n\
    \                    numerator,\n                    fraction_detail::from_u128(reduced_denominator)))\
    \ {\n                return false;\n            }\n            out = tmp;\n  \
    \          return true;\n        }\n\n        friend std::ostream& operator<<(\n\
    \            std::ostream& os, const fraction& x) {\n            write_integer(os,\
    \ x.num);\n            if (x.den != 1) {\n                os.put('/');\n     \
    \           write_integer(os, x.den);\n            }\n            return os;\n\
    \        }\n\n        friend std::istream& operator>>(\n            std::istream&\
    \ is, fraction& x) {\n            std::string s;\n            is >> s;\n     \
    \       if (!is) return is;\n\n            fraction tmp;\n            if (!fraction::parse(s,\
    \ tmp)) {\n                is.setstate(std::ios::failbit);\n                return\
    \ is;\n            }\n            x = tmp;\n            return is;\n        }\n\
    \    };\n\n    template<class T>\n    fraction<T> abs(const fraction<T>& x) {\n\
    \        return x.num < 0 ? -x : x;\n    }\n\n    using fr = fraction<__int128>;\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/fraction.hpp
  requiredBy:
  - tests/test.cpp
  timestamp: '2026-08-25 15:58:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/fraction.hpp
layout: document
title: "\u6709\u7406\u6570"
---

## 概要

`yesantikiss::fraction<T>` は、符号付き整数 `T` を分子・分母に使う有理数型です。
値は常に既約で、分母が正になるよう正規化されます。`fraction<__int128>` の別名
`yesantikiss::fr` も定義されています。

## API

- `fraction()`, `fraction(n)`, `fraction(n, d)`: `0`、整数、有理数から構築します。
- `+`, `-`, `*`, `/` と各複合代入演算子: 四則演算です。
- `==`, `!=`, `<`, `>`, `<=`, `>=`: 正確な比較です。
- `inv()`: 逆数、`abs(x)`: 絶対値を返します。
- `is_integer()`, `floor()`, `ceil()`: 整数判定・床・天井を返します。
- `to_ld()`, `to_double()`: 浮動小数点数へ変換します。
- `parse(s, out)`: 文字列を解析し、成功したかを返します。
- ストリーム入出力に対応します。出力は整数または `num/den` 形式です。

入力は整数、小数、分数に対応します。例: `12`, `-7`, `1.5`, `.5`, `1.`,
`3/4`, `-10/6`。

## 要件・注意

- `T` は `bool` 以外の符号付き整数型で、最大 128 bit です。
- 分母 `0` の構築は `std::invalid_argument`、`0` の逆数や `0` による除算は
  `std::domain_error` を送出します。
- 正規化後の分子・分母が `T` に収まらない演算は `std::overflow_error` を
  送出します。中間積は 256 bit 相当で計算されます。
- `parse` は失敗時に `false` を返して出力先を変更しません。ストリーム入力は
  同じ場合に `failbit` を設定します。

## 計算量

通常の整数型では各演算は整数のビット幅に依存します。`__int128` の除算を含む
一部のオーバーフロー安全な処理は、最大 256 bit の固定長演算を行います。
