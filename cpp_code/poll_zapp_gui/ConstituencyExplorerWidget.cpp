#include "ConstituencyExplorerWidget.h"

#include "ui_ConstituencyExplorerWidget.h"

#include <QDialog>
#include <QItemSelectionModel>
#include <QMessageBox>

#include <QtGlobal>

#include <memory>

#include "ConstituencyModel.h"
#include "app_data_functions.h"
#include "PoliticianModel.h"
#include "PoliticianPictureProxyModel.h"
#include "PollResultModel.h"
#include "PolygonInflatingPositioningEngine.h"
#include "RotatingItemsWidget.h"
#include "SqlDatabaseManagerFactory.h"

ConstituencyExplorerWidget::ConstituencyExplorerWidget(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::ConstituencyExplorerWidget)
{
    ui_->setupUi(this);
    ui_->constituencyWidget->setPolygonLayoutEngine(
        std::unique_ptr<PolygonInflatingPositioningEngine>(
            new PolygonInflatingPositioningEngine()));

    auto factory = SqlDatabaseManagerFactory(QFileInfo(paths::databasePath()));

    auto politicianModel = new PoliticianModel(factory, this);
    auto politicianSelectionModel = new QItemSelectionModel(politicianModel);

    auto constituencyModel = new ConstituencyModel(factory, this);
    auto constituencySelectionModel =
        new QItemSelectionModel(constituencyModel);

    auto pollResultModel = new PollResultModel(factory, this);
    auto pollResultSelectionModel = new QItemSelectionModel(pollResultModel);

    setPoliticianModel(politicianModel);
    setPoliticianSelectionModel(politicianSelectionModel);

    setConstituencyModel(constituencyModel);
    setConstituencySelectionModel(constituencySelectionModel);

    setPollResultModel(pollResultModel);
    setPollResultSelectionModel(pollResultSelectionModel);

    auto dataLoadSuccessful = refreshModels();
    if (!dataLoadSuccessful)
    {
        QMessageBox failureWarning;
        failureWarning.setWindowTitle("Load Failure");
        failureWarning.setIcon(QMessageBox::Warning);
        failureWarning.setText("Data Loading Operation Failed");
        failureWarning.exec();
    }

    if (constituencyModel->rowCount() > 0)
    {
        politicianModel->setConstituency(
            constituencyModel
                ->data(constituencyModel->index(0), ConstituencyModel::IdRole)
                .toInt());
    }

    connect(
        ui_->refreshDataButton,
        &QPushButton::clicked,
        this,
        &ConstituencyExplorerWidget::asynchronouslyRefreshModels);

    connect(
        &dataRefreshTimer_,
        &QTimer::timeout,
        this,
        &ConstituencyExplorerWidget::onDataRefreshTimerTimeout);
}

ConstituencyExplorerWidget::~ConstituencyExplorerWidget()
{
    delete ui_;
}

void ConstituencyExplorerWidget::setConstituencyModel(ConstituencyModel* model)
{
    constituencyModel_ = model;
    if (!politicianModel_)
        return;

    ui_->constituencyWidget->setModels(constituencyModel_, politicianModel_);
}

void ConstituencyExplorerWidget::setConstituencySelectionModel(
    QItemSelectionModel* selectionModel)
{
    if (selectionModel)
        Q_ASSERT(selectionModel->model() == constituencyModel_);
    constituencySelectionModel_ = selectionModel;
    ui_->constituencyWidget->setSelectionModel(constituencySelectionModel_);
    onConstituencySelectionChanged();
    connect(
        constituencySelectionModel_,
        &QItemSelectionModel::selectionChanged,
        this,
        &ConstituencyExplorerWidget::onConstituencySelectionChanged);
}

void ConstituencyExplorerWidget::setPoliticianModel(PoliticianModel* model)
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

    auto textToDisplay = currentConstituencyName();
    if (textToDisplay.isEmpty())
        textToDisplay = "No constituency selected";
    ui_->constituencyDrillDownWidget->setDisplayedConstituencyName(
        textToDisplay);
}

QModelIndex ConstituencyExplorerWidget::selectedConstituencyIndex() const
{
    if (!constituencySelectionModel_
        || constituencySelectionModel_->selectedIndexes().isEmpty())
    {
        if (constituencyModel_)
            return constituencyModel_->index(0, 0);
        else
            return QModelIndex();
    }

    return constituencySelectionModel_->selectedIndexes().first();
}

int ConstituencyExplorerWidget::currentConstituencyId() const
{
    auto index = selectedConstituencyIndex();
    if (!index.isValid() || !constituencyModel_)
        return -1;
    return constituencyModel_->data(index, ConstituencyModel::IdRole).toInt();
}

QString ConstituencyExplorerWidget::currentConstituencyName() const
{
    auto index = selectedConstituencyIndex();
    if (!index.isValid() || !constituencyModel_)
        return QString();
    return constituencyModel_->data(index, ConstituencyModel::NameRole)
        .toString();
}

void ConstituencyExplorerWidget::asynchronouslyRefreshModels()
{
    auto sizeOfMainWindow = rect().size();
    auto desiredSizeOfLoadScreen = 0.5 * sizeOfMainWindow;
    auto edgeLengthOfLoadScreenPixmaps =
        0.15
        * std::min(
              desiredSizeOfLoadScreen.width(),
              desiredSizeOfLoadScreen.height());
    QSize desiredSizeOfLoadScreenPixmaps(
        edgeLengthOfLoadScreenPixmaps, edgeLengthOfLoadScreenPixmaps);

    PoliticianPictureProxyModel politicianProxyModel(politicianModel_, nullptr);
    QVector<QGraphicsItem*> politicianGraphicsItems;
    auto rowCount = politicianProxyModel.rowCount();
    for (auto row = 0; row < rowCount; ++row)
    {
        auto pixmap =
            politicianProxyModel.data(politicianProxyModel.index(row, 0))
                .value<QPixmap>();
        politicianGraphicsItems.push_back(new QGraphicsPixmapItem(pixmap.scaled(
            desiredSizeOfLoadScreenPixmaps, Qt::KeepAspectRatio)));
    }

    loadScreen_ = new QDialog(this);
    loadScreen_->setWindowTitle("Refreshing Data ...");
    auto loadScreenLayout = new QHBoxLayout(loadScreen_);
    loadScreen_->setModal(true);
    auto rotatingItemsWidget = new RotatingItemsWidget();
    {
        rotatingItemsWidget->setFrameRate(60);
        rotatingItemsWidget->setInterFrameAngleDifference(25);
        rotatingItemsWidget->setFixedSize(desiredSizeOfLoadScreen);
        rotatingItemsWidget->setRotationRadius(
            rotatingItemsWidget->preferredRotationRadius());
        rotatingItemsWidget->scene()->setBackgroundBrush(
            QBrush(QColor(10, 15, 68)));
        rotatingItemsWidget->setHorizontalScrollBarPolicy(
            Qt::ScrollBarAlwaysOff);
        rotatingItemsWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        rotatingItemsWidget->setRotatingItems(politicianGraphicsItems);
    }
    loadScreenLayout->addWidget(rotatingItemsWidget);
    loadScreen_->setVisible(true);
    loadScreen_->raise();

    dataRefreshTimer_.setInterval(std::chrono::seconds(1));

    fut_ = std::async(
        std::launch::async, &ConstituencyExplorerWidget::refreshModels, this);
    dataRefreshTimer_.start();
}

void ConstituencyExplorerWidget::onDataRefreshTimerTimeout()
{
    auto status = fut_.wait_for(std::chrono::seconds(0));
    if (status != std::future_status::ready)
        return;

    dataRefreshTimer_.stop();
    delete loadScreen_;
    loadScreen_ = nullptr;

    auto refreshSuccssful = fut_.get();
    if (refreshSuccssful)
        return;

    QMessageBox failureWarning;
    failureWarning.setWindowTitle("Update Failure");
    failureWarning.setIcon(QMessageBox::Warning);
    failureWarning.setText("Data Refresh Operation Failed");
    failureWarning.exec();
}

void ConstituencyExplorerWidget::reloadModels()
{
    if (constituencyModel_)
        constituencyModel_->reload();
    if (politicianModel_)
        politicianModel_->reload();
    if (pollResultModel_)
        pollResultModel_->reload();
}

bool ConstituencyExplorerWidget::refreshModels()
{
    auto refreshSuccessful = true;
    if (constituencyModel_)
    {
        if (!constituencyModel_->refreshDataSource())
            refreshSuccessful = false;
    }
    if (politicianModel_)
    {
        if (!politicianModel_->refreshDataSource())
            refreshSuccessful = false;
    }
    if (pollResultModel_)
    {
        if (!pollResultModel_->refreshDataSource())
            refreshSuccessful = false;
    }
    return refreshSuccessful;
}
