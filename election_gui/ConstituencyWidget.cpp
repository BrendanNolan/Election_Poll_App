#include "ConstituencyWidget.h"

#include <QGraphicsScene>
#include <QItemSelectionModel>
#include <QPoint>
#include <QRect>

#include "ConstituencyModel.h"
#include "ConstituencyScene.h"
#include "RectanglePositionCalculator.h"

ConstituencyWidget::ConstituencyWidget(ConstituencyScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
    , constituencyModel_(nullptr)
    , constituencySelectionModel_(nullptr)
    , constituencyScene_(scene)
{
    makeConnections();
}

ConstituencyWidget::ConstituencyWidget(QWidget* parent)
    : QGraphicsView(parent)
    , constituencyModel_(nullptr)
    , constituencySelectionModel_(nullptr)
{
    makeConnections();
}

void ConstituencyWidget::setModel(ConstituencyModel* constituencyModel)
{
    constituencyModel_ = constituencyModel;
    loadWidgetColours();
}

void ConstituencyWidget::setSelectionModel(QItemSelectionModel* selectionModel)
{
    constituencySelectionModel_ = selectionModel;
}

void ConstituencyWidget::setScene(ConstituencyScene* scene)
{
    QGraphicsView::setScene(scene);
    constituencyScene_ = scene;
    connect(constituencyScene_, &ConstituencyScene::activated,
        this, &ConstituencyWidget::onSceneItemActivated);
}

void ConstituencyWidget::loadIndexRectCache()
{
    auto rows = constituencyModel_->rowCount();
    QHash<QModelIndex, QRect> roughHash;
    indexItemCache_.clear();
    for (auto row = 0; row < rows; ++row)
    {
        auto index = constituencyModel_->index(row);
        roughHash[index] = constituencyModel_->data(
            index, ConstituencyModel::AreaRole).toRect();
    }

}

void ConstituencyWidget::makeConnections()
{
    connect(constituencyModel_, &QAbstractItemModel::modelReset,
        this, &ConstituencyWidget::loadIndexRectCache);
    connect(constituencyModel_, &QAbstractItemModel::rowsInserted,
        this, &ConstituencyWidget::loadIndexRectCache);
    connect(constituencyModel_, &QAbstractItemModel::rowsRemoved,
        this, &ConstituencyWidget::loadIndexRectCache);
    connect(constituencyScene_, &ConstituencyScene::activated,
        this, &ConstituencyWidget::onSceneItemActivated);
}
