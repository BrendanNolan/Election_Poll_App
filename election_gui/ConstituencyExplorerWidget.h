#ifndef CONSTITUENCYEXPLORERWIDGET_H
#define CONSTITUENCYEXPLORERWIDGET_H

#include <QWidget>

class ConstituencyWidget;

namespace Ui
{
    class ConstituencyExplorerWidget;
}

class ConstituencyExplorerWidget : public QWidget
{
    ConstituencyExplorerWidget(QWidget* parent);

signals:
    void politicianClicked(const QModelIndex& index);

private:
    ConstituencyWidget* constituencyWidget_;
    Ui::ConstituencyExplorerWidget* ui_;
};

#endif // CONSTITUENCYEXPLORERWIDGET_H
