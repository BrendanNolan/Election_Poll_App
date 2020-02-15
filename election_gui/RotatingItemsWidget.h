#ifndef ROTATINGITEMSWIDGET_H
#define ROTATINGITEMSWIDGET_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTimer>
#include <QVector>

#include "election_gui_utils.h"

class RotatingItemsWidget : public QGraphicsView
{
    Q_OBJECT

public:
    RotatingItemsWidget(QWidget* parent = nullptr);

    void setRotatingItems(const QVector<QGraphicsItem*>& items);

    void freeze();
    void unfreeze();

public slots:
    void rotateItems();

private:
    void setRadiusOfRotatingItemsCircle(); // Needs proper implentation.

private:
    QTimer rotationTimer_;
    int milisecInterval_ = 250;
    double rotationAngle_ = -(2.0 * geom_utils::pi) / 10.0;
    QVector<QGraphicsItem*> rotatingItems_;
    double radiusOfRotatingItemsCircle_ = 0.0;
};

#endif // ROTATINGITEMSWIDGET_H
