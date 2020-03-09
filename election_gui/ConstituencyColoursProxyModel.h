#ifndef CONSTITUENCYCOLOURSPROXYMODEL_H
#define CONSTITUENCYCOLOURSPROXYMODEL_H

#include <QIdentityProxyModel>
#include <QColor>
#include <QPair>
#include <QPixmap>
#include <QVector>

#include "PoliticianModel.h"

class ConstituencyModel;

class ConstituencyColoursProxyModel : public QIdentityProxyModel
{
    Q_OBJECT

public:
    ConstituencyColoursProxyModel(
        ConstituencyModel& constituencyModel,
        const PoliticianModel& politicianModel,
        QObject* parent = nullptr);
    QVariant data(
        const QModelIndex& index, int role = Qt::DecorationRole) const override;
    void setMaxCacheCapacity(int capacity);

private:
    void insertToCacheWhileRespectingCapacity(
        const QVector<QColor>& colours, const QPixmap& pixmap) const;
    ConstituencyModel* constituencyModel() const;

private:
    mutable PoliticianModel politicianModel_;
    mutable QVector<QPair<QVector<QColor>, QPixmap>> pixmapCache_;
    int maxCacheCapacity_ = 50;
    QPixmap blackPixmap_;
};

#endif// CONSTITUENCYCOLOURSPROXYMODEL_H
