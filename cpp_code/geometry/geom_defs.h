#ifndef GEOM_DEFS_H
#define GEOM_DEFS_H

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

namespace geom
{
const auto pi = 3.141;
const auto doublePrecisionTolerance = 0.000001;

using BoostCartesianPoint2D = boost::geometry::model::d2::
    point_xy<double, boost::geometry::cs::cartesian>;
using BoostPolarPoint2D = boost::geometry::model::d2::
    point_xy<double, boost::geometry::cs::spherical<boost::geometry::radian>>;
}// namespace geom

#endif// GEOM_DEFS_H
