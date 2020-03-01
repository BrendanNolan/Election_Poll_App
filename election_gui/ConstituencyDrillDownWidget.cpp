#include "ConstituencyDrillDownWidget.h"
#include "ui_ConstituencyDrillDownWidget.h"

#include <QtGlobal>

#include <QItemSelectionModel>
#include <QListView>
#include <QRadioButton>

#include <memory>

#include "ConstituencyModel.h"
#include "ThinPixmapDelegate.h"
#include "PoliticianModel.h"
#include "PoliticianPixmapCreatingFunctor.h"
#include "PollResultPixmapCreatingFunctor.h"
#include "PollResultModel.h"
#include "PixmapCreatingProxyModel.h"

ConstituencyDrillDownWidget::ConstituencyDrillDownWidget(
    QWidget* parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
    , ui_(new Ui::ConstituencyDrillDownWidget)
    , politicianModel_(nullptr)
{
    ui_->setupUi(this);
    // Could use dependency inhjection to create two delegates here.
    // Will need a new general delegate class and then inject functionality
    // for politicians and poll results.
    ui_->politicianListView->setItemDelegate(new ThinPixmapDelegate(this));

    connect(ui_->sittingRadioButton,
        &QRadioButton::toggled,
        this,
        &ConstituencyDrillDownWidget::onSittingRadioButtonToggled);
    connect(ui_->candidatesRadioButton,
        &QRadioButton::toggled,
        this,
        &ConstituencyDrillDownWidget::onCandidatesRadioButtonToggled);
}

ConstituencyDrillDownWidget::~ConstituencyDrillDownWidget()
{
    delete ui_;
}

void ConstituencyDrillDownWidget::setPoliticianModel(PoliticianModel* model)
{
    politicianModel_ = model;

    auto proxyModel = new PixmapCreatingProxyModel(
        std::unique_ptr<PixmapCreatingFunctor>(
            new PoliticianPixmapCreatingFunctor(politicianModel_)),
        politicianModel_,
        ui_->politicianListView);

    ui_->politicianListView->setModel(proxyModel);
    ui_->sittingRadioButton->setChecked(true);
}

void ConstituencyDrillDownWidget::setPoliticianSelectionModel(
    QItemSelectionModel* selectionModel)
{
    Q_ASSERT(selectionModel->model() == politicianModel_);
    ui_->politicianListView->setSelectionModel(selectionModel);
}

void ConstituencyDrillDownWidget::setPollResultModel(PollResultModel* model)
{
    auto proxyModel = new PixmapCreatingProxyModel(
        std::unique_ptr<PixmapCreatingFunctor>(
            new PollResultPixmapCreatingFunctor(model)),
        model,
        ui_->pollResultListView);

    ui_->pollResultListView->setModel(proxyModel);
}

void ConstituencyDrillDownWidget::setPollResultSelectionModel(
    QItemSelectionModel* selectionModel)
{
    ui_->pollResultListView->setSelectionModel(selectionModel);
}

void ConstituencyDrillDownWidget::onCandidatesRadioButtonToggled(bool checked)
{
    if (!checked || !politicianModel_)
        return;
    politicianModel_->setElectoralStatus(
        PoliticianModel::ElectoralStatus::CANDIDATE);
}

void ConstituencyDrillDownWidget::onSittingRadioButtonToggled(bool checked)
{
    if (!checked || !politicianModel_)
        return;
    politicianModel_->setElectoralStatus(
        PoliticianModel::ElectoralStatus::SITTING);
}

QModelIndexList ConstituencyDrillDownWidget::selectedPoliticians() const
{
    return ui_->politicianListView->selectionModel()->selectedRows();
}

void ConstituencyDrillDownWidget::setDisplayedConstituencyName(
    const QString& name)
{
    ui_->constituencyLabel->setText(name);
}

void ConstituencyDrillDownWidget::setToInvalidState()
{
    ui_->constituencyLabel->setText("<Constituency Name>");
    disableRadioButtons();
}

void ConstituencyDrillDownWidget::enableRadioButtons()
{
    ui_->sittingRadioButton->setEnabled(true);
    ui_->candidatesRadioButton->setEnabled(true);
}

void ConstituencyDrillDownWidget::disableRadioButtons()
{
    ui_->sittingRadioButton->setEnabled(false);
    ui_->candidatesRadioButton->setEnabled(false);
}
