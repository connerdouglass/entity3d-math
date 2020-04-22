#pragma once

#include "../types/mat.h"
#include <cmath>

namespace e3d::utils::projection {

    /**
     * Creates a perspective projection matrix
     */
    Mat4 mat4_create_perspective(float fov, float aspectRatio, float zNear, float zFar) {

        // Calculate the correct scale for the display, vertically
        float scale = tanf(fov / 2.0f * M_PI / 180.0f) * zNear;

        // Calculate the edge bounds in screen space
        float top = scale;
        float bottom = -scale;
        float right = scale * aspectRatio;
        float left = -right;

        // Create the result matrix
        Mat4 mat = Mat4::zeros();
        mat.set(0, 0, 2 * zNear / (right - left));
        mat.set(1, 1, 2 * zNear / (top - bottom));
        mat.set(2, 0, (right + left) / (right - left));
        mat.set(2, 1, (top + bottom) / (top - bottom));
        mat.set(2, 2, -(zFar + zNear) / (zFar - zNear));
        mat.set(2, 3, -1);
        mat.set(3, 2, -2 * zFar * zNear / (zFar - zNear));

        // Return the matrix
        return mat;

    }

}
