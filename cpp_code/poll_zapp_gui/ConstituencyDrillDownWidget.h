#ifndef CONSTITUENCYDRILLDOWNWIDGET_H
#define CONSTITUENCYDRILLDOWNWIDGET_H

#include <QModelIndex>
#include <QWidget>

class PoliticianModel;
class PollResultModel;
class QItemSelection;
class QItemSelectionModel;
class QRadioButton;

namespace Ui
{
class ConstituencyDrillDownWidget;
}

class ConstituencyDrillDownWidget : public QWidget
{
    Q_OBJECT

public:
    ConstituencyDrillDownWidget(
        QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~ConstituencyDrillDownWidget();

    void setModels(
        PoliticianModel* politicianModel, 
        PollResultModel* pollResultModel);
    void setPoliticianSelectionModel(QItemSelectionModel* selectionModel);
    void setPollResultSelectionModel(QItemSelectionModel* selectionModel);

    void setDisplayedConstituencyName(const QString& name);

signals:
    void pictureActivated(const QModelIndex& pictureIndex);
    void picturesActivated(const QModelIndexList& pictureIndexes);

private slots:
    void onSittingRadioButtonToggled(bool checked);
    void onCandidatesRadioButtonToggled(bool checked);

private:
    QModelIndexList selectedPoliticians() const;
    void setToInvalidState();
    void enableRadioButtons();
    void disableRadioButtons();

private:
    PoliticianModel* politicianModel_;
    Ui::ConstituencyDrillDownWidget* ui_;
};

#endif// CONSTITUENCYDRILLDOWNWIDGET_H
