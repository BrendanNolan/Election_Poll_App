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
    void activateSelectedConstituency();
    void setSceneConstituencies();

private:
    void loadWidgetColours();
    void makeModelConnections();
    void loadModel();

private:
    ConstituencyModel* constituencyModel_;
    QItemSelectionModel* constituencySelectionModel_;
    QGraphicsScene* scene_;
    QHash<QGraphicsItem*, QModelIndex> indexItemCache_;
};

#endif // CONSTITUENCYWIDGET_H
