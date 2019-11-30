#include "ConstituencyModel.h"

QVariant ConstituencyModel::data(const QModelIndex &index, int role) const
{
    auto row = index.row();
    switch (role)
    {
        const auto& constituency = constituencies_[row];
        case Qt::DisplayRole:
        {
            return constituency.pictoralRepresentation().fileName();
        }
        case LatitudeRole:
        {
            return constituency
        }
        case LongitudeRole:
        {

        }
        case NameRole:
        {

        }
        case CurrentPartyRole:
        {

        }
        case CurrentMPRole:
        {

        }
        default:
        {

        }
    }
}

int ConstituencyModel::rowCount() const
{
    return constituencies_.size();
}
