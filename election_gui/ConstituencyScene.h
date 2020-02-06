#ifndef CONSTITUENCYSCENE_H
#define CONSTITUENCYSCENE_H

#include <QGraphicsScene>
#include <QMap>
#include <QModelIndex>
#include <QVector>

#include "Constituency.h"

class ConstituencyPixmapProxyModel;
class QGraphicsItem;
class QItemSelectionModel;
class QPoint;

class ConstituencyScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit ConstituencyScene(QObject* parent = nullptr);

    void setModel(ConstituencyPixmapProxyModel* constituencyModel);
    void setSelectionModel(QItemSelectionModel* selectionModel);

private slots:
    void selectConstituencyInModel();
    void refreshSceneConstituencies();

private:
    void makeModelConnections();
    void loadModel();

private:
    ConstituencyPixmapProxyModel* constituencyModel_ = nullptr;
    QItemSelectionModel* constituencySelectionModel_ = nullptr;
    QMap<QGraphicsItem*, QModelIndex> indexItemCache_;
};

#endif // CONSTITUENCYSCENE_H
