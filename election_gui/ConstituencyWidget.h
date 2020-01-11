#ifndef CONSTITUENCYWIDGET_H
#define CONSTITUENCYWIDGET_H

#include <QWidget>

#include "ui_ConstituencyWidget.h"

class ConstituencyModel;
class QItemSelectionModel;

namespace Ui
{
    class ConstituencyWidget;
}

class ConstituencyWidget : public QWidget
{
public:
    explicit ConstituencyWidget(
        QWidget* parent = nullptr,
        Qt::WindowFlags flags = Qt::WindowFlags());

    void setModel(ConstituencyModel* constituencyModel);
    void setSelectionModel(QItemSelectionModel* selectionModel);

signals:
    void clicked(const QModelIndex& index);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    void loadWidgetColours();

private:
    ConstituencyModel* constituencyModel_;
    QItemSelectionModel* constituencySelectionModel_;

    Ui::ConstituencyWidget* ui_;
};

#endif // CONSTITUENCYWIDGET_H
