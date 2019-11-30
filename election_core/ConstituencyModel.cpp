#include "ConstituencyModel.h"

QVariant ConstituencyModel::data(const QModelIndex &index, int role) const
{
    auto row = index.row();
    // to be continued ...
    // put a switch in here probs
}

int ConstituencyModel::rowCount() const
{
    return constituencies_.size();
}
