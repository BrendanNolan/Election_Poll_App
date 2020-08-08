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
    : boostCartPoint_(x, y)
{
}

Point::Point(const BoostCartesianPoint2D& cartesian)
    : boostCartPoint_(cartesian)
{
}

Point::Point(const BoostPolarPoint2D& polar)
{ 
    transform(polar, boostCartPoint_);
}

Point Point::createCartesian(double x, double y)
{
    return { x, y };
}

Point Point::createPolar(double r, double theta)
{
    return { BoostPolarPoint2D(r, theta) };
}

void Point::operator+=(const Point& other)
{
    auto newX = x() + other.x();
    auto newY = y() + other.y();
    boostCartPoint_.x(newX);
    boostCartPoint_.y(newY);
}

double Point::r() const
{
    BoostPolarPoint2D polar;
    transform(boostCartPoint_, polar);
    return polar.x();
}

double Point::theta() const
{
    BoostPolarPoint2D polar;
    transform(boostCartPoint_, polar);
    return polar.y();
}

double Point::x() const
{
    return boostCartPoint_.x();
}

double Point::y() const
{
    return boostCartPoint_.y();
}

}// namespace geom
