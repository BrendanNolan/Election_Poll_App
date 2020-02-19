#ifndef CONSTITUENCYEXPLORERWIDGET_H
#define CONSTITUENCYEXPLORERWIDGET_H

#include <QList>
#include <QModelIndex>
#include <QWidget>

class ConstituencyModel;
class ConstituencyWidget;
class PoliticianModel;
class PollResultModel;
class QHBoxLayout;
class QItemSelectionModel;
class QModelIndex;

namespace Ui { class ConstituencyExplorerWidget; }

class ConstituencyExplorerWidget : public QWidget
{
    Q_OBJECT

public:
    ConstituencyExplorerWidget(QWidget* parent = nullptr);
    ~ConstituencyExplorerWidget();

    void setConstituencyModel(ConstituencyModel* model);
    void setConstituencySelectionModel(QItemSelectionModel* selectionModel);
    void setPoliticianModel(PoliticianModel* model);
    void setPoliticianSelectionModel(QItemSelectionModel* selectionModel);
    void setPollResultModel(PollResultModel* model);
    void setPollResultSelectionModel(QItemSelectionModel* selectionModel);

    QHBoxLayout* buttonLayout();

signals:
    void politicianActivated(const QModelIndex& politicianIndex);
    void politiciansActivated(const QList<QModelIndex>& politicianIndex);

private slots:
    void onConstituencySelectionChanged();
    
private:
    int currentConstituencyId() const;

private:
    PoliticianModel* politicianModel_ = nullptr;
    ConstituencyModel* constituencyModel_ = nullptr;
    PollResultModel* pollResultModel_;
    QItemSelectionModel* constituencySelectionModel_ = nullptr;

    Ui::ConstituencyExplorerWidget* ui_;
};

#endif // CONSTITUENCYEXPLORERWIDGET_H
