#include "ConstituencyPixmapProxyModel.h"

#include <QtGlobal>

#include "ConstituencyModel.h"
#include "PoliticianModel.h"

ConstituencyPixmapProxyModel::ConstituencyPixmapProxyModel(
    QObject* parent, 
    PoliticianModel* politicianModel)
    : QIdentityProxyModel(parent)
    , politicianModel_(politicianModel)
{}

QVariant ConstituencyPixmapProxyModel::data(
    const QModelIndex& proxyIndex, 
    int role) const
{
    if (role != Qt::DisplayRole)
        return QIdentityProxyModel::data(proxyIndex, role);
    return constituencyPixmapCache_[proxyIndex];
}

void ConstituencyPixmapProxyModel::setSourceModel(
    QAbstractItemModel* sourceModel)
{
    Q_ASSERT(qobject_cast<ConstituencyModel*>(sourceModel));
    QIdentityProxyModel::setSourceModel(sourceModel);
    refreshConstituencyPixmapCache();
    if (!sourceModel)
        return;

    connect(sourceModel, &QAbstractItemModel::dataChanged,
        [this](const QModelIndex& topLeft, const QModelIndex& bottomRight) {
            auto count = bottomRight.row() - topLeft.row();
            if (count <= 0)
                return;
            partiallyRefreshPixmapCache(topLeft, count);
        });
}

void ConstituencyPixmapProxyModel::setPoliticianModel(
    PoliticianModel* politicianModel)
{
    politicianModel_ = politicianModel;
}

ConstituencyModel* ConstituencyPixmapProxyModel::constituencyModel() const
{
    return qobject_cast<ConstituencyModel*>(sourceModel());
}

void ConstituencyPixmapProxyModel::partiallyRefreshPixmapCache(
    const QModelIndex& startIndex, 
    int count)
{
    if (count <= 0)
        return;
    auto startRow = startIndex.row();
    for (auto i = 0; i < count; ++i)
    {
        auto pixmapUpdateIndex = index(startRow + i, 0);
        QPixmap pixmap(10, 10); // Will need to be more creative here in the end of course.
        pixmap.fill(Qt::red);
        constituencyPixmapCache_[pixmapUpdateIndex] = pixmap;
    }
}

void ConstituencyPixmapProxyModel::refreshConstituencyPixmapCache()
{

}
