#ifndef QT_POINT_FUNCTIONS_H
#define QT_POINT_FUNCTIONS_H

class QPointF;

namespace qt_point_functions
{
void rotateAbout(QPointF& point, const QPointF& fulcrum, double radians);

QPointF rotatedAbout(
    const QPointF& point, const QPointF& fulcrum, double radians);

float length(const QPointF& point);
}// namespace geom

#endif// QT_POINT_FUNCTIONS_H
