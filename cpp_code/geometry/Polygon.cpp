#include "Polygon.h"

#include <algorithm>

#include "geom_functions.h"

using namespace std;

namespace geom
{

Polygon::Polygon(const std::vector<Point>& points)
    : points_(points)
{
}

void Polygon::inflate(double inflationFactor)
{
    auto theCentroid = centroid(*this);
    auto& thePoints = points();
    for (auto& point : thePoints)
        dilate(point, theCentroid, inflationFactor);
}

void Polygon::moveTo(const Point& toPoint)
{
    auto translationVec = toPoint - centroid(*this);
    for (auto& point : points_)
        point += translationVec;
}

void geom::Polygon::translate(const Point& translationPoint)
{
    auto newCentroid = centroid(*this) + translationPoint;
    moveTo(newCentroid);
}

const vector<Point>& Polygon::points() const
{
    return points_;
}

vector<Point>& Polygon::points()
{
    return points_;
}

void Polygon::setPoints(const std::vector<Point>& points)
{
    points_ = points;
}

bool Polygon::isValid() const
{
    return points_.size() > 2;// also should check that not all points collinear
}

Point centroid(const Polygon& polygon)
{
    const auto& points = polygon.points();
    auto n = points.size();
    if (n == 0)
        return Point::createCartesian(0.0, 0.0);

    vector<double> x;
    x.reserve(n);
    std::transform(
        points.begin(), points.end(), x.begin(), [](const Point& point) {
            return point.x();
        });

    vector<double> y;
    y.reserve(n);
    std::transform(
        points.begin(), points.end(), y.begin(), [](const Point& point) {
            return point.y();
        });

    auto signedArea = 0.0;
    for (size_t i = 0; i < n; ++i)
        signedArea += x[i] * y[(i + 1) % n] - x[(i + 1) % n] * y[i];
    signedArea *= 0.5;

    auto cx = 0.0;
    for (size_t i = 0; i < n; ++i)
    {
        cx += (x[i] + x[(i + 1) % n])
              * (x[i] * y[(i + 1) % n] - x[(i + 1) % n] * y[i]);
    }
    cx *= (1.0 / 6.0);

    auto cy = 0.0;
    for (size_t i = 0; i < n; ++i)
    {
        cy += (y[i] + y[(i + 1) % n])
              * (x[i] * y[(i + 1) % n] - x[(i + 1) % n] * y[i]);
    }
    cx *= (1.0 / 6.0);

    return Point::createCartesian(cx, cy);
}

}// namespace geom
