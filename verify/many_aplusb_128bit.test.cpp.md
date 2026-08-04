---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utils/int128.hpp
    title: "128 bit \u6574\u6570\u306E\u5165\u51FA\u529B"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/many_aplusb_128bit
    links:
    - https://judge.yosupo.jp/problem/many_aplusb_128bit
  bundledCode: "#line 1 \"verify/many_aplusb_128bit.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/many_aplusb_128bit\"\n\n#include <iostream>\n\n\
    #line 2 \"utils/int128.hpp\"\n\n#include <ios>\n#include <istream>\n#include <ostream>\n\
    #include <string>\n\nnamespace yesantikiss {\n    using i128 = __int128;\n   \
    \ using u128 = unsigned __int128;\n    using int128 = __int128;\n\n    namespace\
    \ int128_detail {\n        inline std::string to_string(u128 value) {\n      \
    \      char digits[39];\n            int size = 0;\n            do {\n       \
    \         digits[size++] =\n                    static_cast<char>('0' + static_cast<int>(value\
    \ % 10));\n                value /= 10;\n            } while (value != 0);\n\n\
    \            std::string result;\n            result.reserve(static_cast<std::size_t>(size));\n\
    \            while (size > 0) result.push_back(digits[--size]);\n            return\
    \ result;\n        }\n\n        inline bool parse_magnitude(\n            const\
    \ std::string& token, std::size_t first, u128 limit,\n            u128& result)\
    \ {\n            if (first == token.size()) return false;\n\n            u128\
    \ value = 0;\n            for (std::size_t i = first; i < token.size(); ++i) {\n\
    \                char c = token[i];\n                if (c < '0' || c > '9') return\
    \ false;\n                u128 digit = static_cast<unsigned>(c - '0');\n     \
    \           if (digit > limit || value > (limit - digit) / 10) {\n           \
    \         return false;\n                }\n                value = value * 10\
    \ + digit;\n            }\n            result = value;\n            return true;\n\
    \        }\n    }\n}\n\ninline std::ostream& operator<<(std::ostream& os, yesantikiss::i128\
    \ value) {\n    yesantikiss::u128 magnitude = static_cast<yesantikiss::u128>(value);\n\
    \    if (value < 0) {\n        magnitude = yesantikiss::u128(0) - magnitude;\n\
    \    }\n    std::string result =\n        yesantikiss::int128_detail::to_string(magnitude);\n\
    \    if (value < 0) result.insert(result.begin(), '-');\n    return os << result;\n\
    }\n\ninline std::ostream& operator<<(std::ostream& os, yesantikiss::u128 value)\
    \ {\n    return os << yesantikiss::int128_detail::to_string(value);\n}\n\ninline\
    \ std::istream& operator>>(std::istream& is, yesantikiss::i128& value) {\n   \
    \ std::string token;\n    if (!(is >> token)) return is;\n\n    std::size_t first\
    \ = 0;\n    bool negative = false;\n    if (token[first] == '+' || token[first]\
    \ == '-') {\n        negative = token[first] == '-';\n        ++first;\n    }\n\
    \n    constexpr yesantikiss::u128 min_magnitude =\n        yesantikiss::u128(1)\
    \ << 127;\n    constexpr yesantikiss::u128 max_magnitude = min_magnitude - 1;\n\
    \    yesantikiss::u128 magnitude;\n    if (!yesantikiss::int128_detail::parse_magnitude(\n\
    \            token, first,\n            negative ? min_magnitude : max_magnitude,\
    \ magnitude)) {\n        is.setstate(std::ios::failbit);\n        return is;\n\
    \    }\n\n    if (!negative) {\n        value = static_cast<yesantikiss::i128>(magnitude);\n\
    \    } else if (magnitude == min_magnitude) {\n        value = -static_cast<yesantikiss::i128>(magnitude\
    \ - 1) - 1;\n    } else {\n        value = -static_cast<yesantikiss::i128>(magnitude);\n\
    \    }\n    return is;\n}\n\ninline std::istream& operator>>(std::istream& is,\
    \ yesantikiss::u128& value) {\n    std::string token;\n    if (!(is >> token))\
    \ return is;\n\n    std::size_t first = 0;\n    if (token[first] == '+') ++first;\n\
    \    if (first == token.size() || token[first] == '-') {\n        is.setstate(std::ios::failbit);\n\
    \        return is;\n    }\n\n    constexpr yesantikiss::u128 max_value = ~yesantikiss::u128(0);\n\
    \    yesantikiss::u128 parsed;\n    if (!yesantikiss::int128_detail::parse_magnitude(\n\
    \            token, first, max_value, parsed)) {\n        is.setstate(std::ios::failbit);\n\
    \        return is;\n    }\n    value = parsed;\n    return is;\n}\n#line 6 \"\
    verify/many_aplusb_128bit.test.cpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int t;\n    std::cin >> t;\n    while (t--)\
    \ {\n        yesantikiss::i128 a = 0, b = 0;\n        std::cin >> a >> b;\n  \
    \      std::cout << a + b << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb_128bit\"\n\n\
    #include <iostream>\n\n#include \"utils/int128.hpp\"\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int t;\n    std::cin >> t;\n    while (t--)\
    \ {\n        yesantikiss::i128 a = 0, b = 0;\n        std::cin >> a >> b;\n  \
    \      std::cout << a + b << '\\n';\n    }\n}\n"
  dependsOn:
  - utils/int128.hpp
  isVerificationFile: true
  path: verify/many_aplusb_128bit.test.cpp
  requiredBy: []
  timestamp: '2026-08-04 23:10:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/many_aplusb_128bit.test.cpp
layout: document
redirect_from:
- /verify/verify/many_aplusb_128bit.test.cpp
- /verify/verify/many_aplusb_128bit.test.cpp.html
title: verify/many_aplusb_128bit.test.cpp
---
