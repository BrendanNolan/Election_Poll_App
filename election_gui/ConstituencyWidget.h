#ifndef CONSTITUENCYWIDGET_H
#define CONSTITUENCYWIDGET_H

#include <QWidget>

class ConstituencyModel;
class QItemSelectionModel;

class ConstituencyWidget : public QWidget
{
public:
    explicit ConstituencyWidget(
        QWidget* parent = nullptr,
        Qt::WindowFlags flags = Qt::WindowFlags());

    void setModel(ConstituencyModel* constituencyModel);
    void setSelectionModel(QItemSelectionModel* selectionModel);

signals:
    void constituencyClicked(const QModelIndex& index);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    void loadWidgetColours();

private:
    ConstituencyModel* constituencyModel_;
    QItemSelectionModel* constituencySelectionModel_;
};

#endif // CONSTITUENCYWIDGET_H
