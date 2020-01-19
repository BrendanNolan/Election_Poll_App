#ifndef CONSTITUENCYWIDGET_H
#define CONSTITUENCYWIDGET_H

#include <QGraphicsView>
#include <QHash>
#include <QModelIndex>
#include <QRect>
#include <QVector>

#include "Constituency.h"

class ConstituencyModel;
class ConstituencyScene;
class QGraphicsItem;
class QGraphicsScene;
class QItemSelectionModel;
class QPoint;
class QRect;

class ConstituencyWidget : public QGraphicsView
{
    Q_OBJECT

public:
    ConstituencyWidget(ConstituencyScene* scene, QWidget* parent = nullptr);
    explicit ConstituencyWidget(QWidget* parent = nullptr);

    void setModel(ConstituencyModel* constituencyModel);
    void setSelectionModel(QItemSelectionModel* selectionModel);
    void setScene(ConstituencyScene* scene);

signals:
    void constituencyActivated(const QModelIndex& index);

private slots:
    void loadIndexRectCache(); // Lots of constituencyModel_'s signals should be connected to this, like QAbstractItemModel::rowsAdded, QAbstractItemModel::rowsRemoved,  
    void onSceneItemActivated(QGraphicsItem* item);

private:
    void loadWidgetColours();
    QModelIndex indexAtPoint(const QPoint& point) const;
    void makeConnections();

private:
    ConstituencyModel* constituencyModel_;
    QItemSelectionModel* constituencySelectionModel_;
    ConstituencyScene* constituencyScene_;
    QHash<QModelIndex, QGraphicsItem*> indexItemCache_;
};

#endif // CONSTITUENCYWIDGET_H
