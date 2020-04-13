#ifndef GRAPHICSITEMLAYOUTENGINE_H
#define GRAPHICSITEMLAYOUTENGINE_H

#include <vector>

#include "Polygon.h"

class GraphicsItemLayoutEngine
{
public:
    virtual ~GraphicsItemLayoutEngine() = default;
    virtual void layout(std::vector<geom::Polygon>& polygons) = 0;
};

#endif// GRAPHICSITEMLAYOUTENGINE_H
