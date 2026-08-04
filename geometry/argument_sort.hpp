#pragma once

#include "geometry/point.hpp"

namespace yesantikiss {
    namespace detail {
        inline int argument_region(const Point& point) {
            if (point.y < 0) return -1;
            if (point.y == 0 && point.x >= 0) return 0;
            return 1;
        }
    }

    struct ArgumentLess {
        bool operator()(const Point& lhs, const Point& rhs) const {
            const int lhs_region = detail::argument_region(lhs);
            const int rhs_region = detail::argument_region(rhs);
            if (lhs_region != rhs_region) return lhs_region < rhs_region;

            // EPS を使う比較は狭義弱順序を壊す可能性があるため、
            // ソート条件では外積の符号を直接比較する。
            return cross(lhs, rhs) > 0;
        }
    };
}
