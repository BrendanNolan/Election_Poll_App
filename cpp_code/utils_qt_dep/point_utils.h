#ifndef POINT_UTILS_H
#define POINT_UTILS_H

class QPointF;

namespace geom
{
void rotateAbout(QPointF& point, const QPointF& fulcrum, double radians);
QPointF rotatedAbout(const QPointF& point, const QPointF& fulcrum, double radians);
} // namespace geom

#endif // POINT_UTILS_H
