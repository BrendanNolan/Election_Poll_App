#include "RotatingItemsWidget.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>

RotatingItemsWidget::RotatingItemsWidget(QWidget* parent = nullptr)
    : QGraphicsView(parent)
{
    setScene(new QGraphicsScene());
    scene()->addItem(new QGraphicsRectItem(0, 0, 10, 10));
}
