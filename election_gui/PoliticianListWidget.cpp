#include "PoliticianListWidget.h"
#include "ui_PoliticianListWidget.h"

#include <QItemSelectionModel>
#include <QRadioButton>

#include "ConstituencyModel.h"
#include "PoliticianModel.h"

#include "ConstituencyWidget.h"

PoliticianListWidget::PoliticianListWidget(QWidget* parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
    , ui_(new Ui::PoliticianListWidget)
{
    constituencyWidget_ = new ConstituencyWidget(this);
    auto constituencyModel = new ConstituencyModel(this);
    auto constituencySelectionModel = 
        new QItemSelectionModel(constituencyModel, this);
    constituencyWidget_->setModel(constituencyModel);
    constituencyWidget_->setSelectionModel(constituencySelectionModel);

    auto politicianModel = new PoliticianModel(this);
    auto politcianSelectionModel =
        new QItemSelectionModel(politicianModel, this);

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
