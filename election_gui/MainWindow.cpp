#include "MainWindow.h"

#include <QFileInfo>
#include <QHBoxLayout>
#include <QItemSelectionModel>
#include <QPushButton>

#include <future>

#include "ConstituencyExplorerWidget.h"
#include "ConstituencyModel.h"
#include "ConstituencyPixmapProxyModel.h"
#include "ElectionDefinitions.h"
#include "PoliticianModel.h"
#include "PoliticianPictureProxyModel.h"
#include "SqlDatabaseManagerFactory.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , constituencyExplorerWidget_(new ConstituencyExplorerWidget)
{
    setCentralWidget(constituencyExplorerWidget_);

    auto factory = SqlDatabaseManagerFactory(QFileInfo(
        databaseFiles::databasePath));

    politicianModel_ = new PoliticianModel(factory, this);
    constituencyModel_ = new ConstituencyModel(factory, this);
    auto constituencyProxyModel = new ConstituencyPixmapProxyModel(
        this, constituencyModel_, politicianModel_);
    auto constituencySelectionModel = new QItemSelectionModel(
        constituencyProxyModel);

    auto politicianProxyModel = new PoliticianPictureProxyModel(
        this, politicianModel_);
    auto politicianSelectionModel = new QItemSelectionModel(
        politicianProxyModel);

    constituencyExplorerWidget_->setPoliticianModel(politicianProxyModel);
    constituencyExplorerWidget_->setPoliticianSelectionModel(
        politicianSelectionModel);
    constituencyExplorerWidget_->setConstituencyModel(constituencyProxyModel);
    constituencyExplorerWidget_->setConstituencySelectionModel(
        constituencySelectionModel);

    refreshDataButton_ = new QPushButton("Refresh Data");
    constituencyExplorerWidget_->buttonLayout()->addWidget(refreshDataButton_);
    connect(refreshDataButton_, &QPushButton::clicked,
        this, &MainWindow::doAsynchronousDataRefresh);
}

void MainWindow::doAsynchronousDataRefresh()
{
    // asynchronously run python script
    refreshModels();
}

void MainWindow::refreshModels()
{
    if (constituencyModel_)
        constituencyModel_->refresh();
    if (politicianModel_)
        politicianModel_->refresh();
}
