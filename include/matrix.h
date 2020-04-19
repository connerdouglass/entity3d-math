#pragma once

#include <cinttypes>
#include <cmath>

template <uint8_t R, uint8_t C>
struct Mat {

    /**
     * Constructs an identity matrix
     */
    static Mat<R, C> identity();

    /**
     * Constructs an x-rotation matrix
     */
    static Mat<R, C> rotate_x(float rot_x);

    /**
     * Constructs a y-rotation matrix
     */
    static Mat<R, C> rotate_y(float rot_y);

    /**
     * Constructs an z-rotation matrix
     */
    static Mat<R, C> rotate_z(float rot_z);

    /**
     * The raw data in the matrix
     */
    float data[R * C];

    /**
     * Constructs a matrix object, and initializes the values in the underlying
     * data to all-zeros.
     */
    Mat<R, C>();

    /**
     * Constructs a matrix object as a copy of another existing matrix.
     */
    Mat<R, C>(const Mat<R, C>& other);

    /**
     * Gets a value from the matrix at the provided row and column
     */
    float get(uint8_t r, uint8_t c) const;

    /**
     * Gets all of the values in a row, and puts them into the `values` array provided
     */
    void get_row(uint8_t row, float* values) const;

    /**
     * Gets all of the values in a column, and puts them into the `values` array provided
     */
    void get_col(uint8_t col, float* values) const;

    /**
     * Sets a value in the matrix at the provided row and column
     */
    void set(uint8_t r, uint8_t c, float value);

    /**
     * Multiplies this matrix with another matrix and returns the result. This method fails
     * with a static assertion at compile-time if the dimensions don't allow multiplication.
     */
    template<uint8_t OtherC>
    Mat<R, OtherC> multiply(Mat<C, OtherC>& other) const;

    /**
     * Multiplies this matrix with some scalar value and returns the resultant matrix.
     */
    Mat<R, C> multiply(float other) const;

    /**
     * Transposes this matrix (swaps rows and columns) and returns the resultant matrix
     */
    Mat<C, R> transpose() const;

    /**
     * Adds another matrix to this one and returns the result
     */
    Mat<R, C> add(Mat<R, C>& other) const;

    /**
     * Operator overload for multiplication with another matrix
     */
    template<uint8_t OtherC>
    Mat<R, OtherC> operator*(Mat<C, OtherC>& other) const;

    /**
     * Operator overload for multiplication with a scalar value
     */
    Mat<R, C> operator*(float other) const;

    /**
     * Operator overload for addition with another matrix
     */
    Mat<R, C> operator+(Mat<R, C>& other) const;

};

template<uint8_t R, uint8_t C>
Mat<R, C>::Mat() {

    // Calculate the total data points
    constexpr int size = R * C;

    // Loop through the data and set to zero
    for (uint8_t i = 0; i < size; i++) this->data[i] = 0;

}

template<uint8_t R, uint8_t C>
Mat<R, C>::Mat(const Mat<R, C>& other) {

    // Calculate the total data points
    constexpr int size = R * C;

    // Loop through the data and copy the value
    for (uint8_t i = 0; i < size; i++) this->data[i] = other.data[i];

}

template<uint8_t R, uint8_t C>
Mat<R, C> Mat<R, C>::rotate_x(float rot_x) {

    // Create the identity matrix
    Mat<R, C> result = Mat<R, C>::identity();

    // Calculate the trig values
    float sin_theta = sinf(rot_x);
    float cos_theta = cosf(rot_x);

    // Fill in the rotation values
    result.set(1, 1, cos_theta);
    result.set(1, 2, -sin_theta);
    result.set(2, 1, sin_theta);
    result.set(2, 2, cos_theta);

    // Return the result matrix
    return result;

}

template<uint8_t R, uint8_t C>
Mat<R, C> Mat<R, C>::rotate_y(float rot_y) {

    // Create the identity matrix
    Mat<R, C> result = Mat<R, C>::identity();

    // Calculate the trig values
    float sin_theta = sinf(rot_y);
    float cos_theta = cosf(rot_y);

    // Fill in the rotation values
    result.set(0, 0, cos_theta);
    result.set(0, 2, sin_theta);
    result.set(2, 0, -sin_theta);
    result.set(2, 2, cos_theta);

    // Return the result matrix
    return result;

}

template<uint8_t R, uint8_t C>
Mat<R, C> Mat<R, C>::rotate_z(float rot_z) {

    // Create the identity matrix
    Mat<R, C> result = Mat<R, C>::identity();

    // Calculate the trig values
    float sin_theta = sinf(rot_z);
    float cos_theta = cosf(rot_z);

    // Fill in the rotation values
    result.set(0, 0, cos_theta);
    result.set(0, 1, -sin_theta);
    result.set(1, 0, sin_theta);
    result.set(1, 1, cos_theta);

    // Return the result matrix
    return result;

}

template<uint8_t R, uint8_t C>
Mat<R, C> Mat<R, C>::identity() {
    static_assert(C == R, "Matrix identity dimension rows must equal columns");

    // Create the matrix
    Mat<R, C> result;

    // Loop through the size
    for (uint8_t i = 0; i < R; i++) result.set(i, i, 1.0);

    // Return the result
    return result;

}

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
    constexpr uint8_t size = R * C;

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
Mat<R, C> Mat<R, C>::add(Mat<R, C>& other) const {
    
    // Create the result matrix
    Mat<R, C> result;

    // Calculate the total data points
    constexpr uint8_t size = R * C;

    // Loop through the data
    for (uint8_t i = 0; i < size; i++) {

        // Move and multiply the data
        result.data[i] = this->data[i] + other.data[i];

    }

    // Return the results
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

    // Return the stream
    return out;

}

template<uint8_t R, uint8_t C>
template<uint8_t OtherC>
Mat<R, OtherC> Mat<R, C>::operator*(Mat<C, OtherC>& other) const {
    return this->multiply(other);
}

template<uint8_t R, uint8_t C>
Mat<R, C> Mat<R, C>::operator*(float other) const {
    return this->multiply(other);
}

template<uint8_t R, uint8_t C>
Mat<R, C> Mat<R, C>::operator+(Mat<R, C>& other) const {
    return this->add(other);
}
