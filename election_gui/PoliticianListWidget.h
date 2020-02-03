#ifndef PoliticianListWidget_H
#define PoliticianListWidget_H

#include <QModelIndex>
#include <QWidget>

class ConstituencyWidget;
class ConstituencyModel;
class PoliticianPictureProxyModel;
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

    void setPoliticianPictureProxyModel(PoliticianPictureProxyModel* model);
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

    Ui::PoliticianListWidget* ui_;
};

#endif // PoliticianListWidget_H
