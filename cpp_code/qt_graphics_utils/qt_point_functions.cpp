#include "qt_point_functions.h"

#include <QPointF>

#include <cmath>

#include "Point.h"
#include "QtSceneCoordConverter.h"

namespace qt_point_functions
{
void rotateAbout(QPointF& point, const QPointF& fulcrum, double radians)
{
    QtSceneCoordConverter converter;
    auto p = converter.point(point);
    auto f = converter.point(fulcrum);
    p.rotateAbout(f, radians);
    point = converter.qPointF(p);
}

QPointF rotatedAbout(
    const QPointF& point, const QPointF& fulcrum, double radians)
{
    auto cpy = point;
    rotateAbout(cpy, fulcrum, radians);
    return cpy;
}

float length(const QPointF& point)
{
    return std::sqrt(std::pow(point.x(), 2) + std::pow(point.y(), 2));
}
}// namespace qt_point_functions
