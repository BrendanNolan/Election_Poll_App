#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <future>

class ConstituencyModel;
class ConstituencyExplorerWidget;
class PoliticianModel;
class PollResultModel;
class RotatingItemsWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void asynchronouslyRefreshData();
    void onDataRefreshTimerTimeout();

private:
    void refreshModels();

private:
    ConstituencyExplorerWidget* constituencyExplorerWidget_ = nullptr;
    RotatingItemsWidget* rotatingItemsLoadScreen_ = nullptr;

    ConstituencyModel* constituencyModel_ = nullptr;
    PoliticianModel* politicianModel_ = nullptr;
    PollResultModel* pollResultModel_ = nullptr;

    std::future<void> fut_;
    QTimer dataRefreshTimer_;
};

#endif // MAINWINDOW_H
