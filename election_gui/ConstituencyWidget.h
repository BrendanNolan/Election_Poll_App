#ifndef CONSTITUENCYWIDGET_H
#define CONSTITUENCYWIDGET_H

#include <QGraphicsView>
#include <QHash>
#include <QModelIndex>
#include <QRect>
#include <QVector>

#include "Constituency.h"

class ConstituencyModel;
class QGraphicsItem;
class QGraphicsScene;
class QItemSelectionModel;
class QPoint;
class QRect;

class ConstituencyWidget : public QGraphicsView
{
    Q_OBJECT

public:
    ConstituencyWidget(QGraphicsScene* scene, QWidget* parent = nullptr);
    explicit ConstituencyWidget(QWidget* parent = nullptr);

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
    void makeConnections();

private:
    ConstituencyModel* constituencyModel_;
    QItemSelectionModel* constituencySelectionModel_;
    QHash<QModelIndex, QGraphicsItem*> indexRectCache_;
};

#endif // CONSTITUENCYWIDGET_H
