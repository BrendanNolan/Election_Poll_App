#ifndef PIXMAPCREATINGPROXYMODEL_H
#define PIXMAPCREATINGPROXYMODEL_H

#include <QQueue>
#include <QIdentityProxyModel>
#include <QModelIndex>
#include <QPixmap>

#include <memory>

class PixmapCreatingFunctor;

class PixmapCreatingProxyModel : public QIdentityProxyModel
{
    Q_OBJECT

public:
    PixmapCreatingProxyModel(
        std::unique_ptr<PixmapCreatingFunctor> pixmapFunctor,
        QAbstractItemModel* sourcemodel,
        QObject* parent = nullptr);
    ~PixmapCreatingProxyModel();

    QVariant data(
        const QModelIndex& index, int role = Qt::DecorationRole) const override;
    void setSourceModel(QAbstractItemModel* source) override;
    void setCacheCapacity(int capacity);

public slots:
    void removeFromCache(int id);
    void clearCache();

private:
    std::unique_ptr<PixmapCreatingFunctor> pixmapFunctor_;
    mutable QQueue<QPair<int, QPixmap>> pixmapCache_;
    int cacheCapacity_ = 100;
};

#endif// PIXMAPCREATINGPROXYMODEL_H
