#include "ConstituencyWidget.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QItemSelectionModel>
#include <QPointF>
#include <QVector>

#include <algorithm>

#include "ConstituencyModel.h"
#include "ConstituencyPixmapCreatingFunctor.h"
#include "PixmapCreatingProxyModel.h"
#include "RectanglePositionCalculator.h"

ConstituencyWidget::ConstituencyWidget(QWidget* parent)
    : QGraphicsView(parent)
{
    setScene(new QGraphicsScene(this));
    connect(scene(),
        &QGraphicsScene::selectionChanged,
        this,
        &ConstituencyWidget::selectConstituencyInModel);
}

void ConstituencyWidget::setModels(
    ConstituencyModel* constituencyModel, PoliticianModel* politicianModel)
{
    politicianModel_ = politicianModel;
    constituencyProxyModel_ = new PixmapCreatingProxyModel(
        std::unique_ptr<PixmapCreatingFunctor>(
            new ConstituencyPixmapCreatingFunctor(
                constituencyModel, *politicianModel_)),
        constituencyModel,
        this);
    connectModelSignals();
    loadModel();
}

void ConstituencyWidget::setSelectionModel(QItemSelectionModel* selectionModel)
{
    constituencySelectionModel_ = selectionModel;
    connect(constituencySelectionModel_,
        &QItemSelectionModel::selectionChanged,
        [this](const QItemSelection& selected) {});
    selectConstituencyInModel();
}

void ConstituencyWidget::loadSceneConstituencies()
{
    scene()->clear();
    indexItemCache_.clear();

    auto rows = constituencyProxyModel_->rowCount();
    QMap<QGraphicsItem*, QModelIndex> roughMap;
    for (auto row = 0; row < rows; ++row)
    {
        auto index = constituencyProxyModel_->index(row, 0);
        QPointF constituencyPosition(
            constituencyProxyModel_
                ->data(index, ConstituencyModel::LongitudeRole)
                .toInt(),
            -(constituencyProxyModel_
                    ->data(index, ConstituencyModel::LatitudeRole)
                    .toInt()));
        auto pixmapItem = new QGraphicsPixmapItem(
            constituencyProxyModel_->data(index, Qt::DecorationRole)
                .value<QPixmap>()
                .scaled(20, 20, Qt::KeepAspectRatio));
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
        index, QItemSelectionModel::ClearAndSelect);
}

void ConstituencyWidget::loadModel()
{
    if (!constituencyProxyModel_)
        return;
    loadSceneConstituencies();
    selectConstituencyInModel();
}

void ConstituencyWidget::connectModelSignals()
{
    // Need to make a similar connection for QAbstractItemModel::dataChanged()
    // as the one below for &QAbstractItemModel::modelReset().
    connect(politicianModel_,
        &QAbstractItemModel::modelReset,
        constituencyProxyModel_,
        &PixmapCreatingProxyModel::reloadCache);
    connect(constituencyProxyModel_,
        &QAbstractItemModel::modelReset,
        this,
        &ConstituencyWidget::loadModel);
    connect(constituencyProxyModel_,
        &QAbstractItemModel::rowsInserted,
        this,
        &ConstituencyWidget::loadModel);
    connect(constituencyProxyModel_,
        &QAbstractItemModel::rowsRemoved,
        this,
        &ConstituencyWidget::loadModel);
    connect(constituencyProxyModel_,
        &QAbstractItemModel::dataChanged,
        this,
        &ConstituencyWidget::refreshPixmaps);
}

void ConstituencyWidget::refreshPixmaps(
    const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
    for (auto it = indexItemCache_.begin(); it != indexItemCache_.end(); ++it)
    {
        if (it.value().row() < topLeft.row()
            || it.value().row() > bottomRight.row())
            continue;
        if (auto pixmapItem =
                qgraphicsitem_cast<QGraphicsPixmapItem*>(it.key()))
        {
            pixmapItem->setPixmap(
                constituencyProxyModel_->data(it.value(), Qt::DecorationRole)
                    .value<QPixmap>());
        }
    }
}
