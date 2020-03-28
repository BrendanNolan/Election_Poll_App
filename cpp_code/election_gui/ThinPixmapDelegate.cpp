#include "ThinPixmapDelegate.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QPainter>
#include <QPixmap>

ThinPixmapDelegate::ThinPixmapDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void ThinPixmapDelegate::paint(
    QPainter* painter,
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    painter->save();

    auto pixmap =
        index.model()->data(index, Qt::DecorationRole).value<QPixmap>();
    painter->drawPixmap(option.rect.x(), option.rect.y(), pixmap);
    if (option.state.testFlag(QStyle::State_Selected))
    {
        QPixmap littlePixmap(7, 7);
        littlePixmap.fill(Qt::red);
        painter->drawPixmap(
            option.rect.x() + pixmap.width() - 10,
            option.rect.top() + 3,
            littlePixmap);
    }

    painter->restore();
}

QSize ThinPixmapDelegate::sizeHint(
    const QStyleOptionViewItem& /*option*/, const QModelIndex& index) const
{
    return index.model()
        ->data(index, Qt::DecorationRole)
        .value<QPixmap>()
        .size();
}
