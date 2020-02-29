#ifndef CONSTITUENCYWIDGET_H
#define CONSTITUENCYWIDGET_H

#include <QGraphicsView>
#include <QMap>
#include <QModelIndex>
#include <QVector>

#include "Constituency.h"

class PixmapCreatingProxyModel;
class QGraphicsItem;
class QGraphicsScene;
class QItemSelectionModel;
class QPoint;

/*
    Should just keep a ConstituencyModel and, in ConstituencyWidget::setModel(),
    make a proxy model parented to the ConstituencyWidget instance.
*/

class ConstituencyWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit ConstituencyWidget(QWidget* parent = nullptr);

    void setModel(PixmapCreatingProxyModel* constituencyModel);
    void setSelectionModel(QItemSelectionModel* selectionModel);

private slots:
    void selectConstituencyInModel();
    void loadModel();
    void refreshPixmaps(
        const QModelIndex& topLeft, const QModelIndex& bottomRight);

private:
    void loadSceneConstituencies();
    void connectModelSignals();

private:
    PixmapCreatingProxyModel* constituencyModel_ = nullptr;
    QItemSelectionModel* constituencySelectionModel_ = nullptr;
    QMap<QGraphicsItem*, QModelIndex> indexItemCache_;
};

#endif// CONSTITUENCYWIDGET_H
