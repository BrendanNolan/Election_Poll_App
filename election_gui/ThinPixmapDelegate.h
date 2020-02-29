#ifndef POLITICIANDELEGATE_H
#define POLITICIANDELEGATE_H

#include <QStyledItemDelegate>

class ThinPixmapDelegate : public QStyledItemDelegate
{
public:
    ThinPixmapDelegate(QObject* parent = nullptr);

    void paint(QPainter* painter,
        const QStyleOptionViewItem& option,
        const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem& option,
        const QModelIndex& index) const override;
};

#endif// POLITICIANDELEGATE_H
