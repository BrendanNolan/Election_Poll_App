#include "ConstituencyWidget.h"

#include <QItemSelectionModel>
#include <QPoint>
#include <QRect>

#include "ConstituencyModel.h"
#include "RectanglePositionCalculator.h"

ConstituencyWidget::ConstituencyWidget(QWidget* parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
    , constituencyModel_(nullptr)
    , constituencySelectionModel_(nullptr)
{
    connect(constituencyModel_, &QAbstractItemModel::modelReset,
        this, &ConstituencyWidget::loadIndexRectCache);
    connect(constituencyModel_, &QAbstractItemModel::rowsInserted,
        this, &ConstituencyWidget::loadIndexRectCache);
    connect(constituencyModel_, &QAbstractItemModel::rowsRemoved,
        this, &ConstituencyWidget::loadIndexRectCache);
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

void ConstituencyWidget::loadIndexRectCache()
{
    auto rows = constituencyModel_->rowCount();
    QHash<QModelIndex, QRect> roughHash;
    indexRectCache_.clear();
    for (auto row = 0; row < rows; ++row)
    {
        auto index = constituencyModel_->index(row);
        roughHash[index] = constituencyModel_->data(
            index, ConstituencyModel::AreaRole).toRect();
    }

}
