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
    if (pixmapCache_.contains(path))
    {
        return pixmapCache_[path];
    }
    else
    {
        auto pixmap = QPixmap(path).scaled(
            PREFERRED_WIDTH, PREFERRED_HEIGHT, Qt::IgnoreAspectRatio);
        pixmapCache_[path] = pixmap;
        return pixmap;
    }
}

void PoliticianPictureProxyModel::setCacheCapacity(int capacity)
{
    pixmapCache_.setCapacity(capacity);
}

PoliticianModel* PoliticianPictureProxyModel::politicianModel() const
{
    auto ret = qobject_cast<PoliticianModel*>(sourceModel());
    Q_ASSERT(ret);
    return ret;
}
