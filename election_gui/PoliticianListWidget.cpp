#include "PoliticianListWidget.h"
#include "ui_PoliticianListWidget.h"

#include <QtGlobal>

#include <QItemSelectionModel>
#include <QRadioButton>

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

    connect(ui_->mpsRadioButton, &QRadioButton::toggled,
        [this](bool checked) { 
            ui_->candidatesRadioButton->setChecked(!checked); 
        });
    connect(ui_->candidatesRadioButton, &QRadioButton::toggled,
        [this](bool checked) {
        ui_->mpsRadioButton->setChecked(!checked);
    });
}

PoliticianListWidget::~PoliticianListWidget()
{
    delete ui_;
}

void PoliticianListWidget::setModel(PoliticianModel* model)
{
    politicianModel_ = model;

    connect(politicianModel_, &PoliticianModel::dataChanged,
        this, &PoliticianListWidget::dataChanged);
    ui_->politicianListView->setModel(politicianModel_);
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

void PoliticianListWidget::setSelectionModel(
    QItemSelectionModel* selectionModel)
{
    auto model = selectionModel->model();
    Q_ASSERT(model == politicianModel_);

    politicianSelectionModel_ = selectionModel;
    politicianSelectionModel_->clear();

    connect(ui_->politicianListView, &QListView::activated,
        this, &PoliticianListWidget::politicianActivated);
    connect(politicianSelectionModel_, &QItemSelectionModel::currentChanged,
        this, &PoliticianListWidget::currentChanged);
    connect(politicianSelectionModel_, &QItemSelectionModel::selectionChanged,
        this, &PoliticianListWidget::selectionChanged);
}

QModelIndexList PoliticianListWidget::selectedPoliticians() const
{
    return politicianSelectionModel_->selectedRows();
}

void PoliticianListWidget::setConstituency(int constituencyId)
{
    politicianModel_->setConstituency(constituencyId);
}
