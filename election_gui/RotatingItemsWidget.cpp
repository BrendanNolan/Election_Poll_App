#include "RotatingItemsWidget.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>

RotatingItemsWidget::RotatingItemsWidget(QWidget* parent)
    : QGraphicsView(parent)
{
    setScene(new QGraphicsScene());
    connect(&rotationTimer_, &QTimer::timeout,
        this, &RotatingItemsWidget::rotateItems);
    rotationTimer_.setInterval(milisecInterval_);
    rotationTimer_.start();
}

void RotatingItemsWidget::setRotatingItems(const QVector<QGraphicsItem*>& items)
{
    qDeleteAll(rotatingItems_);
    rotatingItems_ = items;
    if (rotatingItems_.isEmpty())
        return;

    setRadiusOfRotatingItemsCircle();

    auto itemCount = rotatingItems_.size();

    using namespace geom_utils;

    CartesianPoint startPoint(
        0.0, static_cast<double>(radiusOfRotatingItemsCircle_));
    for (auto i = 0; i < itemCount; ++i)
    {
        scene()->addItem(rotatingItems_[i]);
        auto pos = startPoint.rotatedAbout(
            CartesianPoint(0.0, 0.0),
            (i / static_cast<double>(itemCount)) * (2 * pi));
        rotatingItems_[i]->setPos(pos.x(), pos.y());
    }
}

void RotatingItemsWidget::freeze()
{
    rotationTimer_.stop();
}

void RotatingItemsWidget::unfreeze()
{
    rotationTimer_.start();
}

void RotatingItemsWidget::rotateItems()
{
    using namespace geom_utils;
    for (auto item : rotatingItems_)
    {
        auto pos = item->pos();
        CartesianPoint cartPoint(
            static_cast<double>(pos.x()), static_cast<double>(pos.y()));
        cartPoint.rotateAbout(
            CartesianPoint(0.0, 0.0),
            static_cast<double>(rotationAngle_));
        item->setPos(cartPoint.x(), cartPoint.y());
    }
}

void RotatingItemsWidget::setRadiusOfRotatingItemsCircle()
{
    radiusOfRotatingItemsCircle_ = 100.0;
}
