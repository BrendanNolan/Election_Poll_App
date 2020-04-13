#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

#include "Point.h"

namespace geom
{

class Polygon
{
public:
    Polygon(const std::vector<Point>& points);
    
    void inflate(double inflationFactor);
    void moveTo(const Point& toPoint);

    const std::vector<Point>& points() const;
    std::vector<Point>& points();

private:
    std::vector<Point> points_;
};

Point centroid(const Polygon& polygon);
double area(const Polygon& polygon);

}// namespace geom

#endif// POLYGON_H
