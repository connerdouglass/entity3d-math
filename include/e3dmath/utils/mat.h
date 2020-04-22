#pragma once

#include "../types/mat.h"
#include <cmath>

namespace e3d::utils::mat {

    /**
     * Performs determinant calculation on a matrix from raw data
     */
    float _det(const float* data, uint8_t size) {

        // If the number of rows is zero
        if (size == 0) return 0;
        
        // If the number of rows is one
        if (size == 1) return data[0];

        // Start the sum at zero
        float sum = 0;

        // Create the submatrix
        float subdata[(size - 1) * (size - 1)];

        // Loop through the columns
        for (uint8_t cursor_c = 0; cursor_c < size; cursor_c++) {

            // Get the value at the index
            float cursor_value = data[cursor_c];

            // Loop through the columns and fill up the subdata array
            for (uint8_t c = 0; c < size; c++) {

                // If this is on the cursor column, skip it
                if (c == cursor_c) continue;

                // Get the submatrix column index
                uint8_t sub_c = c < cursor_c ? c : (c - 1);

                // Loop through the rows
                for (uint8_t r = 0; r < size - 1; r++) {

                    // Copy the value over
                    subdata[r * (size - 1) + sub_c] = data[(r + 1) * size + c];

                }

            }

            // Calculate this partial
            float partial = cursor_value * _det(subdata, size - 1);

            // Add to / subtract from the sum
            sum += (cursor_c % 2 == 0) ? partial : -partial;

        }

        // Return the sum
        return sum;

    }

    /**
     * Calculates the determinant of the provided matrix. Determinant can be thought of as the
     * scalar effect the matrix would have on the vector space, if used as a transformation.
     */
    template<uint8_t R>
    float determinant(const Mat<R, R>& mat) {
        return _det(mat.data, R);
    }

    /**
     * Creates a translation matrix
     */
    Mat4 mat4_create_translation(float x, float y, float z) {

        // Create an identity matrix
        Mat4 result = Mat4::identity();

        // Set the translation values
        result.set(0, 3, x);
        result.set(1, 3, y);
        result.set(2, 3, z);

        // Return the result
        return result;

    }

    /**
     * Performs a translation on a matrix and returns the result
     */
    Mat4 mat4_translate(const Mat4& mat, float x, float y, float z) {

        // Create a copy of the matrix
        Mat4 result(mat);

        // Calculate the bottom row of the matrix, one column at a time
        for (uint8_t i = 0; i < 4; i++) {

            // Update the value for the bottom row
            result.set(3, i,
                x * mat.get(0, i) +
                y * mat.get(1, i) +
                z * mat.get(2, i) +
                mat.get(3, i));

        }

        // Return the result
        return result;

    }
    Mat4 mat4_translate(const Mat4& mat, const Vec4& vec) { return mat4_translate(mat, vec.x(), vec.y(), vec.z()); }
    Mat4 mat4_translate(const Mat4& mat, const Vec3& vec) { return mat4_translate(mat, vec.x(), vec.y(), vec.z()); }

    /**
     * Creates a matrix for scaling transformations
     */
    Mat4 mat4_create_scale(float x, float y, float z) {

        // Create the matrix
        Mat4 mat = Mat4::identity();

        // Assign the components
        mat.set(0, 0, x);
        mat.set(1, 1, y);
        mat.set(2, 2, z);

        // Return the matrix
        return mat;

    }

    /**
     * Performs a scale transformation on a matrix and returns the result
     */
    Mat4 mat4_scale(const Mat4& mat, float x, float y, float z) {

        // Create a copy of the matrix
        Mat4 result(mat);

        // Multiply the appropriate components
        int i = 0;
        for (; i < 4; i++) result.data[i] *= x;
        for (; i < 8; i++) result.data[i] *= y;
        for (; i < 12; i++) result.data[i] *= z;

        // Return the result
        return result;

    }
    Mat4 mat4_scale(const Mat4& mat, const Vec4& vec) { return mat4_scale(mat, vec.x(), vec.y(), vec.z()); }
    Mat4 mat4_scale(const Mat4& mat, const Vec3& vec) { return mat4_scale(mat, vec.x(), vec.y(), vec.z()); }

    /**
     * Creates a rotation matrix for rotation of `x` radians on the x-axis
     */
    Mat4 mat4_create_rotation_x(float x) {

        // Create the identity matrix
        Mat4 result = Mat4::identity();

        // Calculate the trig values
        float sin_theta = sinf(x);
        float cos_theta = cosf(x);

        // Fill in the rotation values
        result.set(1, 1, cos_theta);
        result.set(1, 2, -sin_theta);
        result.set(2, 1, sin_theta);
        result.set(2, 2, cos_theta);

        // Return the result matrix
        return result;

    }

    /**
     * Creates a rotation matrix for rotation of `y` radians on the y-axis
     */
    Mat4 mat4_create_rotation_y(float y) {

        // Create the identity matrix
        Mat4 result = Mat4::identity();

        // Calculate the trig values
        float sin_theta = sinf(y);
        float cos_theta = cosf(y);

        // Fill in the rotation values
        result.set(0, 0, cos_theta);
        result.set(0, 2, sin_theta);
        result.set(2, 0, -sin_theta);
        result.set(2, 2, cos_theta);

        // Return the result matrix
        return result;

    }
    
    /**
     * Creates a rotation matrix for rotation of `z` radians on the z-axis
     */
    Mat4 mat4_create_rotation_z(float z) {

        // Create the identity matrix
        Mat4 result = Mat4::identity();

        // Calculate the trig values
        float sin_theta = sinf(z);
        float cos_theta = cosf(z);

        // Fill in the rotation values
        result.set(0, 0, cos_theta);
        result.set(0, 1, -sin_theta);
        result.set(1, 0, sin_theta);
        result.set(1, 1, cos_theta);

        // Return the result matrix
        return result;

    }

    /**
     * Performs a rotate transformation on the matrix in YXZ-order, and then returns the result
     */
    Mat4 mat4_create_rotation_yxz(float x, float y, float z) {

        // Create the result matrix
        Mat4 mat;

        // Calculate the trig values
        const float cx = cosf(x);
        const float sx = sinf(x);
        const float cy = cosf(y);
        const float sy = sinf(y);
        const float cz = cosf(z);
        const float sz = sinf(z);

        // Insert the values to the matrix
        mat.data[0] = (cy * cz) + (sx * sy * sz);
        mat.data[1] = cx * sz;
        mat.data[2] = (cy * sx * sz) - (cz * sy);
        mat.data[3] = 0.0;
        
        mat.data[4] = (cz * sx * sy) - (cy * sz);
        mat.data[5] = cx * cz;
        mat.data[6] = (cy * cz * sx) + (sy * sz);
        mat.data[7] = 0.0;
        
        mat.data[8] = cx * sy;
        mat.data[9] = -sx;
        mat.data[10] = cx * cy;
        mat.data[11] = 0.0;
        
        mat.data[12] = 0.0;
        mat.data[13] = 0.0;
        mat.data[14] = 0.0;
        mat.data[15] = 1.0;
        
        // Return the matrix
        return mat;

    }
    Mat4 mat4_rotate_yxz(const Mat4& mat, float x, float y, float z) { return mat * mat4_create_rotation_yxz(x, y, z); }
    Mat4 mat4_rotate_yxz(const Mat4& mat, const Vec4& vec) { return mat4_rotate_yxz(mat, vec.x(), vec.y(), vec.z()); }
    Mat4 mat4_rotate_yxz(const Mat4& mat, const Vec3& vec) { return mat4_rotate_yxz(mat, vec.x(), vec.y(), vec.z()); }

};
