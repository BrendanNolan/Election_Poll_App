#include "ConstituencyExplorerWidget.h"

#include "ui_ConstituencyExplorerWidget.h"

#include <QModelIndex>

#include "ConstituencyModel.h"
#include "PoliticianModel.h"

ConstituencyExplorerWidget::ConstituencyExplorerWidget(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::ConstituencyExplorerWidget)
    , constituencyModel_(nullptr)
    , constituencySelectionModel_(nullptr)
    , politicianModel_(nullptr)
    , politicianSelectionModel_(nullptr)
{
    ui_->setupUi(this);
    
    connect(ui_->constituencyWidget, &ConstituencyWidget::constituencyActivated,
        this, &ConstituencyExplorerWidget::onConstituencyActivated);
}

ConstituencyExplorerWidget::~ConstituencyExplorerWidget()
{
    delete ui_;
}

void ConstituencyExplorerWidget::setConstituencyModel(ConstituencyModel* model)
{
    constituencyModel_ = model;
    ui_->constituencyWidget->setModel(model);
}

void ConstituencyExplorerWidget::setConstituencySelectionModel(
    QItemSelectionModel* selectionModel)
{
    constituencySelectionModel_ = selectionModel;
    ui_->constituencyWidget->setSelectionModel(selectionModel);
}

void ConstituencyExplorerWidget::setPoliticianModel(PoliticianModel* model)
{
    politicianModel_ = model;
    ui_->politicianListWidget->setModel(model);
}

void ConstituencyExplorerWidget::setPoliticianSelectionModel(
    QItemSelectionModel* selectionModel)
{
    politicianSelectionModel_ = selectionModel;
    ui_->politicianListWidget->setSelectionModel(selectionModel);
}

void ConstituencyExplorerWidget::onConstituencyActivated(const QModelIndex& index)
{
    auto constituencyId = constituencyModel_->data(
        index, ConstituencyModel::IdRole).toInt();
    politicianModel_->setConstituency(constituencyId);
}
