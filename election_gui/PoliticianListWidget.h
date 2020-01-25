#ifndef PoliticianListWidget_H
#define PoliticianListWidget_H

#include <QModelIndex>
#include <QWidget>

class ConstituencyWidget;
class ConstituencyModel;
class PoliticianModel;
class QItemSelection;
class QItemSelectionModel;

namespace Ui
{
    class PoliticianListWidget;
}

class PoliticianListWidget : public QWidget
{
    Q_OBJECT

public:
    PoliticianListWidget(
        QWidget* parent = nullptr,
        Qt::WindowFlags flags = Qt::WindowFlags());
    ~PoliticianListWidget();

    void setPoliticianModel(PoliticianModel* model);
    void setPoliticianSelectionModel(QItemSelectionModel* selectionModel);
    void setConstituencyModel(ConstituencyModel* model);
    void setConstituencySelectionModel(QItemSelectionModel* selectionModel);

private slots:
    void onconstituencyDataChanged(
        const QModelIndex& topLeft, 
        const QModelIndex& bottomRight);

private:
    QModelIndexList	selectedPoliticians() const;
    QModelIndex currentConstituency() const;
    void loadConstituency();

private:
    PoliticianModel* politicianModel_;
    QItemSelectionModel* politicianSelectionModel_;
    ConstituencyModel* constituencyModel_;
    QItemSelectionModel* constituencySelectionModel_;
    Ui::PoliticianListWidget* ui_;
};

#endif // PoliticianListWidget_H
