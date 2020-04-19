#pragma once

#include <cinttypes>
#include "matrix.h"

template<uint8_t S>
struct Vec : public Mat<S, 1> {

    static Vec<S> axis_x() { return Vec<S>::axis_i(0); };
    static Vec<S> axis_y() { return Vec<S>::axis_i(1); };
    static Vec<S> axis_z() { return Vec<S>::axis_i(2); };
    static Vec<S> axis_i(uint8_t index);

    void set(uint8_t index, float value);
    float get(uint8_t index) const;
    float dot(Vec<S>& other) const;
    Vec<S> cross(Vec<S>& other) const;
    float magnitude() const;

};

template<uint8_t S>
Vec<S> Vec<S>::axis_i(uint8_t index) {
    Vec<S> vec;
    vec.set(index, 1.0);
    return vec;
}

template<uint8_t S>
void Vec<S>::set(uint8_t index, float value) {

    // Set the value
    Mat<S, 1>::set(index, 0, value);

}

template<uint8_t S>
float Vec<S>::get(uint8_t index) const {

    // Return the element at the index
    return Mat<S, 1>::get(index, 0);

}

template<uint8_t S>
float Vec<S>::dot(Vec<S>& other) const {

    // Start at zero
    float dot = 0;

    // Loop through the elements
    for (uint8_t i = 0; i < S; i++) dot += this->get(i) * other.get(i);

    // Return the dot produce
    return dot;

}

template<uint8_t S>
Vec<S> Vec<S>::cross(Vec<S>& other) const {
    static_assert(S == 3, "Cross product only possible in 3-dimensions");

    // Create the result vector
    Vec<S> result;

    // Get all of the values from this matrix
    float a_x = this->get(0);
    float a_y = this->get(1);
    float a_z = this->get(2);

    // Get all of the values from the other matrix
    float b_x = other.get(0);
    float b_y = other.get(1);
    float b_z = other.get(2);

    // Calculate each component of the result
    result.set(0, a_y * b_z - a_z * b_y);
    result.set(1, a_z * b_x - a_x * b_z);
    result.set(2, a_x * b_y - a_y * b_x);

    // Return the result
    return result;

}

template<uint8_t S>
std::ostream& operator<<(std::ostream& out, Vec<S> const& obj) {

    // Output all the elements
    out << "<";
    for (uint8_t i = 0; i < S; i++) {
        if (i > 0) out << ", ";
        out << obj.get(i);
    }
    out << ">";

    // Return the stream
    return out;

}
