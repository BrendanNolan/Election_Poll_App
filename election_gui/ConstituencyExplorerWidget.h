#ifndef CONSTITUENCYEXPLORERWIDGET_H
#define CONSTITUENCYEXPLORERWIDGET_H

#include <QList>
#include <QModelIndex>
#include <QWidget>

class ConstituencyPixmapProxyModel;
class ConstituencyWidget;
class PoliticianPictureProxyModel;
class QItemSelectionModel;
class QModelIndex;

namespace Ui { class ConstituencyExplorerWidget; }

class ConstituencyExplorerWidget : public QWidget
{
    Q_OBJECT

public:
    ConstituencyExplorerWidget(QWidget* parent = nullptr);
    ~ConstituencyExplorerWidget();

    void setConstituencyModel(ConstituencyPixmapProxyModel* model);
    void setConstituencySelectionModel(QItemSelectionModel* selectionModel);
    void setPoliticianModel(PoliticianPictureProxyModel* model);
    void setPoliticianSelectionModel(QItemSelectionModel* selectionModel);

signals:
    void politicianActivated(const QModelIndex& politicianIndex);
    void politiciansActivated(const QList<QModelIndex>& politicianIndex);

private:
    Ui::ConstituencyExplorerWidget* ui_;
};

#endif // CONSTITUENCYEXPLORERWIDGET_H
