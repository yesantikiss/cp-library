---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/argument_sort.hpp
    title: "\u504F\u89D2\u30BD\u30FC\u30C8"
  - icon: ':heavy_check_mark:'
    path: geometry/core.hpp
    title: "\u5E7E\u4F55\u306E\u57FA\u672C\u578B\u3068\u8AA4\u5DEE\u5224\u5B9A"
  - icon: ':heavy_check_mark:'
    path: geometry/point.hpp
    title: "\u4E8C\u6B21\u5143\u306E\u70B9\u30FB\u30D9\u30AF\u30C8\u30EB"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sort_points_by_argument
    links:
    - https://judge.yosupo.jp/problem/sort_points_by_argument
  bundledCode: "#line 1 \"verify/sort_points_by_argument.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/sort_points_by_argument\"\n\n#include <algorithm>\n\
    #include <iostream>\n#include <vector>\n\n#line 2 \"geometry/argument_sort.hpp\"\
    \n\n#line 2 \"geometry/point.hpp\"\n\n#include <istream>\n#include <ostream>\n\
    \n#line 2 \"geometry/core.hpp\"\n\n#include <cmath>\n\nnamespace yesantikiss {\n\
    \    using Real = long double;\n\n    inline constexpr Real EPS = 1e-10L;\n\n\
    \    inline int sign(Real x) {\n        if (x > EPS) return 1;\n        if (x\
    \ < -EPS) return -1;\n        return 0;\n    }\n\n    inline bool almost_equal(Real\
    \ a, Real b) {\n        return sign(a - b) == 0;\n    }\n}\n#line 7 \"geometry/point.hpp\"\
    \n\nnamespace yesantikiss {\n    struct Point {\n        Real x = 0;\n       \
    \ Real y = 0;\n\n        Point() = default;\n        Point(Real x, Real y) : x(x),\
    \ y(y) {}\n\n        Point& operator+=(const Point& other) {\n            x +=\
    \ other.x;\n            y += other.y;\n            return *this;\n        }\n\n\
    \        Point& operator-=(const Point& other) {\n            x -= other.x;\n\
    \            y -= other.y;\n            return *this;\n        }\n\n        Point&\
    \ operator*=(Real scalar) {\n            x *= scalar;\n            y *= scalar;\n\
    \            return *this;\n        }\n\n        Point& operator/=(Real scalar)\
    \ {\n            x /= scalar;\n            y /= scalar;\n            return *this;\n\
    \        }\n\n        Point operator+() const {\n            return *this;\n \
    \       }\n\n        Point operator-() const {\n            return {-x, -y};\n\
    \        }\n\n        friend Point operator+(Point lhs, const Point& rhs) {\n\
    \            lhs += rhs;\n            return lhs;\n        }\n\n        friend\
    \ Point operator-(Point lhs, const Point& rhs) {\n            lhs -= rhs;\n  \
    \          return lhs;\n        }\n\n        friend Point operator*(Point point,\
    \ Real scalar) {\n            point *= scalar;\n            return point;\n  \
    \      }\n\n        friend Point operator*(Real scalar, Point point) {\n     \
    \       point *= scalar;\n            return point;\n        }\n\n        friend\
    \ Point operator/(Point point, Real scalar) {\n            point /= scalar;\n\
    \            return point;\n        }\n\n        friend bool operator==(const\
    \ Point& lhs, const Point& rhs) {\n            return lhs.x == rhs.x && lhs.y\
    \ == rhs.y;\n        }\n\n        friend bool operator!=(const Point& lhs, const\
    \ Point& rhs) {\n            return !(lhs == rhs);\n        }\n\n        friend\
    \ std::istream& operator>>(std::istream& input, Point& point) {\n            return\
    \ input >> point.x >> point.y;\n        }\n\n        friend std::ostream& operator<<(std::ostream&\
    \ output, const Point& point) {\n            return output << point.x << ' ' <<\
    \ point.y;\n        }\n    };\n\n    inline Real dot(const Point& a, const Point&\
    \ b) {\n        return a.x * b.x + a.y * b.y;\n    }\n\n    inline Real cross(const\
    \ Point& a, const Point& b) {\n        return a.x * b.y - a.y * b.x;\n    }\n\n\
    \    inline Real norm_squared(const Point& point) {\n        return dot(point,\
    \ point);\n    }\n\n    inline Real norm(const Point& point) {\n        return\
    \ std::sqrt(norm_squared(point));\n    }\n\n    inline Real distance(const Point&\
    \ a, const Point& b) {\n        return norm(a - b);\n    }\n\n    inline bool\
    \ almost_equal(const Point& a, const Point& b) {\n        return almost_equal(a.x,\
    \ b.x) && almost_equal(a.y, b.y);\n    }\n}\n#line 4 \"geometry/argument_sort.hpp\"\
    \n\nnamespace yesantikiss {\n    namespace detail {\n        inline int argument_region(const\
    \ Point& point) {\n            if (point.y < 0) return -1;\n            if (point.y\
    \ == 0 && point.x >= 0) return 0;\n            return 1;\n        }\n    }\n\n\
    \    struct ArgumentLess {\n        bool operator()(const Point& lhs, const Point&\
    \ rhs) const {\n            const int lhs_region = detail::argument_region(lhs);\n\
    \            const int rhs_region = detail::argument_region(rhs);\n          \
    \  if (lhs_region != rhs_region) return lhs_region < rhs_region;\n\n         \
    \   // EPS \u3092\u4F7F\u3046\u6BD4\u8F03\u306F\u72ED\u7FA9\u5F31\u9806\u5E8F\u3092\
    \u58CA\u3059\u53EF\u80FD\u6027\u304C\u3042\u308B\u305F\u3081\u3001\n         \
    \   // \u30BD\u30FC\u30C8\u6761\u4EF6\u3067\u306F\u5916\u7A4D\u306E\u7B26\u53F7\
    \u3092\u76F4\u63A5\u6BD4\u8F03\u3059\u308B\u3002\n            return cross(lhs,\
    \ rhs) > 0;\n        }\n    };\n}\n#line 8 \"verify/sort_points_by_argument.test.cpp\"\
    \n\nint main() {\n    using namespace yesantikiss;\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n\n    std::vector<Point>\
    \ points(n);\n    for (Point& point : points) std::cin >> point;\n\n    std::sort(points.begin(),\
    \ points.end(), ArgumentLess{});\n\n    for (const Point& point : points) {\n\
    \        std::cout << static_cast<long long>(point.x) << ' '\n               \
    \   << static_cast<long long>(point.y) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sort_points_by_argument\"\
    \n\n#include <algorithm>\n#include <iostream>\n#include <vector>\n\n#include \"\
    geometry/argument_sort.hpp\"\n\nint main() {\n    using namespace yesantikiss;\n\
    \n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ n;\n    std::cin >> n;\n\n    std::vector<Point> points(n);\n    for (Point&\
    \ point : points) std::cin >> point;\n\n    std::sort(points.begin(), points.end(),\
    \ ArgumentLess{});\n\n    for (const Point& point : points) {\n        std::cout\
    \ << static_cast<long long>(point.x) << ' '\n                  << static_cast<long\
    \ long>(point.y) << '\\n';\n    }\n}\n"
  dependsOn:
  - geometry/argument_sort.hpp
  - geometry/point.hpp
  - geometry/core.hpp
  isVerificationFile: true
  path: verify/sort_points_by_argument.test.cpp
  requiredBy: []
  timestamp: '2026-08-25 15:58:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/sort_points_by_argument.test.cpp
layout: document
redirect_from:
- /verify/verify/sort_points_by_argument.test.cpp
- /verify/verify/sort_points_by_argument.test.cpp.html
title: verify/sort_points_by_argument.test.cpp
---
