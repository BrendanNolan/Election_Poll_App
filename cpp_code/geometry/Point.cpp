#include "Point.h"

#include <boost/geometry/algorithms/transform.hpp>

#include <cmath>
#include <exception>
#include <utility>

#include "geom_defs.h"

using namespace boost::geometry;

namespace geom
{
Point::Point(double x, double y)
    : boostPoint_(x, y)
{
}

Point::Point(const BoostCartesianPoint2D& cartesian)
    : boostPoint_(cartesian)
{
}

Point::Point(const BoostPolarPoint2D& polar)
{ 
    transform(polar, boostPoint_);
}

Point Point::createCartesian(double x, double y)
{
    return { x, y };
}

Point Point::createPolar(double r, double theta)
{
    return { BoostPolarPoint2D(r, theta) };
}

double Point::r() const
{
    BoostPolarPoint2D polar;
    transform(boostPoint_, polar);
    return polar.x();
}

double Point::theta() const
{
    BoostPolarPoint2D polar;
    transform(boostPoint_, polar);
    return polar.y();
}

double Point::x() const
{
    return boostPoint_.x();
}

double Point::y() const
{
    return boostPoint_.y();
}

}// namespace geom
