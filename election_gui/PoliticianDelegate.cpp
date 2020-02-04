#include "PoliticianDelegate.h"

#include <QPainter>

namespace
{
    const auto PREFERRED_WIDTH = 60;
    const auto PREFERRED_HEIGHT = 60;
}

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
    const QModelIndex& /*index*/) const
{
    return QSize(PREFERRED_WIDTH, PREFERRED_HEIGHT);
}
