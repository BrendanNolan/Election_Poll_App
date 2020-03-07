#include "PixmapCreatingProxyModel.h"

#include "PixmapCreatingFunctor.h"

namespace
{
const auto PREFERRED_WIDTH = 60;
const auto PREFERRED_HEIGHT = 60;
}// namespace

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
{
}

QVariant PixmapCreatingProxyModel::data(
    const QModelIndex& index, int role) const
{
    if (role != Qt::DecorationRole)
        return QIdentityProxyModel::data(index, role);
    auto id = sourceModel()->data(index, ); // uh oh. Cannot ask for IdRole. All we have is a QAbstractItemModel
}

void PixmapCreatingProxyModel::setSourceModel(QAbstractItemModel* source)
{
    if (source == sourceModel())
        return;
    clearCache();
    QIdentityProxyModel::setSourceModel(source);
}

void PixmapCreatingProxyModel::setCacheCapacity(int capacity)
{
    cacheCapacity_ = capacity;
}

void PixmapCreatingProxyModel::removeFromCache(int id)
{
    for (auto& pair : pixmapCache_)
    {
        if (pair.first == id)
        {
            pixmapCache_.removeOne(pair);
            return;
        }
    }
}

void PixmapCreatingProxyModel::clearCache()
{
    pixmapCache_.clear();
}
