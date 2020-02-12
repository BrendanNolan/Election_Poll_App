#ifndef ROTATINGITEMSWIDGET_H
#define ROTATINGITEMSWIDGET_H

#include <QGraphicsView>
#include <QTimer>

class RotatingItemsWidget : public QGraphicsView
{
    Q_OBJECT

public:
    RotatingItemsWidget(QWidget* parent = nullptr);
    void freeze();

private:
    QTimer sceneRotationTimer_;
};

#endif // ROTATINGITEMSWIDGET_H
