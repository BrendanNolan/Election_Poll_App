#ifndef GRAPHICSITEMLAYOUTENGINE_H
#define GRAPHICSITEMLAYOUTENGINE_H

#include <vector>

#include "Polygon.h"

class IPolygonLayoutEngine
{
public:
    virtual ~IPolygonLayoutEngine() = default;
    virtual void layout(std::vector<geom::Polygon>& polygons) = 0;
};

#endif// GRAPHICSITEMLAYOUTENGINE_H
