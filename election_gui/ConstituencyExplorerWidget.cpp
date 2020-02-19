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
}

void ConstituencyExplorerWidget::setConstituencySelectionModel(
    QItemSelectionModel* selectionModel)
{
    if (selectionModel)
        Q_ASSERT(selectionModel->model() == constituencyModel_);
    constituencySelectionModel_ = selectionModel;
    ui_->constituencyWidget->setSelectionModel(constituencySelectionModel_);
    onConstituencySelectionChanged();
    connect(constituencySelectionModel_, &QItemSelectionModel::selectionChanged,
        this, &ConstituencyExplorerWidget::onConstituencySelectionChanged);
}

void ConstituencyExplorerWidget::setPoliticianModel(
    PoliticianModel* model)
{
    politicianModel_ = model;
    politicianModel_->setConstituency(currentConstituencyId());
    ui_->constituencyDrillDownWidget->setPoliticianModel(politicianModel_);
}

void ConstituencyExplorerWidget::setPoliticianSelectionModel(
    QItemSelectionModel* selectionModel)
{
    ui_->constituencyDrillDownWidget->setPoliticianSelectionModel(
        selectionModel);
}

void ConstituencyExplorerWidget::setPollResultModel(PollResultModel* model)
{
    pollResultModel_ = model;
    pollResultModel_->setConstituency(currentConstituencyId());
    ui_->constituencyDrillDownWidget->setPollResultModel(pollResultModel_);
}

void ConstituencyExplorerWidget::setPollResultSelectionModel(
    QItemSelectionModel* selectionModel)
{
    ui_->constituencyDrillDownWidget->setPollResultSelectionModel(
        selectionModel);
}

QHBoxLayout* ConstituencyExplorerWidget::buttonLayout()
{
    return ui_->buttonLayout;
}

void ConstituencyExplorerWidget::onConstituencySelectionChanged()
{
    if (politicianModel_)
        politicianModel_->setConstituency(currentConstituencyId());
    if (pollResultModel_)
        pollResultModel_->setConstituency(currentConstituencyId());
}

int ConstituencyExplorerWidget::currentConstituencyId() const
{
    if (!constituencySelectionModel_ ||
        constituencySelectionModel_->selectedIndexes().isEmpty())
    {
        if (constituencyModel_)
        {
            return constituencyModel_->data(
                constituencyModel_->index(0, 0), 
                ConstituencyModel::IdRole).toInt();
        }
        
        return -1;
    }

    auto selectedIndex = constituencySelectionModel_->selectedIndexes().first();
    return constituencyModel_->data(
        selectedIndex, 
        ConstituencyModel::IdRole).toInt();
}
