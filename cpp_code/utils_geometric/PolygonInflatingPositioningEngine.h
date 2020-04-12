#ifndef POLYGONINFLATINGPOSITIONINGENGINE_H
#define POLYGONINFLATINGPOSITIONINGENGINE_H

#include <vector>

#include "IPolygonLayoutEngine.h"
#include "Polygon.h"

class PolygonInflatingPositioningEngine : public IPolygonLayoutEngine
{
public:
    void layout(std::vector<geom::Polygon>& polygons) override;

private:
    void reposition(geom::Polygon& rect) const;

private:
    std::vector<geom::Polygon>* polygons_;
};

#endif// POLYGONINFLATINGPOSITIONINGENGINE_H
