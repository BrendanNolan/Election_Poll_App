#ifndef CONSTITUENCYWIDGETVIEW_H
#define CONSTITUENCYWIDGETVIEW_H

#include <QWidget>

class ConstituencyWidget;

class ConstituencyWidgetView : public QWidget
{
public:
    explicit ConstituencyWidgetView(QWidget* parent = nullptr);

signals:
    void clicked(const QModelIndex& index);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    ConstituencyWidget* constituencyWidget_;
};

#endif // CONSTITUENCYWIDGETVIEW_H
