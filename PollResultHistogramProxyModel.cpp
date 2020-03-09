#include "PollResultHistogramProxyModel.h"

PollResultHistogramProxyModel::PollResultHistogramProxyModel(
    QObject* parent, PollResultModel* pollResultModel)
{
}

QVariant PollResultHistogramProxyModel::data(
    const QModelIndex & index, int role) const
{
}

void PollResultHistogramProxyModel::setSourceModel(QAbstractItemModel * source)
{
}

PollResultModel * PollResultHistogramProxyModel::pollResultModel() const
{
}

void PollResultHistogramProxyModel::partiallyReloadCache(const QModelIndex & startIndex, int count)
{
}

void PollResultHistogramProxyModel::reloadCache()
{
}
