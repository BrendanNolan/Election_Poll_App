#ifndef ROTATINGITEMSWIDGET_H
#define ROTATINGITEMSWIDGET_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTimer>
#include <QVector>

class RotatingItemsWidget : public QGraphicsView
{
    Q_OBJECT

public:
    RotatingItemsWidget(QWidget* parent = nullptr);
    void freeze();

    void setRotatingItems(const QVector<QGraphicsItem*>& items);

private:
    QTimer sceneRotationTimer_;
    QVector<QGraphicsItem*> rotatingItems_;
};

#endif // ROTATINGITEMSWIDGET_H
