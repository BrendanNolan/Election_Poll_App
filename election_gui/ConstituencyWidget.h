#ifndef CONSTITUENCYWIDGET_H
#define CONSTITUENCYWIDGET_H

#include <QHash>
#include <QModelIndex>
#include <QRect>
#include <QVector>
#include <QWidget>

#include "Constituency.h"

class ConstituencyModel;
class QItemSelectionModel;
class QPoint;
class QRect;

class ConstituencyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConstituencyWidget(
        QWidget* parent = nullptr,
        Qt::WindowFlags flags = Qt::WindowFlags());

    void setModel(ConstituencyModel* constituencyModel);
    void setSelectionModel(QItemSelectionModel* selectionModel);

signals:
    void constituencyActivated(const QModelIndex& index);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void loadIndexRectCache(); // Lots of constituencyModel_'s signals should be connected to this, like QAbstractItemModel::rowsAdded, QAbstractItemModel::rowsRemoved,  

private:
    void loadWidgetColours();
    QModelIndex indexAtPoint(const QPoint& point) const;

private:
    ConstituencyModel* constituencyModel_;
    QItemSelectionModel* constituencySelectionModel_;
    QVector<QRect> constituencyRectangles_;
    QHash<QModelIndex, QRect> indexRectCache_;
};

#endif // CONSTITUENCYWIDGET_H
