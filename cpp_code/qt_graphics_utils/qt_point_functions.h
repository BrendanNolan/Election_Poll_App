#ifndef POINT_UTILS_H
#define POINT_UTILS_H

class QPointF;

namespace qt_point_functions
{
void rotateAbout(QPointF& point, const QPointF& fulcrum, double radians);

QPointF rotatedAbout(
    const QPointF& point, const QPointF& fulcrum, double radians);

float length(const QPointF& point);
}// namespace geom

#endif// POINT_UTILS_H
