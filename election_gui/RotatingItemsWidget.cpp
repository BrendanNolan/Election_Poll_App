#include "RotatingItemsWidget.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>

RotatingItemsWidget::RotatingItemsWidget(QWidget* parent)
    : QGraphicsView(parent)
{
    setScene(new QGraphicsScene());
    scene()->addItem(new QGraphicsRectItem(0, 0, 10, 10));
}

void RotatingItemsWidget::freeze()
{
    sceneRotationTimer_.stop();
}
