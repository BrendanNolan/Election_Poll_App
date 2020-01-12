#include "PoliticianListWidget.h"
#include "ui_PoliticianListWidget.h"

#include <QItemSelectionModel>
#include <QRadioButton>

#include "PoliticianModel.h"

PoliticianListWidget::PoliticianListWidget(QWidget* parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
    , ui_(new Ui::PoliticianListWidget)
    , politicianModel_(new PoliticianModel(this))
{
    politicianSelectionModel_ = new QItemSelectionModel(politicianModel_, this);

    ui_->mpsRadioButton->setChecked(true);
    ui_->candidatesRadioButton->setChecked(false);

    connect(ui_->mpsRadioButton, QRadioButton::toggled,
        [this](bool checked) { 
            ui_->candidatesRadioButton->setChecked(!checked); 
        });
    connect(ui_->candidatesRadioButton, QRadioButton::toggled,
        [this](bool checked) {
        ui_->mpsRadioButton->setChecked(!checked);
    });
    connect(ui_->mpsRadioButton, QRadioButton::toggled,
        [this](bool checked) {
            if (!checked)
                return;
            politicianModel_->setElectoralStatus(
                PoliticianModel::ElectoralStatus::SITTING);
        });
    connect(ui_->candidatesRadioButton, QRadioButton::toggled,
        [this](bool checked) {
        if (!checked)
            return;
        politicianModel_->setElectoralStatus(
            PoliticianModel::ElectoralStatus::CANDIDATE);
    });
}

PoliticianListWidget::~PoliticianListWidget()
{
    delete ui_;
}
