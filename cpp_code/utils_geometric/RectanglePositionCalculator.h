#ifndef RECTANGLEPOSITIONCALCULATOR_H
#define RECTANGLEPOSITIONCALCULATOR_H

#include <vector>

#include "IRectanglePositionCalculator.h"
#include "Rectangle.h"

class PolygonInflatingPositioningEngine : public IPolygonLayoutEngine
{
public:
    void setPositions(std::vector<Rectangle>& rectangles) override;

private:
    void reposition(Rectangle& rect) const;
    std::vector<Rectangle>* rectangles;
};

#endif// RECTANGLEPOSITIONCALCULATOR_H
