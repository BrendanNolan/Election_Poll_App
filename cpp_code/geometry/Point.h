#ifndef POINT_H
#define POINT_H

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
    static Point newCartesianPoint(double x, double y);
    static Point newPolarPoint(double r, double theta);
    static Point origin();

    bool operator==(const Point& other) const;

    void rotateAbout(const Point& fulcrum, double radians);
    Point rotatedAbout(const Point& fulcrum, double radians) const;
    void normalise();

    void setPolarCoords(double r, double theta);
    void setCartesianCoords(double x, double y);

    void operator*=(double scalar);
    void operator/=(double scalar);

    double x() const;
    double y() const;
    double r() const;
    double theta() const;

private:
    void rotateAboutOrigin(double radians);
    Point rotatedAboutOrigin(double radians) const;

private:
    double x_ = 0;
    double y_ = 0;
};

Point operator+(const Point& a, const Point& b);
Point operator-(const Point& a, const Point& b);
double dist(const Point& a, const Point& b);
double norm(const Point& point);
Quadrant quadrant(const Point& point);

};// namespace geom

#endif// POINT_H
