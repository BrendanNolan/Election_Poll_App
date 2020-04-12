#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

#include "Point.h"

namespace geom
{

class Polygon
{
public:
    geom::Point centroid() const;
    void inflate(double inflationFactor);

private:
    std::vector<geom::Point> points_;
};

}

#endif// POLYGON_H
