#include "ConstituencyWidget.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QPointF>
#include <QVector>

#include <algorithm>

#include "ConstituencyModel.h"
#include "ConstituencyColoursProxyModel.h "
#include "poll_zapp_core_utils.h"
#include "geom_functions.h"
#include "GraphicsItemLayoutEngine.h"
#include "GraphicsItemInflatingPositioningEngine.h"
#include "Point.h"
#include "Polygon.h"

ConstituencyWidget::ConstituencyWidget(QWidget* parent)
    : QGraphicsView(parent)
{
    setScene(new QGraphicsScene(this));
    connect(
        scene(),
        &QGraphicsScene::selectionChanged,
        this,
        &ConstituencyWidget::selectConstituencyInModel);
}

ConstituencyWidget::~ConstituencyWidget()
{
}

void ConstituencyWidget::setModels(
    ConstituencyModel* constituencyModel, PoliticianModel* politicianModel)
{
    if (!constituencyModel || !politicianModel)
    {
        constituencyProxyModel_ = nullptr;
        politicianModel_ = nullptr;
        constituencySelectionModel_ = nullptr;
    }
    politicianModel_ = politicianModel;
    constituencyProxyModel_ = new ConstituencyColoursProxyModel(
        constituencyModel, *politicianModel_, this);
    connectModelSignals();
    loadModel();
}

void ConstituencyWidget::setSelectionModel(QItemSelectionModel* selectionModel)
{
    constituencySelectionModel_ = selectionModel;
    connect(
        constituencySelectionModel_,
        &QItemSelectionModel::selectionChanged,
        this,
        &ConstituencyWidget::onSelectionChanged);
    selectConstituencyInModel();
}

void ConstituencyWidget::setPolygonLayoutEngine(
    std::unique_ptr<GraphicsItemLayoutEngine> graphicsItemLayoutEngine)
{
    graphicsItemLayoutEngine_ = std::move(graphicsItemLayoutEngine);
}

void ConstituencyWidget::loadSceneConstituencies()
{
    using namespace geom;

    scene()->clear();
    itemConstituencyIds_.clear();

    auto rowCount = constituencyProxyModel_->rowCount();
    
    std::vector<Point> constituencyPositions;
    constituencyPositions.reserve(rowCount);
    for (auto row = 0; row < rowCount; ++row)
    {
        auto index = constituencyProxyModel_->index(row, 0);
        auto x = constituencyProxyModel_
                          ->data(index, ConstituencyModel::LongitudeRole)
                          .toInt();
        auto y = constituencyProxyModel_
                          ->data(index, ConstituencyModel::LatitudeRole)
                          .toInt();
        constituencyPositions.push_back(Point::createCartesian(x, y));
    }
    
    QMap<QGraphicsItem*, int> roughMap;
    for (auto row = 0; row < rowCount; ++row)
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
        roughMap[pixmapItem] =
            constituencyProxyModel_->data(index, ConstituencyModel::IdRole)
                .toInt();
    }

    auto items = itemConstituencyIds_.keys().toVector();

    itemConstituencyIds_ = roughMap;
}

void ConstituencyWidget::onSelectionChanged(const QItemSelection& selected)
{
    if (selected.isEmpty())
        return;
    auto indexList = selected.indexes();
    if (indexList.isEmpty())
        return;
    idOfMostRecentlySelectedConstituency_ =
        constituencyProxyModel_
            ->data(indexList.first(), ConstituencyModel::IdRole)
            .toInt();
}

void ConstituencyWidget::selectConstituencyInModel()
{
    if (!constituencySelectionModel_)
        return;
    auto selectedItemList = scene()->selectedItems();
    if (selectedItemList.isEmpty()
        && idOfMostRecentlySelectedConstituency_ > -1)
    {
        auto indexOfMostRecentlySelectedConstituency =
            poll_zapp_core_utils::idToModelIndex(
                *(constituencyProxyModel_->constituencyModel()),
                idOfMostRecentlySelectedConstituency_);
        if (indexOfMostRecentlySelectedConstituency.isValid())
        {
            constituencySelectionModel_->select(
                indexOfMostRecentlySelectedConstituency,
                QItemSelectionModel::ClearAndSelect);
            return;
        }
    }
    if (selectedItemList.isEmpty())
        selectedItemList = scene()->items();
    if (selectedItemList.isEmpty())
        return;
    auto itemToSelect = selectedItemList.first();
    if (!itemToSelect)
        return;
    auto id = itemConstituencyIds_[itemToSelect];
    auto index = poll_zapp_core_utils::idToModelIndex(
        *(constituencyProxyModel_->constituencyModel()), id);
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
    connect(
        politicianModel_,
        &PoliticianModel::refreshed,
        this,
        &ConstituencyWidget::loadModel);

    connect(
        constituencyProxyModel_,
        &QAbstractItemModel::modelReset,
        this,
        &ConstituencyWidget::loadModel);
    connect(
        constituencyProxyModel_,
        &QAbstractItemModel::rowsInserted,
        this,
        &ConstituencyWidget::loadModel);
    connect(
        constituencyProxyModel_,
        &QAbstractItemModel::rowsRemoved,
        this,
        &ConstituencyWidget::loadModel);
    connect(
        constituencyProxyModel_,
        &QAbstractItemModel::dataChanged,
        this,
        &ConstituencyWidget::refreshPixmaps);
}

void ConstituencyWidget::refreshPixmaps(
    const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
    for (auto it = itemConstituencyIds_.begin();
         it != itemConstituencyIds_.end();
         ++it)
    {
        auto index = poll_zapp_core_utils ::idToModelIndex(
            *(constituencyProxyModel_->constituencyModel()), it.value());
        if (index.row() < topLeft.row() || index.row() > bottomRight.row())
            continue;
        if (auto pixmapItem =
                qgraphicsitem_cast<QGraphicsPixmapItem*>(it.key()))
        {
            pixmapItem->setPixmap(
                constituencyProxyModel_->data(index, Qt::DecorationRole)
                    .value<QPixmap>());
        }
    }
}
