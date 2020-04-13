#ifndef GRAPHICSITEMINFLATINGPOSITIONINGENGINE_H
#define GRAPHICSITEMINFLATINGPOSITIONINGENGINE_H

#include <vector>

#include "GraphicsItemLayoutEngine.h"
#include "Polygon.h"

class GraphicsItemInflatingPositioningEngine : public GraphicsItemLayoutEngine
{
public:
    void layout(std::vector<geom::Polygon>& polygons) override;

private:
    void reposition(geom::Polygon& rect) const;

private:
    std::vector<geom::Polygon>* polygons_;
};

#endif// GRAPHICSITEMINFLATINGPOSITIONINGENGINE_H
