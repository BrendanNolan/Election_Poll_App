#include "ConstituencyWidget.h"

#include <QItemSelectionModel>
#include <QPoint>
#include <QRect>

#include "ConstituencyModel.h"

ConstituencyWidget::ConstituencyWidget(QWidget* parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
    , constituencyModel_(nullptr)
    , constituencySelectionModel_(nullptr)
{

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
