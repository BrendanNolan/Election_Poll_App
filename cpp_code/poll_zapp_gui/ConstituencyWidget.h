#ifndef CONSTITUENCYWIDGET_H
#define CONSTITUENCYWIDGET_H

#include <QGraphicsView>
#include <QMap>
#include <QModelIndex>
#include <QVector>

#include <memory>

#include "Constituency.h"

class ConstituencyModel;
class ConstituencyColoursProxyModel;
class PoliticianModel;
class QGraphicsItem;
class QGraphicsScene;
class QItemSelection;
class QItemSelectionModel;
class QPoint;
class GraphicsItemLayoutEngine;

/*
   Should just keep a ConstituencyModel and, in
   ConstituencyWidget::setModel(), make a proxy model parented to the
   ConstituencyWidget instance.
*/

class ConstituencyWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit ConstituencyWidget(QWidget* parent = nullptr);
    ~ConstituencyWidget();

    void setModels(
        ConstituencyModel* constituencyModel, PoliticianModel* politicianModel);
    void setSelectionModel(QItemSelectionModel* selectionModel);
    void setPolygonLayoutEngine(
        std::unique_ptr<GraphicsItemLayoutEngine> polygonLayoutEngine);

private slots:
    void onSelectionChanged(const QItemSelection& selected);
    void selectConstituencyInModel();
    void loadModel();
    void refreshPixmaps(
        const QModelIndex& topLeft, const QModelIndex& bottomRight);

private:
    void loadSceneConstituencies();
    void connectModelSignals();

private:
    ConstituencyColoursProxyModel* constituencyProxyModel_ = nullptr;
    QItemSelectionModel* constituencySelectionModel_ = nullptr;
    PoliticianModel* politicianModel_;

    std::unique_ptr<GraphicsItemLayoutEngine> polygonLayoutEngine_;

    int idOfMostRecentlySelectedConstituency_ = -1;

    QMap<QGraphicsItem*, int> ItemConstituencyIds;
};

#endif// CONSTITUENCYWIDGET_H
