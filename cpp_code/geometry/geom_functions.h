#ifndef GEOM_FUNCTIONS_H
#define GEOM_FUNCTIONS_H

namespace geom
{

class Point;

void dilate(Point& moveablePoint, const Point& anchor, double dilationFactor);

}// namespace geom

#endif// GEOM_FUNCTIONS_H
