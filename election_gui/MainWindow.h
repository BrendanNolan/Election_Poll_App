#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <future>
#include <mutex>

class ConstituencyModel;
class ConstituencyExplorerWidget;
class PoliticianModel;
class RotatingItemsWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

public:
    void refreshData();

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

    std::future<void> fut_;
    mutable std::mutex mutex_;
    QTimer dataRefreshTimer_;
};

#endif // MAINWINDOW_H
