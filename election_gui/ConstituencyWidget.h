#ifndef CONSTITUENCYWIDGET_H
#define CONSTITUENCYWIDGET_H

#include <QGraphicsView>
#include <QMap>
#include <QModelIndex>
#include <QRect>
#include <QVector>

#include "Constituency.h"

class ConstituencyModel;
class QGraphicsItem;
class QGraphicsScene;
class QItemSelectionModel;
class QPoint;
class QRect;

class ConstituencyWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit ConstituencyWidget(QWidget* parent = nullptr);

    void setModel(ConstituencyModel* constituencyModel);
    void setSelectionModel(QItemSelectionModel* selectionModel);

private slots:
    void selectConstituencyInModel();
    void setSceneConstituencies();

private:
    void loadWidgetColours();
    void makeModelConnections();
    void loadModel();

private:
    ConstituencyModel* constituencyModel_ = nullptr;
    QItemSelectionModel* constituencySelectionModel_ = nullptr;
    QMap<QGraphicsItem*, QModelIndex> indexItemCache_;
};

#endif // CONSTITUENCYWIDGET_H
