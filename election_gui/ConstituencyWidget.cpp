#include "ConstituencyWidget.h"

#include <QGraphicsScene>
#include <QItemSelectionModel>
#include <QPoint>
#include <QRect>

#include "ConstituencyModel.h"
#include "RectanglePositionCalculator.h"

ConstituencyWidget::ConstituencyWidget(
    QGraphicsScene* scene, 
    QWidget* parent)
    : QGraphicsView(scene, parent)
    , constituencyModel_(nullptr)
    , constituencySelectionModel_(nullptr)
    , scene_(scene)
{
    makeConnections();
    activateSelectedConstituency();
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

void ConstituencyWidget::setScene(QGraphicsScene* scene)
{
    QGraphicsView::setScene(scene);
    scene_ = scene;
    connect(scene_, &QGraphicsScene::selectionChanged,
        this, &ConstituencyWidget::activateSelectedConstituency);
}

void ConstituencyWidget::loadIndexItemCache()
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

void ConstituencyWidget::activateSelectedConstituency()
{
    // Calculate the index of the selected constituency and call it index
    auto selectedItem = scene_->selectedItems().first();
    auto index = indexItemCache_[selectedItem];
    if (index.isValid())
        emit constituencyActivated(index);
}

void ConstituencyWidget::makeConnections()
{
    connect(constituencyModel_, &QAbstractItemModel::modelReset,
        this, &ConstituencyWidget::loadIndexItemCache);
    connect(constituencyModel_, &QAbstractItemModel::rowsInserted,
        this, &ConstituencyWidget::loadIndexItemCache);
    connect(constituencyModel_, &QAbstractItemModel::rowsRemoved,
        this, &ConstituencyWidget::loadIndexItemCache);
    connect(scene_, &QGraphicsScene::selectionChanged,
        this, &ConstituencyWidget::activateSelectedConstituency);
}
