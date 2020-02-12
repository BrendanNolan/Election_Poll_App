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

private :
    void refreshModels();

private:
    ConstituencyExplorerWidget* constituencyExplorerWidget_ = nullptr;
    RotatingItemsWidget* rotatingItemsWidget_;

    ConstituencyModel* constituencyModel_;
    PoliticianModel* politicianModel_;

    std::future<void> fut_;
    mutable std::mutex mutex_;
    QTimer timer_;
};

#endif // MAINWINDOW_H
