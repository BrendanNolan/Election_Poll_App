#include "ConstituencyExplorerWidget.h"

#include "ui_ConstituencyExplorerWidget.h"

#include <QItemSelectionModel>

#include <QtGlobal>

#include <memory>

#include "ConstituencyModel.h"
#include "ConstituencyPixmapCreatingFunctor.h"
#include "PixmapCreatingProxyModel.h"
#include "PoliticianModel.h"
#include "PoliticianPixmapCreatingFunctor.h"
#include "PollResultModel.h"

#include "election_core_definitions.h"
#include "election_gui_utils.h"
#include "RotatingItemsWidget.h"
#include "SqlDatabaseManagerFactory.h"

ConstituencyExplorerWidget::ConstituencyExplorerWidget(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::ConstituencyExplorerWidget)
{
    ui_->setupUi(this);

    python_scripting::runPythonScript(QFileInfo(paths::scraperScript));

    auto factory = SqlDatabaseManagerFactory(QFileInfo(
        paths::databasePath));

    auto politicianModel = new PoliticianModel(factory, this);
    auto politicianSelectionModel = new QItemSelectionModel(politicianModel);

    auto constituencyModel = new ConstituencyModel(factory, this);
    auto constituencySelectionModel = new QItemSelectionModel(
        constituencyModel);

    auto pollResultModel = new PollResultModel(factory, this);
    auto pollResultSelectionModel = new QItemSelectionModel(pollResultModel);

    setPoliticianModel(politicianModel);
    setPoliticianSelectionModel(politicianSelectionModel);

    setConstituencyModel(constituencyModel);
    setConstituencySelectionModel(constituencySelectionModel);

    setPollResultModel(pollResultModel);
    setPollResultSelectionModel(pollResultSelectionModel);

    connect(ui_->refreshDataButton, &QPushButton::clicked,
        this, &ConstituencyExplorerWidget::asynchronouslyRefreshData);

    connect(&dataRefreshTimer_, &QTimer::timeout,
        this, &ConstituencyExplorerWidget::onDataRefreshTimerTimeout);
}

ConstituencyExplorerWidget::~ConstituencyExplorerWidget()
{
    delete ui_;
}

void ConstituencyExplorerWidget::setConstituencyModel(
    ConstituencyModel* model)
{
    constituencyModel_ = model;
    if (!politicianModel_)
        return;
    auto constituencyProxyModel = new PixmapCreatingProxyModel(
        std::unique_ptr<PixmapCreatingFunctor>(
            new ConstituencyPixmapCreatingFunctor(
                constituencyModel_,
                *politicianModel_)),
        ui_->constituencyWidget);

    ui_->constituencyWidget->setModel(constituencyProxyModel);
}

void ConstituencyExplorerWidget::setConstituencySelectionModel(
    QItemSelectionModel* selectionModel)
{
    if (selectionModel)
        Q_ASSERT(selectionModel->model() == constituencyModel_);
    constituencySelectionModel_ = selectionModel;
    ui_->constituencyWidget->setSelectionModel(constituencySelectionModel_);
    onConstituencySelectionChanged();
    connect(constituencySelectionModel_, &QItemSelectionModel::selectionChanged,
        this, &ConstituencyExplorerWidget::onConstituencySelectionChanged);
}

void ConstituencyExplorerWidget::setPoliticianModel(
    PoliticianModel* model)
{
    politicianModel_ = model;
    politicianModel_->setConstituency(currentConstituencyId());
    ui_->constituencyDrillDownWidget->setPoliticianModel(politicianModel_);
}

void ConstituencyExplorerWidget::setPoliticianSelectionModel(
    QItemSelectionModel* selectionModel)
{
    ui_->constituencyDrillDownWidget->setPoliticianSelectionModel(
        selectionModel);
}

void ConstituencyExplorerWidget::setPollResultModel(PollResultModel* model)
{
    pollResultModel_ = model;
    pollResultModel_->setConstituency(currentConstituencyId());
    ui_->constituencyDrillDownWidget->setPollResultModel(pollResultModel_);
}

void ConstituencyExplorerWidget::setPollResultSelectionModel(
    QItemSelectionModel* selectionModel)
{
    ui_->constituencyDrillDownWidget->setPollResultSelectionModel(
        selectionModel);
}

void ConstituencyExplorerWidget::onConstituencySelectionChanged()
{
    if (politicianModel_)
        politicianModel_->setConstituency(currentConstituencyId());
    if (pollResultModel_)
        pollResultModel_->setConstituency(currentConstituencyId());
}

int ConstituencyExplorerWidget::currentConstituencyId() const
{
    if (!constituencySelectionModel_ ||
        constituencySelectionModel_->selectedIndexes().isEmpty())
    {
        if (constituencyModel_)
        {
            return constituencyModel_->data(
                constituencyModel_->index(0, 0), 
                ConstituencyModel::IdRole).toInt();
        }
        
        return -1;
    }

    auto selectedIndex = constituencySelectionModel_->selectedIndexes().first();
    return constituencyModel_->data(
        selectedIndex, 
        ConstituencyModel::IdRole).toInt();
}

void ConstituencyExplorerWidget::asynchronouslyRefreshData()
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

    PixmapCreatingProxyModel politicianProxyModel(
        std::unique_ptr<PixmapCreatingFunctor>(
            new PoliticianPixmapCreatingFunctor(politicianModel_)),
        nullptr);
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

void ConstituencyExplorerWidget::onDataRefreshTimerTimeout()
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

void ConstituencyExplorerWidget::refreshModels()
{
    if (constituencyModel_)
        constituencyModel_->refresh();
    if (politicianModel_)
        politicianModel_->refresh();
    if (pollResultModel_)
        pollResultModel_->refresh();
}
