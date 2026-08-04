#pragma once

#include <ios>
#include <istream>
#include <ostream>
#include <string>

namespace yesantikiss {
    using i128 = __int128;
    using u128 = unsigned __int128;
    using int128 = __int128;

    namespace int128_detail {
        inline std::string to_string(u128 value) {
            char digits[39];
            int size = 0;
            do {
                digits[size++] =
                    static_cast<char>('0' + static_cast<int>(value % 10));
                value /= 10;
            } while (value != 0);

            std::string result;
            result.reserve(static_cast<std::size_t>(size));
            while (size > 0) result.push_back(digits[--size]);
            return result;
        }

        inline bool parse_magnitude(
            const std::string& token, std::size_t first, u128 limit,
            u128& result) {
            if (first == token.size()) return false;

            u128 value = 0;
            for (std::size_t i = first; i < token.size(); ++i) {
                char c = token[i];
                if (c < '0' || c > '9') return false;
                u128 digit = static_cast<unsigned>(c - '0');
                if (digit > limit || value > (limit - digit) / 10) {
                    return false;
                }
                value = value * 10 + digit;
            }
            result = value;
            return true;
        }
    }
}

inline std::ostream& operator<<(std::ostream& os, yesantikiss::i128 value) {
    yesantikiss::u128 magnitude = static_cast<yesantikiss::u128>(value);
    if (value < 0) {
        magnitude = yesantikiss::u128(0) - magnitude;
    }
    std::string result =
        yesantikiss::int128_detail::to_string(magnitude);
    if (value < 0) result.insert(result.begin(), '-');
    return os << result;
}

inline std::ostream& operator<<(std::ostream& os, yesantikiss::u128 value) {
    return os << yesantikiss::int128_detail::to_string(value);
}

inline std::istream& operator>>(std::istream& is, yesantikiss::i128& value) {
    std::string token;
    if (!(is >> token)) return is;

    std::size_t first = 0;
    bool negative = false;
    if (token[first] == '+' || token[first] == '-') {
        negative = token[first] == '-';
        ++first;
    }

    constexpr yesantikiss::u128 min_magnitude =
        yesantikiss::u128(1) << 127;
    constexpr yesantikiss::u128 max_magnitude = min_magnitude - 1;
    yesantikiss::u128 magnitude;
    if (!yesantikiss::int128_detail::parse_magnitude(
            token, first,
            negative ? min_magnitude : max_magnitude, magnitude)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    if (!negative) {
        value = static_cast<yesantikiss::i128>(magnitude);
    } else if (magnitude == min_magnitude) {
        value = -static_cast<yesantikiss::i128>(magnitude - 1) - 1;
    } else {
        value = -static_cast<yesantikiss::i128>(magnitude);
    }
    return is;
}

inline std::istream& operator>>(std::istream& is, yesantikiss::u128& value) {
    std::string token;
    if (!(is >> token)) return is;

    std::size_t first = 0;
    if (token[first] == '+') ++first;
    if (first == token.size() || token[first] == '-') {
        is.setstate(std::ios::failbit);
        return is;
    }

    constexpr yesantikiss::u128 max_value = ~yesantikiss::u128(0);
    yesantikiss::u128 parsed;
    if (!yesantikiss::int128_detail::parse_magnitude(
            token, first, max_value, parsed)) {
        is.setstate(std::ios::failbit);
        return is;
    }
    value = parsed;
    return is;
}
