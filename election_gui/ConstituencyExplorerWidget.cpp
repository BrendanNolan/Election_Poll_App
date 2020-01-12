#include "ConstituencyExplorerWidget.h"

#include "ui_ConstituencyExplorerWidget.h"

ConstituencyExplorerWidget::ConstituencyExplorerWidget(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::ConstituencyExplorerWidget)
{
    ui_->setupUi(this);
}
