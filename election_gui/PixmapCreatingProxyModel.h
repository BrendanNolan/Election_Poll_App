#ifndef PIXMAPCREATINGPROXYMODEL_H
#define PIXMAPCREATINGPROXYMODEL_H

#include <QHash>
#include <QIdentityProxyModel>
#include <QModelIndex>
#include <QPixmap>

#include <memory>

class PixmapCreatingFunctor;

class PixmapCreatingProxyModel : public QIdentityProxyModel
{
public:
    PixmapCreatingProxyModel(
        std::unique_ptr<PixmapCreatingFunctor> pixmapFunctor,
        QObject* parent = nullptr);
    ~PixmapCreatingProxyModel();

    QVariant data(
        const QModelIndex& index, int role = Qt::DecorationRole) const override;
    void setSourceModel(QAbstractItemModel* source) override;

protected:
    void reloadCache();

private:
    virtual void partiallyReloadCache(
        const QModelIndex& startIndex, int count);

private:
    std::unique_ptr<PixmapCreatingFunctor> pixmapFunctor_;
    QHash<QModelIndex, QPixmap> pixmapCache_;
};

#endif // PIXMAPCREATINGPROXYMODEL_H
