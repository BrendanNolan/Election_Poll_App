#include "point_utils.h"

#include <QPointF>

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
}// namespace geom
