#include "ConstituencyExplorerWidget.h"

#include "ui_ConstituencyExplorerWidget.h"

#include "ConstituencyModel.h"
#include "PoliticianModel.h"

ConstituencyExplorerWidget::ConstituencyExplorerWidget(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::ConstituencyExplorerWidget)
{
    ui_->setupUi(this);
    connect(ui_->politicianListWidget, &PoliticianListWidget::pictureActivated,
        this, &ConstituencyExplorerWidget::politicianActivated);
    connect(ui_->politicianListWidget, &PoliticianListWidget::picturesActivated,
        this, &ConstituencyExplorerWidget::politiciansActivated);
}

ConstituencyExplorerWidget::~ConstituencyExplorerWidget()
{
    delete ui_;
}

void ConstituencyExplorerWidget::setConstituencyModel(ConstituencyModel* model)
{
    ui_->constituencyWidget->setModel(model);
    ui_->politicianListWidget->setConstituencyModel(model);
}

void ConstituencyExplorerWidget::setConstituencySelectionModel(
    QItemSelectionModel* selectionModel)
{
    ui_->constituencyWidget->setSelectionModel(selectionModel);
    ui_->politicianListWidget->setConstituencySelectionModel(selectionModel);
}

void ConstituencyExplorerWidget::setPoliticianModel(PoliticianModel* model)
{
    ui_->politicianListWidget->setPoliticianModel(model);
}

void ConstituencyExplorerWidget::setPoliticianSelectionModel(
    QItemSelectionModel* selectionModel)
{
    ui_->politicianListWidget->setPoliticianSelectionModel(selectionModel);
}
