#include "Point.h"

#include <cmath>
#include <exception>
#include <utility>

#include "geom_defs.h"

namespace
{
std::pair<double, double> cartesianToPolar(double x, double y);
std::pair<double, double> polarToCartesian(double r, double theta);
}// namespace

namespace geom
{
Point::Point(double x, double y)
    : x_(x)
    , y_(y)
{
}

Point Point::newCartesianPoint(double x, double y)
{
    return Point(x, y);
}

Point Point::newPolarPoint(double r, double theta)
{
    auto xyPair = polarToCartesian(r, theta);
    return Point(xyPair.first, xyPair.second);
}

Point Point::origin()
{
    return Point(0.0, 0.0);
}

bool Point::operator==(const Point& other) const
{
    return other.x_ == x_ && other.y_ == y_;
}

double Point::r() const
{
    return cartesianToPolar(x_, y_).first;
}

double Point::theta() const
{
    return cartesianToPolar(x_, y_).second;
}

void Point::setPolarCoords(double r, double theta)
{
    auto xyPair = polarToCartesian(r, theta);
    x_ = xyPair.first;
    y_ = xyPair.second;
}

void Point::setCartesianCoords(double x, double y)
{
    x_ = x;
    y_ = y;
}

void Point::rotateAbout(const Point& fulcrum, double radians)
{
    *this = *this - fulcrum;
    rotateAboutOrigin(radians);
    *this = *this + fulcrum;
}

Point Point::rotatedAbout(const Point& fulcrum, double radians) const
{
    auto rotatedCopy = *this;
    rotatedCopy.rotateAbout(fulcrum, radians);
    return rotatedCopy;
}

void Point::normalise()
{
    if (*this == origin())
        return;

    *this /= norm(*this);
}

double Point::x() const
{
    return x_;
}

double Point::y() const
{
    return y_;
}

void Point::rotateAboutOrigin(double radians)
{
    setPolarCoords(r(), theta() + radians);
}

Point Point::rotatedAboutOrigin(double radians) const
{
    auto cpy = *this;
    cpy.rotateAboutOrigin(radians);
    return cpy;
}

void Point::operator*=(double scalar)
{
    x_ *= scalar;
    y_ *= scalar;
}

void Point::operator/=(double scalar)
{
    x_ /= scalar;
    y_ /= scalar;
}

Point operator+(const Point& a, const Point& b)
{
    return Point::newCartesianPoint(a.x() + b.x(), a.y() + b.y());
}

Point operator-(const Point& a, const Point& b)
{
    return Point::newCartesianPoint(a.x() - b.x(), a.y() - b.y());
}

double dist(const Point& a, const Point& b)
{
    return std::sqrt(std::pow(a.x() - b.x(), 2) + std::pow(a.y() - b.y(), 2));
}

double norm(const Point& point)
{
    return dist(point, Point::origin());
}

double angle(const Point& a, const Point& corner, const Point& b)
{
    if (a == b || b == corner || a == corner)
        throw std::exception("At least two points the same.");
    auto a2 = a - corner;
    auto b2 = b - corner;
    a2.normalise();
    b2.normalise();
}

Quadrant quadrant(const Point& point)
{
    auto x = point.x();
    auto y = point.y();

    if (x >= 0 && y >= 0)
        return Quadrant::first;
    else if (x < 0 && y >= 0)
        return Quadrant::second;
    else if (x < 0 && y < 0)
        return Quadrant::third;
    else
        return Quadrant::fourth;
}

}// namespace geom

namespace
{
std::pair<double, double> cartesianToPolar(double x, double y)
{
    auto r = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    if (r < geom::doublePrecisionTolerance)
        return { 0.0, 0.0 };
    auto theta = (y >= 0.0) ? std::acos(x / r) : -std::acos(x / r);
    return { r, theta };
}
std::pair<double, double> polarToCartesian(double r, double theta)
{
    auto x = r * std::cos(theta);
    auto y = r * std::sin(theta);
    return { x, y };
}
}// namespace
