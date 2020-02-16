#include "MainWindow.h"

#include <QBrush>
#include <QColor>
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
#include "election_core_definitions.h"
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
    
    auto sizeOfMainWindow = rect().size();
    auto desiredSizeOfLoadScreen = 0.5 * sizeOfMainWindow;
    auto desiredPositionOfLoadScreen = rect().topLeft()
        + QPoint(rect().width() * 1.0 / 4.0, rect().height() * 1.0 / 4.0);
    auto edgeLengthOfLoadScreenPixmaps = 0.15 * std::min(
        desiredSizeOfLoadScreen.width(), 
        desiredSizeOfLoadScreen.height());
    QSize desiredSizeOfLoadScreenPixmaps(
        edgeLengthOfLoadScreenPixmaps, edgeLengthOfLoadScreenPixmaps);

    PoliticianPictureProxyModel politicianProxyModel(nullptr, politicianModel_);
    QVector<QGraphicsItem*> politicianGraphicsItems;
    auto rowCount = politicianProxyModel.rowCount();
    for (auto row = 0; row < rowCount; ++row)
    {
        auto pixmap = politicianProxyModel.data(
            politicianProxyModel.index(row, 0))
            .value<QPixmap>();
        politicianGraphicsItems.push_back(new QGraphicsPixmapItem(
            pixmap.scaled(
                desiredSizeOfLoadScreenPixmaps, 
                Qt::KeepAspectRatio)));
    }

    rotatingItemsLoadScreen_ = new RotatingItemsWidget(this);
    rotatingItemsLoadScreen_->setFixedSize(desiredSizeOfLoadScreen);
    rotatingItemsLoadScreen_->setRotationRadius(
        rotatingItemsLoadScreen_->preferredRotationRadius());
    rotatingItemsLoadScreen_->scene()->setBackgroundBrush(
        QBrush(QColor(10, 15, 68)));
    rotatingItemsLoadScreen_->setHorizontalScrollBarPolicy(
        Qt::ScrollBarAlwaysOff);
    rotatingItemsLoadScreen_->setVerticalScrollBarPolicy(
        Qt::ScrollBarAlwaysOff);
    rotatingItemsLoadScreen_->setRotatingItems(politicianGraphicsItems);
    rotatingItemsLoadScreen_->setWindowModality(Qt::ApplicationModal);
    rotatingItemsLoadScreen_->move(desiredPositionOfLoadScreen);
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
