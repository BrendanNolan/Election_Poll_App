#include "PoliticianPictureProxyModel.h"

#include <QtGlobal>

#include <QFileInfo>

#include "PoliticianModel.h"

namespace
{
    const auto PREFERRED_WIDTH = 60;
    const auto PREFERRED_HEIGHT = 60;
}

PoliticianPictureProxyModel::PoliticianPictureProxyModel(
    QObject* parent, PoliticianModel* politicianModel)
    : QIdentityProxyModel(parent)
{
    setSourceModel(politicianModel);
}

QVariant PoliticianPictureProxyModel::data(
    const QModelIndex& index, int role) const
{
    if (role != Qt::DecorationRole)
        return QIdentityProxyModel::data(index, role);
    auto path = politicianModel()->data(
        index, PoliticianModel::FilePathRole).toString();
    if (!pixmapCache_.contains(path))
        return QPixmap();
    return pixmapCache_[path];
}

void PoliticianPictureProxyModel::setSourceModel(QAbstractItemModel* source)
{
    if (source)
        Q_ASSERT(qobject_cast<PoliticianModel*>(source));
    QIdentityProxyModel::setSourceModel(source);

    reloadCache();
    if (!source)
        return;

    connect(source, &QAbstractItemModel::modelReset,
        this, &PoliticianPictureProxyModel::reloadCache);
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

PoliticianModel* PoliticianPictureProxyModel::politicianModel() const
{
    return qobject_cast<PoliticianModel*>(sourceModel());
}

void PoliticianPictureProxyModel::partiallyReloadCache(
    const QModelIndex& startIndex, int count)
{
    if (!sourceModel() 
        || !politicianModel() 
        || count <= 0 
        || count + startIndex.row() > rowCount())
        return;
    const auto& politicianMod = *(politicianModel());
    for (auto i = 0; i < count; ++i)
    {
        auto path = politicianMod.data(
            index(startIndex.row() + i, 0), PoliticianModel::FilePathRole).
                toString();
        pixmapCache_[path] = QPixmap(path).scaled(
            PREFERRED_WIDTH, PREFERRED_HEIGHT);
    }
}

void PoliticianPictureProxyModel::reloadCache()
{
    pixmapCache_.clear();
    if (!sourceModel() || !politicianModel())
        return;
    partiallyReloadCache(index(0, 0), rowCount());
}
