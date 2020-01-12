#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ConstituencyWidget;
class PoliticianModel;

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
public:
    MainWindow(
        QWidget* parent = nullptr,
        Qt::WindowFlags flags = Qt::WindowFlags());

signals:
    void clicked(const QModelIndex& index);

private:
    PoliticianModel* politicianModel_;

    ConstituencyWidget* constituencyWidget_;
    Ui::MainWindow* ui_;
};

#endif // MAINWINDOW_H
