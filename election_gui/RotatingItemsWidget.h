#ifndef ROTATINGITEMSWIDGET_H
#define ROTATINGITEMSWIDGET_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QSize>
#include <QTimer>
#include <QVector>

#include "election_gui_utils.h"

class RotatingItemsWidget : public QGraphicsView
{
    Q_OBJECT

public:
    RotatingItemsWidget(QWidget* parent = nullptr);

    void setRotatingItems(const QVector<QGraphicsItem*>& items);
    void setRotationRadius(double radius);
    void setSizeForRotatingItems(const QSize& size);

    void freeze();
    void unfreeze();

public slots:
    void rotateItems();

private:
    double calculateSensibleRadiusForRotatingItemsCircle();
    QSize calculateSensibleSizeForRotatingItems();

private:
    QTimer rotationTimer_;
    int milisecInterval_ = 250;

    double rotationAngle_ = (2.0 * geom_utils::pi) / 10.0;

    QVector<QGraphicsItem*> rotatingItems_;
};

#endif // ROTATINGITEMSWIDGET_H
