#ifndef POINTS_H
#define POINTS_H

/*
    These utils are far from their final form. I am addiing to them as and when
    I need new utilities.
*/

#include <cmath>

namespace geom
{

class PolarPoint
{
public:
    PolarPoint() = default;
    PolarPoint(double r, double theta);

    void rotate(double radians);

    PolarPoint rotated(double radians) const;

    double r() const;
    double theta() const;
    void setR(double r);
    void setTheta(double theta);

private:
    double r_ = 0;
    double theta_ = 0;
};

class CartesianPoint
{
public:
    CartesianPoint() = default;
    CartesianPoint(double x, double y);

    void rotateAbout(const CartesianPoint& fulcrum, double radians);

    CartesianPoint rotatedAbout(
        const CartesianPoint& fulcrum, double radians) const;

    double x() const;
    double y() const;
    void setX(double x);
    void setY(double y);

private:
    double x_ = 0;
    double y_ = 0;
};

CartesianPoint operator+(const CartesianPoint& a, const CartesianPoint& b);

CartesianPoint operator-(const CartesianPoint& a, const CartesianPoint& b);

PolarPoint cartesianToPolar(const CartesianPoint& cartPoint);

CartesianPoint polarToCartesian(const PolarPoint& polarPoint);

double dist(const CartesianPoint& a, const CartesianPoint& b);

double distFromOrigin(const CartesianPoint& point);

};// namespace geom

#endif// POINTS_H
