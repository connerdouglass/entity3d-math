#pragma once

#include "vec.h"

namespace e3d {

    template<uint8_t S> using Point = e3d::Vec<S>;

    typedef Vec<2> Point2;
    typedef Vec<3> Point3;

}
