#include "PoliticianListWidget.h"
#include "ui_PoliticianListWidget.h"

#include <QtGlobal>

#include <QItemSelectionModel>
#include <QListView>
#include <QRadioButton>

#include "ConstituencyModel.h"
#include "PoliticianModel.h"

PoliticianListWidget::PoliticianListWidget(QWidget* parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
    , ui_(new Ui::PoliticianListWidget)
    , politicianModel_(nullptr)
    , politicianSelectionModel_(nullptr)
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
    ui_->politicianListView->setModel(politicianModel_);
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
    politicianSelectionModel_ = selectionModel;
    ui_->politicianListView->setSelectionModel(selectionModel);
}

void PoliticianListWidget::setConstituencyModel(ConstituencyModel* model)
{
    constituencyModel_ = model;
    connect(model, &QAbstractItemModel::dataChanged,
        this, &PoliticianListWidget::onconstituencyDataChanged);
}

void PoliticianListWidget::onconstituencyDataChanged(
    const QModelIndex& topLeft,
    const QModelIndex& bottomRight)
{
    auto current = currentConstituency();
    if (!current.isValid())
        return;
    if (QItemSelectionRange(topLeft, bottomRight).contains(current))
        loadConstituency();
}

void PoliticianListWidget::setConstituencySelectionModel(
    QItemSelectionModel* selectionModel)
{
    constituencySelectionModel_ = selectionModel;
    connect(selectionModel, &QItemSelectionModel::selectionChanged,
        [this]() { loadConstituency(); });
}

QModelIndexList PoliticianListWidget::selectedPoliticians() const
{
    return politicianSelectionModel_->selectedRows();
}

QModelIndex PoliticianListWidget::currentConstituency() const
{
    if (!constituencyModel_ || !constituencySelectionModel_)
        return QModelIndex();
    return constituencySelectionModel_->currentIndex();
}

void PoliticianListWidget::loadConstituency()
{ 
    auto constituencyIndex = currentConstituency();
    if (!constituencyIndex.isValid())
        return;
    auto constituencyId = constituencyModel_->data(
        constituencyIndex, ConstituencyModel::IdRole).toInt();
    politicianModel_->setConstituency(constituencyId);
}
