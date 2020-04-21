#include <iostream>
#include "e3dmath.h"

using namespace e3d;

int main() {

    // // Get the axis-aligned unit vectors
    // Vec3 x = utils::vec::x_axis<3>();
    // Vec3 y = utils::vec::y_axis<3>();
    // Vec3 z = utils::vec::z_axis<3>();

    // // Define our starting point
    // Vec4 original ((float[]){ 1, 2, 3, 0 });
    // e3d::Mat4 r = utils::mat::mat4_create_rotation_y(M_PI);
    // e3d::Vec4 result = r * original;
    // std::cout << result << std::endl;

    // // Create a point
    // Point2 p1 ((float[]){ 0, 1 });
    // Point2 p2 ((float[]){ 3, 3 });
    // std::cout << "P1: " << p1 << std::endl;
    // std::cout << "P2: " << p2 << std::endl;
    // std::cout << "P1 -> P2: " << utils::point::between(p1, p2) << std::endl;
    // std::cout << "Dist: " << utils::point::distance(p2, p1) << std::endl;

    // Vec3 normal = utils::point::normal(
    //     // utils::vec::resize<3>(p1),
    //     // utils::vec::resize<3>(p2),
    //     Point3((float[]){ 0, 0, 0 }),
    //     Point3((float[]){ 1, 0, 0 }),
    //     Point3((float[]){ 1, 1, 0 })
    // );
    // std::cout << normal << std::endl;

    // // Create some composite based on the unit vectors
    // // Vec3 comp = x * 2.0f + y * 3.0f + z * 4.0f;
    // Vec3 comp ((float[]){ 2, 3, 4 });
    // std::cout << comp << std::endl;

    // Mat4 rotation = utils::mat::mat4_create_rotation_y(M_PI);
    // // Vec4 rot = utils::vec::resize<4>(x).multiply(rotation);

    // auto rot = rotation * utils::vec::resize<4>(x);
    // std::cout << rot << std::endl;

    // utils::mat::mat4_create_scale(2, 2, 2);

    // // Mat<4, 3>::identity();

    // std::cout << "Cross:" << std::endl;
    // std::cout << utils::vec::cross(
    //     utils::vec::x_axis<3>() * 3,
    //     utils::vec::z_axis<3>() * 2
    // ) << std::endl;

    // std::cout
    //     << "Proj"
    //     << std::endl
    //     << e3d::utils::projection::mat4_create_perspective(45.0f, 16.0f / 9.0f, 0.1f, 10.0f)
    //     << std::endl;

    Point3 top_right ((float[]){ 1, 1, 0});
    top_right = e3d::utils::vec::resize<3>(
        e3d::utils::mat::mat4_create_rotation_z(M_PI / 2) * e3d::utils::vec::resize<4>(top_right)
    );
    std::cout << top_right << std::endl;

    Quad3 tri ({
        Point3((float[]){ 0, 0, 0 }),
        Point3((float[]){ 1, 0, 0 }),
        top_right,
        Point3((float[]){ 0, 1, 0 })
    });
    std::cout << e3d::utils::polygon::area(tri) << std::endl;
    for (uint8_t i = 0; i < 4; i++) std::cout << int(i + 1) << ": " << tri.points[i] << std::endl;

    std::cout << "Planar? " << e3d::utils::polygon::is_planar(tri) << std::endl;
    std::cout << "Convex? " << e3d::utils::polygon::is_convex(tri) << std::endl;
    
}
