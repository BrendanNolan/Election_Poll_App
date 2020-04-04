#ifndef IRECTANGLEPOSITIONCALCULATOR_H
#define IRECTANGLEPOSITIONCALCULATOR_H

#include <vector>

#include "Rectangle.h"

class IPolygonLayoutEngine
{
public:
    virtual void setPositions(std::vector<Rectangle>& rectangles) = 0;
};

#endif// IRECTANGLEPOSITIONCALCULATOR_H
