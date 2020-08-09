#ifndef POINT_H
#define POINT_H

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
protected:
    Point(double x, double y);

public:
    static Point createCartesian(double x, double y);
    static Point createPolar(double r, double theta);
    static Point origin();

    void rotateAbout(const Point& fulcrum, double radians);
    Point rotatedAbout(const Point& fulcrum, double radians) const;
    void normalise();

    void setPolarCoords(double r, double theta);
    void setCartesianCoords(double x, double y);

    void operator+=(const Point& other);
    void operator-=(const Point& other);
    void operator*=(double scalar);
    void operator/=(double scalar);

    const double& x() const;
    const double& y() const;
    void x(const double& x);
    void y(const double& y);

    double r() const;
    double theta() const;

private:
    void rotateAboutOrigin(double radians);
    Point rotatedAboutOrigin(double radians) const;

private:
    BoostCartesianPoint2D boostCartPoint_;
};

Point operator+(const Point& a, const Point& b);
Point operator-(const Point& a, const Point& b);
double dist(const Point& a, const Point& b);
double norm(const Point& point);
Quadrant quadrant(const Point& point);

};// namespace geom

#endif// POINT_H
