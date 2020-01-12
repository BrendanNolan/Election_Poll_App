#ifndef PoliticianListWidget_H
#define PoliticianListWidget_H

#include <QModelIndex>
#include <QWidget>

class ConstituencyWidget;
class PoliticianModel;
class QItemSelection;
class QItemSelectionModel;

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
    ~PoliticianListWidget();

    void setModel(PoliticianModel* model);
    void setSelectionModel(QItemSelectionModel* selectionModel);

    QModelIndexList	selectedPoliticians() const;

signals:
    void dataChanged(
        const QModelIndex& topLeft, const QModelIndex& bottomRight);
    void politicianActivated(const QModelIndex& index);
    void currentChanged(
        const QModelIndex& current, const QModelIndex& previous);
    void selectionChanged(
        const QItemSelection& selected, const QItemSelection& deselected);


public slots:
    void setConstituency(int constituencyId);

private:
    PoliticianModel* politicianModel_;
    QItemSelectionModel* politicianSelectionModel_;
    Ui::PoliticianListWidget* ui_;
};

#endif // PoliticianListWidget_H
