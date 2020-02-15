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

    CartesianPoint<qreal> startPoint(0, radiusOfRotatingItemsCircle_);
    for (size_t i = 0; i < itemCount; ++i)
    {
        scene()->addItem(rotatingItems_[i]);
        auto pos = startPoint.rotatedAbout(
            CartesianPoint<qreal>(0.0, 0.0),
            (i / itemCount) * (2 * static_cast<qreal>(pi)));
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
        CartesianPoint<qreal> cartPoint(pos.x(), pos.y());
        cartPoint.rotateAbout(
            CartesianPoint<qreal>(0, 0),
            rotationAngle_);
        item->setPos(cartPoint.x(), cartPoint.y());
    }
}

void RotatingItemsWidget::setRadiusOfRotatingItemsCircle()
{
    radiusOfRotatingItemsCircle_ = 30.0;
}
