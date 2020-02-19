#include "ConstituencyExplorerWidget.h"

#include "ui_ConstituencyExplorerWidget.h"

#include <QItemSelectionModel>

#include <QtGlobal>

#include "ConstituencyModel.h"
#include "PoliticianModel.h"
#include "PollResultModel.h"

ConstituencyExplorerWidget::ConstituencyExplorerWidget(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::ConstituencyExplorerWidget)
{
    ui_->setupUi(this);
    connect(
        ui_->constituencyDrillDownWidget, 
        &ConstituencyDrillDownWidget::pictureActivated,
        this, 
        &ConstituencyExplorerWidget::politicianActivated);
    connect(
        ui_->constituencyDrillDownWidget, 
        &ConstituencyDrillDownWidget::picturesActivated,
        this, 
        &ConstituencyExplorerWidget::politiciansActivated);
}

ConstituencyExplorerWidget::~ConstituencyExplorerWidget()
{
    delete ui_;
}

void ConstituencyExplorerWidget::setConstituencyModel(
    ConstituencyModel* model)
{
    constituencyModel_ = model;
    ui_->constituencyWidget->setModel(model);
    ui_->constituencyDrillDownWidget->setConstituencyModel(
        model);
}

void ConstituencyExplorerWidget::setConstituencySelectionModel(
    QItemSelectionModel* selectionModel)
{
    if (selectionModel)
        Q_ASSERT(selectionModel->model() == constituencyModel_);
    constituencySelectionModel_ = selectionModel;
    ui_->constituencyWidget->setSelectionModel(selectionModel);
    ui_->constituencyDrillDownWidget->setConstituencySelectionModel(
        selectionModel);
    setConstituency();
    connect(selectionModel, &QItemSelectionModel::selectionChanged,
        this, &ConstituencyExplorerWidget::setConstituency);
}

void ConstituencyExplorerWidget::setPoliticianModel(
    PoliticianModel* model)
{
    politicianModel_ = model;
    ui_->constituencyDrillDownWidget->setPoliticianModel(model);
    ui_->constituencyWidget->setPoliticianModel(model);
    setConstituency();
}

void ConstituencyExplorerWidget::setPoliticianSelectionModel(
    QItemSelectionModel* selectionModel)
{
    ui_->constituencyDrillDownWidget->setPoliticianSelectionModel(
        selectionModel);
}

QHBoxLayout* ConstituencyExplorerWidget::buttonLayout()
{
    return ui_->buttonLayout;
}

void ConstituencyExplorerWidget::setConstituency()
{
    if (!constituencySelectionModel_)
        return;
    auto selectedIndexes = constituencySelectionModel_->selectedIndexes();
    if (selectedIndexes.isEmpty())
        return;
    auto selectedIndex = selectedIndexes.first();
    auto constituencyId = constituencyModel_->data(
        selectedIndex, ConstituencyModel::IdRole).toInt();
    if (politicianModel_)
        politicianModel_->setConstituency(constituencyId);
    if (pollResultModel_)
        pollResultModel_->setConstituency
}
