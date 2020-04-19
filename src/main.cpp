#include <iostream>
#include "matrix.h"
#include "vector.h"

int main() {

    // ...
    Mat<1, 3> a;
    a.set(0, 0, 1.0);
    a.set(0, 1, 2.0);
    a.set(0, 2, 3.0);

    Mat<3, 1> b;
    b.set(0, 0, 4.0);
    b.set(1, 0, 5.0);
    b.set(2, 0, 6.0);

    Mat<1, 1> c = a.multiply(b);
    std::cout << c << std::endl;
    std::cout << std::endl << std::endl;

    Mat<1, 3> a2 = a.multiply(3.0);
    std::cout << a2 << std::endl;
    std::cout << std::endl << std::endl;

    // Mat<3, 3> d = b.multiply(a);
    Mat<3, 3> d = b * a;
    std::cout << d << std::endl;

    Mat<4, 4> identity = Mat<4, 4>::identity();
    std::cout << identity << std::endl;

    Vec<3> v1;
    v1.set(0, 2.0);
    v1.set(1, 3.0);
    v1.set(2, 4.0);

    Vec<3> v2;
    v2.set(0, 5.0);
    v2.set(1, 6.0);
    v2.set(2, 7.0);

    Vec<3> cross = v1.cross(v2);
    std::cout << cross << std::endl << std::endl;

    // std::cout << (cross * 5) << std::endl;

    Vec<3> x_axis = Vec<3>::axis_x();
    std::cout << x_axis << std::endl;

}
