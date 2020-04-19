#pragma once

#include <cinttypes>
#include <iostream>

template <uint8_t R, uint8_t C>
struct Mat {

    float data[R * C];

    float get(uint8_t r, uint8_t c) const;
    void get_row(uint8_t row, float* values) const;
    void get_col(uint8_t col, float* values) const;

    void set(uint8_t r, uint8_t c, float value);

    template<uint8_t OtherC>
    Mat<R, OtherC> multiply(Mat<C, OtherC>& other) const;
    Mat<R, C> multiply(float other) const;
    Mat<C, R> transpose() const;

};

// typedef Mat<4, 4> Mat4;

template<uint8_t R, uint8_t C>
float Mat<R, C>::get(uint8_t r, uint8_t c) const {
    return this->data[r * C + c];
}

template<uint8_t R, uint8_t C>
void Mat<R, C>::get_row(uint8_t row, float* values) const {

    // Get the offset for the row
    uint8_t row_offset = row * C;

    // Add the values to the array
    for (uint8_t c = 0; c < C; c++) values[c] = this->data[row_offset + c];

}

template<uint8_t R, uint8_t C>
void Mat<R, C>::get_col(uint8_t col, float* values) const {

    // Add the values to the array
    for (uint8_t r = 0; r < R; r++) values[r] = this->get(r, col);

}

template<uint8_t R, uint8_t C>
void Mat<R, C>::set(uint8_t r, uint8_t c, float value) {
    this->data[r * C + c] = value;
}

template<uint8_t R, uint8_t C>
template<uint8_t OtherC>
Mat<R, OtherC> Mat<R, C>::multiply(Mat<C, OtherC>& other) const {

    // Create the result matrix
    Mat<R, OtherC> result;

    // Arrays for row/col values
    float row[C];
    float col[C];

    // Loop through the rows
    for (int r = 0; r < R; r++) {

        // Get the values in the column from the first matrix
        this->get_row(r, row);

        // Loop through the columns
        for (int c = 0; c < OtherC; c++) {

            // Get the column
            other.get_col(c, col);

            // Calculate the dot product
            float dotProduct = 0;
            for (int i = 0; i < C; i++) dotProduct += row[i] * col[i];

            // Insert the dot product
            result.set(r, c, dotProduct);

        }

    }

    // Return the result
    return result;

}

template<uint8_t R, uint8_t C>
Mat<R, C> Mat<R, C>::multiply(float other) const {

    // Create the result matrix
    Mat<R, C> result;

    // Calculate the total data points
    constexpr int size = R * C;

    // Loop through the data
    for (uint8_t i = 0; i < size; i++) {

        // Move and multiply the data
        result.data[i] = this->data[i] * other;

    }

    // Return the result
    return result;

}

template<uint8_t R, uint8_t C>
Mat<C, R> Mat<R, C>::transpose() const {

    // Create the result matrix
    Mat<C, R> result;

    // Loop through the rows and columns
    for (uint8_t r = 0; r < R; r++) {
        for (uint8_t c = 0; c < C; c++) {

            // Copy the value and swap rows/columns
            result.set(c, r, this->get(r, c));

        }
    }

    // Return the result
    return result;

}

template<uint8_t R, uint8_t C>
std::ostream& operator<<(std::ostream& out, Mat<R, C> const& obj) {

    // Loop through the rows
    for (uint8_t r = 0; r < R; r++) {
        if (r != 0) out << std::endl;
        out << "| ";
        for (uint8_t c = 0; c < C; c++) {
            if (c != 0) out << "\t";
            out << obj.get(r, c);
        }
        out << " |";
    }

    // Return the strea
    return out;

}
