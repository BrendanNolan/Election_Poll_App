#include "PoliticianListWidget.h"
#include "ui_PoliticianListWidget.h"

#include <QtGlobal>

#include <QItemSelectionModel>
#include <QListView>
#include <QRadioButton>

#include "ConstituencyModel.h"
#include "PoliticianModel.h"

PoliticianListWidget::PoliticianListWidget(
    QWidget* parent, 
    Qt::WindowFlags flags)
    : QWidget(parent, flags)
    , ui_(new Ui::PoliticianListWidget)
    , politicianModel_(nullptr)
{
    ui_->setupUi(this);
    ui_->mpsRadioButton->setChecked(true);
    ui_->candidatesRadioButton->setChecked(false);
}

PoliticianListWidget::~PoliticianListWidget()
{
    delete ui_;
}

void PoliticianListWidget::setPoliticianModel(PoliticianModel* model)
{
    politicianModel_ = model;
    ui_->politicianListView->setModel(model);
    loadConstituency();

    if (ui_->mpsRadioButton->isChecked())
    {
        politicianModel_->setElectoralStatus(
            PoliticianModel::ElectoralStatus::SITTING);
    }
    else if (ui_->candidatesRadioButton->isChecked())
    {
        politicianModel_->setElectoralStatus(
            PoliticianModel::ElectoralStatus::CANDIDATE);
    }
    connect(ui_->mpsRadioButton, &QRadioButton::toggled,
        [this](bool checked) {
            if (!checked)
                return;
            politicianModel_->setElectoralStatus(
                PoliticianModel::ElectoralStatus::SITTING);
        });
    connect(ui_->candidatesRadioButton, &QRadioButton::toggled,
        [this](bool checked) {
            if (!checked)
                return;
            politicianModel_->setElectoralStatus(
                PoliticianModel::ElectoralStatus::CANDIDATE);
        });
}

void PoliticianListWidget::setPoliticianSelectionModel(
    QItemSelectionModel* selectionModel)
{
    Q_ASSERT(selectionModel->model() == politicianModel_);
    ui_->politicianListView->setSelectionModel(selectionModel);
}

void PoliticianListWidget::setConstituencyModel(ConstituencyModel* model)
{
    constituencyModel_ = model;
    loadConstituency();
    connect(model, &QAbstractItemModel::dataChanged,
        this, &PoliticianListWidget::onConstituencyDataChanged);
}

void PoliticianListWidget::onConstituencyDataChanged(
    const QModelIndex& topLeft,
    const QModelIndex& bottomRight)
{
    auto toDisplay = constituencyToDisplay();
    if (!toDisplay.isValid())
    {
        setToInvalidState();
        return;
    }
    if (QItemSelectionRange(topLeft, bottomRight).contains(toDisplay))
        loadConstituency();
}

void PoliticianListWidget::setConstituencySelectionModel(
    QItemSelectionModel* selectionModel)
{
    constituencySelectionModel_ = selectionModel;
    loadConstituency();
    connect(selectionModel, &QItemSelectionModel::selectionChanged,
        [this]() { loadConstituency(); });
}

QModelIndexList PoliticianListWidget::selectedPoliticians() const
{
    return ui_->politicianListView->selectionModel()->selectedRows();
}

QModelIndex PoliticianListWidget::constituencyToDisplay() const
{
    if (!constituencyModel_) 
        return QModelIndex();
    if (!constituencySelectionModel_ || 
        !(constituencySelectionModel_->selectedIndexes().first().isValid()))
        return constituencyModel_->index(0);
    return constituencySelectionModel_->selectedIndexes().first();
}

void PoliticianListWidget::loadConstituency()
{ 
    auto constituencyIndex = constituencyToDisplay();
    if (!constituencyIndex.isValid() || !politicianModel_)
    {
        setToInvalidState();
        return;
    }

    enableRadioButtons();
    
    auto constituencyName = constituencyModel_->data(
        constituencyIndex, ConstituencyModel::NameRole).toString();
    ui_->constituencyLabel->setText(constituencyName);

    auto constituencyId = constituencyModel_->data(
        constituencyIndex, ConstituencyModel::IdRole).toInt();
    politicianModel_->setConstituency(constituencyId);
}

void PoliticianListWidget::setToInvalidState()
{
    if (politicianModel_)
        politicianModel_->setConstituency(-1);
    ui_->constituencyLabel->setText("<Constituency Name>");
    disableRadioButtons();
}

void PoliticianListWidget::enableRadioButtons()
{
    ui_->mpsRadioButton->setEnabled(true);
    ui_->candidatesRadioButton->setEnabled(true);
}

void PoliticianListWidget::disableRadioButtons()
{
    ui_->mpsRadioButton->setDisabled(true);
    ui_->candidatesRadioButton->setDisabled(true);
}
