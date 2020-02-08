#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ConstituencyModel;
class ConstituencyExplorerWidget;
class PoliticianModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void doAsynchronousDataRefresh();

private :
    void refreshModels();

private:
    ConstituencyExplorerWidget* constituencyExplorerWidget_ = nullptr;

    ConstituencyModel* constituencyModel_;
    PoliticianModel* politicianModel_;
};

#endif // MAINWINDOW_H
