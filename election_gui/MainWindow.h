#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

signals:
    void dataRefreshed();

private slots:
    void asynchronouslyRefreshData();

private :
    void refreshModels();

private:
    ConstituencyExplorerWidget* constituencyExplorerWidget_ = nullptr;
    RotatingItemsWidget* rotatingItemsWidget_;

    ConstituencyModel* constituencyModel_;
    PoliticianModel* politicianModel_;
};

#endif // MAINWINDOW_H
