#include "PoliticianPictureProxyModel.h"

#include <QtGlobal>

#include <QFileInfo>

#include "PoliticianModel.h"

namespace
{
const auto PREFERRED_WIDTH = 60;
const auto PREFERRED_HEIGHT = 60;
}// namespace

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
    auto path = politicianModel()
                    ->data(index, PoliticianModel::FilePathRole)
                    .toString();
    if (!pixmapCache_.contains(path))
        return QPixmap();
    return pixmapCache_[path];
}

PoliticianModel* PoliticianPictureProxyModel::politicianModel() const
{
    auto ret = qobject_cast<PoliticianModel*>(sourceModel());
    Q_ASSERT(ret);
    return ret;
}
