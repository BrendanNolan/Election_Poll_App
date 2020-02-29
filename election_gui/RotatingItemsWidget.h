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
    double preferredRotationRadius() const;

    void freeze();
    void unfreeze();

    void setFrameRate(int framesPerSecond);
    void setInterFrameAngleDifference(int degrees);

public slots:
    void rotateItems();

private:
    void positionRotatingItems();

private:
    QTimer rotationTimer_;
    int milisecInterval_ = 250;

    double rotationAngle_ = (2.0 * geom_utils::pi) / 10.0;
    double rotationRadius_ = 0.0;

    QVector<QGraphicsItem*> rotatingItems_;
};

#endif// ROTATINGITEMSWIDGET_H
