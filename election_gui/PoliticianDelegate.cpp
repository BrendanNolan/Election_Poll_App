#include "PoliticianDelegate.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QPainter>
#include <QPixmap>

PoliticianDelegate::PoliticianDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{}

void PoliticianDelegate::paint(
    QPainter* painter,
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    painter->save();

    auto pixmap = index.model()->data(
        index, Qt::DecorationRole).value<QPixmap>();
    painter->drawPixmap(
        option.rect.x(),
        option.rect.y(),
        pixmap);

    painter->restore();
}

QSize PoliticianDelegate::sizeHint(
    const QStyleOptionViewItem& /*option*/,
    const QModelIndex& index) const
{
    return index.model()->data(index, Qt::DecorationRole)
        .value<QPixmap>().size();
}
