#pragma once

#include <istream>
#include <ostream>

#include "geometry/core.hpp"

namespace yesantikiss {
    struct Point {
        Real x = 0;
        Real y = 0;

        Point() = default;
        Point(Real x, Real y) : x(x), y(y) {}

        Point& operator+=(const Point& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        Point& operator-=(const Point& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Point& operator*=(Real scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        Point& operator/=(Real scalar) {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        Point operator+() const {
            return *this;
        }

        Point operator-() const {
            return {-x, -y};
        }

        friend Point operator+(Point lhs, const Point& rhs) {
            lhs += rhs;
            return lhs;
        }

        friend Point operator-(Point lhs, const Point& rhs) {
            lhs -= rhs;
            return lhs;
        }

        friend Point operator*(Point point, Real scalar) {
            point *= scalar;
            return point;
        }

        friend Point operator*(Real scalar, Point point) {
            point *= scalar;
            return point;
        }

        friend Point operator/(Point point, Real scalar) {
            point /= scalar;
            return point;
        }

        friend bool operator==(const Point& lhs, const Point& rhs) {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }

        friend bool operator!=(const Point& lhs, const Point& rhs) {
            return !(lhs == rhs);
        }

        friend std::istream& operator>>(std::istream& input, Point& point) {
            return input >> point.x >> point.y;
        }

        friend std::ostream& operator<<(std::ostream& output, const Point& point) {
            return output << point.x << ' ' << point.y;
        }
    };

    inline Real dot(const Point& a, const Point& b) {
        return a.x * b.x + a.y * b.y;
    }

    inline Real cross(const Point& a, const Point& b) {
        return a.x * b.y - a.y * b.x;
    }

    inline Real norm_squared(const Point& point) {
        return dot(point, point);
    }

    inline Real norm(const Point& point) {
        return std::sqrt(norm_squared(point));
    }

    inline Real distance(const Point& a, const Point& b) {
        return norm(a - b);
    }

    inline bool almost_equal(const Point& a, const Point& b) {
        return almost_equal(a.x, b.x) && almost_equal(a.y, b.y);
    }
}
