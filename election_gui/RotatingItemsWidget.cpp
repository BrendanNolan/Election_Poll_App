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

    for (auto item : rotatingItems_)
        scene()->addItem(item);
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
            rotationAngle_);
        item->setPos(cartPoint.x(), cartPoint.y());
    }
}

void RotatingItemsWidget::setRotationRadius(double radius)
{
    rotationRadius_ = radius;
    positionRotatingItems();
}

double RotatingItemsWidget::preferredRotationRadius() const
{
    auto totalWidgetSize = size();
    return 0.45 * std::min(
        totalWidgetSize.width(), totalWidgetSize.height());
}

void RotatingItemsWidget::positionRotatingItems()
{
    using namespace geom_utils;
    auto itemCount = rotatingItems_.size();
    auto newRadius = rotationRadius_;
    CartesianPoint startPoint(0.0, newRadius);
    for (auto i = 0; i < itemCount; ++i)
    {
        auto item = rotatingItems_[i];
        auto itemAlreadyInScene = false;
        auto iter = std::find(
            scene()->items().cbegin(),
            scene()->items().cend(),
            item);
        if (iter == scene()->items().cend())
            itemAlreadyInScene = false;
        else
            itemAlreadyInScene = true;

        if (itemAlreadyInScene)
        {
            auto pos = item->pos();
            auto currentRadius = distFromOrigin(pos);
            item->setPos(pos * newRadius / currentRadius);
        }
        else
        {

        }

        scene()->addItem(rotatingItems_[i]);
        auto pos = startPoint.rotatedAbout(
            CartesianPoint(0.0, 0.0),
            (i / static_cast<double>(itemCount)) * (2 * pi));
        rotatingItems_[i]->setPos(pos.x(), pos.y());
    }
}
