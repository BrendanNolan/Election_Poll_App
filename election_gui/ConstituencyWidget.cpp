#include "ConstituencyWidget.h"

#include <QGraphicsrectItem>
#include <QGraphicsScene>
#include <QItemSelectionModel>
#include <QPointF>

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
    connect(scene_, &QGraphicsScene::selectionChanged,
        this, &ConstituencyWidget::activateSelectedConstituency);
    loadModel();
}

ConstituencyWidget::ConstituencyWidget(QWidget* parent)
    : QGraphicsView(parent)
    , constituencyModel_(nullptr)
    , constituencySelectionModel_(nullptr)
{
    connect(scene_, &QGraphicsScene::selectionChanged,
        this, &ConstituencyWidget::activateSelectedConstituency);
    loadModel();
}

void ConstituencyWidget::setModel(ConstituencyModel* constituencyModel)
{
    constituencyModel_ = constituencyModel;
    loadModel();
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

void ConstituencyWidget::setSceneConstituencies()
{
    scene_->clear();

    auto rows = constituencyModel_->rowCount();
    QHash<QGraphicsItem*, QModelIndex> roughHash;
    indexItemCache_.clear();
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
        scene_->addItem(rectItem);
        roughHash[rectItem] = index;
    }
    /*
        The following line is temporary. Eventually a 
        RectanglePositionCalculator will calculate new sizes and positions
        for the QRectItems.
    */
    indexItemCache_ = roughHash;
}

void ConstituencyWidget::activateSelectedConstituency()
{
    auto selectedItem = scene_->selectedItems().first();
    auto index = indexItemCache_[selectedItem];
    if (index.isValid())
        emit constituencyActivated(index);
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
    makeModelConnections();
    setSceneConstituencies();
    loadWidgetColours();
    activateSelectedConstituency();
}
