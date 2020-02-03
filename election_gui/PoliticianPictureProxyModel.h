#ifndef POLITICIANPICTUREPROXYMODEL_H
#define POLITICIANPICTUREPROXYMODEL_H

#include <QFileInfo>
#include <QHash>
#include <QIdentityProxyModel>
#include <QPixmap>

class PoliticianModel;

class PoliticianPictureProxyModel : public QIdentityProxyModel
{
public:
    PoliticianPictureProxyModel(
        QObject* parent = nullptr, PoliticianModel* politicianModel = nullptr);
    QVariant data(
        const QModelIndex& index, int role = Qt::DisplayRole) const override;
    void setSourceModel(QAbstractItemModel* source) override;
    PoliticianModel* politicianModel() const;

private:
    void partiallyReloadCache(const QModelIndex& startIndex, int count);
    void reloadCache();

private:
    QHash<QFileInfo, QPixmap> pixmapCache_;
};

#endif // POLITICIANPICTUREPROXYMODEL_H
