#ifndef CONSTITUENCYEXPLORERWIDGET_H
#define CONSTITUENCYEXPLORERWIDGET_H

#include <QWidget>

class ConstituencyModel;
class ConstituencyWidget;
class PoliticianModel;
class QItemSelectionModel;
class QModelIndex;

namespace Ui
{
    class ConstituencyExplorerWidget;
}

class ConstituencyExplorerWidget : public QWidget
{
    Q_OBJECT

public:
    ConstituencyExplorerWidget(QWidget* parent);
    ~ConstituencyExplorerWidget();

    void setConstituencyModel(ConstituencyModel* model);
    void setConstituencySelectionModel(QItemSelectionModel* selectionModel);
    void setPoliticianModel(PoliticianModel* model);
    void setPoliticianSelectionModel(QItemSelectionModel* selectionModel);

private slots:
    void onConstituencyActivated(const QModelIndex& index);

private:
    ConstituencyModel* constituencyModel_;
    QItemSelectionModel* constituencySelectionModel_;
    PoliticianModel* politicianModel_;
    QItemSelectionModel* politicianSelectionModel_;

    Ui::ConstituencyExplorerWidget* ui_;
};

#endif // CONSTITUENCYEXPLORERWIDGET_H
