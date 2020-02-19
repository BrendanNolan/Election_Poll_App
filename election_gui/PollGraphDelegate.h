#ifndef POLLGRAPHDELEGATE_H
#define POLLGRAPHDELEGATE_H

#include <QStyledItemDelegate>

/*
    THIS CURRENTLY HAS NOTHING MORE THAN A DUMMY IMPLEMENTATION
*/

class PollGraphDelegate : public QStyledItemDelegate
{
public:
    PollGraphDelegate(QObject* parent = nullptr);

    void paint(
        QPainter* painter,
        const QStyleOptionViewItem& option,
        const QModelIndex& index) const override;
    QSize sizeHint(
        const QStyleOptionViewItem& option,
        const QModelIndex& index) const override;
};

#endif // POLLGRAPHDELEGATE_H
