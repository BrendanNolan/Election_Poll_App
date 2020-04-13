#ifndef GRAPHICSITEMINFLATINGPOSITIONINGENGINE_H
#define GRAPHICSITEMINFLATINGPOSITIONINGENGINE_H

#include "GraphicsItemLayoutEngine.h"

class GraphicsItemInflatingPositioningEngine : public GraphicsItemLayoutEngine
{
public:
    void layout(QVector<QGraphicsItem>& items) override;

private:
    void reposition(QGraphicsItem& item) const;

private:
    QVector<QGraphicsItem>* items_;
};

#endif// GRAPHICSITEMINFLATINGPOSITIONINGENGINE_H
