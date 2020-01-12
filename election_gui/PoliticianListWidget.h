#ifndef PoliticianListWidget_H
#define PoliticianListWidget_H

#include <QWidget>

class ConstituencyWidget;
class PoliticianModel;

namespace Ui
{
    class PoliticianListWidget;
}

class PoliticianListWidget : public QWidget
{
public:
    PoliticianListWidget(
        QWidget* parent = nullptr,
        Qt::WindowFlags flags = Qt::WindowFlags());

signals:
    void clicked(const QModelIndex& index);

private:
    PoliticianModel* politicianModel_;
    Ui::PoliticianListWidget* ui_;
};

#endif // PoliticianListWidget_H
