#pragma once

#include <cinttypes>
#include "point.h"

/**
 * Polygon is templated, where P is the number of points in the polygon, and S is the
 * dimensionality of the coordinate space of those points.
 */
template<uint8_t P, uint8_t S>
struct Polygon {

    /**
     * The array of points in the triangle
     */
    e3d::Point<S> points[P];

};

template<uint8_t S> using Tri = Polygon<3, S>;
typedef Tri<2> Tri2;
typedef Tri<3> Tri3;

template<uint8_t S> using Quad = Polygon<4, S>;
typedef Quad<2> Quad2;
typedef Quad<3> Quad3;
