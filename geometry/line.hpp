#pragma once

#include <cassert>

#include "geometry/point.hpp"

namespace yesantikiss {
    struct Line {
        Point a;
        Point b;
    };

    enum class PointPosition {
        counter_clockwise,
        clockwise,
        online_back,
        online_front,
        on_segment,
    };

    inline Point projection(const Line& line, const Point& point) {
        const Point direction = line.b - line.a;
        const Real denominator = norm_squared(direction);
        assert(denominator > 0);
        return line.a + direction * (dot(point - line.a, direction) / denominator);
    }

    inline Point reflection(const Line& line, const Point& point) {
        return point + (projection(line, point) - point) * 2;
    }

    inline PointPosition point_position(
        const Point& a,
        const Point& b,
        const Point& point
    ) {
        const Point direction = b - a;
        const Point relative = point - a;

        const int side = sign(cross(direction, relative));
        if (side > 0) return PointPosition::counter_clockwise;
        if (side < 0) return PointPosition::clockwise;
        if (sign(dot(direction, relative)) < 0) {
            return PointPosition::online_back;
        }
        if (sign(norm_squared(relative) - norm_squared(direction)) > 0) {
            return PointPosition::online_front;
        }
        return PointPosition::on_segment;
    }

    inline PointPosition point_position(const Line& line, const Point& point) {
        return point_position(line.a, line.b, point);
    }
}
