#ifndef CONSTITUENCYWIDGET_H
#define CONSTITUENCYWIDGET_H

#include <QWidget>

#include "ui_ConstituencyWidget.h"

class ConstituencyWidgetView;

namespace Ui
{
    class ConstituencyWidget;
}

class ConstituencyWidget : public QWidget
{
public:
    explicit ConstituencyWidget(QWidget* parent = nullptr);

private:
    Ui::ConstituencyWidget* ui_;
    ConstituencyWidgetView* view_;
};

#endif // CONSTITUENCYWIDGET_H
