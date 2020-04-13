#ifndef GEOM_FUNCTIONS_H
#define GEOM_FUNCTIONS_H

#include <vector>

#include "Polygon.h"
#include "Rectangle.h"

namespace geom
{

class Point;

void dilate(Point& moveablePoint, const Point& anchor, double dilationFactor);
Polygon createSquareOfArea(double area);
Rectangle boundingRect(const std::vector<Point>& points);

}// namespace geom

#endif// GEOM_FUNCTIONS_H
