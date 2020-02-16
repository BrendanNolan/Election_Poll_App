#ifndef CONSTITUENCYDRILLDOWNWIDGET_H
#define CONSTITUENCYDRILLDOWNWIDGET_H

#include <QModelIndex>
#include <QWidget>

class ConstituencyModel;
class PoliticianPictureProxyModel;
class QItemSelection;
class QItemSelectionModel;

namespace Ui
{
    class ConstituencyDrillDownWidget;
}

class ConstituencyDrillDownWidget : public QWidget
{
    Q_OBJECT

public:
    ConstituencyDrillDownWidget(
        QWidget* parent = nullptr,
        Qt::WindowFlags flags = Qt::WindowFlags());
    ~ConstituencyDrillDownWidget();

    void setPoliticianModel(PoliticianPictureProxyModel* model);
    void setPoliticianSelectionModel(QItemSelectionModel* selectionModel);
    void setConstituencyModel(ConstituencyModel* model);
    void setConstituencySelectionModel(QItemSelectionModel* selectionModel);

signals:
    void pictureActivated(const QModelIndex& pictureIndex);
    void picturesActivated(const QModelIndexList& pictureIndexes);

private slots:
    void onConstituencyDataChanged(
        const QModelIndex& topLeft, 
        const QModelIndex& bottomRight);

private:
    QModelIndexList	selectedPoliticians() const;
    QModelIndex constituencyToDisplay() const;
    void loadConstituency();
    void setToInvalidState();
    void enableRadioButtons();
    void disableRadioButtons();

private:
    PoliticianPictureProxyModel* politicianProxyModel_ = nullptr;
    ConstituencyModel* constituencyModel_ = nullptr;
    QItemSelectionModel* constituencySelectionModel_ = nullptr;

    Ui::ConstituencyDrillDownWidget* ui_;
};

#endif // CONSTITUENCYDRILLDOWNWIDGET_H
