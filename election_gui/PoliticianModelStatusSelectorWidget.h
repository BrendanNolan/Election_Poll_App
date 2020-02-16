#ifndef POLITICIANMODELSTATUSSELECTORWIDGET_H
#define POLITICIANMODELSTATUSSELECTORWIDGET_H

#include <QWidget>

class PoliticianModel;

namespace Ui { class PoliticianModelStatusSelectorWidget;  }

class PoliticianModelStatusSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PoliticianModelStatusSelectorWidget(
        QWidget* parent = nullptr,
        PoliticianModel* politicianModel = nullptr);

    void setPoliticianModel(PoliticianModel* model);

    void enableRadioButtons();
    void disableRadioButtons();

private:
    void connectWith(PoliticianModel* model);

private:
    Ui::PoliticianModelStatusSelectorWidget* ui_;
};

#endif // POLITICIANMODELSTATUSSELECTORWIDGET_H
