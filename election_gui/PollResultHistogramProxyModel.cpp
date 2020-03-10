#include "PollResultHistogramProxyModel.h"

#include <QtGlobal>

#include "PollResultModel.h"

PollResultHistogramProxyModel::PollResultHistogramProxyModel(
    PollResultModel* pollResultModel, QObject* parent)
    : QIdentityProxyModel(parent)
{
    setSourceModel(pollResultModel);
}

QVariant PollResultHistogramProxyModel::data(
    const QModelIndex& index, int role) const
{
    return sourceModel()->data(index, role);
}

PollResultModel* PollResultHistogramProxyModel::pollResultModel() const
{
    auto prm = qobject_cast<PollResultModel*>(sourceModel());
    Q_ASSERT(prm);
    return prm;
}
