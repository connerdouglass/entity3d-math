#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cinttypes>
#include <cmath>

namespace e3d {

    template <uint8_t R, uint8_t C>
    struct Mat {

        /**
         * Constructs an identity matrix
         */
        static Mat<R, C> identity();

        /**
         * Constructs a matrix with all values set to zero
         */
        static Mat<R, C> zeros();

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
         * Constructs a matrix with an array of raw values. This is useful for points or vectors
         */
        Mat<R, C>(const float values[R * C]);

        /**
         * Constructs a matrix object as a copy of another existing matrix.
         */
        Mat<R, C>(const Mat<R, C>& other);

        /**
         * Gets a value from the matrix at the provided row and column
         */
        float get(uint8_t r, uint8_t c) const;

        /**
         * Gets a value from the matrix underlying data buffer, by index
         */
        float get(uint8_t index) const;

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
         * Sets a value in the underlying data buffer, by index
         */
        void set(uint8_t index, float value);

        /**
         * Multiplies this matrix with another matrix and returns the result. This method fails
         * with a static assertion at compile-time if the dimensions don't allow multiplication.
         */
        template<uint8_t OtherC>
        Mat<R, OtherC> multiply(const Mat<C, OtherC>& other) const;

        /**
         * Multiplies this matrix with some scalar value and returns the resultant matrix.
         */
        Mat<R, C> multiply(float other) const;

        /**
         * Divides this matrix by another matrix, by transposing the other and then
         * multiplying the two matrices.
         */
        template<uint8_t OtherR>
        Mat<R, OtherR> divide(const Mat<OtherR, C>& other) const;

        /**
         * Divides this matrix by a scalar value and returns the result
         */
        Mat<R, C> divide(float other) const;

        /**
         * Transposes this matrix (swaps rows and columns) and returns the resultant matrix
         */
        Mat<C, R> transpose() const;

        /**
         * Adds another matrix to this one and returns the result
         */
        Mat<R, C> add(const Mat<R, C>& other) const;

        float x() const { return this->get(0, 0); }
        float y() const { return this->get(0, 1); }
        float z() const { return this->get(0, 2); }
        float w() const { return this->get(0, 3); }

        /**
         * Operator overload for multiplication with another matrix
         */
        template<uint8_t OtherC>
        Mat<R, OtherC> operator*(const Mat<C, OtherC>& other) const {
            return this->multiply(other);
        };

        /**
         * Operator overload for multiplication with a scalar value
         */
        Mat<R, C> operator*(float other) const {
            return this->multiply(other);
        };

        /**
         * Operator overload for addition with another matrix
         */
        Mat<R, C> operator+(const Mat<R, C>& other) const {
            return this->add(other);
        };

        /**
         * Operator overload for subtraction with another matrix
         */
        Mat<R, C> operator-(const Mat<R, C>& other) const {
            return this->add(other * -1);
        };

        /**
         * Operator overload for division of this matrix with another
         */
        template<uint8_t OtherR>
        Mat<R, OtherR> operator/(const Mat<OtherR, C>& other) const {
            return this->divide(other);
        };

        /**
         * Operator overload for division with a scalar value
         */
        Mat<R, C> operator/(float other) const {
            return this->divide(other);
        }

        /**
         * Creates a string representation of the matrix
         */
        std::string to_str() const;

    };

    typedef Mat<4, 4> Mat4;

    template<uint8_t R, uint8_t C>
    Mat<R, C>::Mat(const float values[R * C]) {

        // Calculate the total data points
        constexpr int size = R * C;

        // Loop through the data and set to zero
        for (uint8_t i = 0; i < size; i++) this->data[i] = values[i];

    }

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
    Mat<R, C> Mat<R, C>::zeros() {

        // Create the matrix
        return Mat<R, C>();

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
    float Mat<R, C>::get(uint8_t index) const {
        return this->data[index];
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
    void Mat<R, C>::set(uint8_t index, float value) {
        this->data[index] = value;
    }

    template<uint8_t R, uint8_t C>
    template<uint8_t OtherC>
    Mat<R, OtherC> Mat<R, C>::multiply(const Mat<C, OtherC>& other) const {

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
    template<uint8_t OtherR>
    Mat<R, OtherR> Mat<R, C>::divide(const Mat<OtherR, C>& other) const {
        return this->multiply(other.transpose());
    }

    template<uint8_t R, uint8_t C>
    Mat<R, C> Mat<R, C>::divide(float other) const {
        return this->multiply(1.0 / other);
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
    Mat<R, C> Mat<R, C>::add(const Mat<R, C>& other) const {
        
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
    std::string Mat<R, C>::to_str() const {

        // Create the string stream
        std::stringstream ss;

        // If it's a vector
        if (C == 1) {

            // Print it as a single line
            ss << "<";
            for (uint8_t i = 0; i < R; i++) {
                if (i > 0) ss << ", ";
                float value = this->get(i);
                if (value >= 0) ss << " ";
                ss << std::fixed << std::setprecision(3) << value;
            }
            ss << ">";

        } else {

            // Loop through the rows
            for (uint8_t r = 0; r < R; r++) {
                if (r > 0) ss << std::endl;
                ss << "|";
                for (uint8_t c = 0; c < C; c++) {
                    if (c > 0) ss << "  ";
                    float value = this->get(r, c);
                    if (value >= 0) ss << " ";
                    ss << std::fixed << std::setprecision(3) << value;
                }
                ss << " |";
            }

        }

        // Return the string value
        return ss.str();

    }

    template<uint8_t R, uint8_t C>
    ::std::ostream& operator<<(::std::ostream& out, Mat<R, C> const& obj) {

        // Print the buffered string value
        out << obj.to_str();

        // Return the stream
        return out;

    }

}
