#include "ConstituencyWidget.h"

#include <QGraphicsrectItem>
#include <QGraphicsScene>
#include <QItemSelectionModel>
#include <QPointF>

#include "ConstituencyModel.h"
#include "RectanglePositionCalculator.h"

ConstituencyWidget::ConstituencyWidget(
    QGraphicsScene* theScene, 
    QWidget* parent)
    : QGraphicsView(theScene, parent)
{
    connect(scene(), &QGraphicsScene::selectionChanged,
        this, &ConstituencyWidget::selectConstituencyInModel);
}

ConstituencyWidget::ConstituencyWidget(QWidget* parent)
    : QGraphicsView(parent)
{
    connect(scene(), &QGraphicsScene::selectionChanged,
        this, &ConstituencyWidget::selectConstituencyInModel);
}

void ConstituencyWidget::setModel(ConstituencyModel* constituencyModel)
{
    constituencyModel_ = constituencyModel;
    loadModel();
}

void ConstituencyWidget::setSelectionModel(QItemSelectionModel* selectionModel)
{
    constituencySelectionModel_ = selectionModel;
    selectConstituencyInModel();
}

void ConstituencyWidget::setScene(QGraphicsScene* scene)
{
    QGraphicsView::setScene(scene);
    connect(scene, &QGraphicsScene::selectionChanged,
        this, &ConstituencyWidget::selectConstituencyInModel);
}

void ConstituencyWidget::setSceneConstituencies()
{
    scene()->clear();
    indexItemCache_.clear();

    auto rows = constituencyModel_->rowCount();
    QHash<QGraphicsItem*, QModelIndex> roughHash;
    for (auto row = 0; row < rows; ++row)
    {
        auto index = constituencyModel_->index(row);
        QPointF constituencyPosition(
            constituencyModel_->data(
                index, 
                ConstituencyModel::LongitudeRole).toInt(),
            constituencyModel_->data(
                index,
                ConstituencyModel::LatitudeRole).toInt());
        auto rectItem = new QGraphicsRectItem(
            QRectF(constituencyPosition, QSizeF(10, 10)));
        scene()->addItem(rectItem);
        roughHash[rectItem] = index;
    }
    /*
        The following line is temporary. Eventually a 
        RectanglePositionCalculator will calculate new sizes and positions
        for the QRectItems.
    */
    indexItemCache_ = roughHash;
}

void ConstituencyWidget::selectConstituencyInModel()
{
    if (!constituencySelectionModel_)
        return;
    auto selectedItem = scene()->selectedItems().first();
    if (!selectedItem)
        selectedItem = scene()->items().first();
    auto index = indexItemCache_[selectedItem];
    if (!index.isValid())
        return;
    constituencySelectionModel_->select(
        index, 
        QItemSelectionModel::ClearAndSelect);
}

void ConstituencyWidget::loadWidgetColours()
{
    // NEEDS TO BE IMPLEMENTED
}

void ConstituencyWidget::makeModelConnections()
{
    connect(constituencyModel_, &QAbstractItemModel::modelReset,
        this, &ConstituencyWidget::setSceneConstituencies);
    connect(constituencyModel_, &QAbstractItemModel::rowsInserted,
        this, &ConstituencyWidget::setSceneConstituencies);
    connect(constituencyModel_, &QAbstractItemModel::rowsRemoved,
        this, &ConstituencyWidget::setSceneConstituencies);
}

void ConstituencyWidget::loadModel()
{
    if (!constituencyModel_)
        return;
    makeModelConnections();
    setSceneConstituencies();
    loadWidgetColours();
    selectConstituencyInModel();
}
