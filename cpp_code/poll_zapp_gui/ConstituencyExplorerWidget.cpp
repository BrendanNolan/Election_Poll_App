#include "ConstituencyExplorerWidget.h"

#include "ui_ConstituencyExplorerWidget.h"

#include <QDialog>
#include <QItemSelectionModel>
#include <QLabel>
#include <QMessageBox>
#include <QMovie>

#include <QtGlobal>

#include <memory>

#include "ConstituencyModel.h"
#include "app_data_functions.h"
#include "PoliticianModel.h"
#include "PoliticianPictureProxyModel.h"
#include "PollResultModel.h"
#include "GraphicsItemInflatingPositioningEngine.h"
#include "SqlDatabaseManagerFactory.h"

ConstituencyExplorerWidget::ConstituencyExplorerWidget(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::ConstituencyExplorerWidget)
{
    ui_->setupUi(this);
    ui_->loadIndicatorLabel_->hide();
    ui_->constituencyWidget->setPolygonLayoutEngine(
        std::unique_ptr<GraphicsItemInflatingPositioningEngine>(
            new GraphicsItemInflatingPositioningEngine()));

    SqlDatabaseManagerFactory factory{ QFileInfo(paths::databasePath()) };

    auto politicianModel = new PoliticianModel(factory, this);
    auto politicianSelectionModel = new QItemSelectionModel(politicianModel);

    auto constituencyModel = new ConstituencyModel(factory, this);
    auto constituencySelectionModel =
        new QItemSelectionModel(constituencyModel);

    auto pollResultModel = new PollResultModel(factory, this);
    auto pollResultSelectionModel = new QItemSelectionModel(pollResultModel);

    setModels(politicianModel, constituencyModel, pollResultModel);
    setPoliticianSelectionModel(politicianSelectionModel);
    setConstituencySelectionModel(constituencySelectionModel);
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
}

ConstituencyExplorerWidget::~ConstituencyExplorerWidget()
{
    delete ui_;
}

void ConstituencyExplorerWidget::setModels(
    PoliticianModel* politicianModel,
    ConstituencyModel* constituencyModel,
    PollResultModel* pollResultModel)
{
    politicianModel_ = politicianModel;
    pollResultModel_ = pollResultModel;

    ui_->constituencyDrillDownWidget->setModels(
        politicianModel_, pollResultModel_);

    constituencyModel_ = constituencyModel;
    ui_->constituencyWidget->setModels(constituencyModel_, politicianModel_);

    pollResultModel_->setConstituency(currentConstituencyId());
    politicianModel_->setConstituency(currentConstituencyId());
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

void ConstituencyExplorerWidget::setPoliticianSelectionModel(
    QItemSelectionModel* selectionModel)
{
    ui_->constituencyDrillDownWidget->setPoliticianSelectionModel(
        selectionModel);
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
    auto movie = new QMovie(":resources/loading_indictor.gif");
    ui_->loadIndicatorLabel_->setMovie(movie);
    ui_->loadIndicatorLabel_->show();
    movie->start();
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
