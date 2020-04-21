#pragma once

#include <cinttypes>
#include "../types/point.h"
#include "./vec.h"

namespace e3d::utils::point {

    /**
     * Calculates the absolute distance between two points
     */
    template<uint8_t S>
    float distance(const Point<S>& left, const Point<S>& right) {
        return e3d::utils::vec::magnitude(
            vector_between(left, right)
        );
    }

    /**
     * Calculates a vector between two points, starting at the first and pointing
     * toward the second
     */
    template<uint8_t S>
    Vec<S> between(const Point<S>& from, const Point<S>& to) {
        return to - from;
    }

    /**
     * Calculates the normal vector from the provided triangle. This is not templated
     * because cross-product is always a three-dimensional operation, and the number
     * of arguments is 3 for that reason.
     */
    Vec3 normal(const Point3& a, const Point3& b, const Point3& c) {

        // Create the two vectors
        Vec3 vec_a = b - a;
        Vec3 vec_b = c - b;

        // Calculate the cross product
        return e3d::utils::vec::cross(vec_a, vec_b);

    }

}
