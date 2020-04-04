#ifndef RECTANGLEPOSITIONCALCULATOR_H
#define RECTANGLEPOSITIONCALCULATOR_H

#include <vector>

#include "Rectangle.h"

class RectanglePositionCalculator
{
public:
    void setPositions(std::vector<Rectangle>& rectangles);

private:
    void reposition(Rectangle& rect) const;
    std::vector<Rectangle>* rectangles;
};

#endif// RECTANGLEPOSITIONCALCULATOR_H
