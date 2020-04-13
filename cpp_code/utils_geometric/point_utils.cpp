#include "point_utils.h"

#include <QPointF>

#include <cmath>

#include "Point.h"
#include "QtSceneCoordConverter.h"

namespace geom
{
void rotateAbout(QPointF& point, const QPointF& fulcrum, double radians)
{
    QtSceneCoordConverter converter;
    auto p = converter.point(point);
    auto f = converter.point(fulcrum);
    p.rotateAbout(f, radians);
    point = converter.qPointF(p);
}

QPointF geom::rotatedAbout(
    const QPointF& point, const QPointF& fulcrum, double radians)
{
    auto cpy = point;
    rotateAbout(cpy, fulcrum, radians);
    return cpy;
}

float geom::length(const QPointF& point)
{
    return std::sqrt(std::pow(point.x(), 2) + std::pow(point.y(), 2));
}
}// namespace geom
