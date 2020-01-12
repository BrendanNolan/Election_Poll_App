#include "ConstituencyWidget.h"
#include "ui_ConstituencyWidget.h"

#include "ConstituencyModel.h"


ConstituencyWidget::ConstituencyWidget(QWidget* parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
    , ui_(new Ui::ConstituencyWidget)
{
    auto constituencyModel = new ConstituencyModel(this);
    auto constituencySelectionModel =
    new QItemSelectionModel(constituencyModel, this);
    constituencyWidget_->setModel(constituencyModel);
    constituencyWidget_->setSelectionModel(constituencySelectionModel);
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
