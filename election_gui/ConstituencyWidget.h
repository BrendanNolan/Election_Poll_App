#ifndef CONSTITUENCYWIDGET_H
#define CONSTITUENCYWIDGET_H

#include <QModelIndex>
#include <QVector>
#include <QWidget>

class ConstituencyModel;
class QItemSelectionModel;
class QPoint;
class QRect;

class ConstituencyWidget : public QWidget
{
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

private:
    void loadWidgetColours();
    QModelIndex indexAtPoint(const QPoint& point) const;

private:
    ConstituencyModel* constituencyModel_;
    QItemSelectionModel* constituencySelectionModel_;
    QVector<QRect> constituencyRectangles_;
};

#endif // CONSTITUENCYWIDGET_H
