#include "MainWindow.h"

#include <QFileInfo>
#include <QItemSelectionModel>

#include "ConstituencyExplorerWidget.h"

#include "ConstituencyModel.h"
#include "ElectionDefinitions.h"
#include "PoliticianModel.h"
#include "SqlDatabaseManagerFactory.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , constituencyExplorerWidget_(new ConstituencyExplorerWidget(this))
{
    QFileInfo dbInfo(databaseFiles::databasePath);
    SqlDatabaseManagerFactory factory(dbInfo);
    auto politicianModel = new PoliticianModel(factory, this);
    auto politicianSelectionModel = new QItemSelectionModel(politicianModel);
    auto constituencyModel = new ConstituencyModel(factory, this);
    auto constituencySelectionModel = new QItemSelectionModel(
        constituencyModel);

    constituencyExplorerWidget_->setPoliticianModel(politicianModel);
    constituencyExplorerWidget_->setPoliticianSelectionModel(
        politicianSelectionModel);
    constituencyExplorerWidget_->setConstituencyModel(constituencyModel);
    constituencyExplorerWidget_->setConstituencySelectionModel(
        constituencySelectionModel);
}
