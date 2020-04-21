#pragma once

#include <cinttypes>
#include "../types/vec.h"

namespace e3d::utils::vec {

    template<uint8_t S>
    Vec<S> i_axis(uint8_t index) {
        float values[S];
        for (uint8_t i = 0; i < S; i++) {
            values[i] = i == index ? 1.0 : 0.0;
        }
        return Vec<S>(values);
    }

    template<uint8_t S>
    Vec<S> x_axis() { return i_axis<S>(0); }

    template<uint8_t S>
    Vec<S> y_axis() { return i_axis<S>(1); }

    template<uint8_t S>
    Vec<S> z_axis() { return i_axis<S>(2); }

    /**
     * Calculates the dot product of two vectors
     */
    template<uint8_t S>
    float dot(const Vec<S>& left, const Vec<S>& right) {

        // Start at zero
        float dot = 0;

        // Loop through the elements
        for (uint8_t i = 0; i < S; i++) dot += left.get(i) * right.get(i);

        // Return the dot product
        return dot;

    }

    /**
     * Calculates the cross product of two vectors
     */
    template<uint8_t S>
    Vec<S> cross(const Vec<S>& left, const Vec<S>& right) {
        static_assert(S == 3, "Cross product only possible in 3-dimensions");

        // Create the result vector
        Vec<S> result;

        // Get all of the values from the left matrix
        float a_x = left.get(0);
        float a_y = left.get(1);
        float a_z = left.get(2);

        // Get all of the values from the right matrix
        float b_x = right.get(0);
        float b_y = right.get(1);
        float b_z = right.get(2);

        // Calculate each component of the result
        result.set(0, a_y * b_z - a_z * b_y);
        result.set(1, a_z * b_x - a_x * b_z);
        result.set(2, a_x * b_y - a_y * b_x);

        // Return the result
        return result;

    }

    template<uint8_t S>
    float magnitude(const Vec<S>& vec) {

        // Create the sum
        float sum = 0;

        // Loop through the components
        for (int i = 0; i < S; i++) {
            float val = vec.get(i);
            sum += val * val;
        }

        // Return the square-root
        return sqrtf(sum);

    }

    template<uint8_t S>
    Vec<S> normalize(const Vec<S>& vec) {

        // Get the magnitude of the matrix
        float mag = magnitude(vec);

        // If the magnitude is zero, return a zero vector
        if (std::abs(mag) <= 0.00001) return Vec<S>::zeros();

        // Divide the vector by the magnitude
        return vec / mag;

    }

    template<uint8_t Sto, uint8_t Sfrom>
    Vec<Sto> resize(const Vec<Sfrom>& vec) {

        // Create the new vector
        Vec<Sto> result;

        // Copy the values
        for (uint8_t i = 0; i < Sto; i++) {
            if (i < Sfrom) result.set(i, vec.get(i));
            else result.set(i, 0);
        }

        // Return the result
        return result;

    }

    /**
     * Calculates the angle between two vectors
     */
    template<uint8_t S>
    float angle_between(const Vec<S>& left, const Vec<S>& right) {

        // Get the dot product
        float dot_product = dot(left, right);

        // Divide it by the magnitudes
        float cos_theta = dot_product / magnitude(left) / magnitude(right);

        // Return the angle
        return acosf(cos_theta);

    }

}
