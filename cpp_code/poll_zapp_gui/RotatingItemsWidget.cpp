#include "RotatingItemsWidget.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "Point.h"

RotatingItemsWidget::RotatingItemsWidget(QWidget* parent)
    : QGraphicsView(parent)
{
    setScene(new QGraphicsScene());
    setRotationRadius(preferredRotationRadius());
    connect(
        &rotationTimer_,
        &QTimer::timeout,
        this,
        &RotatingItemsWidget::rotateItems);
    rotationTimer_.setInterval(milisecInterval_);
    rotationTimer_.start();
}

void RotatingItemsWidget::setRotatingItems(const QVector<QGraphicsItem*>& items)
{
    qDeleteAll(rotatingItems_);
    rotatingItems_ = items;
    for (auto item : rotatingItems_) scene()->addItem(item);
    positionRotatingItems();
}

void RotatingItemsWidget::freeze()
{
    rotationTimer_.stop();
}

void RotatingItemsWidget::unfreeze()
{
    rotationTimer_.start();
}

void RotatingItemsWidget::setFrameRate(int framesPerSecond)
{
    if (framesPerSecond < 1)
        return;
    milisecInterval_ = 1000 / framesPerSecond;
}

void RotatingItemsWidget::setInterFrameAngleDifference(int degrees)
{
    degrees %= 360;
    rotationAngle_ = ((2.0 * geom::pi) / 360) * degrees;
}

void RotatingItemsWidget::rotateItems()
{
    using namespace geom;
    for (auto item : rotatingItems_)
    {
        auto pos = item->pos();
        auto point = Point::newCartesianPoint(
            static_cast<double>(pos.x()), static_cast<double>(pos.y()));
        point.rotateAbout(Point::origin(), rotationAngle_);
        item->setPos(point.x(), point.y());
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
    return 0.35 * std::min(totalWidgetSize.width(), totalWidgetSize.height());
}

void RotatingItemsWidget::positionRotatingItems()
{
    if (rotatingItems_.isEmpty())
        return;

    using namespace geom;
    auto itemCount = rotatingItems_.size();
    auto newRadius = rotationRadius_;
    auto startPoint = Point::newPolarPoint(0.0, newRadius);
    for (auto i = 0; i < itemCount; ++i)
    {
        auto item = rotatingItems_[i];

        /*auto itemAlreadyInScene = false;
        auto iter = std::find(
            scene()->items().cbegin(),
            scene()->items().cend(),
            item);
        if (iter == scene()->items().cend())
            itemAlreadyInScene = false;
        else
            itemAlreadyInScene = true;*/

        auto pos = item->pos();
        auto currentRadius = Point::newCartesianPoint(pos.x(), pos.y()).r();

        if (currentRadius != 0)
        {
            item->setPos(pos * (newRadius / currentRadius));
        }
        else
        {
            auto pos = startPoint.rotatedAbout(
                CartesianPoint(0.0, 0.0),
                (i / static_cast<double>(itemCount)) * (2 * pi));
            item->setPos(pos.x(), pos.y());
        }
    }
}