#include "PolygonFactory.h"

namespace geom
{

Polygon PolygonFactory::createRectangle(
    const Point& centre, double width, double height)
{
    auto w = width / 2;
    auto h = height / 2;
    auto topRight = Point::createCartesian(w, h);
    auto bottomRight = Point::createCartesian(w, -h);
    auto bottomLeft = Point::createCartesian(-w, -h);
    auto topLeft = Point::createCartesian(-w, h);
    auto ret = Polygon(
        std::vector<Point>{ topRight, bottomRight, bottomLeft, topLeft });
    ret.moveTo(centre);
    return ret;
}

}// namespace geom
