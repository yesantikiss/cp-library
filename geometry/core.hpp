#pragma once

#include <cmath>

namespace yesantikiss {
    using Real = long double;

    inline constexpr Real EPS = 1e-10L;

    inline int sign(Real x) {
        if (x > EPS) return 1;
        if (x < -EPS) return -1;
        return 0;
    }

    inline bool almost_equal(Real a, Real b) {
        return sign(a - b) == 0;
    }
}
