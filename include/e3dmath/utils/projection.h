#pragma once

#include "../types/mat.h"
#include <cmath>

namespace e3d::utils::projection {

    /**
     * Creates a perspective projection matrix
     */
    static Mat4 mat4_create_perspective(float fov, float ratio, float near, float far) {

        // Calculate the correct scale for the display, vertically
        float tanfov = tanf(fov / 2.0f * M_PI / 180.0f);

        // Create the result matrix
        Mat4 mat = Mat4::zeros();
        mat.set(0, 0, 1.0f / (ratio * tanfov));
        mat.set(1, 1, 1.0f / tanfov);
        mat.set(2, 2, -(far + near) / (far - near));
        mat.set(3, 2, -1);
        mat.set(2, 3, -(2.0f * far * near) / (far - near));

        // Return the matrix
        return mat;

    }

    /**
     * Creates an orthographic projection matrix
     */
    static Mat4 mat4_create_orthographic(float left, float right, float bottom, float top, float near, float far) {

        // Create the result matrix
        Mat4 mat = Mat4::zeros();
        mat.set(0, 0, 2.0f / (right - left));
        mat.set(1, 1, 2.0f / (top - bottom));
        mat.set(2, 2, -2.0f / (far - near));
        mat.set(0, 3, -(right + left) / (right - left));
        mat.set(1, 3, -(top + bottom) / (top - bottom));
        mat.set(2, 3, -(far + near) / (far - near));
        mat.set(3, 3, 1);

        // Return the matrix
        return mat;

    }

}
