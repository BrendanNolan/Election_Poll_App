#include "ConstituencyExplorerWidget.h"

#include "ui_ConstituencyExplorerWidget.h"

#include "ConstituencyPixmapProxyModel.h"
#include "ConstituencyScene.h"
#include "PoliticianPictureProxyModel.h"

ConstituencyExplorerWidget::ConstituencyExplorerWidget(
    QWidget* parent, ConstituencyScene* constituencyScene)
    : QWidget(parent)
    , constituencyScene_(constituencyScene)
    , ui_(new Ui::ConstituencyExplorerWidget)
{
    ui_->setupUi(this);
    connect(ui_->politicianListWidget, &PoliticianListWidget::pictureActivated,
        this, &ConstituencyExplorerWidget::politicianActivated);
    connect(ui_->politicianListWidget, &PoliticianListWidget::picturesActivated,
        this, &ConstituencyExplorerWidget::politiciansActivated);
    if (!constituencyScene_)
        constituencyScene_ = new ConstituencyScene();
    ui_->constituencyGraphicsView->setScene(constituencyScene_);
}

ConstituencyExplorerWidget::~ConstituencyExplorerWidget()
{
    delete ui_;
}

void ConstituencyExplorerWidget::setConstituencyModel(
    ConstituencyPixmapProxyModel* model)
{
    constituencyScene_->setModel(model);
    ui_->politicianListWidget->setConstituencyModel(model->constituencyModel());
}

void ConstituencyExplorerWidget::setConstituencyScene(ConstituencyScene* scene)
{
    constituencyScene_ = scene;
    ui_->constituencyGraphicsView->setScene(constituencyScene_);
}

void ConstituencyExplorerWidget::setConstituencySelectionModel(
    QItemSelectionModel* selectionModel)
{
    constituencyScene_->setSelectionModel(selectionModel);
    ui_->politicianListWidget->setConstituencySelectionModel(selectionModel);
}

void ConstituencyExplorerWidget::setPoliticianModel(
    PoliticianPictureProxyModel* model)
{
    ui_->politicianListWidget->setPoliticianModel(model);
}

void ConstituencyExplorerWidget::setPoliticianSelectionModel(
    QItemSelectionModel* selectionModel)
{
    ui_->politicianListWidget->setPoliticianSelectionModel(selectionModel);
}
