#ifndef QTSCENECOORDCONVERTER_H
#define QTSCENECOORDCONVERTER_H

#include <QPointF>

#include <vector>

#include "Point.h"

/*
    At some time, must make sure to use this class whenever we are converting
    between normal coordinates and QGraphicsScene coordinates (where the y-axis
    is inverted).
*/

class QGraphicsScene;

class QtSceneCoordConverter
{
public:
    /*
        A distance of 1 between two geom::Point objects is represented by a
        distance of 1/scale on the QGraphicsScene.

        In other words, scale is the shrinkage factor when going from a
       geom::Point to a QPointF. This will be very large if, for example, your
       QGraphicsScene is displaying a map of the world and the geom::Point
       objects represnting points on the globe are measured in milimetres.
    */
    QtSceneCoordConverter(double scale = 1);

    QPointF qPointF(const geom::Point& point) const;
    geom::Point point(const QPointF& qPointF) const;

    void setScale(double scale);
    void inferScale(
        const std::vector<geom::Point>& points, const QGraphicsScene& scene);

private:
    double scale_ = 1.0;
};

#endif// QTSCENECOORDCONVERTER_H
