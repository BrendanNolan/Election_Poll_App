#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

#include "Point.h"

namespace geom
{

class Polygon
{
public:
    void inflate(double inflationFactor);

    const std::vector<Point>& points() const;
    std::vector<Point>& points();

private:
    std::vector<Point> points_;
};

Point centroid(const Polygon& polygon);
double area(const Polygon& polygon);

}

#endif// POLYGON_H
