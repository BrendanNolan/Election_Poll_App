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
    : boostCartPoint_(x, y)
{
}

Point Point::createCartesian(double x, double y)
{
    return Point(x, y);
}

Point Point::createPolar(double r, double theta)
{
    auto xyPair = polarToCartesian(r, theta);
    return Point(xyPair.first, xyPair.second);
}

Point Point::origin()
{
    return Point(0.0, 0.0);
}

double Point::r() const
{
    return cartesianToPolar(boostCartPoint_.x(), boostCartPoint_.y()).first;
}

double Point::theta() const
{
    return cartesianToPolar(boostCartPoint_.x(), boostCartPoint_.y()).second;
}

void Point::setPolarCoords(double r, double theta)
{
    auto xyPair = polarToCartesian(r, theta);
    boostCartPoint_.x(xyPair.first);
    boostCartPoint_.y(xyPair.second);
}

void Point::setCartesianCoords(double x, double y)
{
    boostCartPoint_.x(x);
    boostCartPoint_.y(y);
}

void Point::operator+=(const Point& other)
{
    *this = *this + other;
}

void Point::operator-=(const Point& other)
{
    *this = *this - other;
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
    if (norm(*this) > 0.0)
        *this /= norm(*this);
}

const double& Point::x() const
{
    return boostCartPoint_.x();
}

const double& Point::y() const
{
    return boostCartPoint_.y();
}

void Point::x(const double& x)
{
    boostCartPoint_.x(x);
}

void Point::y(const double& y)
{
    boostCartPoint_.y(y);
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
    auto x = boostCartPoint_.x();
    auto y = boostCartPoint_.y();
    boostCartPoint_.x(scalar * x);
    boostCartPoint_.y(scalar * y);
}

void Point::operator/=(double scalar)
{
    if (scalar == 0.0)
        return;
    auto x = boostCartPoint_.x();
    auto y = boostCartPoint_.y();
    boostCartPoint_.x(x / scalar);
    boostCartPoint_.y(y / scalar);
}

Point operator+(const Point& a, const Point& b)
{
    return Point::createCartesian(a.x() + b.x(), a.y() + b.y());
}

Point operator-(const Point& a, const Point& b)
{
    return Point::createCartesian(a.x() - b.x(), a.y() - b.y());
}

double dist(const Point& a, const Point& b)
{
    return std::sqrt(std::pow(a.x() - b.x(), 2) + std::pow(a.y() - b.y(), 2));
}

double norm(const Point& point)
{
    return dist(point, Point::origin());
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
