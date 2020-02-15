#include "RotatingItemsWidget.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>

RotatingItemsWidget::RotatingItemsWidget(QWidget* parent)
    : QGraphicsView(parent)
{
    setScene(new QGraphicsScene());
}

void RotatingItemsWidget::freeze()
{
    sceneRotationTimer_.stop();
}

void RotatingItemsWidget::setRotatingItems(const QVector<QGraphicsItem*>& items)
{
    scene()->clear();
    rotatingItems_ = items;
    auto itemCount = items.size();
    for (auto item : items)
    {
        scene()->addItem(item);
    }
    for (auto i = 0; i < itemCount; ++i)
    {

    }
}
