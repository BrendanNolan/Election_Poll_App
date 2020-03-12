#include "PoliticianPictureProxyModel.h"

#include <QtGlobal>

#include <QFileInfo>

#include <algorithm>

#include "PoliticianModel.h"

namespace
{
const auto PREFERRED_WIDTH = 60;
const auto PREFERRED_HEIGHT = 60;
}// namespace

PoliticianPictureProxyModel::PoliticianPictureProxyModel(
    PoliticianModel* politicianModel, QObject* parent)
    : QIdentityProxyModel(parent)
    , blackPixmap_(1, 1)
{
    setSourceModel(politicianModel);
    blackPixmap_.fill(Qt::black);
}

QVariant PoliticianPictureProxyModel::data(
    const QModelIndex& index, int role) const
{
    if (role != Qt::DecorationRole)
        return QIdentityProxyModel::data(index, role);
    auto path = politicianModel()
                    ->data(index, PoliticianModel::FilePathRole)
                    .toString();
    auto found = std::find_if(
        pixmapCache_.begin(),
        pixmapCache_.end(),
        [&path](const QPair<QString, QPixmap>& pair) {
            return pair.first == path;
        });
    if (found != pixmapCache_.end())
    {
        return found->second;
    }
    else
    {
        auto pixmap = QPixmap(path).scaled(
            PREFERRED_WIDTH, PREFERRED_HEIGHT, Qt::IgnoreAspectRatio);
        insertIntoCacheWhileRespectingCapacity(path, pixmap);
        return pixmap;
    }
}

void PoliticianPictureProxyModel::setMaxCacheCapacity(int capacity)
{
    if (capacity < maxCacheCapacity_)
    {
        pixmapCache_.erase(
            pixmapCache_.end()
                - static_cast<ptrdiff_t>(maxCacheCapacity_ - capacity),
            pixmapCache_.end());
    }

    maxCacheCapacity_ = capacity;
}

PoliticianModel* PoliticianPictureProxyModel::politicianModel() const
{
    auto ret = qobject_cast<PoliticianModel*>(sourceModel());
    Q_ASSERT(ret);
    return ret;
}

void PoliticianPictureProxyModel::insertIntoCacheWhileRespectingCapacity(
    const QString& filePath, const QPixmap& pixmap) const
{
    if (pixmapCache_.size() > maxCacheCapacity_)
        pixmapCache_.pop_front();
    pixmapCache_.append(QPair<QString, QPixmap>(filePath, pixmap));
}
