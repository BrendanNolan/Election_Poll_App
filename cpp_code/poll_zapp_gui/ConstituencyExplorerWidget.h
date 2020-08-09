#ifndef CONSTITUENCYEXPLORERWIDGET_H
#define CONSTITUENCYEXPLORERWIDGET_H

#include <QModelIndex>
#include <QWidget>

#include <condition_variable>

class ConstituencyModel;
class PoliticianModel;
class PollResultModel;
class QDialog;
class QItemSelectionModel;

namespace Ui
{
class ConstituencyExplorerWidget;
}

class ConstituencyExplorerWidget : public QWidget
{
    Q_OBJECT

public:
    ConstituencyExplorerWidget(QWidget* parent = nullptr);
    ~ConstituencyExplorerWidget();

    void setModels(
        PoliticianModel* politicianModel,
        ConstituencyModel* constituencyModel,
        PollResultModel* pollResultModel);
    void setConstituencySelectionModel(QItemSelectionModel* selectionModel);
    void setPoliticianSelectionModel(QItemSelectionModel* selectionModel);
    void setPollResultSelectionModel(QItemSelectionModel* selectionModel);

private slots:
    void asynchronouslyRefreshModels();
    void onConstituencySelectionChanged();

private:
    QModelIndex selectedConstituencyIndex() const;
    int currentConstituencyId() const;
    QString currentConstituencyName() const;

    void reloadModels();
    bool refreshModels(
        std::condition_variable& condVar,
        std::mutex& mutex);

private:
    PoliticianModel* politicianModel_ = nullptr;
    ConstituencyModel* constituencyModel_ = nullptr;
    PollResultModel* pollResultModel_ = nullptr;
    QItemSelectionModel* constituencySelectionModel_ = nullptr;

    QDialog* loadScreen_ = nullptr;

    Ui::ConstituencyExplorerWidget* ui_;
};

#endif// CONSTITUENCYEXPLORERWIDGET_H
