#pragma once

#include "./mat.h"

template<uint8_t S> using Vec = e3d::Mat<1, S>;

typedef Vec<2> Vec2;
typedef Vec<3> Vec3;
typedef Vec<4> Vec4;
