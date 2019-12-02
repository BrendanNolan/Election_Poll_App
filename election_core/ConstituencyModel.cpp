#include "ConstituencyModel.h"

int ConstituencyModel::rowCount() const
{
    return constituencies_.size();
}

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
            return constituency.latitude();
        }
        case LongitudeRole:
        {
            return constituency.longitude();
        }
        case NameRole:
        {
            return constituency.name();
        }
        case CurrentPartyRole:
        {
            return constituency.mp().party_;
        }
        case CurrentMPRole:
        {
            return constituency.mp().name_;
        }
        default:
        {
            return QVariant();
        }
    }
}


