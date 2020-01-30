#include "ConstituencyColoursProxyModel.h"

#include <QtGlobal>

#include "ConstituencyModel.h"
#include "PoliticianModel.h"

void ConstituencyColoursProxyModel::setSourceModel(
    QAbstractItemModel * sourceModel)
{
    Q_ASSERT(qobject_cast<ConstituencyModel*>(sourceModel));
    QIdentityProxyModel::setSourceModel(sourceModel);
}