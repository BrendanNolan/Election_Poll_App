#include "MainWindow.h"

#include <QFileInfo>
#include <QHBoxLayout>
#include <QItemSelectionModel>
#include <QPushButton>
#include <QVector>

#include <chrono>

#include "ConstituencyExplorerWidget.h"
#include "ConstituencyModel.h"
#include "ConstituencyPixmapProxyModel.h"
#include "ElectionDefinitions.h"
#include "ElectionGuiFunctions.h"
#include "PoliticianModel.h"
#include "PoliticianPictureProxyModel.h"
#include "RotatingItemsWidget.h"
#include "SqlDatabaseManagerFactory.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , constituencyExplorerWidget_(new ConstituencyExplorerWidget)
    , rotatingItemsWidget_(new RotatingItemsWidget(this))
{
    rotatingItemsWidget_->hide();
    setCentralWidget(constituencyExplorerWidget_);

    election_gui_functions::runPythonScript(QFileInfo(paths::scraperScript));

    auto factory = SqlDatabaseManagerFactory(QFileInfo(
        paths::databasePath));

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

    auto refreshDataButton = new QPushButton("Refresh Data");
    constituencyExplorerWidget_->buttonLayout()->addWidget(refreshDataButton);
    connect(refreshDataButton, &QPushButton::clicked,
        this, &MainWindow::asynchronouslyRefreshData);
}

void MainWindow::refreshModels()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (constituencyModel_)
        constituencyModel_->refresh();
    if (politicianModel_)
        politicianModel_->refresh();
}

void MainWindow::refreshData()
{
    mutex_.lock();
    election_gui_functions::runPythonScript(QFileInfo(paths::scraperScript));
    mutex_.unlock();
    refreshModels();
}

void MainWindow::asynchronouslyRefreshData()
{
    rotatingItemsWidget_->show();
    timer_.setInterval(std::chrono::seconds(1));
    fut_ = std::async(std::launch::async, &MainWindow::refreshData, this);
    connect(&timer_, &QTimer::timeout,
        [this]() {
            auto status = fut_.wait_for(std::chrono::seconds(0));
            if (status == std::future_status::ready)
            {
                timer_.stop();
                rotatingItemsWidget_->hide();
            }
        });
    timer_.start();
}
