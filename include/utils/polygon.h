#pragma once

#include <cinttypes>
#include "../types/polygon.h"
#include "./point.h"

namespace e3d::utils::polygon {

    /**
     * Calculates the normal vector from the provided triangle. This is not templated
     * because cross-product is always a three-dimensional operation, and the number
     * of arguments is 3 for that reason.
     */
    Vec3 tri_normal(const Tri3& tri) {

        // Return the normal of the triangle
        return e3d::utils::point::normal(
            tri.points[0],
            tri.points[1],
            tri.points[2]
        );

    }

    /**
     * Calculates the area of a polygon
     */
    template<uint8_t P, uint8_t S>
    float area(const Polygon<P, S>& poly) {

        // The total area
        float sum = 0;

        // Save the side_b value after each, and reuse it for side_a on the next iteration.
        // This is an optimization and is not a requirement of the underlying math.
        float side_b;

        // Loop through all of the points
        for (uint8_t i = 1; i < P - 1; i++) {

            // Get the length to the two points
            float side_a = i == 1
                ? e3d::utils::point::distance(poly.points[0], poly.points[i])
                : side_b;

            // Get the side-b value
            side_b = e3d::utils::point::distance(poly.points[0], poly.points[i + 1]);

            // Calculate the area between them
            float between_edge = e3d::utils::point::distance(poly.points[i], poly.points[i + 1]);

            // Calculate half of the permieter
            float hp = (side_a + side_b + between_edge) * 0.5f;

            // Lastly, calculate the area of this triangle
            sum += sqrtf(hp * (hp - side_a) * (hp - side_b) * (hp - between_edge));

        }

        // Return the sum area
        return sum;

    }

    /**
     * Determines if the given polygon is convex
     */
    template<uint8_t P, uint8_t S>
    bool is_convex(const Polygon<P, S>& poly) {

        // The previous cross product
        bool prev_sign;

        // Loop through the points 
        for (uint8_t i = 0; i < P - 2; i++) {

            // Calculate the cross product with the next
            Vec<S> cross = e3d::utils::vec::cross(
                e3d::utils::point::between(poly.points[i], poly.points[i + 1]),
                e3d::utils::point::between(poly.points[i + 1], poly.points[i + 2])
            );

            // Get the sign of the cross product
            float prod = 1;
            for (uint8_t j = 0; j < S; j++) prod *= cross.get(j) > 0 ? 1 : -1;
            bool sign = prod >= 0;

            // If this is not the first, and the sign is opposite
            if (i > 0 && sign != prev_sign) return false;

            // Update the previous sign
            prev_sign = sign;

        }

        // Return true by default
        return true;

    }

    /**
     * Determines if the given polygon is planar, meaning that all of its constituent points
     * exist on the same plane.
     */
    template<uint8_t P, uint8_t S>
    bool is_planar(const Polygon<P, S>& poly) {

        // The previous cross product
        Vec<S> prev_cross;

        // Loop through the points
        for (uint8_t i = 0; i < P - 2; i++) {

            // Calculate the cross product with the next
            Vec<S> cross = e3d::utils::vec::cross(
                e3d::utils::point::between(poly.points[i], poly.points[i + 1]),
                e3d::utils::point::between(poly.points[i + 1], poly.points[i + 2])
            );

            // If this is not the first
            if (i > 0) {

                // Calculate the angle with the previous cross produce
                float angle = e3d::utils::vec::angle_between(prev_cross, cross);

                // If the angle is greater than our approximation to zero
                if (abs(angle) >= 0.00001 && abs(angle - M_PI) >= 0.00001) return false;

            }

            // Set the previous value
            prev_cross = cross;

        }

        // Return true by default
        return true;

    }

}
