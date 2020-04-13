#include "geom_functions.h"

#include "Point.h"

namespace geom
{

void dilate(Point& moveablePoint, const Point& anchor, double dilationFactor)
{
    auto translated = moveablePoint - anchor;
    translated *= dilationFactor;
    moveablePoint = translated + anchor;
}

}// namespace geom
