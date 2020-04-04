#ifndef IPOLYGONLAYOUTENGINE_H
#define IPOLYGONLAYOUTENGINE_H

#include <vector>

#include "Polygon.h"

class IPolygonLayoutEngine
{
public:
    virtual void layout(std::vector<Polygon>& polygons) = 0;
};

#endif// IPOLYGONLAYOUTENGINE_H
