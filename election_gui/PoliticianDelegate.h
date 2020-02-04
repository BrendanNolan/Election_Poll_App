#ifndef POLITICIANDELEGATE_H
#define POLITICIANDELEGATE_H

#include <QStyledItemDelegate>

class PoliticianDelegate : public QStyledItemDelegate
{
public:
    PoliticianDelegate(QObject* parent = nullptr);
    
public:
    void paint(
        QPainter* painter, 
        const QStyleOptionViewItem& option, 
        const QModelIndex& index) const override;
    QSize sizeHint(
        const QStyleOptionViewItem& option, 
        const QModelIndex& index) const override;
};

#endif // POLITICIANDELEGATE_H
