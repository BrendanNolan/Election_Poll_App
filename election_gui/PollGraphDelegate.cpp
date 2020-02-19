#include "PollGraphDelegate.h"

#include <QPainter>
#include <QPixmap>

PollGraphDelegate::PollGraphDelegate(QObject * parent)
    : QStyledItemDelegate(parent)
{}

void PollGraphDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    QPixmap pixmap(1, 1);
    pixmap.fill(Qt::green);
    painter->drawPixmap(
        option.rect.x() + 20 - 10,
        option.rect.top() + 3,
        pixmap);
}

QSize PollGraphDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    return QSize(10, 10);
}
