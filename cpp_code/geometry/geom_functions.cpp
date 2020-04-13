#include "geom_functions.h"

#include <algorithm>
#include <cmath>
#include <exception>

#include "geom_defs.h"
#include "Point.h"

namespace geom
{

void dilate(Point& moveablePoint, const Point& anchor, double dilationFactor)
{
    auto translated = moveablePoint - anchor;
    translated *= dilationFactor;
    moveablePoint = translated + anchor;
}

Polygon geom::createSquareOfArea(double area)
{
    if (area < doublePrecisionTolerance)
        throw std::exception("Cannot create polygon of zero or negative area");
    auto c = std::sqrt(area) / 2;
    auto topRight = Point::newCartesianPoint(c, c);
    auto bottomRight = Point::newCartesianPoint(c, -c);
    auto bottomLeft = Point::newCartesianPoint(-c, -c);
    auto topLeft = Point::newCartesianPoint(-c, c);
    std::vector<Point> points = { topRight, bottomRight, bottomLeft, topLeft };
    return Polygon(points);
}

Polygon boundingRect(const std::vector<Point>& points)
{
    std::vector<double> xs;
    std::vector<double> ys;
    xs.reserve(points.size());
    ys.reserve(points.size());
    std::transform(
        points.begin(), points.end(), xs.begin(), [](const Point& point) {
            return point.x();
        });
    std::transform(
        points.begin(), points.end(), ys.begin(), [](const Point& point) {
            return point.y();
        });
    auto left = *(std::min(xs.begin(), xs.end()));
    auto right = *(std::max(xs.begin(), xs.end()));
    auto top = *(std::max(ys.begin(), ys.end()));
    auto bottom = *(std::min(xs.begin(), xs.end()));
    return Polygon(std::vector<Point>{});
}

}// namespace geom
