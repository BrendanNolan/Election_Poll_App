#include "ConstituencyModel.h"

#include <QMap>
#include <QString>

#include <algorithm>
#include <map>

#include "IConstituencyDatabaseManager.h"
#include "IDatabaseManagerFactory.h"
#include "IPoliticianDatabaseManager.h"

using namespace std;

ConstituencyModel::ConstituencyModel(
    const IDatabaseManagerFactory& factory,
    QObject* parent = nullptr)
    : QAbstractListModel(parent)
    , constituencyManager_(factory.createConstituencyDatabaseManager())
{
    constituencyManager_->init();
    loadConstituencies();
}

int ConstituencyModel::rowCount() const
{
    return constituencies_.size();
}

QVariant ConstituencyModel::data(const QModelIndex &index, int role) const
{
    const auto& constituency = *(constituencies_[index.row()]);
    switch (role)
    {
        case Qt::DisplayRole:
        {
            // Not quite working but should be fixable.
            const auto mps = politicianManager_->mpsForConstituency(
                constituency.id());
            map<QString, int> displayVals;
            for (const auto& mp : mps)
            {
                ++displayVals[mp.party().name_];
            }
            QMap<QString, QVariant> ret;
            for (const auto& keyValuePair : displayVals)
                ret[keyValuePair.first] = keyValuePair.second;
            return ret;
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
        case IdRole:
        {
            return constituency.id();
        }
        default:
        {
            return QVariant();
        }
    }
}

bool ConstituencyModel::setData(
    const QModelIndex& index,
    const QVariant& value,
    int role)
{
    auto& constituency = *(constituencies_[index.row()]);
    switch (role)
    {
        case LatitudeRole: constituency.setLatitude(value.toInt());
                           break;
        case LongitudeRole: constituency.setLongitude(value.toInt());
                           break;
        case NameRole: constituency.setName(value.toString());
                       break;
        default: return false;
    }
    constituencyManager_->updateConstituency(constituency);
    return true;
}

QHash<int, QByteArray> ConstituencyModel::roleNames() const
{
    QHash<int, QByteArray> ret;
    ret[LatitudeRole] = "Latitude";
    ret[LongitudeRole] = "Longitude";
    ret[NameRole] = "Name";
    ret[IdRole] = "Id";
}

QModelIndex ConstituencyModel::addConstituency(const Constituency& constituency)
{
    auto row = rowCount();

    beginInsertRows(QModelIndex(), row, row);
    unique_ptr<Constituency> newConstituency(new Constituency(constituency));
    constituencyManager_->addConstituency(*newConstituency);
    constituencies_.push_back(move(newConstituency));
    endInsertRows();

    return index(row);
}

void ConstituencyModel::refreshConstituency(int id)
{
    auto toUpdate = find_if(
        constituencies_.begin(),
        constituencies_.end(),
        [id](const unique_ptr<Constituency>& c) { 
            return c->id() == id; 
        });
    if (toUpdate == constituencies_.end())
        return;
    auto row = static_cast<int>(toUpdate - constituencies_.begin());
    *toUpdate = move(constituencyManager_->constituency(id));
    emit dataChanged(index(row), index(row));
}

void ConstituencyModel::loadConstituencies()
{
    beginResetModel();
    constituencies_ = constituencyManager_->constituencies();
    endResetModel();
}
