#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ConstituencyExplorerWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    ConstituencyExplorerWidget* constituencyExplorerWidget_;
};

#endif // MAINWINDOW_H
