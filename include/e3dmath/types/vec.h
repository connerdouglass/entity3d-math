#pragma once

#include "mat.h"

namespace e3d {

    template<uint8_t S> using Vec = e3d::Mat<S, 1>;

    typedef Vec<2> Vec2;
    typedef Vec<3> Vec3;
    typedef Vec<4> Vec4;

}