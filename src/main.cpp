#include <iostream>
#include "e3dmath.h"

using namespace e3d;

int main() {

    // Get the axis-aligned unit vectors
    Vec3 x = utils::vec::x_axis<3>();
    Vec3 y = utils::vec::y_axis<3>();
    Vec3 z = utils::vec::z_axis<3>();

    // Define our starting point
    Vec4 original ((float[]){ 1, 2, 3 });
    Mat4 r = utils::mat::mat4_create_rotation_y(M_PI);
    Vec4 result = original * r;
    std::cout << "Rotated: " << result << std::endl;

    // Create some composite based on the unit vectors
    // Vec3 comp = x * 2.0f + y * 3.0f + z * 4.0f;
    Vec3 comp ((float[]){ 2, 3, 4 });
    std::cout << comp << std::endl;

    Mat4 rotation = utils::mat::mat4_create_rotation_y(M_PI);
    // Vec4 rot = utils::vec::resize<4>(x).multiply(rotation);

    auto rot = utils::vec::resize<4>(x).multiply(rotation);
    std::cout << rot << std::endl;

    utils::mat::mat4_create_scale(2, 2, 2);

    Mat<4, 3>::identity();

    std::cout << "Cross:" << std::endl;
    std::cout << utils::vec::cross(
        utils::vec::x_axis<3>() * 3,
        utils::vec::z_axis<3>() * 2
    ) << std::endl;

    std::cout
        << "Proj"
        << std::endl
        << e3d::utils::projection::mat4_create_perspective(45.0f, 16.0f / 9.0f, 0.1f, 10.0f)
        << std::endl;
    
}
