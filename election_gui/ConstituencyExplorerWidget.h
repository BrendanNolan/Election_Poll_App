#ifndef CONSTITUENCYEXPLORERWIDGET_H
#define CONSTITUENCYEXPLORERWIDGET_H

#include <QModelIndex>
#include <QWidget>
#include <QTimer>

#include <future>

class ConstituencyModel;
class PoliticianModel;
class PollResultModel;
class RotatingItemsWidget;
class QItemSelectionModel;

namespace Ui
{
class ConstituencyExplorerWidget;
}

class ConstituencyExplorerWidget : public QWidget
{
    Q_OBJECT

public:
    ConstituencyExplorerWidget(QWidget* parent = nullptr);
    ~ConstituencyExplorerWidget();

    void setConstituencyModel(ConstituencyModel* model);
    void setConstituencySelectionModel(QItemSelectionModel* selectionModel);
    void setPoliticianModel(PoliticianModel* model);
    void setPoliticianSelectionModel(QItemSelectionModel* selectionModel);
    void setPollResultModel(PollResultModel* model);
    void setPollResultSelectionModel(QItemSelectionModel* selectionModel);

private slots:
    void asynchronouslyRefreshData();
    void onDataRefreshTimerTimeout();
    void onConstituencySelectionChanged();

private:
    QModelIndex currentConstituencyIndex() const;
    int currentConstituencyId() const;
    QString currentConstituencyName() const;

    void refreshModels();

private:
    PoliticianModel* politicianModel_ = nullptr;
    ConstituencyModel* constituencyModel_ = nullptr;
    PollResultModel* pollResultModel_ = nullptr;
    QItemSelectionModel* constituencySelectionModel_ = nullptr;

    std::future<void> fut_;
    QTimer dataRefreshTimer_;

    RotatingItemsWidget* rotatingItemsLoadScreen_ = nullptr;

    Ui::ConstituencyExplorerWidget* ui_;
};

#endif// CONSTITUENCYEXPLORERWIDGET_H
