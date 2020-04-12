#include "Polygon.h"

#include <algorithm>

using namespace std;

namespace geom
{

Point Polygon::centroid() const
{
    auto n = points_.size();
    if (n == 0)
        return Point::newCartesianPoint(0.0, 0.0);

    vector<double> x;
    x.reserve(n);
    std::transform(
        points_.begin(), points_.end(), x.begin(), [](const Point& point) {
            return point.x();
        });

    vector<double> y;
    y.reserve(n);
    std::transform(
        points_.begin(), points_.end(), y.begin(), [](const Point& point) {
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

    return Point::newCartesianPoint(cx, cy);
}

void Polygon::inflate(double inflationFactor)
{
}

}// namespace geom
