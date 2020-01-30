#ifndef CONSTITUENCYPIXMAPPROXYMODEL_H
#define CONSTITUENCYPIXMAPPROXYMODEL_H

#include <QPixmap>
#include <QIdentityProxyModel>
#include <QMap>

class ConstituencyModel;
class PoliticianModel;

class ConstituencyPixmapProxyModel : public QIdentityProxyModel
{
public:
    // In this constructor, will probably need to connect politicianModel_ 
    // and sourceModel() signals to lambdas which just call
    // ConstituencyPixmapProxyModel::loadConstituencyPixmapCache() and 
    // ConstituencyPixmapProxyModel::reLoadConstituencyPixmapCache().
    ConstituencyPixmapProxyModel(
        QObject* parent = nullptr,
        PoliticianModel* politicianModel = nullptr);
    
    QVariant data(
        const QModelIndex &proxyIndex, 
        int role = Qt::DisplayRole) const override;
    void setSourceModel(QAbstractItemModel* sourceModel) override;

    void setPoliticianModel(PoliticianModel* politicianModel);
    ConstituencyModel* constituencyModel() const;
    
private:
    void loadConstituencyPixmapCache(const QModelIndex& startIndex, int count);
    void reLoadConstituencyPixmapCache();

private:
    PoliticianModel* politicianModel_ = nullptr;
    QMap<QModelIndex, QPixmap> constituencyPixmapCache_;
};

#endif // CONSTITUENCYPIXMAPPROXYMODEL_H
