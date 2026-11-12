---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utils/fraction.hpp
    title: "\u6709\u7406\u6570"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/random_fraction.test.cpp\"\n// \u7D20\u6734\u306A\
    \u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\u30E9\u30F3\u30C0\u30E0\
    \u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089 A + B \u3092\u89E3\u304F\
    \u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include\
    \ <cassert>\n#include <iostream>\n#include <random>\n#include <sstream>\n#include\
    \ <stdexcept>\n#include <string>\n\n#line 2 \"utils/fraction.hpp\"\n\n#include\
    \ <cstddef>\n#include <ios>\n#include <istream>\n#include <limits>\n#include <ostream>\n\
    #line 10 \"utils/fraction.hpp\"\n#include <type_traits>\n\nnamespace yesantikiss\
    \ {\n    namespace fraction_detail {\n        using i128 = __int128;\n       \
    \ using u128 = unsigned __int128;\n\n        template<class T>\n        inline\
    \ constexpr bool is_supported_integer_v =\n            (std::is_integral_v<T>\
    \ && std::is_signed_v<T> &&\n             !std::is_same_v<T, bool>) ||\n     \
    \       std::is_same_v<T, i128>;\n\n        struct u256 {\n            u128 hi\
    \ = 0;\n            u128 lo = 0;\n        };\n\n        inline bool is_zero(const\
    \ u256& x) {\n            return x.hi == 0 && x.lo == 0;\n        }\n\n      \
    \  inline int compare(const u256& a, const u256& b) {\n            if (a.hi !=\
    \ b.hi) return a.hi < b.hi ? -1 : 1;\n            if (a.lo != b.lo) return a.lo\
    \ < b.lo ? -1 : 1;\n            return 0;\n        }\n\n        inline u256 add(const\
    \ u256& a, const u256& b) {\n            u256 res;\n            res.lo = a.lo\
    \ + b.lo;\n            res.hi = a.hi + b.hi + (res.lo < a.lo);\n            return\
    \ res;\n        }\n\n        // a >= b \u3092\u4EEE\u5B9A\u3059\u308B\u3002\n\
    \        inline u256 subtract(const u256& a, const u256& b) {\n            u256\
    \ res;\n            res.lo = a.lo - b.lo;\n            res.hi = a.hi - b.hi -\
    \ (a.lo < b.lo);\n            return res;\n        }\n\n        inline u256 multiply(u128\
    \ a, u128 b) {\n            constexpr u128 mask64 = (u128(1) << 64) - 1;\n\n \
    \           u128 a0 = a & mask64;\n            u128 a1 = a >> 64;\n          \
    \  u128 b0 = b & mask64;\n            u128 b1 = b >> 64;\n\n            u128 p00\
    \ = a0 * b0;\n            u128 p01 = a0 * b1;\n            u128 p10 = a1 * b0;\n\
    \            u128 p11 = a1 * b1;\n\n            u128 lo = p00;\n            u128\
    \ x = p01 << 64;\n            u128 next = lo + x;\n            u128 carry = next\
    \ < lo;\n            lo = next;\n\n            x = p10 << 64;\n            next\
    \ = lo + x;\n            carry += next < lo;\n            lo = next;\n\n     \
    \       u128 hi = p11 + (p01 >> 64) + (p10 >> 64) + carry;\n            return\
    \ {hi, lo};\n        }\n\n        inline u256 from_u128(u128 x) {\n          \
    \  return {0, x};\n        }\n\n        struct div_result {\n            u256\
    \ quotient;\n            u128 remainder;\n        };\n\n        inline div_result\
    \ divide(const u256& value, u128 divisor) {\n            if (divisor == 0) {\n\
    \                throw std::domain_error(\"fraction: division by zero\");\n  \
    \          }\n            if (value.hi == 0) {\n                return {{0, value.lo\
    \ / divisor}, value.lo % divisor};\n            }\n\n            // \u5272\u308B\
    \u6570\u304C64\u30D3\u30C3\u30C8\u306B\u53CE\u307E\u308B\u306A\u3089\u300164\u30D3\
    \u30C3\u30C8\u305A\u30644\u56DE\u306E\u5272\u308A\u7B97\u3067\u6E08\u3080\u3002\
    \n            if ((divisor >> 64) == 0) {\n                constexpr u128 mask64\
    \ = (u128(1) << 64) - 1;\n                const u128 limbs[4] = {\n          \
    \          value.hi >> 64, value.hi & mask64,\n                    value.lo >>\
    \ 64, value.lo & mask64};\n                u128 digits[4];\n                u128\
    \ carry = 0;\n                for (int i = 0; i < 4; ++i) {\n                \
    \    u128 current = (carry << 64) | limbs[i];\n                    digits[i] =\
    \ current / divisor;\n                    carry = current % divisor;\n       \
    \         }\n                return {{(digits[0] << 64) | digits[1],\n       \
    \                  (digits[2] << 64) | digits[3]},\n                        carry};\n\
    \            }\n\n            u256 quotient;\n            u128 remainder = 0;\n\
    \            for (int bit_index = 255; bit_index >= 0; --bit_index) {\n      \
    \          u128 bit;\n                if (bit_index >= 128) {\n              \
    \      bit = (value.hi >> (bit_index - 128)) & 1;\n                } else {\n\
    \                    bit = (value.lo >> bit_index) & 1;\n                }\n\n\
    \                bool carry = (remainder >> 127) != 0;\n                remainder\
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
    \            }\n            return result.quotient;\n        }\n\n        // \u5272\
    \u308A\u7B97\u3092\u4F7F\u308F\u306A\u3044 binary gcd\u3002\u5927\u5C0F\u306E\u5165\
    \u308C\u66FF\u3048\u3092\u5206\u5C90\u306A\u3057\u3067\u66F8\u304F\u3002\n   \
    \     inline unsigned long long gcd64(\n            unsigned long long a, unsigned\
    \ long long b) {\n            if (a == 0 || b == 0) return a | b;\n          \
    \  int a_zeros = __builtin_ctzll(a);\n            int b_zeros = __builtin_ctzll(b);\n\
    \            int shift = a_zeros < b_zeros ? a_zeros : b_zeros;\n            a\
    \ >>= a_zeros;\n            b >>= b_zeros;\n            // \u3053\u3053\u304B\u3089\
    \ a, b \u306F\u3069\u3061\u3089\u3082\u5947\u6570\n            while (a != b)\
    \ {\n                unsigned long long difference = a > b ? a - b : b - a;\n\
    \                b = a < b ? a : b;\n                a = difference >> __builtin_ctzll(difference);\n\
    \            }\n            return a << shift;\n        }\n\n        inline int\
    \ count_trailing_zeros(u128 x) {\n            unsigned long long lo = static_cast<unsigned\
    \ long long>(x);\n            if (lo != 0) return __builtin_ctzll(lo);\n     \
    \       return 64 + __builtin_ctzll(\n                static_cast<unsigned long\
    \ long>(x >> 64));\n        }\n\n        // 128\u30D3\u30C3\u30C8\u306E\u5270\u4F59\
    \u306F\u9045\u3044\u306E\u3067\u300164\u30D3\u30C3\u30C8\u306B\u53CE\u307E\u308A\
    \u6B21\u7B2C gcd64 \u306B\u5207\u308A\u66FF\u3048\u308B\u3002\n        inline\
    \ u128 gcd(u128 a, u128 b) {\n            if ((a >> 64) == 0 && (b >> 64) == 0)\
    \ {\n                return gcd64(\n                    static_cast<unsigned long\
    \ long>(a),\n                    static_cast<unsigned long long>(b));\n      \
    \      }\n            if (a < b) {\n                u128 t = a;\n            \
    \    a = b;\n                b = t;\n            }\n            if (b == 0) return\
    \ a;\n            // \u6841\u6570\u306E\u5DEE\u304C\u5927\u304D\u3044\u3068\u304D\
    \u306B\u5099\u3048\u3066\u3001\u6700\u521D\u306B1\u56DE\u3060\u3051\u5270\u4F59\
    \u3092\u53D6\u308B\u3002\n            a %= b;\n            if (a == 0) return\
    \ b;\n\n            int shift = count_trailing_zeros(a | b);\n            a >>=\
    \ count_trailing_zeros(a);\n            do {\n                b >>= count_trailing_zeros(b);\n\
    \                if (a > b) {\n                    u128 t = a;\n             \
    \       a = b;\n                    b = t;\n                }\n              \
    \  if ((b >> 64) == 0) {\n                    return static_cast<u128>(gcd64(\n\
    \                               static_cast<unsigned long long>(a),\n        \
    \                       static_cast<unsigned long long>(b)))\n               \
    \            << shift;\n                }\n                b -= a;\n         \
    \   } while (b != 0);\n            return a << shift;\n        }\n\n        struct\
    \ signed_u256 {\n            bool negative = false;\n            u256 magnitude;\n\
    \        };\n\n        inline signed_u256 add(const signed_u256& a, const signed_u256&\
    \ b) {\n            if (a.negative == b.negative) {\n                signed_u256\
    \ res{a.negative, add(a.magnitude, b.magnitude)};\n                if (is_zero(res.magnitude))\
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
    \                product\n            };\n        }\n\n        using u64 = unsigned\
    \ long long;\n\n        // \u5206\u5B50\u306E\u7D76\u5BFE\u5024\u304C 2^63 \u4EE5\
    \u4E0B\u3001\u5206\u6BCD\u304C 2^63 \u672A\u6E80\u306A\u3089\u3001\u9014\u4E2D\
    \u306E\u7A4D\u3068\u548C\u304C\n        // u128 \u306B\u53CE\u307E\u308B\u306E\
    \u3067\u3001256\u30D3\u30C3\u30C8\u306E\u8A08\u7B97\u3092\u4F7F\u308F\u305A\u306B\
    \u6E08\u3080\u3002\n        static bool is_small(const fraction& x) {\n      \
    \      if constexpr (sizeof(T) <= sizeof(u64)) {\n                return true;\n\
    \            } else {\n                constexpr u128 limit = u128(1) << 63;\n\
    \                return magnitude(x.num) <= limit &&\n                       static_cast<u128>(x.den)\
    \ < limit;\n            }\n        }\n\n        fraction& add_or_subtract_small(const\
    \ fraction& other, bool subtract) {\n            u64 b = static_cast<u64>(den);\n\
    \            u64 d = static_cast<u64>(other.den);\n            u64 common = fraction_detail::gcd64(b,\
    \ d);\n            u64 b_reduced = b / common;\n\n            u128 left = magnitude(num)\
    \ * (d / common);\n            u128 right = magnitude(other.num) * b_reduced;\n\
    \            bool left_negative = num < 0;\n            bool right_negative =\
    \ (other.num < 0) != subtract;\n\n            bool negative;\n            u128\
    \ numerator;\n            if (left_negative == right_negative) {\n           \
    \     negative = left_negative;\n                numerator = left + right;\n \
    \           } else if (left >= right) {\n                negative = left_negative;\n\
    \                numerator = left - right;\n            } else {\n           \
    \     negative = right_negative;\n                numerator = right - left;\n\
    \            }\n            if (numerator == 0) {\n                num = 0;\n\
    \                den = 1;\n                return *this;\n            }\n\n  \
    \          u64 reduction = common;\n            if (common != 1) {\n         \
    \       reduction = fraction_detail::gcd64(\n                    static_cast<u64>(numerator\
    \ % common), common);\n                numerator /= reduction;\n            }\n\
    \            assign_reduced(\n                negative,\n                fraction_detail::from_u128(numerator),\n\
    \                fraction_detail::from_u128(\n                    static_cast<u128>(b_reduced)\
    \ * (d / reduction)));\n            return *this;\n        }\n\n        // (a\
    \ / b) * (c / d) \u3092\u3001a, b, c, d \u304C 2^63 \u4EE5\u4E0B\u306E\u3068\u304D\
    \u306B\u8A08\u7B97\u3059\u308B\u3002\n        fraction& multiply_small(bool negative,\
    \ u64 a, u64 b, u64 c, u64 d) {\n            u64 left_reduction = fraction_detail::gcd64(a,\
    \ d);\n            u64 right_reduction = fraction_detail::gcd64(c, b);\n     \
    \       assign_reduced(\n                negative,\n                fraction_detail::from_u128(\n\
    \                    static_cast<u128>(a / left_reduction) *\n               \
    \     (c / right_reduction)),\n                fraction_detail::from_u128(\n \
    \                   static_cast<u128>(b / right_reduction) *\n               \
    \     (d / left_reduction)));\n            return *this;\n        }\n\n      \
    \  fraction& add_or_subtract(const fraction& other, bool subtract) {\n       \
    \     if (is_small(*this) && is_small(other)) {\n                return add_or_subtract_small(other,\
    \ subtract);\n            }\n\n            u128 b = static_cast<u128>(den);\n\
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
    \           }\n\n            if (is_small(*this) && is_small(other)) {\n     \
    \           return multiply_small(\n                    (num < 0) != (other.num\
    \ < 0),\n                    static_cast<u64>(magnitude(num)),\n             \
    \       static_cast<u64>(den),\n                    static_cast<u64>(magnitude(other.num)),\n\
    \                    static_cast<u64>(other.den));\n            }\n\n        \
    \    u128 a = magnitude(num);\n            u128 b = static_cast<u128>(den);\n\
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
    \ = 1;\n                return *this;\n            }\n\n            if (is_small(*this)\
    \ && is_small(other)) {\n                // (a / b) / (c / d) = (a / b) * (d /\
    \ c)\n                return multiply_small(\n                    (num < 0) !=\
    \ (other.num < 0),\n                    static_cast<u64>(magnitude(num)),\n  \
    \                  static_cast<u64>(den),\n                    static_cast<u64>(other.den),\n\
    \                    static_cast<u64>(magnitude(other.num)));\n            }\n\
    \n            u128 a = magnitude(num);\n            u128 b = static_cast<u128>(den);\n\
    \            u128 c = magnitude(other.num);\n            u128 d = static_cast<u128>(other.den);\n\
    \            u128 numerator_reduction = fraction_detail::gcd(a, c);\n        \
    \    u128 denominator_reduction = fraction_detail::gcd(d, b);\n\n            u256\
    \ numerator = fraction_detail::multiply(\n                a / numerator_reduction,\n\
    \                d / denominator_reduction);\n            u256 denominator = fraction_detail::multiply(\n\
    \                b / denominator_reduction,\n                c / numerator_reduction);\n\
    \            assign_reduced(\n                (num < 0) != (other.num < 0),\n\
    \                numerator,\n                denominator);\n            return\
    \ *this;\n        }\n\n        friend fraction operator+(fraction a, const fraction&\
    \ b) {\n            a += b;\n            return a;\n        }\n\n        friend\
    \ fraction operator-(fraction a, const fraction& b) {\n            a -= b;\n \
    \           return a;\n        }\n\n        friend fraction operator*(fraction\
    \ a, const fraction& b) {\n            a *= b;\n            return a;\n      \
    \  }\n\n        friend fraction operator/(fraction a, const fraction& b) {\n \
    \           a /= b;\n            return a;\n        }\n\n        friend bool operator==(const\
    \ fraction& a, const fraction& b) {\n            return a.num == b.num && a.den\
    \ == b.den;\n        }\n\n        friend bool operator!=(const fraction& a, const\
    \ fraction& b) {\n            return !(a == b);\n        }\n\n        friend bool\
    \ operator<(const fraction& a, const fraction& b) {\n            if ((a.num <\
    \ 0) != (b.num < 0)) return a.num < 0;\n\n            if (is_small(a) && is_small(b))\
    \ {\n                u128 left = magnitude(a.num) * static_cast<u128>(b.den);\n\
    \                u128 right = magnitude(b.num) * static_cast<u128>(a.den);\n \
    \               return a.num < 0 ? left > right : left < right;\n            }\n\
    \n            u256 left = fraction_detail::multiply(\n                magnitude(a.num),\
    \ static_cast<u128>(b.den));\n            u256 right = fraction_detail::multiply(\n\
    \                magnitude(b.num), static_cast<u128>(a.den));\n            int\
    \ cmp = fraction_detail::compare(left, right);\n            return a.num < 0 ?\
    \ cmp > 0 : cmp < 0;\n        }\n\n        friend bool operator>(const fraction&\
    \ a, const fraction& b) {\n            return b < a;\n        }\n\n        friend\
    \ bool operator<=(const fraction& a, const fraction& b) {\n            return\
    \ !(b < a);\n        }\n\n        friend bool operator>=(const fraction& a, const\
    \ fraction& b) {\n            return !(a < b);\n        }\n\n        // \u5BFE\
    \u5FDC\u5F62\u5F0F: 12, -7, 1.5, .5, 1., 3/4, -10/6\n        static bool parse(const\
    \ std::string& s, fraction& out) {\n            if (s.empty()) return false;\n\
    \n            bool negative = false;\n            std::size_t first = 0;\n   \
    \         if (s[first] == '+') {\n                ++first;\n            } else\
    \ if (s[first] == '-') {\n                negative = true;\n                ++first;\n\
    \            }\n            if (first == s.size()) return false;\n\n         \
    \   std::size_t slash = s.find('/', first);\n            if (slash != std::string::npos)\
    \ {\n                if (s.find('/', slash + 1) != std::string::npos) return false;\n\
    \n                u128 numerator;\n                u128 denominator;\n       \
    \         if (!parse_unsigned(\n                        s, first, slash, max_u128(),\
    \ numerator) ||\n                    !parse_unsigned(\n                      \
    \  s, slash + 1, s.size(),\n                        max_u128(), denominator) ||\n\
    \                    denominator == 0) {\n                    return false;\n\
    \                }\n\n                fraction tmp;\n                if (!tmp.try_assign_normalized(\n\
    \                        negative, numerator, denominator)) {\n              \
    \      return false;\n                }\n                out = tmp;\n        \
    \        return true;\n            }\n\n            std::size_t dot = s.find('.',\
    \ first);\n            if (dot == std::string::npos) {\n                u128 numerator;\n\
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
    }\n#line 12 \"verify/random_fraction.test.cpp\"\n\nnamespace {\n    using i128\
    \ = __int128;\n    using u128 = unsigned __int128;\n    using yesantikiss::fraction;\n\
    \n    std::mt19937_64 random_engine(20261110);\n\n    template <class T>\n   \
    \ T max_of() {\n        return static_cast<T>((u128(1) << (8 * sizeof(T) - 1))\
    \ - 1);\n    }\n\n    template <class T>\n    T min_of() {\n        return static_cast<T>(-max_of<T>()\
    \ - 1);\n    }\n\n    i128 gcd(i128 a, i128 b) {\n        if (a < 0) a = -a;\n\
    \        if (b < 0) b = -b;\n        while (b != 0) {\n            i128 r = a\
    \ % b;\n            a = b;\n            b = r;\n        }\n        return a;\n\
    \    }\n\n    std::string to_string(i128 x) {\n        if (x == 0) return \"0\"\
    ;\n        bool negative = x < 0;\n        u128 magnitude = negative ? u128(0)\
    \ - static_cast<u128>(x)\n                                  : static_cast<u128>(x);\n\
    \        std::string digits;\n        while (magnitude != 0) {\n            digits.insert(digits.begin(),\n\
    \                          static_cast<char>('0' + static_cast<int>(magnitude\
    \ % 10)));\n            magnitude /= 10;\n        }\n        return negative ?\
    \ \"-\" + digits : digits;\n    }\n\n    // \u7D20\u6734\u306A\u6709\u7406\u6570\
    \u3002\u5206\u5B50\u30FB\u5206\u6BCD\u3092 __int128 \u3067\u6301\u3061\u3001\u3042\
    \u3075\u308C\u306A\u3044\u7BC4\u56F2\u3067\u3060\u3051\u4F7F\u3046\u3002\n   \
    \ struct Exact {\n        i128 num = 0, den = 1;\n        bool defined = true;\n\
    \    };\n\n    Exact normalize(i128 num, i128 den) {\n        if (den == 0) return\
    \ {0, 1, false};\n        if (den < 0) {\n            num = -num;\n          \
    \  den = -den;\n        }\n        i128 g = gcd(num, den);\n        return {num\
    \ / g, den / g, true};\n    }\n\n    template <class T>\n    bool fits(const Exact&\
    \ x) {\n        return min_of<T>() <= x.num && x.num <= max_of<T>() &&\n     \
    \          x.den <= max_of<T>();\n    }\n\n    template <class T>\n    bool same(const\
    \ fraction<T>& x, const Exact& expected) {\n        return static_cast<i128>(x.num)\
    \ == expected.num &&\n               static_cast<i128>(x.den) == expected.den;\n\
    \    }\n\n    // \u7D76\u5BFE\u5024\u304C limit \u4EE5\u4E0B\u306E\u5024\u3002\
    \u7AEF\u306E\u5024\u3068\u5C0F\u3055\u3044\u5024\u304C\u51FA\u3084\u3059\u3044\
    \u3088\u3046\u306B\u3059\u308B\u3002\n    i128 random_value(i128 limit, bool allow_min)\
    \ {\n        int kind = static_cast<int>(random_engine() % 8);\n        if (kind\
    \ == 0) return 0;\n        if (kind == 1) return limit;\n        if (kind == 2)\
    \ return allow_min ? -limit - 1 : -limit;\n        if (kind == 3) {\n        \
    \    return static_cast<i128>(random_engine() % 7) - 3;\n        }\n        //\
    \ \u6841\u6570\u3092\u4E00\u69D8\u306B\u9078\u3076\n        int bits = 0;\n  \
    \      while ((limit >> bits) > 1) ++bits;\n        int use = 1 + static_cast<int>(random_engine()\
    \ % (bits + 1));\n        u128 raw = (static_cast<u128>(random_engine()) << 64)\
    \ | random_engine();\n        i128 value = static_cast<i128>(raw % (u128(1) <<\
    \ use));\n        if (value > limit) value = limit;\n        return random_engine()\
    \ % 2 == 0 ? value : -value;\n    }\n\n    // f \u3092\u5B9F\u884C\u3057\u3001\
    \u671F\u5F85\u5024\u304C T \u306B\u53CE\u307E\u308B\u306A\u3089\u4E00\u81F4\u3001\
    \u53CE\u307E\u3089\u306A\u3044\u306A\u3089\n    // overflow_error\u3001\u672A\u5B9A\
    \u7FA9\u306A\u3089 domain_error \u306B\u306A\u308B\u3053\u3068\u3092\u78BA\u304B\
    \u3081\u308B\u3002\n    template <class T, class F>\n    void check(const Exact&\
    \ expected, F f) {\n        try {\n            fraction<T> result = f();\n   \
    \         assert(expected.defined && fits<T>(expected));\n            assert(same(result,\
    \ expected));\n        } catch (const std::overflow_error&) {\n            assert(expected.defined\
    \ && !fits<T>(expected));\n        } catch (const std::domain_error&) {\n    \
    \        assert(!expected.defined);\n        }\n    }\n\n    // T \u306E\u5168\
    \u7BC4\u56F2\u3092\u4F7F\u3044\u3001\u3042\u3075\u308C\u306E\u5883\u754C\u3082\
    \u542B\u3081\u3066\u7D20\u6734\u89E3\u3068\u6BD4\u3079\u308B\u3002\n    // limit\
    \ \u306F\u7D20\u6734\u89E3\u306E\u9014\u4E2D\u8A08\u7B97\u304C __int128 \u306B\
    \u53CE\u307E\u308B\u4E0A\u9650\u3002\n    template <class T>\n    void test_against_exact(int\
    \ trials, i128 limit, bool allow_min) {\n        using F = fraction<T>;\n    \
    \    for (int trial = 0; trial < trials; ++trial) {\n            i128 a = random_value(limit,\
    \ allow_min);\n            i128 b = random_value(limit, allow_min);\n        \
    \    i128 c = random_value(limit, allow_min);\n            i128 d = random_value(limit,\
    \ allow_min);\n            if (b == 0) b = 1;\n            if (d == 0) d = 1;\n\
    \n            Exact ex = normalize(a, b), ey = normalize(c, d);\n            check<T>(ex,\
    \ [&] { return F(static_cast<T>(a), static_cast<T>(b)); });\n            if (!fits<T>(ex)\
    \ || !fits<T>(ey)) continue;\n\n            const F x(static_cast<T>(a), static_cast<T>(b));\n\
    \            const F y(static_cast<T>(c), static_cast<T>(d));\n            assert(same(x,\
    \ ex) && same(y, ey));\n            assert(x.is_integer() == (ex.den == 1));\n\
    \n            // \u56DB\u5247\u6F14\u7B97\n            Exact sum = normalize(ex.num\
    \ * ey.den + ey.num * ex.den,\n                                  ex.den * ey.den);\n\
    \            Exact difference = normalize(\n                ex.num * ey.den -\
    \ ey.num * ex.den, ex.den * ey.den);\n            Exact product = normalize(ex.num\
    \ * ey.num, ex.den * ey.den);\n            Exact quotient = normalize(ex.num *\
    \ ey.den, ex.den * ey.num);\n            check<T>(sum, [&] { return x + y; });\n\
    \            check<T>(difference, [&] { return x - y; });\n            check<T>(product,\
    \ [&] { return x * y; });\n            check<T>(quotient, [&] { return x / y;\
    \ });\n\n            // \u8907\u5408\u4EE3\u5165\u306F\u3001\u4F8B\u5916\u3092\
    \u6295\u3052\u305F\u3068\u304D\u306B\u5143\u306E\u5024\u3092\u58CA\u3055\u306A\
    \u3044\n            for (int op = 0; op < 4; ++op) {\n                F z = x;\n\
    \                try {\n                    if (op == 0) z += y;\n           \
    \         if (op == 1) z -= y;\n                    if (op == 2) z *= y;\n   \
    \                 if (op == 3) z /= y;\n                    const Exact& expected\
    \ = op == 0   ? sum\n                                            : op == 1 ? difference\n\
    \                                            : op == 2 ? product\n           \
    \                                           : quotient;\n                    assert(same(z,\
    \ expected));\n                } catch (const std::overflow_error&) {\n      \
    \              assert(z == x);\n                } catch (const std::domain_error&)\
    \ {\n                    assert(z == x && op == 3 && ey.num == 0);\n         \
    \       }\n            }\n\n            // \u5358\u9805\u6F14\u7B97\n        \
    \    check<T>(normalize(-ex.num, ex.den), [&] { return -x; });\n            check<T>(normalize(ex.num\
    \ < 0 ? -ex.num : ex.num, ex.den),\n                     [&] { return abs(x);\
    \ });\n            check<T>(normalize(ex.den, ex.num), [&] { return x.inv(); });\n\
    \n            // \u6BD4\u8F03\n            i128 left = ex.num * ey.den, right\
    \ = ey.num * ex.den;\n            assert((x < y) == (left < right));\n       \
    \     assert((x > y) == (left > right));\n            assert((x <= y) == (left\
    \ <= right));\n            assert((x >= y) == (left >= right));\n            assert((x\
    \ == y) == (left == right));\n            assert((x != y) == (left != right));\n\
    \n            // floor / ceil\n            i128 floor = ex.num / ex.den, ceil\
    \ = ex.num / ex.den;\n            if (ex.num % ex.den != 0) {\n              \
    \  if (ex.num < 0) --floor;\n                else ++ceil;\n            }\n   \
    \         assert(static_cast<i128>(x.floor()) == floor);\n            assert(static_cast<i128>(x.ceil())\
    \ == ceil);\n\n            // \u51FA\u529B\u3057\u305F\u6587\u5B57\u5217\u3092\
    \u8AAD\u307F\u76F4\u3059\u3068\u5143\u306B\u623B\u308B\n            std::ostringstream\
    \ os;\n            os << x;\n            std::string text = to_string(ex.num);\n\
    \            if (ex.den != 1) text += \"/\" + to_string(ex.den);\n           \
    \ assert(os.str() == text);\n            F parsed(1);\n            assert(F::parse(text,\
    \ parsed) && parsed == x);\n\n            // \u65E2\u7D04\u3067\u306A\u3044 a/b\
    \ \u306E\u5F62\u3002\u53CE\u307E\u3089\u306A\u3044\u306A\u3089 false \u3067\u3001\
    out \u306F\u5909\u3048\u306A\u3044\n            if (b > 0) {\n               \
    \ parsed = F(1);\n                bool ok = F::parse(to_string(a) + \"/\" + to_string(b),\
    \ parsed);\n                assert(ok && parsed == x);\n            }\n      \
    \  }\n    }\n\n    // \u5C0F\u6570\u306E\u6587\u5B57\u5217\u3092\u8AAD\u3080\u3002\
    \n    template <class T>\n    void test_parse_decimal(int trials, int max_digits)\
    \ {\n        using F = fraction<T>;\n        for (int trial = 0; trial < trials;\
    \ ++trial) {\n            int integer_digits =\n                static_cast<int>(random_engine()\
    \ % (max_digits + 1));\n            int fraction_digits =\n                static_cast<int>(random_engine()\
    \ % (max_digits + 1));\n            std::string integer_part, fraction_part;\n\
    \            i128 numerator = 0, denominator = 1;\n            for (int i = 0;\
    \ i < integer_digits; ++i) {\n                int digit = static_cast<int>(random_engine()\
    \ % 10);\n                integer_part += static_cast<char>('0' + digit);\n  \
    \              numerator = numerator * 10 + digit;\n            }\n          \
    \  for (int i = 0; i < fraction_digits; ++i) {\n                // \u672B\u5C3E\
    \u306E 0 \u304C\u7D9A\u304F\u5834\u5408\u3082\u8A66\u3059\n                int\
    \ digit = random_engine() % 3 == 0\n                                ? 0\n    \
    \                            : static_cast<int>(random_engine() % 10);\n     \
    \           fraction_part += static_cast<char>('0' + digit);\n               \
    \ numerator = numerator * 10 + digit;\n                denominator *= 10;\n  \
    \          }\n            int sign = static_cast<int>(random_engine() % 3);\n\
    \            std::string text = sign == 0 ? \"\" : sign == 1 ? \"+\" : \"-\";\n\
    \            text += integer_part;\n            bool has_dot = fraction_digits\
    \ > 0 || random_engine() % 2 == 0;\n            if (has_dot) text += \".\" + fraction_part;\n\
    \n            Exact expected =\n                normalize(sign == 2 ? -numerator\
    \ : numerator, denominator);\n            bool valid = integer_digits + fraction_digits\
    \ > 0;\n            F parsed(7);\n            bool ok = F::parse(text, parsed);\n\
    \            assert(ok == (valid && fits<T>(expected)));\n            if (ok)\
    \ assert(same(parsed, expected));\n            else assert(parsed == F(7));\n\
    \        }\n    }\n\n    template <class T>\n    void test_parse_fixed() {\n \
    \       using F = fraction<T>;\n        for (const char* text :\n            \
    \ {\"\", \"+\", \"-\", \".\", \"-.\", \"+.\", \"1/0\", \"0/0\", \"1//2\", \"1/2/3\"\
    ,\n              \"/2\", \"1/\", \"a\", \"1a\", \"1.2.3\", \"1/-2\", \"1/+2\"\
    , \"--1\", \"+-1\",\n              \" 1\", \"1 \", \"1e5\", \"0x1\", \"1/ 2\"\
    , \"1./2\", \"1/2.\", \"1.5/2\"}) {\n            F parsed(7);\n            assert(!F::parse(text,\
    \ parsed));\n            assert(parsed == F(7));\n        }\n        F parsed;\n\
    \        assert(F::parse(\"1.\", parsed) && parsed == F(1));\n        assert(F::parse(\"\
    .5\", parsed) && parsed == F(1, 2));\n        assert(F::parse(\"-.25\", parsed)\
    \ && parsed == F(-1, 4));\n        assert(F::parse(\"-0\", parsed) && parsed ==\
    \ F(0));\n        assert(F::parse(\"-0.000\", parsed) && parsed == F(0));\n  \
    \      assert(F::parse(\"+3/6\", parsed) && parsed == F(1, 2));\n        assert(F::parse(\"\
    0/5\", parsed) && parsed == F(0));\n        assert(F::parse(\"007\", parsed) &&\
    \ parsed == F(7));\n        assert(F::parse(\"-10/4\", parsed) && parsed == F(-5,\
    \ 2));\n\n        // \u30B9\u30C8\u30EA\u30FC\u30E0\u304B\u3089\u306E\u8AAD\u307F\
    \u8FBC\u307F\u3002\u5931\u6557\u3057\u305F\u3089 failbit \u304C\u7ACB\u3061\u3001\
    \u5024\u306F\u5909\u308F\u3089\u306A\u3044\n        std::istringstream is(\"3/4\
    \ -1.25 x 5\");\n        F p, q, r(7);\n        is >> p >> q;\n        assert(is\
    \ && p == F(3, 4) && q == F(-5, 4));\n        is >> r;\n        assert(is.fail()\
    \ && r == F(7));\n        std::istringstream empty(\"\");\n        empty >> r;\n\
    \        assert(empty.fail() && r == F(7));\n\n        // \u30BC\u30ED\u9664\u7B97\
    \n        bool thrown = false;\n        try {\n            F zero_denominator(1,\
    \ 0);\n        } catch (const std::invalid_argument&) {\n            thrown =\
    \ true;\n        }\n        assert(thrown);\n    }\n\n    // \u5185\u90E8\u306E\
    \ gcd \u3068 256\u30D3\u30C3\u30C8 \xF7 128\u30D3\u30C3\u30C8\u306E\u5272\u308A\
    \u7B97\u3092\u3001\u7D20\u6734\u306A\u8A08\u7B97\u3068\u6BD4\u3079\u308B\u3002\
    \n    void test_detail() {\n        namespace detail = yesantikiss::fraction_detail;\n\
    \        auto random_bits = [&](int bits) {\n            u128 raw =\n        \
    \        (static_cast<u128>(random_engine()) << 64) | random_engine();\n     \
    \       return bits == 128 ? raw : raw % (u128(1) << bits);\n        };\n    \
    \    auto naive_gcd = [](u128 a, u128 b) {\n            while (b != 0) {\n   \
    \             u128 r = a % b;\n                a = b;\n                b = r;\n\
    \            }\n            return a;\n        };\n        for (int trial = 0;\
    \ trial < 20000; ++trial) {\n            // \u6841\u6570\u3092\u3070\u3089\u3070\
    \u3089\u306B\u9078\u3073\u3001\u5171\u901A\u56E0\u6570\u3082\u6301\u305F\u305B\
    \u308B\n            u128 a = random_bits(static_cast<int>(random_engine() % 129));\n\
    \            u128 b = random_bits(static_cast<int>(random_engine() % 129));\n\
    \            if (trial % 3 == 0) {\n                u128 g = random_bits(static_cast<int>(random_engine()\
    \ % 70));\n                a = (a >> 70) * g;\n                b = (b >> 70) *\
    \ g;\n            }\n            if (trial % 11 == 0) b = a;\n            if (trial\
    \ % 13 == 0) a <<= random_engine() % 40;\n            if (trial % 7 == 0) {\n\
    \                // \u4E0B\u4F4D64\u30D3\u30C3\u30C8\u304C\u3059\u3079\u3066 0\
    \ \u306E\u5024\n                a = (a >> 100 | 1) << (64 + random_engine() %\
    \ 36);\n                b = (b >> 100 | 1) << (64 + random_engine() % 36);\n \
    \           }\n            u128 expected = naive_gcd(a, b);\n            assert(detail::gcd(a,\
    \ b) == expected);\n            assert(detail::gcd(b, a) == expected);\n     \
    \       if ((a >> 64) == 0 && (b >> 64) == 0) {\n                assert(detail::gcd64(static_cast<unsigned\
    \ long long>(a),\n                                     static_cast<unsigned long\
    \ long>(b)) ==\n                       expected);\n            }\n        }\n\
    \        assert(detail::gcd(0, 0) == 0 && detail::gcd64(0, 0) == 0);\n       \
    \ assert(detail::gcd(0, 7) == 7 && detail::gcd(~u128(0), 0) == ~u128(0));\n  \
    \      assert(detail::gcd(~u128(0), ~u128(0)) == ~u128(0));\n        assert(detail::gcd(u128(1)\
    \ << 127, u128(1) << 100) == u128(1) << 100);\n\n        for (int trial = 0; trial\
    \ < 6000; ++trial) {\n            // value = quotient * divisor + remainder \u3092\
    \u4F5C\u3063\u3066\u304B\u3089\u5272\u308A\u76F4\u3059\u3002\n            // \u5272\
    \u308B\u6570\u304C64\u30D3\u30C3\u30C8\u4EE5\u4E0B\u306E\u8FD1\u9053\u3068\u3001\
    \u305D\u308C\u3088\u308A\u5927\u304D\u3044\u5834\u5408\u306E\u4E21\u65B9\u3092\
    \u901A\u3059\u3002\n            u128 divisor =\n                random_bits(1\
    \ + static_cast<int>(random_engine() % 128)) + 1;\n            if (divisor ==\
    \ 0) divisor = 1;\n            u128 quotient =\n                random_bits(static_cast<int>(random_engine()\
    \ % 129));\n            u128 remainder = random_bits(128) % divisor;\n       \
    \     detail::u256 value = detail::add(\n                detail::multiply(quotient,\
    \ divisor),\n                detail::from_u128(remainder));\n            detail::div_result\
    \ result = detail::divide(value, divisor);\n            assert(result.quotient.hi\
    \ == 0 && result.quotient.lo == quotient);\n            assert(result.remainder\
    \ == remainder);\n            assert(detail::modulo(value, divisor) == remainder);\n\
    \        }\n        // \u5546\u304C128\u30D3\u30C3\u30C8\u3092\u8D85\u3048\u308B\
    \u5834\u5408: (2^256 - 1) / 3 = 0x5555...\n        detail::div_result all = detail::divide({~u128(0),\
    \ ~u128(0)}, 3);\n        assert(all.remainder == 0);\n        assert(all.quotient.hi\
    \ == ~u128(0) / 3 && all.quotient.lo == ~u128(0) / 3);\n        all = detail::divide({~u128(0),\
    \ ~u128(0)}, (u128(1) << 64) + 1);\n        assert(detail::compare(\n        \
    \           detail::add(detail::add(\n                                   detail::multiply(all.quotient.lo,\n\
    \                                                    (u128(1) << 64) + 1),\n \
    \                                  detail::u256{\n                           \
    \            all.quotient.hi * ((u128(1) << 64) + 1),\n                      \
    \                 0}),\n                               detail::from_u128(all.remainder)),\n\
    \                   detail::u256{~u128(0), ~u128(0)}) == 0);\n    }\n\n    //\
    \ __int128 \u3067\u300164\u30D3\u30C3\u30C8\u306B\u53CE\u307E\u308B\u3068\u304D\
    \u306E\u8FD1\u9053\u3068\u901A\u5E38\u306E\u7D4C\u8DEF\u306E\u5207\u308A\u66FF\
    \u308F\u308A\n    // (2^63 \u3068 2^64 \u306E\u524D\u5F8C) \u3092\u3001\u7D20\u6734\
    \u89E3\u304C __int128 \u306B\u53CE\u307E\u308B\u7D44\u307F\u5408\u308F\u305B\u3067\
    \u8A66\u3059\u3002\n    void test_boundary() {\n        using F = fraction<i128>;\n\
    \        auto small = [&]() {\n            return static_cast<i128>(random_engine()\
    \ % 2000001) - 1000000;\n        };\n        auto near = [&](bool allow_64) {\n\
    \            i128 pivot = i128(1) << (allow_64 && random_engine() % 2 ? 64 : 63);\n\
    \            i128 value = pivot + static_cast<i128>(random_engine() % 7) - 3;\n\
    \            return random_engine() % 2 == 0 ? value : -value;\n        };\n \
    \       for (int trial = 0; trial < 20000; ++trial) {\n            i128 a, b,\
    \ c, d;\n            if (trial % 2 == 0) {\n                // \u5206\u5B50\u304C\
    \u5883\u754C\u306E\u8FD1\u304F\u3001\u5206\u6BCD\u306F\u5C0F\u3055\u3044\n   \
    \             a = random_engine() % 4 == 0 ? small() : near(true);\n         \
    \       c = random_engine() % 4 == 0 ? small() : near(true);\n               \
    \ b = small();\n                d = small();\n            } else {\n         \
    \       // \u5206\u6BCD\u304C\u5883\u754C\u306E\u8FD1\u304F\u3001\u5206\u5B50\u306F\
    \u5C0F\u3055\u3044\n                a = small();\n                c = small();\n\
    \                b = random_engine() % 4 == 0 ? small() : near(false);\n     \
    \           d = random_engine() % 4 == 0 ? small() : near(false);\n          \
    \  }\n            if (b == 0) b = 1;\n            if (d == 0) d = 1;\n       \
    \     Exact ex = normalize(a, b), ey = normalize(c, d);\n            const F x(a,\
    \ b), y(c, d);\n            assert(same(x, ex) && same(y, ey));\n\n          \
    \  check<i128>(normalize(ex.num * ey.den + ey.num * ex.den,\n                \
    \                  ex.den * ey.den),\n                        [&] { return x +\
    \ y; });\n            check<i128>(normalize(ex.num * ey.den - ey.num * ex.den,\n\
    \                                  ex.den * ey.den),\n                       \
    \ [&] { return x - y; });\n            // \u7A4D\u3068\u5546\u306F\u3001\u7D20\
    \u6734\u89E3\u306E\u9014\u4E2D\u8A08\u7B97\u304C\u53CE\u307E\u308B\u5411\u304D\
    \u3060\u3051\u78BA\u304B\u3081\u308B\n            if (trial % 2 == 0) {\n    \
    \            check<i128>(normalize(ex.num * ey.den, ex.den * ey.num),\n      \
    \                      [&] { return x / y; });\n            } else {\n       \
    \         check<i128>(normalize(ex.num * ey.num, ex.den * ey.den),\n         \
    \                   [&] { return x * y; });\n            }\n            i128 left\
    \ = ex.num * ey.den, right = ey.num * ex.den;\n            assert((x < y) == (left\
    \ < right));\n            assert((y < x) == (right < left));\n            assert((x\
    \ == y) == (left == right));\n        }\n    }\n\n    // __int128 \u3067\u3001\
    \u9014\u4E2D\u306E\u7A4D\u304C128\u30D3\u30C3\u30C8\u3092\u8D85\u3048\u308B\u7D4C\
    \u8DEF\u3092\u901A\u3059\u3002\n    // \u7B54\u3048\u304C\u5206\u304B\u308B\u5F62\
    \u306B\u5024\u3092\u7D44\u307F\u7ACB\u3066\u3066\u6BD4\u3079\u308B\u3002\n   \
    \ void test_wide() {\n        using F = fraction<i128>;\n        auto random_bits\
    \ = [&](int bits) {\n            u128 raw =\n                (static_cast<u128>(random_engine())\
    \ << 64) | random_engine();\n            return static_cast<i128>(raw % (u128(1)\
    \ << bits)) + 1;\n        };\n        int wide_sums = 0;\n        for (int trial\
    \ = 0; trial < 2000; ++trial) {\n            // \u540C\u3058\u5206\u6BCD m: p/m\
    \ \xB1 q/m = (p \xB1 q)/m\n            {\n                i128 m = random_bits(40\
    \ + static_cast<int>(random_engine() % 80));\n                i128 p = random_bits(125),\
    \ q = random_bits(125);\n                if (random_engine() % 2 == 0) p = -p;\n\
    \                if (random_engine() % 2 == 0) q = -q;\n                F x(p,\
    \ m), y(q, m);\n                assert(same(x, normalize(p, m)) && same(y, normalize(q,\
    \ m)));\n                // \u7D04\u5206\u5F8C\u306E\u5206\u6BCD\u3069\u3046\u3057\
    \u306E\u7A4D\u304C\u5927\u304D\u3044\u3068\u3001\u9014\u4E2D\u3067128\u30D3\u30C3\
    \u30C8\u3092\u8D85\u3048\u308B\n                if (x.den > (i128(1) << 64) &&\
    \ y.den > (i128(1) << 64)) {\n                    ++wide_sums;\n             \
    \   }\n                assert(same(x + y, normalize(p + q, m)));\n           \
    \     assert(same(x - y, normalize(p - q, m)));\n                assert((x < y)\
    \ == (p < q));\n                assert((x == y) == (p == q));\n            }\n\
    \            // \u4E92\u3044\u306B\u7D04\u5206\u3055\u308C\u308B\u7A4D: (p*s)/(q*t)\
    \ * (q*u)/(p*v) = (s*u)/(t*v)\n            {\n                i128 p = random_bits(62),\
    \ q = random_bits(62);\n                i128 s = random_bits(60), t = random_bits(60);\n\
    \                i128 u = random_bits(60), v = random_bits(60);\n            \
    \    F x(p * s, q * t), y(q * u, p * v);\n                if (random_engine()\
    \ % 2 == 0) x = -x;\n                Exact expected = normalize(s * u, t * v);\n\
    \                if (x.num < 0) expected.num = -expected.num;\n              \
    \  assert(same(x * y, expected));\n                // x / (1/y) \u3082\u540C\u3058\
    \u5024\n                assert(same(x / y.inv(), expected));\n            }\n\
    \            // \u5927\u304D\u3044\u5024\u3069\u3046\u3057\u306E\u6BD4\u8F03:\
    \ p/q \u3068 (p+1)/q\u3001p/q \u3068 p/(q+1)\n            {\n                i128\
    \ p = random_bits(126), q = random_bits(126);\n                assert(F(p, q)\
    \ < F(p + 1, q) && F(p, q + 1) < F(p, q));\n                assert(F(-p - 1, q)\
    \ < F(-p, q) && F(-p, q) < F(-p, q + 1));\n                assert(!(F(p, q) <\
    \ F(p, q)) && F(p, q) <= F(p, q));\n                assert(F(-p, q) < F(p, q +\
    \ 1));\n            }\n            // \u8DB3\u3057\u3066\u5F15\u304F\u3068\u5143\
    \u306B\u623B\u308B (\u3042\u3075\u308C\u305F\u3089\u4F8B\u5916\u3067\u3001\u5143\
    \u306E\u5024\u306F\u5909\u308F\u3089\u306A\u3044)\n            {\n           \
    \     F x(random_bits(100), random_bits(60));\n                F y(random_bits(100),\
    \ random_bits(60));\n                try {\n                    F z = x + y;\n\
    \                    assert(z - y == x && z - x == y);\n                } catch\
    \ (const std::overflow_error&) {\n                }\n                try {\n \
    \                   F z = x * y;\n                    assert(z / y == x && z /\
    \ x == y);\n                } catch (const std::overflow_error&) {\n         \
    \       }\n            }\n        }\n        assert(wide_sums > 100);\n\n    \
    \    // \u578B\u306E\u7AEF\u306E\u5024\n        const i128 max = max_of<i128>(),\
    \ min = min_of<i128>();\n        assert(same(F(max, 3) - F(max - 1, 3), normalize(1,\
    \ 3)));\n        assert(F(min, min) == F(1) && F(max, max) == F(1));\n       \
    \ assert(F(min, 2) < F(max, 2) && F(min) < F(min + 1));\n        assert(F(max,\
    \ max - 1) * F(max - 1, max) == F(1));\n        assert(F(min).floor() == min &&\
    \ F(max).ceil() == max);\n        bool thrown = false;\n        try {\n      \
    \      (void)-F(min);\n        } catch (const std::overflow_error&) {\n      \
    \      thrown = true;\n        }\n        assert(thrown);\n        thrown = false;\n\
    \        try {\n            (void)(F(max) + F(1));\n        } catch (const std::overflow_error&)\
    \ {\n            thrown = true;\n        }\n        assert(thrown);\n\n      \
    \  std::ostringstream os;\n        os << F(min) << ' ' << F(max, 2);\n       \
    \ assert(os.str() == to_string(min) + \" \" + to_string(max) + \"/2\");\n    \
    \    F parsed;\n        assert(F::parse(to_string(min), parsed) && parsed == F(min));\n\
    \        assert(!F::parse(to_string(max) + \"0\", parsed));\n    }\n}\n\nint main()\
    \ {\n    // verify \u3067\u306F\u30C6\u30B9\u30C8\u30B1\u30FC\u30B9\u3054\u3068\
    \u306B\u5B9F\u884C\u3055\u308C\u308B\u306E\u3067\u3001\u56DE\u6570\u306F1\u79D2\
    \u4EE5\u5185\u306B\u53CE\u307E\u308B\n    // \u7A0B\u5EA6\u306B\u3057\u3066\u3044\
    \u308B\u3002\n    // 8\u30D3\u30C3\u30C8\u3067\u306F\u5168\u7BC4\u56F2\u3092\u4F7F\
    \u3044\u3001\u3042\u3075\u308C\u306E\u5883\u754C\u3092\u96C6\u4E2D\u7684\u306B\
    \u8A66\u3059\u3002\n    test_against_exact<signed char>(20000, max_of<signed char>(),\
    \ true);\n    test_against_exact<short>(8000, max_of<short>(), true);\n    test_against_exact<int>(12000,\
    \ max_of<int>(), true);\n    // \u7D20\u6734\u89E3\u306E\u9014\u4E2D\u8A08\u7B97\
    \u304C __int128 \u306B\u53CE\u307E\u308B\u3088\u3046\u3001\u7D76\u5BFE\u5024\u306F\
    \ 2^62 \u307E\u3067\n    test_against_exact<long long>(12000, i128(1) << 62, false);\n\
    \    test_against_exact<i128>(12000, i128(1) << 62, false);\n\n    test_parse_decimal<signed\
    \ char>(20000, 4);\n    test_parse_decimal<int>(20000, 11);\n    test_parse_decimal<long\
    \ long>(20000, 18);\n    test_parse_decimal<i128>(20000, 18);\n    test_parse_fixed<int>();\n\
    \    test_parse_fixed<long long>();\n    test_parse_fixed<i128>();\n\n    test_detail();\n\
    \    test_boundary();\n    test_wide();\n\n    long long a, b;\n    std::cin >>\
    \ a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "// \u7D20\u6734\u306A\u5B9F\u88C5\u3068\u7A81\u304D\u5408\u308F\u305B\u308B\
    \u30E9\u30F3\u30C0\u30E0\u30C6\u30B9\u30C8\u3092\u901A\u3057\u3066\u304B\u3089\
    \ A + B \u3092\u89E3\u304F\u3002\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#include <cassert>\n#include <iostream>\n#include <random>\n#include <sstream>\n\
    #include <stdexcept>\n#include <string>\n\n#include \"utils/fraction.hpp\"\n\n\
    namespace {\n    using i128 = __int128;\n    using u128 = unsigned __int128;\n\
    \    using yesantikiss::fraction;\n\n    std::mt19937_64 random_engine(20261110);\n\
    \n    template <class T>\n    T max_of() {\n        return static_cast<T>((u128(1)\
    \ << (8 * sizeof(T) - 1)) - 1);\n    }\n\n    template <class T>\n    T min_of()\
    \ {\n        return static_cast<T>(-max_of<T>() - 1);\n    }\n\n    i128 gcd(i128\
    \ a, i128 b) {\n        if (a < 0) a = -a;\n        if (b < 0) b = -b;\n     \
    \   while (b != 0) {\n            i128 r = a % b;\n            a = b;\n      \
    \      b = r;\n        }\n        return a;\n    }\n\n    std::string to_string(i128\
    \ x) {\n        if (x == 0) return \"0\";\n        bool negative = x < 0;\n  \
    \      u128 magnitude = negative ? u128(0) - static_cast<u128>(x)\n          \
    \                        : static_cast<u128>(x);\n        std::string digits;\n\
    \        while (magnitude != 0) {\n            digits.insert(digits.begin(),\n\
    \                          static_cast<char>('0' + static_cast<int>(magnitude\
    \ % 10)));\n            magnitude /= 10;\n        }\n        return negative ?\
    \ \"-\" + digits : digits;\n    }\n\n    // \u7D20\u6734\u306A\u6709\u7406\u6570\
    \u3002\u5206\u5B50\u30FB\u5206\u6BCD\u3092 __int128 \u3067\u6301\u3061\u3001\u3042\
    \u3075\u308C\u306A\u3044\u7BC4\u56F2\u3067\u3060\u3051\u4F7F\u3046\u3002\n   \
    \ struct Exact {\n        i128 num = 0, den = 1;\n        bool defined = true;\n\
    \    };\n\n    Exact normalize(i128 num, i128 den) {\n        if (den == 0) return\
    \ {0, 1, false};\n        if (den < 0) {\n            num = -num;\n          \
    \  den = -den;\n        }\n        i128 g = gcd(num, den);\n        return {num\
    \ / g, den / g, true};\n    }\n\n    template <class T>\n    bool fits(const Exact&\
    \ x) {\n        return min_of<T>() <= x.num && x.num <= max_of<T>() &&\n     \
    \          x.den <= max_of<T>();\n    }\n\n    template <class T>\n    bool same(const\
    \ fraction<T>& x, const Exact& expected) {\n        return static_cast<i128>(x.num)\
    \ == expected.num &&\n               static_cast<i128>(x.den) == expected.den;\n\
    \    }\n\n    // \u7D76\u5BFE\u5024\u304C limit \u4EE5\u4E0B\u306E\u5024\u3002\
    \u7AEF\u306E\u5024\u3068\u5C0F\u3055\u3044\u5024\u304C\u51FA\u3084\u3059\u3044\
    \u3088\u3046\u306B\u3059\u308B\u3002\n    i128 random_value(i128 limit, bool allow_min)\
    \ {\n        int kind = static_cast<int>(random_engine() % 8);\n        if (kind\
    \ == 0) return 0;\n        if (kind == 1) return limit;\n        if (kind == 2)\
    \ return allow_min ? -limit - 1 : -limit;\n        if (kind == 3) {\n        \
    \    return static_cast<i128>(random_engine() % 7) - 3;\n        }\n        //\
    \ \u6841\u6570\u3092\u4E00\u69D8\u306B\u9078\u3076\n        int bits = 0;\n  \
    \      while ((limit >> bits) > 1) ++bits;\n        int use = 1 + static_cast<int>(random_engine()\
    \ % (bits + 1));\n        u128 raw = (static_cast<u128>(random_engine()) << 64)\
    \ | random_engine();\n        i128 value = static_cast<i128>(raw % (u128(1) <<\
    \ use));\n        if (value > limit) value = limit;\n        return random_engine()\
    \ % 2 == 0 ? value : -value;\n    }\n\n    // f \u3092\u5B9F\u884C\u3057\u3001\
    \u671F\u5F85\u5024\u304C T \u306B\u53CE\u307E\u308B\u306A\u3089\u4E00\u81F4\u3001\
    \u53CE\u307E\u3089\u306A\u3044\u306A\u3089\n    // overflow_error\u3001\u672A\u5B9A\
    \u7FA9\u306A\u3089 domain_error \u306B\u306A\u308B\u3053\u3068\u3092\u78BA\u304B\
    \u3081\u308B\u3002\n    template <class T, class F>\n    void check(const Exact&\
    \ expected, F f) {\n        try {\n            fraction<T> result = f();\n   \
    \         assert(expected.defined && fits<T>(expected));\n            assert(same(result,\
    \ expected));\n        } catch (const std::overflow_error&) {\n            assert(expected.defined\
    \ && !fits<T>(expected));\n        } catch (const std::domain_error&) {\n    \
    \        assert(!expected.defined);\n        }\n    }\n\n    // T \u306E\u5168\
    \u7BC4\u56F2\u3092\u4F7F\u3044\u3001\u3042\u3075\u308C\u306E\u5883\u754C\u3082\
    \u542B\u3081\u3066\u7D20\u6734\u89E3\u3068\u6BD4\u3079\u308B\u3002\n    // limit\
    \ \u306F\u7D20\u6734\u89E3\u306E\u9014\u4E2D\u8A08\u7B97\u304C __int128 \u306B\
    \u53CE\u307E\u308B\u4E0A\u9650\u3002\n    template <class T>\n    void test_against_exact(int\
    \ trials, i128 limit, bool allow_min) {\n        using F = fraction<T>;\n    \
    \    for (int trial = 0; trial < trials; ++trial) {\n            i128 a = random_value(limit,\
    \ allow_min);\n            i128 b = random_value(limit, allow_min);\n        \
    \    i128 c = random_value(limit, allow_min);\n            i128 d = random_value(limit,\
    \ allow_min);\n            if (b == 0) b = 1;\n            if (d == 0) d = 1;\n\
    \n            Exact ex = normalize(a, b), ey = normalize(c, d);\n            check<T>(ex,\
    \ [&] { return F(static_cast<T>(a), static_cast<T>(b)); });\n            if (!fits<T>(ex)\
    \ || !fits<T>(ey)) continue;\n\n            const F x(static_cast<T>(a), static_cast<T>(b));\n\
    \            const F y(static_cast<T>(c), static_cast<T>(d));\n            assert(same(x,\
    \ ex) && same(y, ey));\n            assert(x.is_integer() == (ex.den == 1));\n\
    \n            // \u56DB\u5247\u6F14\u7B97\n            Exact sum = normalize(ex.num\
    \ * ey.den + ey.num * ex.den,\n                                  ex.den * ey.den);\n\
    \            Exact difference = normalize(\n                ex.num * ey.den -\
    \ ey.num * ex.den, ex.den * ey.den);\n            Exact product = normalize(ex.num\
    \ * ey.num, ex.den * ey.den);\n            Exact quotient = normalize(ex.num *\
    \ ey.den, ex.den * ey.num);\n            check<T>(sum, [&] { return x + y; });\n\
    \            check<T>(difference, [&] { return x - y; });\n            check<T>(product,\
    \ [&] { return x * y; });\n            check<T>(quotient, [&] { return x / y;\
    \ });\n\n            // \u8907\u5408\u4EE3\u5165\u306F\u3001\u4F8B\u5916\u3092\
    \u6295\u3052\u305F\u3068\u304D\u306B\u5143\u306E\u5024\u3092\u58CA\u3055\u306A\
    \u3044\n            for (int op = 0; op < 4; ++op) {\n                F z = x;\n\
    \                try {\n                    if (op == 0) z += y;\n           \
    \         if (op == 1) z -= y;\n                    if (op == 2) z *= y;\n   \
    \                 if (op == 3) z /= y;\n                    const Exact& expected\
    \ = op == 0   ? sum\n                                            : op == 1 ? difference\n\
    \                                            : op == 2 ? product\n           \
    \                                           : quotient;\n                    assert(same(z,\
    \ expected));\n                } catch (const std::overflow_error&) {\n      \
    \              assert(z == x);\n                } catch (const std::domain_error&)\
    \ {\n                    assert(z == x && op == 3 && ey.num == 0);\n         \
    \       }\n            }\n\n            // \u5358\u9805\u6F14\u7B97\n        \
    \    check<T>(normalize(-ex.num, ex.den), [&] { return -x; });\n            check<T>(normalize(ex.num\
    \ < 0 ? -ex.num : ex.num, ex.den),\n                     [&] { return abs(x);\
    \ });\n            check<T>(normalize(ex.den, ex.num), [&] { return x.inv(); });\n\
    \n            // \u6BD4\u8F03\n            i128 left = ex.num * ey.den, right\
    \ = ey.num * ex.den;\n            assert((x < y) == (left < right));\n       \
    \     assert((x > y) == (left > right));\n            assert((x <= y) == (left\
    \ <= right));\n            assert((x >= y) == (left >= right));\n            assert((x\
    \ == y) == (left == right));\n            assert((x != y) == (left != right));\n\
    \n            // floor / ceil\n            i128 floor = ex.num / ex.den, ceil\
    \ = ex.num / ex.den;\n            if (ex.num % ex.den != 0) {\n              \
    \  if (ex.num < 0) --floor;\n                else ++ceil;\n            }\n   \
    \         assert(static_cast<i128>(x.floor()) == floor);\n            assert(static_cast<i128>(x.ceil())\
    \ == ceil);\n\n            // \u51FA\u529B\u3057\u305F\u6587\u5B57\u5217\u3092\
    \u8AAD\u307F\u76F4\u3059\u3068\u5143\u306B\u623B\u308B\n            std::ostringstream\
    \ os;\n            os << x;\n            std::string text = to_string(ex.num);\n\
    \            if (ex.den != 1) text += \"/\" + to_string(ex.den);\n           \
    \ assert(os.str() == text);\n            F parsed(1);\n            assert(F::parse(text,\
    \ parsed) && parsed == x);\n\n            // \u65E2\u7D04\u3067\u306A\u3044 a/b\
    \ \u306E\u5F62\u3002\u53CE\u307E\u3089\u306A\u3044\u306A\u3089 false \u3067\u3001\
    out \u306F\u5909\u3048\u306A\u3044\n            if (b > 0) {\n               \
    \ parsed = F(1);\n                bool ok = F::parse(to_string(a) + \"/\" + to_string(b),\
    \ parsed);\n                assert(ok && parsed == x);\n            }\n      \
    \  }\n    }\n\n    // \u5C0F\u6570\u306E\u6587\u5B57\u5217\u3092\u8AAD\u3080\u3002\
    \n    template <class T>\n    void test_parse_decimal(int trials, int max_digits)\
    \ {\n        using F = fraction<T>;\n        for (int trial = 0; trial < trials;\
    \ ++trial) {\n            int integer_digits =\n                static_cast<int>(random_engine()\
    \ % (max_digits + 1));\n            int fraction_digits =\n                static_cast<int>(random_engine()\
    \ % (max_digits + 1));\n            std::string integer_part, fraction_part;\n\
    \            i128 numerator = 0, denominator = 1;\n            for (int i = 0;\
    \ i < integer_digits; ++i) {\n                int digit = static_cast<int>(random_engine()\
    \ % 10);\n                integer_part += static_cast<char>('0' + digit);\n  \
    \              numerator = numerator * 10 + digit;\n            }\n          \
    \  for (int i = 0; i < fraction_digits; ++i) {\n                // \u672B\u5C3E\
    \u306E 0 \u304C\u7D9A\u304F\u5834\u5408\u3082\u8A66\u3059\n                int\
    \ digit = random_engine() % 3 == 0\n                                ? 0\n    \
    \                            : static_cast<int>(random_engine() % 10);\n     \
    \           fraction_part += static_cast<char>('0' + digit);\n               \
    \ numerator = numerator * 10 + digit;\n                denominator *= 10;\n  \
    \          }\n            int sign = static_cast<int>(random_engine() % 3);\n\
    \            std::string text = sign == 0 ? \"\" : sign == 1 ? \"+\" : \"-\";\n\
    \            text += integer_part;\n            bool has_dot = fraction_digits\
    \ > 0 || random_engine() % 2 == 0;\n            if (has_dot) text += \".\" + fraction_part;\n\
    \n            Exact expected =\n                normalize(sign == 2 ? -numerator\
    \ : numerator, denominator);\n            bool valid = integer_digits + fraction_digits\
    \ > 0;\n            F parsed(7);\n            bool ok = F::parse(text, parsed);\n\
    \            assert(ok == (valid && fits<T>(expected)));\n            if (ok)\
    \ assert(same(parsed, expected));\n            else assert(parsed == F(7));\n\
    \        }\n    }\n\n    template <class T>\n    void test_parse_fixed() {\n \
    \       using F = fraction<T>;\n        for (const char* text :\n            \
    \ {\"\", \"+\", \"-\", \".\", \"-.\", \"+.\", \"1/0\", \"0/0\", \"1//2\", \"1/2/3\"\
    ,\n              \"/2\", \"1/\", \"a\", \"1a\", \"1.2.3\", \"1/-2\", \"1/+2\"\
    , \"--1\", \"+-1\",\n              \" 1\", \"1 \", \"1e5\", \"0x1\", \"1/ 2\"\
    , \"1./2\", \"1/2.\", \"1.5/2\"}) {\n            F parsed(7);\n            assert(!F::parse(text,\
    \ parsed));\n            assert(parsed == F(7));\n        }\n        F parsed;\n\
    \        assert(F::parse(\"1.\", parsed) && parsed == F(1));\n        assert(F::parse(\"\
    .5\", parsed) && parsed == F(1, 2));\n        assert(F::parse(\"-.25\", parsed)\
    \ && parsed == F(-1, 4));\n        assert(F::parse(\"-0\", parsed) && parsed ==\
    \ F(0));\n        assert(F::parse(\"-0.000\", parsed) && parsed == F(0));\n  \
    \      assert(F::parse(\"+3/6\", parsed) && parsed == F(1, 2));\n        assert(F::parse(\"\
    0/5\", parsed) && parsed == F(0));\n        assert(F::parse(\"007\", parsed) &&\
    \ parsed == F(7));\n        assert(F::parse(\"-10/4\", parsed) && parsed == F(-5,\
    \ 2));\n\n        // \u30B9\u30C8\u30EA\u30FC\u30E0\u304B\u3089\u306E\u8AAD\u307F\
    \u8FBC\u307F\u3002\u5931\u6557\u3057\u305F\u3089 failbit \u304C\u7ACB\u3061\u3001\
    \u5024\u306F\u5909\u308F\u3089\u306A\u3044\n        std::istringstream is(\"3/4\
    \ -1.25 x 5\");\n        F p, q, r(7);\n        is >> p >> q;\n        assert(is\
    \ && p == F(3, 4) && q == F(-5, 4));\n        is >> r;\n        assert(is.fail()\
    \ && r == F(7));\n        std::istringstream empty(\"\");\n        empty >> r;\n\
    \        assert(empty.fail() && r == F(7));\n\n        // \u30BC\u30ED\u9664\u7B97\
    \n        bool thrown = false;\n        try {\n            F zero_denominator(1,\
    \ 0);\n        } catch (const std::invalid_argument&) {\n            thrown =\
    \ true;\n        }\n        assert(thrown);\n    }\n\n    // \u5185\u90E8\u306E\
    \ gcd \u3068 256\u30D3\u30C3\u30C8 \xF7 128\u30D3\u30C3\u30C8\u306E\u5272\u308A\
    \u7B97\u3092\u3001\u7D20\u6734\u306A\u8A08\u7B97\u3068\u6BD4\u3079\u308B\u3002\
    \n    void test_detail() {\n        namespace detail = yesantikiss::fraction_detail;\n\
    \        auto random_bits = [&](int bits) {\n            u128 raw =\n        \
    \        (static_cast<u128>(random_engine()) << 64) | random_engine();\n     \
    \       return bits == 128 ? raw : raw % (u128(1) << bits);\n        };\n    \
    \    auto naive_gcd = [](u128 a, u128 b) {\n            while (b != 0) {\n   \
    \             u128 r = a % b;\n                a = b;\n                b = r;\n\
    \            }\n            return a;\n        };\n        for (int trial = 0;\
    \ trial < 20000; ++trial) {\n            // \u6841\u6570\u3092\u3070\u3089\u3070\
    \u3089\u306B\u9078\u3073\u3001\u5171\u901A\u56E0\u6570\u3082\u6301\u305F\u305B\
    \u308B\n            u128 a = random_bits(static_cast<int>(random_engine() % 129));\n\
    \            u128 b = random_bits(static_cast<int>(random_engine() % 129));\n\
    \            if (trial % 3 == 0) {\n                u128 g = random_bits(static_cast<int>(random_engine()\
    \ % 70));\n                a = (a >> 70) * g;\n                b = (b >> 70) *\
    \ g;\n            }\n            if (trial % 11 == 0) b = a;\n            if (trial\
    \ % 13 == 0) a <<= random_engine() % 40;\n            if (trial % 7 == 0) {\n\
    \                // \u4E0B\u4F4D64\u30D3\u30C3\u30C8\u304C\u3059\u3079\u3066 0\
    \ \u306E\u5024\n                a = (a >> 100 | 1) << (64 + random_engine() %\
    \ 36);\n                b = (b >> 100 | 1) << (64 + random_engine() % 36);\n \
    \           }\n            u128 expected = naive_gcd(a, b);\n            assert(detail::gcd(a,\
    \ b) == expected);\n            assert(detail::gcd(b, a) == expected);\n     \
    \       if ((a >> 64) == 0 && (b >> 64) == 0) {\n                assert(detail::gcd64(static_cast<unsigned\
    \ long long>(a),\n                                     static_cast<unsigned long\
    \ long>(b)) ==\n                       expected);\n            }\n        }\n\
    \        assert(detail::gcd(0, 0) == 0 && detail::gcd64(0, 0) == 0);\n       \
    \ assert(detail::gcd(0, 7) == 7 && detail::gcd(~u128(0), 0) == ~u128(0));\n  \
    \      assert(detail::gcd(~u128(0), ~u128(0)) == ~u128(0));\n        assert(detail::gcd(u128(1)\
    \ << 127, u128(1) << 100) == u128(1) << 100);\n\n        for (int trial = 0; trial\
    \ < 6000; ++trial) {\n            // value = quotient * divisor + remainder \u3092\
    \u4F5C\u3063\u3066\u304B\u3089\u5272\u308A\u76F4\u3059\u3002\n            // \u5272\
    \u308B\u6570\u304C64\u30D3\u30C3\u30C8\u4EE5\u4E0B\u306E\u8FD1\u9053\u3068\u3001\
    \u305D\u308C\u3088\u308A\u5927\u304D\u3044\u5834\u5408\u306E\u4E21\u65B9\u3092\
    \u901A\u3059\u3002\n            u128 divisor =\n                random_bits(1\
    \ + static_cast<int>(random_engine() % 128)) + 1;\n            if (divisor ==\
    \ 0) divisor = 1;\n            u128 quotient =\n                random_bits(static_cast<int>(random_engine()\
    \ % 129));\n            u128 remainder = random_bits(128) % divisor;\n       \
    \     detail::u256 value = detail::add(\n                detail::multiply(quotient,\
    \ divisor),\n                detail::from_u128(remainder));\n            detail::div_result\
    \ result = detail::divide(value, divisor);\n            assert(result.quotient.hi\
    \ == 0 && result.quotient.lo == quotient);\n            assert(result.remainder\
    \ == remainder);\n            assert(detail::modulo(value, divisor) == remainder);\n\
    \        }\n        // \u5546\u304C128\u30D3\u30C3\u30C8\u3092\u8D85\u3048\u308B\
    \u5834\u5408: (2^256 - 1) / 3 = 0x5555...\n        detail::div_result all = detail::divide({~u128(0),\
    \ ~u128(0)}, 3);\n        assert(all.remainder == 0);\n        assert(all.quotient.hi\
    \ == ~u128(0) / 3 && all.quotient.lo == ~u128(0) / 3);\n        all = detail::divide({~u128(0),\
    \ ~u128(0)}, (u128(1) << 64) + 1);\n        assert(detail::compare(\n        \
    \           detail::add(detail::add(\n                                   detail::multiply(all.quotient.lo,\n\
    \                                                    (u128(1) << 64) + 1),\n \
    \                                  detail::u256{\n                           \
    \            all.quotient.hi * ((u128(1) << 64) + 1),\n                      \
    \                 0}),\n                               detail::from_u128(all.remainder)),\n\
    \                   detail::u256{~u128(0), ~u128(0)}) == 0);\n    }\n\n    //\
    \ __int128 \u3067\u300164\u30D3\u30C3\u30C8\u306B\u53CE\u307E\u308B\u3068\u304D\
    \u306E\u8FD1\u9053\u3068\u901A\u5E38\u306E\u7D4C\u8DEF\u306E\u5207\u308A\u66FF\
    \u308F\u308A\n    // (2^63 \u3068 2^64 \u306E\u524D\u5F8C) \u3092\u3001\u7D20\u6734\
    \u89E3\u304C __int128 \u306B\u53CE\u307E\u308B\u7D44\u307F\u5408\u308F\u305B\u3067\
    \u8A66\u3059\u3002\n    void test_boundary() {\n        using F = fraction<i128>;\n\
    \        auto small = [&]() {\n            return static_cast<i128>(random_engine()\
    \ % 2000001) - 1000000;\n        };\n        auto near = [&](bool allow_64) {\n\
    \            i128 pivot = i128(1) << (allow_64 && random_engine() % 2 ? 64 : 63);\n\
    \            i128 value = pivot + static_cast<i128>(random_engine() % 7) - 3;\n\
    \            return random_engine() % 2 == 0 ? value : -value;\n        };\n \
    \       for (int trial = 0; trial < 20000; ++trial) {\n            i128 a, b,\
    \ c, d;\n            if (trial % 2 == 0) {\n                // \u5206\u5B50\u304C\
    \u5883\u754C\u306E\u8FD1\u304F\u3001\u5206\u6BCD\u306F\u5C0F\u3055\u3044\n   \
    \             a = random_engine() % 4 == 0 ? small() : near(true);\n         \
    \       c = random_engine() % 4 == 0 ? small() : near(true);\n               \
    \ b = small();\n                d = small();\n            } else {\n         \
    \       // \u5206\u6BCD\u304C\u5883\u754C\u306E\u8FD1\u304F\u3001\u5206\u5B50\u306F\
    \u5C0F\u3055\u3044\n                a = small();\n                c = small();\n\
    \                b = random_engine() % 4 == 0 ? small() : near(false);\n     \
    \           d = random_engine() % 4 == 0 ? small() : near(false);\n          \
    \  }\n            if (b == 0) b = 1;\n            if (d == 0) d = 1;\n       \
    \     Exact ex = normalize(a, b), ey = normalize(c, d);\n            const F x(a,\
    \ b), y(c, d);\n            assert(same(x, ex) && same(y, ey));\n\n          \
    \  check<i128>(normalize(ex.num * ey.den + ey.num * ex.den,\n                \
    \                  ex.den * ey.den),\n                        [&] { return x +\
    \ y; });\n            check<i128>(normalize(ex.num * ey.den - ey.num * ex.den,\n\
    \                                  ex.den * ey.den),\n                       \
    \ [&] { return x - y; });\n            // \u7A4D\u3068\u5546\u306F\u3001\u7D20\
    \u6734\u89E3\u306E\u9014\u4E2D\u8A08\u7B97\u304C\u53CE\u307E\u308B\u5411\u304D\
    \u3060\u3051\u78BA\u304B\u3081\u308B\n            if (trial % 2 == 0) {\n    \
    \            check<i128>(normalize(ex.num * ey.den, ex.den * ey.num),\n      \
    \                      [&] { return x / y; });\n            } else {\n       \
    \         check<i128>(normalize(ex.num * ey.num, ex.den * ey.den),\n         \
    \                   [&] { return x * y; });\n            }\n            i128 left\
    \ = ex.num * ey.den, right = ey.num * ex.den;\n            assert((x < y) == (left\
    \ < right));\n            assert((y < x) == (right < left));\n            assert((x\
    \ == y) == (left == right));\n        }\n    }\n\n    // __int128 \u3067\u3001\
    \u9014\u4E2D\u306E\u7A4D\u304C128\u30D3\u30C3\u30C8\u3092\u8D85\u3048\u308B\u7D4C\
    \u8DEF\u3092\u901A\u3059\u3002\n    // \u7B54\u3048\u304C\u5206\u304B\u308B\u5F62\
    \u306B\u5024\u3092\u7D44\u307F\u7ACB\u3066\u3066\u6BD4\u3079\u308B\u3002\n   \
    \ void test_wide() {\n        using F = fraction<i128>;\n        auto random_bits\
    \ = [&](int bits) {\n            u128 raw =\n                (static_cast<u128>(random_engine())\
    \ << 64) | random_engine();\n            return static_cast<i128>(raw % (u128(1)\
    \ << bits)) + 1;\n        };\n        int wide_sums = 0;\n        for (int trial\
    \ = 0; trial < 2000; ++trial) {\n            // \u540C\u3058\u5206\u6BCD m: p/m\
    \ \xB1 q/m = (p \xB1 q)/m\n            {\n                i128 m = random_bits(40\
    \ + static_cast<int>(random_engine() % 80));\n                i128 p = random_bits(125),\
    \ q = random_bits(125);\n                if (random_engine() % 2 == 0) p = -p;\n\
    \                if (random_engine() % 2 == 0) q = -q;\n                F x(p,\
    \ m), y(q, m);\n                assert(same(x, normalize(p, m)) && same(y, normalize(q,\
    \ m)));\n                // \u7D04\u5206\u5F8C\u306E\u5206\u6BCD\u3069\u3046\u3057\
    \u306E\u7A4D\u304C\u5927\u304D\u3044\u3068\u3001\u9014\u4E2D\u3067128\u30D3\u30C3\
    \u30C8\u3092\u8D85\u3048\u308B\n                if (x.den > (i128(1) << 64) &&\
    \ y.den > (i128(1) << 64)) {\n                    ++wide_sums;\n             \
    \   }\n                assert(same(x + y, normalize(p + q, m)));\n           \
    \     assert(same(x - y, normalize(p - q, m)));\n                assert((x < y)\
    \ == (p < q));\n                assert((x == y) == (p == q));\n            }\n\
    \            // \u4E92\u3044\u306B\u7D04\u5206\u3055\u308C\u308B\u7A4D: (p*s)/(q*t)\
    \ * (q*u)/(p*v) = (s*u)/(t*v)\n            {\n                i128 p = random_bits(62),\
    \ q = random_bits(62);\n                i128 s = random_bits(60), t = random_bits(60);\n\
    \                i128 u = random_bits(60), v = random_bits(60);\n            \
    \    F x(p * s, q * t), y(q * u, p * v);\n                if (random_engine()\
    \ % 2 == 0) x = -x;\n                Exact expected = normalize(s * u, t * v);\n\
    \                if (x.num < 0) expected.num = -expected.num;\n              \
    \  assert(same(x * y, expected));\n                // x / (1/y) \u3082\u540C\u3058\
    \u5024\n                assert(same(x / y.inv(), expected));\n            }\n\
    \            // \u5927\u304D\u3044\u5024\u3069\u3046\u3057\u306E\u6BD4\u8F03:\
    \ p/q \u3068 (p+1)/q\u3001p/q \u3068 p/(q+1)\n            {\n                i128\
    \ p = random_bits(126), q = random_bits(126);\n                assert(F(p, q)\
    \ < F(p + 1, q) && F(p, q + 1) < F(p, q));\n                assert(F(-p - 1, q)\
    \ < F(-p, q) && F(-p, q) < F(-p, q + 1));\n                assert(!(F(p, q) <\
    \ F(p, q)) && F(p, q) <= F(p, q));\n                assert(F(-p, q) < F(p, q +\
    \ 1));\n            }\n            // \u8DB3\u3057\u3066\u5F15\u304F\u3068\u5143\
    \u306B\u623B\u308B (\u3042\u3075\u308C\u305F\u3089\u4F8B\u5916\u3067\u3001\u5143\
    \u306E\u5024\u306F\u5909\u308F\u3089\u306A\u3044)\n            {\n           \
    \     F x(random_bits(100), random_bits(60));\n                F y(random_bits(100),\
    \ random_bits(60));\n                try {\n                    F z = x + y;\n\
    \                    assert(z - y == x && z - x == y);\n                } catch\
    \ (const std::overflow_error&) {\n                }\n                try {\n \
    \                   F z = x * y;\n                    assert(z / y == x && z /\
    \ x == y);\n                } catch (const std::overflow_error&) {\n         \
    \       }\n            }\n        }\n        assert(wide_sums > 100);\n\n    \
    \    // \u578B\u306E\u7AEF\u306E\u5024\n        const i128 max = max_of<i128>(),\
    \ min = min_of<i128>();\n        assert(same(F(max, 3) - F(max - 1, 3), normalize(1,\
    \ 3)));\n        assert(F(min, min) == F(1) && F(max, max) == F(1));\n       \
    \ assert(F(min, 2) < F(max, 2) && F(min) < F(min + 1));\n        assert(F(max,\
    \ max - 1) * F(max - 1, max) == F(1));\n        assert(F(min).floor() == min &&\
    \ F(max).ceil() == max);\n        bool thrown = false;\n        try {\n      \
    \      (void)-F(min);\n        } catch (const std::overflow_error&) {\n      \
    \      thrown = true;\n        }\n        assert(thrown);\n        thrown = false;\n\
    \        try {\n            (void)(F(max) + F(1));\n        } catch (const std::overflow_error&)\
    \ {\n            thrown = true;\n        }\n        assert(thrown);\n\n      \
    \  std::ostringstream os;\n        os << F(min) << ' ' << F(max, 2);\n       \
    \ assert(os.str() == to_string(min) + \" \" + to_string(max) + \"/2\");\n    \
    \    F parsed;\n        assert(F::parse(to_string(min), parsed) && parsed == F(min));\n\
    \        assert(!F::parse(to_string(max) + \"0\", parsed));\n    }\n}\n\nint main()\
    \ {\n    // verify \u3067\u306F\u30C6\u30B9\u30C8\u30B1\u30FC\u30B9\u3054\u3068\
    \u306B\u5B9F\u884C\u3055\u308C\u308B\u306E\u3067\u3001\u56DE\u6570\u306F1\u79D2\
    \u4EE5\u5185\u306B\u53CE\u307E\u308B\n    // \u7A0B\u5EA6\u306B\u3057\u3066\u3044\
    \u308B\u3002\n    // 8\u30D3\u30C3\u30C8\u3067\u306F\u5168\u7BC4\u56F2\u3092\u4F7F\
    \u3044\u3001\u3042\u3075\u308C\u306E\u5883\u754C\u3092\u96C6\u4E2D\u7684\u306B\
    \u8A66\u3059\u3002\n    test_against_exact<signed char>(20000, max_of<signed char>(),\
    \ true);\n    test_against_exact<short>(8000, max_of<short>(), true);\n    test_against_exact<int>(12000,\
    \ max_of<int>(), true);\n    // \u7D20\u6734\u89E3\u306E\u9014\u4E2D\u8A08\u7B97\
    \u304C __int128 \u306B\u53CE\u307E\u308B\u3088\u3046\u3001\u7D76\u5BFE\u5024\u306F\
    \ 2^62 \u307E\u3067\n    test_against_exact<long long>(12000, i128(1) << 62, false);\n\
    \    test_against_exact<i128>(12000, i128(1) << 62, false);\n\n    test_parse_decimal<signed\
    \ char>(20000, 4);\n    test_parse_decimal<int>(20000, 11);\n    test_parse_decimal<long\
    \ long>(20000, 18);\n    test_parse_decimal<i128>(20000, 18);\n    test_parse_fixed<int>();\n\
    \    test_parse_fixed<long long>();\n    test_parse_fixed<i128>();\n\n    test_detail();\n\
    \    test_boundary();\n    test_wide();\n\n    long long a, b;\n    std::cin >>\
    \ a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - utils/fraction.hpp
  isVerificationFile: true
  path: verify/random_fraction.test.cpp
  requiredBy: []
  timestamp: '2026-11-12 13:13:02+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/random_fraction.test.cpp
layout: document
redirect_from:
- /verify/verify/random_fraction.test.cpp
- /verify/verify/random_fraction.test.cpp.html
title: verify/random_fraction.test.cpp
---
