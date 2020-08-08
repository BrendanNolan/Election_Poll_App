#ifndef POINT_H
#define POINT_H

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include "geom_defs.h"

/*
    These utils are far from their final form. I am addiing to them as and when
    I need new utilities.
*/

namespace geom
{

enum class Quadrant
{
    first,
    second,
    third,
    fourth
};

class Point
{
private:
    Point(double x, double y);
    Point(const BoostCartesianPoint2D& cartesian);
    Point(const BoostPolarPoint2D& polar);

public:
    static Point createCartesian(double x, double y);
    static Point createPolar(double r, double theta);

    double x() const;
    double y() const;
    double r() const;
    double theta() const;

private:
    BoostCartesianPoint2D boostPoint_;
};

};// namespace geom

#endif// POINT_H
