#ifndef CONSTITUENCYCOLOURSPROXYMODEL_H
#define CONSTITUENCYCOLOURSPROXYMODEL_H

#include <QIdentityProxyModel>
#include <QColor>
#include <QPixmap>
#include <QVector>

#include "PoliticianModel.h"
#include "RollingKeyValueCache.h"

class ConstituencyModel;

class ConstituencyColoursProxyModel : public QIdentityProxyModel
{
    Q_OBJECT

public:
    ConstituencyColoursProxyModel(
        ConstituencyModel* constituencyModel,
        const PoliticianModel& politicianModel,
        QObject* parent = nullptr);
    QVariant data(
        const QModelIndex& index, int role = Qt::DecorationRole) const override;

    void setCacheCapacity(int capacity);
    ConstituencyModel* constituencyModel() const;

private:
    mutable PoliticianModel politicianModel_;
    mutable RollingKeyValueCache<QVector<QColor>, QPixmap> pixmapCache_;
    QPixmap blackPixmap_;
};

#endif// CONSTITUENCYCOLOURSPROXYMODEL_H
