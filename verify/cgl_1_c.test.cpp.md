---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/core.hpp
    title: "\u5E7E\u4F55\u306E\u57FA\u672C\u578B\u3068\u8AA4\u5DEE\u5224\u5B9A"
  - icon: ':heavy_check_mark:'
    path: geometry/line.hpp
    title: "\u76F4\u7DDA\u3068\u70B9\u306E\u4F4D\u7F6E\u95A2\u4FC2"
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/CGL_1_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/CGL_1_C
  bundledCode: "#line 1 \"verify/cgl_1_c.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/CGL_1_C\"\
    \n\n#include <iostream>\n\n#line 2 \"geometry/line.hpp\"\n\n#include <cassert>\n\
    \n#line 2 \"geometry/point.hpp\"\n\n#include <istream>\n#include <ostream>\n\n\
    #line 2 \"geometry/core.hpp\"\n\n#include <cmath>\n\nnamespace yesantikiss {\n\
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
    \ b.x) && almost_equal(a.y, b.y);\n    }\n}\n#line 6 \"geometry/line.hpp\"\n\n\
    namespace yesantikiss {\n    struct Line {\n        Point a;\n        Point b;\n\
    \    };\n\n    enum class PointPosition {\n        counter_clockwise,\n      \
    \  clockwise,\n        online_back,\n        online_front,\n        on_segment,\n\
    \    };\n\n    inline Point projection(const Line& line, const Point& point) {\n\
    \        const Point direction = line.b - line.a;\n        const Real denominator\
    \ = norm_squared(direction);\n        assert(denominator > 0);\n        return\
    \ line.a + direction * (dot(point - line.a, direction) / denominator);\n    }\n\
    \n    inline Point reflection(const Line& line, const Point& point) {\n      \
    \  return point + (projection(line, point) - point) * 2;\n    }\n\n    inline\
    \ PointPosition point_position(\n        const Point& a,\n        const Point&\
    \ b,\n        const Point& point\n    ) {\n        const Point direction = b -\
    \ a;\n        const Point relative = point - a;\n\n        const int side = sign(cross(direction,\
    \ relative));\n        if (side > 0) return PointPosition::counter_clockwise;\n\
    \        if (side < 0) return PointPosition::clockwise;\n        if (sign(dot(direction,\
    \ relative)) < 0) {\n            return PointPosition::online_back;\n        }\n\
    \        if (sign(norm_squared(relative) - norm_squared(direction)) > 0) {\n \
    \           return PointPosition::online_front;\n        }\n        return PointPosition::on_segment;\n\
    \    }\n\n    inline PointPosition point_position(const Line& line, const Point&\
    \ point) {\n        return point_position(line.a, line.b, point);\n    }\n}\n\
    #line 6 \"verify/cgl_1_c.test.cpp\"\n\nint main() {\n    using namespace yesantikiss;\n\
    \n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    Line\
    \ line;\n    std::cin >> line.a >> line.b;\n\n    int q;\n    std::cin >> q;\n\
    \n    while (q--) {\n        Point point;\n        std::cin >> point;\n\n    \
    \    switch (point_position(line, point)) {\n            case PointPosition::counter_clockwise:\n\
    \                std::cout << \"COUNTER_CLOCKWISE\\n\";\n                break;\n\
    \            case PointPosition::clockwise:\n                std::cout << \"CLOCKWISE\\\
    n\";\n                break;\n            case PointPosition::online_back:\n \
    \               std::cout << \"ONLINE_BACK\\n\";\n                break;\n   \
    \         case PointPosition::online_front:\n                std::cout << \"ONLINE_FRONT\\\
    n\";\n                break;\n            case PointPosition::on_segment:\n  \
    \              std::cout << \"ON_SEGMENT\\n\";\n                break;\n     \
    \   }\n    }\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/CGL_1_C\"\n\n\
    #include <iostream>\n\n#include \"geometry/line.hpp\"\n\nint main() {\n    using\
    \ namespace yesantikiss;\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    Line line;\n    std::cin >> line.a >> line.b;\n\n    int q;\n    std::cin\
    \ >> q;\n\n    while (q--) {\n        Point point;\n        std::cin >> point;\n\
    \n        switch (point_position(line, point)) {\n            case PointPosition::counter_clockwise:\n\
    \                std::cout << \"COUNTER_CLOCKWISE\\n\";\n                break;\n\
    \            case PointPosition::clockwise:\n                std::cout << \"CLOCKWISE\\\
    n\";\n                break;\n            case PointPosition::online_back:\n \
    \               std::cout << \"ONLINE_BACK\\n\";\n                break;\n   \
    \         case PointPosition::online_front:\n                std::cout << \"ONLINE_FRONT\\\
    n\";\n                break;\n            case PointPosition::on_segment:\n  \
    \              std::cout << \"ON_SEGMENT\\n\";\n                break;\n     \
    \   }\n    }\n}\n"
  dependsOn:
  - geometry/line.hpp
  - geometry/point.hpp
  - geometry/core.hpp
  isVerificationFile: true
  path: verify/cgl_1_c.test.cpp
  requiredBy: []
  timestamp: '2026-08-25 15:58:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/cgl_1_c.test.cpp
layout: document
redirect_from:
- /verify/verify/cgl_1_c.test.cpp
- /verify/verify/cgl_1_c.test.cpp.html
title: verify/cgl_1_c.test.cpp
---
