#include "PolygonFactory.h"

namespace geom
{

Polygon PolygonFactory::createRectangle(
    const Point& centre, double width, double height)
{
    auto w = width / 2;
    auto h = height / 2;
    auto topRight = Point::newCartesianPoint(w, h);
    auto bottomRight = Point::newCartesianPoint(w, -h);
    auto bottomLeft = Point::newCartesianPoint(-w, -h);
    auto topLeft = Point::newCartesianPoint(-w, h);
    auto ret = Polygon(
        std::vector<Point>{ topRight, bottomRight, bottomLeft, topLeft });
    ret.moveTo(centre);
    return ret;
}

}// namespace geom
