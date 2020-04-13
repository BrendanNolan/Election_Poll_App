#ifndef GRAPHICSITEMLAYOUTENGINE_H
#define GRAPHICSITEMLAYOUTENGINE_H

#include <QGraphicsItem>
#include <QVector>

class GraphicsItemLayoutEngine
{
public:
    virtual ~GraphicsItemLayoutEngine() = default;
    virtual void layout(QVector<QGraphicsItem>& items) = 0;
};

#endif// GRAPHICSITEMLAYOUTENGINE_H
