#ifndef RECTANGLEPOSITIONCALCULATOR_H
#define RECTANGLEPOSITIONCALCULATOR_H

// May be possible to use a forward declaration rather than including QRect and 
// QVector
#include <QRect>
#include <QVector>

class RectanglePositionCalculator
{
public:
    RectanglePositionCalculator(const QVector<QRect>& rectangles);
    QRect reposition(const QRect& rect) const; // Should return a copy of its argument if it is passed a QRct that was not in its initialising QVector of QRects
};

#endif // RECTANGLEPOSITIONCALCULATOR_H
