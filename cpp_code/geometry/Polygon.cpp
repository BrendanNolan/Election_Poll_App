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

int Polygon::edgeCount() const
{
    return static_cast<int>(points_.size());
}

Point centroid(const Polygon& polygon)
{
    auto n = polygon.edgeCount();
    if (n == 0)
        return Point::createCartesian(0.0, 0.0);

    auto x = xCoords(polygon);
    auto y = yCoords(polygon);

    auto signedArea = 0.0;
    for (auto i = 0; i < n; ++i)
        signedArea += x[i] * y[(i + 1) % n] - x[(i + 1) % n] * y[i];
    signedArea *= 0.5;

    auto cx = 0.0;
    for (auto i = 0; i < n; ++i)
    {
        cx += (x[i] + x[(i + 1) % n])
              * (x[i] * y[(i + 1) % n] - x[(i + 1) % n] * y[i]);
    }
    cx *= (1.0 / 6.0);

    auto cy = 0.0;
    for (auto i = 0; i < n; ++i)
    {
        cy += (y[i] + y[(i + 1) % n])
              * (x[i] * y[(i + 1) % n] - x[(i + 1) % n] * y[i]);
    }
    cx *= (1.0 / 6.0);

    return Point::createCartesian(cx, cy);
}

double width(const Polygon& polygon)
{
    if (polygon.edgeCount() < 1)
        return 0;

    auto xs = xCoords(polygon);
    std::sort(xs.begin(), xs.end());

    return std::abs(xs.back() - xs.front());
}

double height(const Polygon& polygon)
{
    if (polygon.edgeCount() < 1)
        return 0;

    auto ys = yCoords(polygon);
    std::sort(ys.begin(), ys.end());

    return std::abs(ys.back() - ys.front());
}

vector<double> xCoords(const Polygon& polygon)
{
    vector<double> x;
    auto points = polygon.points();
    std::transform(
        points.begin(),
        points.end(),
        std::back_inserter(x),
        [](const Point& point) { return point.x(); });
    return x;
}

vector<double> yCoords(const Polygon& polygon)
{
    vector<double> y;
    auto points = polygon.points();
    std::transform(
        points.begin(),
        points.end(),
        std::back_inserter(y),
        [](const Point& point) { return point.y(); });
    return y;
}

}// namespace geom
