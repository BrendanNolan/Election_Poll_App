#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QItemSelectionModel>
#include <QRadioButton>

#include "ConstituencyModel.h"
#include "PoliticianModel.h"

#include "ConstituencyWidget.h"

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
    , ui_(new Ui::MainWindow)
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

    // Below here needs work
    connect(ui_->mpsRadioButton, QRadioButton::toggled,
        [this, checked]() { ui_->candidatesRadioButton->setChecked(!checked); });
    connect(ui_->candidatesRadioButton, QRadioButton::toggled,
        [this]() { ui_->mpsRadioButton->toggle(); });
    connect(ui_-);
}
