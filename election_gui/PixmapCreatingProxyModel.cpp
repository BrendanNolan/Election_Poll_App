#include "PixmapCreatingProxyModel.h"

#include "PixmapCreatingFunctor.h"

namespace
{
    const auto PREFERRED_WIDTH = 60;
    const auto PREFERRED_HEIGHT = 60;
}

PixmapCreatingProxyModel::PixmapCreatingProxyModel(
    std::unique_ptr<PixmapCreatingFunctor> pixmapFunctor,
    QAbstractItemModel* sourceModel,
    QObject* parent)
    : QIdentityProxyModel(parent)
    , pixmapFunctor_(move(pixmapFunctor))
{
    setSourceModel(sourceModel);
}

PixmapCreatingProxyModel::~PixmapCreatingProxyModel()
{}

QVariant PixmapCreatingProxyModel::data(
    const QModelIndex& index, int role) const
{
    if (role != Qt::DecorationRole)
        return QIdentityProxyModel::data(index, role);
    if (!pixmapCache_.contains(index))
        return QPixmap();
    return pixmapCache_[index];
}

void PixmapCreatingProxyModel::setSourceModel(QAbstractItemModel* source)
{
    QIdentityProxyModel::setSourceModel(source);

    reloadCache();
    if (!source)
        return;

    connect(source, &QAbstractItemModel::modelReset,
        this, &PixmapCreatingProxyModel::reloadCache);
    connect(source, &QAbstractItemModel::rowsInserted,
        [this](const QModelIndex& /*parent*/, int first, int last) {
        partiallyReloadCache(index(first, 0), last - first + 1);
    });
    connect(source, &QAbstractItemModel::dataChanged,
        [this](const QModelIndex& topLeft, const QModelIndex& bottomRight) {
        auto count = bottomRight.row() - topLeft.row();
        if (count <= 0)
            return;
        partiallyReloadCache(topLeft, count);
    });
}

void PixmapCreatingProxyModel::partiallyReloadCache(
    const QModelIndex& startIndex, int count)
{
    if (!sourceModel()
        || count <= 0
        || count + startIndex.row() > rowCount())
        return;
    for (auto i = 0; i < count; ++i)
    {
        auto theIndex = index(startIndex.row() + i, 0);
        const auto& createPixmap = *pixmapFunctor_;
        pixmapCache_[theIndex] = createPixmap(theIndex).scaled(
            PREFERRED_WIDTH, PREFERRED_HEIGHT);
    }
}

void PixmapCreatingProxyModel::reloadCache()
{
    pixmapCache_.clear();
    if (!sourceModel())
        return;
    partiallyReloadCache(index(0, 0), rowCount());
}
