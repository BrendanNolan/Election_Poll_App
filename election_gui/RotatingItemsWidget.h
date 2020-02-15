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
    int milisecInterval_ = 500;
    qreal rotationAngle_ = (2 * geom_utils::pi) / 360;
    QVector<QGraphicsItem*> rotatingItems_;
    qreal radiusOfRotatingItemsCircle_ = 0;
};

#endif // ROTATINGITEMSWIDGET_H
