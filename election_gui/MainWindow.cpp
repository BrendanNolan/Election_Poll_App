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
#include "election_core_definitions.h"
#include "election_gui_utils.h"
#include "PoliticianModel.h"
#include "PoliticianPictureProxyModel.h"
#include "PollResultModel.h"
#include "RotatingItemsWidget.h"
#include "SqlDatabaseManagerFactory.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , constituencyExplorerWidget_(new ConstituencyExplorerWidget)
{
    setCentralWidget(constituencyExplorerWidget_);

    python_scripting::runPythonScript(QFileInfo(paths::scraperScript));

    auto factory = SqlDatabaseManagerFactory(QFileInfo(
        paths::databasePath));

    politicianModel_ = new PoliticianModel(factory, this);
    auto politicianSelectionModel = new QItemSelectionModel(politicianModel_);

    constituencyModel_ = new ConstituencyModel(factory, this);
    auto constituencySelectionModel = new QItemSelectionModel(
        constituencyModel_);

    pollResultModel_ = new PollResultModel(factory, this);
    auto pollResultSelectionModel = new QItemSelectionModel(pollResultModel_);

    constituencyExplorerWidget_->setPoliticianModel(politicianModel_);
    constituencyExplorerWidget_->setPoliticianSelectionModel(
        politicianSelectionModel);

    constituencyExplorerWidget_->setConstituencyModel(constituencyModel_);
    constituencyExplorerWidget_->setConstituencySelectionModel(
        constituencySelectionModel);

    constituencyExplorerWidget_->setPollResultModel(pollResultModel_);
    constituencyExplorerWidget_->setPollResultSelectionModel(
        pollResultSelectionModel);

    auto refreshDataButton = new QPushButton("Refresh Data");
    constituencyExplorerWidget_->buttonLayout()->addWidget(refreshDataButton);
    connect(refreshDataButton, &QPushButton::clicked,
        this, &MainWindow::asynchronouslyRefreshData);

    connect(&dataRefreshTimer_, &QTimer::timeout,
        this, &MainWindow::onDataRefreshTimerTimeout);
}

void MainWindow::asynchronouslyRefreshData()
{
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
    rotatingItemsLoadScreen_->setFrameRate(60);
    rotatingItemsLoadScreen_->setInterFrameAngleDifference(25);
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
    
    fut_ = std::async(
        std::launch::async, 
        &python_scripting::runPythonScript,
        QFileInfo(paths::scraperScript));
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
        refreshModels();
    }
}

void MainWindow::refreshModels()
{
    if (constituencyModel_)
        constituencyModel_->refresh();
    if (politicianModel_)
        politicianModel_->refresh();
    if (pollResultModel_)
        pollResultModel_->refresh();
}
