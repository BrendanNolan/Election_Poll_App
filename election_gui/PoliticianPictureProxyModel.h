#ifndef POLITICIANPICTUREPROXYMODEL_H
#define POLITICIANPICTUREPROXYMODEL_H

#include <QHash>
#include <QIdentityProxyModel>
#include <QPixmap>
#include <QString>

class PoliticianModel;

class PoliticianPictureProxyModel : public QIdentityProxyModel
{
public:
    PoliticianPictureProxyModel(
        QObject* parent = nullptr, PoliticianModel* politicianModel = nullptr);
    QVariant data(
        const QModelIndex& index, int role = Qt::DecorationRole) const override;

private:
    PoliticianModel* politicianModel() const;

private:
    QHash<QString, QPixmap> pixmapCache_;
};

#endif// POLITICIANPICTUREPROXYMODEL_H
