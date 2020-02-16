#include "PoliticianModelStatusSelectorWidget.h"

#include "ui_PoliticianModelStatusSelectorWidget.h"

PoliticianModelStatusSelectorWidget::PoliticianModelStatusSelectorWidget(
    QWidget* parent = nullptr,
    PoliticianModel* politicianModel = nullptr)
    : QWidget(parent)
    , ui_(new Ui::PoliticianModelStatusSelectorWidget)
{
    ui_->setupUi(this);
    ui_->mpsRadioButton->setChecked(true);
    ui_->candidatesRadioButton->setChecked(false);

    if (politicianModel)
        setPoliticianModel(politicianModel);
}

void PoliticianModelStatusSelectorWidget::setPoliticianModel(
    PoliticianModel* model)
{
    if (!model)
        return;
    
    if (ui_->mpsRadioButton->isChecked())
    {
        model->setElectoralStatus(
            PoliticianModel::ElectoralStatus::SITTING);
    }
    else if (ui_->candidatesRadioButton->isChecked())
    {
        model_->setElectoralStatus(
            PoliticianModel::ElectoralStatus::CANDIDATE);
    }

    connectWith(model);
}

void PoliticianModelStatusSelectorWidget::enableRadioButtons()
{
    ui_->mpsRadioButton->setEnabled(true);
    ui_->candidatesRadioButton->setEnabled(true);
}

void PoliticianModelStatusSelectorWidget::disableRadioButtons()
{
    ui_->mpsRadioButton->setDisabled(true);
    ui_->candidatesRadioButton->setDisabled(true);
}

void PoliticianModelStatusSelectorWidget::connectWith(PoliticianModel* model)
{
    connect(ui_->mpsRadioButton, &QRadioButton::toggled,
        [this](bool checked) {
            if (!checked)
                return;
            model->setElectoralStatus(
                PoliticianModel::ElectoralStatus::SITTING);
        });

    connect(ui_->candidatesRadioButton, &QRadioButton::toggled,
        [this](bool checked) {
            if (!checked)
                return;
            model->setElectoralStatus(
                PoliticianModel::ElectoralStatus::CANDIDATE);
        });
}
