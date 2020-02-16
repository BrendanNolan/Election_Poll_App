#include "ConstituencyExplorerWidget.h"

#include "ui_ConstituencyExplorerWidget.h"

#include "ConstituencyPixmapProxyModel.h"
#include "PoliticianPictureProxyModel.h"

ConstituencyExplorerWidget::ConstituencyExplorerWidget(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::ConstituencyExplorerWidget)
{
    ui_->setupUi(this);
    connect(ui_->constituencyDrillDownWidget, &ConstituencyDrillDownWidget::pictureActivated,
        this, &ConstituencyExplorerWidget::politicianActivated);
    connect(ui_->constituencyDrillDownWidget, &ConstituencyDrillDownWidget::picturesActivated,
        this, &ConstituencyExplorerWidget::politiciansActivated);
}

ConstituencyExplorerWidget::~ConstituencyExplorerWidget()
{
    delete ui_;
}

void ConstituencyExplorerWidget::setConstituencyModel(
    ConstituencyPixmapProxyModel* model)
{
    ui_->constituencyWidget->setModel(model);
    ui_->constituencyDrillDownWidget->setConstituencyModel(model->constituencyModel());
}

void ConstituencyExplorerWidget::setConstituencySelectionModel(
    QItemSelectionModel* selectionModel)
{
    ui_->constituencyWidget->setSelectionModel(selectionModel);
    ui_->constituencyDrillDownWidget->setConstituencySelectionModel(selectionModel);
}

void ConstituencyExplorerWidget::setPoliticianModel(
    PoliticianPictureProxyModel* model)
{
    ui_->constituencyDrillDownWidget->setPoliticianModel(model);
}

void ConstituencyExplorerWidget::setPoliticianSelectionModel(
    QItemSelectionModel* selectionModel)
{
    ui_->constituencyDrillDownWidget->setPoliticianSelectionModel(selectionModel);
}

QHBoxLayout* ConstituencyExplorerWidget::buttonLayout()
{
    return ui_->buttonLayout;
}
