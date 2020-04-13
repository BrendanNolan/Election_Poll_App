#ifndef POLYGONFACTORY_H
#define POLYGONFACTORY_H

#include "Point.h"
#include "Polygon.h"

namespace geom
{

class PolygonFactory
{
public:
    Polygon createRectangle(const Point& centre, double width, double height);
};

}// namespace geom

#endif// POLYGONFACTORY_H
