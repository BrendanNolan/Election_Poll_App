#include "MainWindow.h"

#include <QFileInfo>
#include <QGraphicsPixmapItem>
#include <QHBoxLayout>
#include <QItemSelectionModel>
#include <QPushButton>
#include <QVector>

#include <chrono>

#include "ConstituencyExplorerWidget.h"
#include "ConstituencyModel.h"
#include "ConstituencyPixmapProxyModel.h"
#include "election_definitions.h"
#include "election_gui_utils.h"
#include "PoliticianModel.h"
#include "PoliticianPictureProxyModel.h"
#include "RotatingItemsWidget.h"
#include "SqlDatabaseManagerFactory.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , constituencyExplorerWidget_(new ConstituencyExplorerWidget)
{
    setCentralWidget(constituencyExplorerWidget_);

    python_script_running::runPythonScript(QFileInfo(paths::scraperScript));

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

    connect(&dataRefreshTimer_, &QTimer::timeout,
        this, &MainWindow::onDataRefreshTimerTimeout);
}

void MainWindow::refreshData()
{
    mutex_.lock();
    python_script_running::runPythonScript(QFileInfo(paths::scraperScript));
    mutex_.unlock();
    refreshModels();
}

void MainWindow::asynchronouslyRefreshData()
{
    mutex_.lock();
    
    PoliticianPictureProxyModel politicianProxyModel(nullptr, politicianModel_);
    QVector<QGraphicsItem*> politicianGraphicsItems;
    auto rowCount = politicianProxyModel.rowCount();
    for (auto row = 0; row < rowCount; ++row)
    {
        auto pixmap = politicianProxyModel.data(
            politicianProxyModel.index(row, 0))
            .value<QPixmap>();
        politicianGraphicsItems.push_back(new QGraphicsPixmapItem(pixmap));
    }

    rotatingItemsLoadScreen_ = new RotatingItemsWidget(this);
    rotatingItemsLoadScreen_->setRotatingItems(politicianGraphicsItems);
    rotatingItemsLoadScreen_->setFixedSize(rect().size() * 1.0 / 2.0);
    rotatingItemsLoadScreen_->setWindowModality(Qt::ApplicationModal);
    rotatingItemsLoadScreen_->move(
        rect().topLeft()
        + QPoint(rect().width() * 1.0 / 4.0, rect().height() * 1.0 / 4.0));
    rotatingItemsLoadScreen_->show();
    rotatingItemsLoadScreen_->raise();
    dataRefreshTimer_.setInterval(std::chrono::seconds(1));
    
    mutex_.unlock();
    
    fut_ = std::async(std::launch::async, &MainWindow::refreshData, this);
    dataRefreshTimer_.start();
}

void MainWindow::onDataRefreshTimerTimeout()
{
    auto status = fut_.wait_for(std::chrono::seconds(0));
    if (status == std::future_status::ready)
    {
        dataRefreshTimer_.stop();
        delete rotatingItemsLoadScreen_;
        rotatingItemsLoadScreen_ = nullptr;
    }
}

void MainWindow::refreshModels()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (constituencyModel_)
        constituencyModel_->refresh();
    if (politicianModel_)
        politicianModel_->refresh();
}
