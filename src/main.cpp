#include <iostream>
#include "matrix.h"

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

    Mat<3, 3> d = b.multiply(a);
    std::cout << d << std::endl;

    Mat<4, 4> identity = Mat<4, 4>::identity();
    std::cout << identity << std::endl;

}
