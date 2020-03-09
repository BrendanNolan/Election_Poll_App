#include "PollResultHistogramProxyModel.h"

PollResultHistogramProxyModel::PollResultHistogramProxyModel(
    QObject* parent, PollResultModel* pollResultModel)
{
}

QVariant PollResultHistogramProxyModel::data(
    const QModelIndex & index, int role) const
{
}

PollResultModel * PollResultHistogramProxyModel::pollResultModel() const
{
}
