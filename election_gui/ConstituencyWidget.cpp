#include "ConstituencyWidget.h"

#include <QGraphicsPixmapItem>
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
        scene()->addItem(pixmapItem);
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
