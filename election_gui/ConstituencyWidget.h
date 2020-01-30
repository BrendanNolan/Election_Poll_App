#ifndef CONSTITUENCYWIDGET_H
#define CONSTITUENCYWIDGET_H

#include <QGraphicsView>
#include <QMap>
#include <QModelIndex>
#include <QVector>

#include "Constituency.h"

class ConstituencyPixmapProxyModel;
class QGraphicsItem;
class QGraphicsScene;
class QItemSelectionModel;
class QPoint;

class ConstituencyWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit ConstituencyWidget(QWidget* parent = nullptr);

    void setModel(ConstituencyPixmapProxyModel* constituencyModel);
    void setSelectionModel(QItemSelectionModel* selectionModel);

private slots:
    void selectConstituencyInModel();
    void refreshSceneConstituencies();

private:
    void loadWidgetColours();
    void makeModelConnections();
    void loadModel();

private:
    ConstituencyPixmapProxyModel* constituencyModel_ = nullptr;
    QItemSelectionModel* constituencySelectionModel_ = nullptr;
    QMap<QGraphicsItem*, QModelIndex> indexItemCache_;
};

#endif // CONSTITUENCYWIDGET_H
