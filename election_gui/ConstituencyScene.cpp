#include "ConstituencyScene.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QItemSelectionModel>
#include <QPointF>

#include "ConstituencyModel.h"
#include "ConstituencyPixmapProxyModel.h"
#include "RectanglePositionCalculator.h"

ConstituencyScene::ConstituencyScene(QObject* parent)
    : QGraphicsScene(parent)
{
    connect(this, &QGraphicsScene::selectionChanged,
        this, &ConstituencyScene::selectConstituencyInModel);
}

void ConstituencyScene::setModel(
    ConstituencyPixmapProxyModel* constituencyModel)
{
    constituencyModel_ = constituencyModel;
    loadModel();
}

void ConstituencyScene::setSelectionModel(QItemSelectionModel* selectionModel)
{
    constituencySelectionModel_ = selectionModel;
    selectConstituencyInModel();
}

void ConstituencyScene::refreshSceneConstituencies()
{
    clear();
    indexItemCache_.clear();

    auto rows = constituencyModel_->rowCount();
    QMap<QGraphicsItem*, QModelIndex> roughMap;
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
        auto pixmapItem = new QGraphicsPixmapItem(
            constituencyModel_->data(index, Qt::DisplayRole).value<QPixmap>().
                scaled(20, 20, Qt::KeepAspectRatio));
        pixmapItem->setFlag(QGraphicsItem::ItemIsSelectable);
        addItem(pixmapItem);
        pixmapItem->setPos(constituencyPosition);
        roughMap[pixmapItem] = index;
    }
    /*
        The following line is temporary. Eventually a 
        RectanglePositionCalculator will calculate new sizes and positions
        for the QPixmapItems.
    */
    indexItemCache_ = roughMap;
}

void ConstituencyScene::selectConstituencyInModel()
{
    if (!constituencySelectionModel_)
        return;
    auto itemList = selectedItems();
    if (itemList.isEmpty())
        itemList = items();
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

void ConstituencyScene::makeModelConnections()
{
    connect(constituencyModel_, &QAbstractItemModel::modelReset,
        this, &ConstituencyScene::refreshSceneConstituencies);
    connect(constituencyModel_, &QAbstractItemModel::rowsInserted,
        this, &ConstituencyScene::refreshSceneConstituencies);
    connect(constituencyModel_, &QAbstractItemModel::rowsRemoved,
        this, &ConstituencyScene::refreshSceneConstituencies);
}

void ConstituencyScene::loadModel()
{
    if (!constituencyModel_)
        return;
    makeModelConnections();
    refreshSceneConstituencies();
    selectConstituencyInModel();
}
