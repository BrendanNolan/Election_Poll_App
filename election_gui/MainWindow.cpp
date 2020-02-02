#include "MainWindow.h"

#include <QFileInfo>
#include <QItemSelectionModel>

#include "ConstituencyExplorerWidget.h"

#include "ConstituencyModel.h"
#include "ConstituencyPixmapProxyModel.h"
#include "ElectionDefinitions.h"
#include "PoliticianModel.h"
#include "SqlDatabaseManagerFactory.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , constituencyExplorerWidget_(new ConstituencyExplorerWidget(this))
{
    auto factory = SqlDatabaseManagerFactory(QFileInfo(
        databaseFiles::databasePath));
    auto politicianModel = new PoliticianModel(factory, this);
    auto politicianSelectionModel = new QItemSelectionModel(politicianModel);
    
    auto constituencyModel = new ConstituencyModel(factory, this);
    auto constituencyProxyModel = new ConstituencyPixmapProxyModel(
        this, constituencyModel, politicianModel);
    auto constituencySelectionModel = new QItemSelectionModel(
        constituencyProxyModel);

    constituencyExplorerWidget_->setPoliticianModel(politicianModel);
    constituencyExplorerWidget_->setPoliticianSelectionModel(
        politicianSelectionModel);
    constituencyExplorerWidget_->setConstituencyModel(constituencyProxyModel);
    constituencyExplorerWidget_->setConstituencySelectionModel(
        constituencySelectionModel);
}
