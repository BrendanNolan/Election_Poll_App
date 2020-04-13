#include "QtSceneCoordConverter.h"

#include <QGraphicsScene>

#include <algorithm>
#include <cmath>

#include "geom_defs.h"
#include "geom_functions.h"

using namespace geom;

QtSceneCoordConverter::QtSceneCoordConverter(double scale)
    : scale_(scale)
{
}

QPointF QtSceneCoordConverter::qPointF(const geom::Point& point) const
{
    auto scale = scale_;
    if (std::abs(scale) < geom::doublePrecisionTolerance)
        scale = 1;

    return QPointF(point.x() / scale, -(point.y() / scale));
}

geom::Point QtSceneCoordConverter::point(const QPointF& qPointF) const
{
    auto scale = scale_;
    if (std::abs(scale) < geom::doublePrecisionTolerance)
        scale = 1;

    return Point::newCartesianPoint(
        qPointF.x() * scale, -(qPointF.y() * scale));
}

void QtSceneCoordConverter::setScale(double scale)
{
    scale_ = scale;
}

void QtSceneCoordConverter::inferScale(
    const std::vector<Point>& points, const QGraphicsScene& scene)
{
    auto rectBound = boundingRect(points);

    auto widthRatio = rectBound.width() / scene.width();
    auto heightRatio = rectBound.height() / scene.height();

    scale_ = std::max(widthRatio, heightRatio);
}
