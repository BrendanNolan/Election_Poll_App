#ifndef POLITICIANPICTUREPROXYMODEL_H
#define POLITICIANPICTUREPROXYMODEL_H

#include <QIdentityProxyModel>
#include <QPixmap>
#include <QString>

#include "RollingKeyValueCache.h"

class PoliticianModel;

class PoliticianPictureProxyModel : public QIdentityProxyModel
{
public:
    PoliticianPictureProxyModel(
        PoliticianModel* politicianModel = nullptr, QObject* parent = nullptr);
    QVariant data(
        const QModelIndex& index, int role = Qt::DecorationRole) const override;

    void setCacheCapacity(int capacity);
    PoliticianModel* politicianModel() const;

private:
    mutable RollingKeyValueCache<QString, QPixmap> pixmapCache_;
    QPixmap blackPixmap_;
};

#endif// POLITICIANPICTUREPROXYMODEL_H
