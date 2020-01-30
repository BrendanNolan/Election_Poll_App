#include "ConstituencyWidget.h"

#include <QGraphicsrectItem>
#include <QGraphicsScene>
#include <QItemSelectionModel>
#include <QPointF>

#include "ConstituencyModel.h"
#include "ConstituencyPixmapProxyModel.h"
#include "RectanglePositionCalculator.h"

ConstituencyWidget::ConstituencyWidget(QWidget* parent)
    : QGraphicsView(parent)
{
    setScene(new QGraphicsScene(this));
    connect(scene(), &QGraphicsScene::selectionChanged,
        this, &ConstituencyWidget::selectConstituencyInModel);
}

void ConstituencyWidget::setModel(
    ConstituencyPixmapProxyModel* constituencyModel)
{
    constituencyModel_ = constituencyModel;
    loadModel();
}

void ConstituencyWidget::setSelectionModel(QItemSelectionModel* selectionModel)
{
    constituencySelectionModel_ = selectionModel;
    selectConstituencyInModel();
}

void ConstituencyWidget::refreshSceneConstituencies()
{
    scene()->clear();
    indexItemCache_.clear();

    auto rows = constituencyModel_->rowCount();
    QMap<QGraphicsItem*, QModelIndex> roughHash;
    for (auto row = 0; row < rows; ++row)
    {
        auto index = constituencyModel_->index(row, 0);
        QPointF constituencyPosition(
            constituencyModel_->data(
                index, 
                ConstituencyModel::LongitudeRole).toInt(),
            -(constituencyModel_->data(
                index,
                ConstituencyModel::LatitudeRole).toInt()));
        auto rectItem = new QGraphicsRectItem(
            QRectF(constituencyPosition, QSizeF(10, 10)));
        rectItem->setFlag(QGraphicsItem::ItemIsSelectable);
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
    auto itemList = scene()->selectedItems();
    if (itemList.isEmpty())
        itemList = scene()->items();
    if (itemList.isEmpty())
        return;
    auto itemToSelect = itemList.first();
    if (!itemToSelect)
        return;
    auto index = indexItemCache_[itemToSelect];
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
        this, &ConstituencyWidget::refreshSceneConstituencies);
    connect(constituencyModel_, &QAbstractItemModel::rowsInserted,
        this, &ConstituencyWidget::refreshSceneConstituencies);
    connect(constituencyModel_, &QAbstractItemModel::rowsRemoved,
        this, &ConstituencyWidget::refreshSceneConstituencies);
}

void ConstituencyWidget::loadModel()
{
    if (!constituencyModel_)
        return;
    makeModelConnections();
    refreshSceneConstituencies();
    loadWidgetColours();
    selectConstituencyInModel();
}
