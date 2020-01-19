#ifndef CONSTITUENCYWIDGET_H
#define CONSTITUENCYWIDGET_H

#include <QGraphicsView>
#include <QHash>
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
    ConstituencyWidget(QGraphicsScene* scene, QWidget* parent = nullptr);
    explicit ConstituencyWidget(QWidget* parent = nullptr);

    void setModel(ConstituencyModel* constituencyModel);
    void setSelectionModel(QItemSelectionModel* selectionModel);
    void setScene(QGraphicsScene* scene);

signals:
    void constituencyActivated(const QModelIndex& index);

private slots:
    /* 
       Lots of constituencyModel_'s signals should be connected to this, 
       like QAbstractItemModel::rowsAdded, QAbstractItemModel::rowsRemoved,  
    */
    void loadIndexItemCache();
    void activateSelectedConstituency();

private:
    void loadWidgetColours();
    QModelIndex indexAtPoint(const QPoint& point) const;
    void makeConnections();

private:
    ConstituencyModel* constituencyModel_;
    QItemSelectionModel* constituencySelectionModel_;
    QGraphicsScene* scene_;
    QHash<QModelIndex, QGraphicsItem*> indexItemCache_;
};

#endif // CONSTITUENCYWIDGET_H
