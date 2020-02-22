#ifndef PIXMAPCACHINGPROXYMODEL_H
#define PIXMAPCACHINGPROXYMODEL_H

#include <QHash>
#include <QIdentityProxyModel>
#include <QModelIndex>
#include <QPixmap>

#include <memory>

class PixmapCreatingFunctor;

class PixmapCachingProxyModel : public QIdentityProxyModel
{
public:
    PixmapCachingProxyModel(
        std::unique_ptr<PixmapCreatingFunctor> pixmapFunctor,
        QObject* parent = nullptr);
    ~PixmapCachingProxyModel();

    QVariant data(
        const QModelIndex& index, int role = Qt::DecorationRole) const override;
    void setSourceModel(QAbstractItemModel* source) override;

protected:
    void reloadCache();

private:
    virtual void partiallyReloadCache(
        const QModelIndex& startIndex, int count) = 0;

private:
    std::unique_ptr<PixmapCreatingFunctor> pixmapFunctor_;
    QHash<QModelIndex, QPixmap> pixmapCache_;
};

#endif // PIXMAPCACHINGPROXYMODEL_H
