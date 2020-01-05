#include "ConstituencyModel.h"

#include <QMap>
#include <QString>

#include <algorithm>
#include <map>

#include "IConstituencyDatabaseManager.h"
#include "IDatabaseManagerFactory.h"
#include "IPoliticianDatabaseManager.h"
#include "SqlDatabaseManagerFactory.h"

#include "ListModelFunctions.h"

using namespace std;

ConstituencyModel::ConstituencyModel(QObject* parent)
    : ConstituencyModel(SqlDatabaseManagerFactory(), parent)
{}

ConstituencyModel::ConstituencyModel(
    const IDatabaseManagerFactory& factory,
    QObject* parent)
    : QAbstractListModel(parent)
    , constituencyManager_(factory.createConstituencyDatabaseManager())
    , politicianManager_(factory.createPoliticianDatabaseManager())
{
    beginResetModel();
    loadConstituencyCache();
    endResetModel();
}

int ConstituencyModel::rowCount() const
{
    return constituencyCache_.size();
}

QVariant ConstituencyModel::data(const QModelIndex &index, int role) const
{
    if (!isIndexValid(index, *this))
        return false;
    const auto& constituency = *(constituencyCache_[index.row()]);
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
            ++displayVals[mp->partyDetails().name_];
        }
        QMap<QString, QVariant> ret;
        for (const auto& keyValuePair : displayVals)
            ret[keyValuePair.first] = keyValuePair.second;
        return ret;
    }
    case LatitudeRole: 
        return constituency.latitude();
    case LongitudeRole: 
        return constituency.longitude();
    case NameRole: 
        return constituency.name();
    case IdRole: 
        return constituency.id();
    default: 
        return QVariant();
    }
}

/* MIGHT NOT WANT TO IMPLEMENT THIS
bool ConstituencyModel::setData(
    const QModelIndex& index,
    const QVariant& value,
    int role)
{
    if (!isIndexValid(index, *this))
        return false;

    auto& constituency = *(constituencyCache_[index.row()]);
    switch (role)
    {
        case LatitudeRole: 
            constituency.setLatitude(value.toInt());
            break;
        case LongitudeRole: 
            constituency.setLongitude(value.toInt());
            break;
        case NameRole: 
            constituency.setName(value.toString());
            break;
        default: 
            return false;
    }
    constituencyManager_->updateConstituency(constituency);
    emit dataChanged(index, index);
    return true;
}*/

bool ConstituencyModel::removeRows(
    int row, 
    int count, 
    const QModelIndex& /*parent*/)
{
    if (row < 0 || count < 0 || row + count > rowCount())
        return false;

    beginRemoveRows(QModelIndex(), row, row + count - 1);
    auto rowsLeftToRemove = count;
    while (rowsLeftToRemove > 0)
    {
        constituencyManager_->removeConstituency(
            constituencyCache_[row + rowsLeftToRemove - 1]->id());
        --rowsLeftToRemove;
    }
    constituencyCache_.erase(
        constituencyCache_.begin() + row, 
        constituencyCache_.begin() + row + count);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> ConstituencyModel::roleNames() const
{
    QHash<int, QByteArray> ret;
    ret[LatitudeRole] = "Latitude";
    ret[LongitudeRole] = "Longitude";
    ret[NameRole] = "Name";
    ret[IdRole] = "Id";
    return ret;
}

QModelIndex ConstituencyModel::addConstituency(
    unique_ptr<Constituency> constituency)
{
    auto row = rowCount();

    beginInsertRows(QModelIndex(), row, row);
    constituencyManager_->addConstituency(*constituency);
    constituencyCache_.push_back(move(constituency));
    endInsertRows();

    return index(row);
}

bool ConstituencyModel::refreshCachedConstituency(int id)
{
    auto toUpdate = find_if(
        constituencyCache_.begin(),
        constituencyCache_.end(),
        [id](const unique_ptr<Constituency>& c) { 
            return c->id() == id; 
        });
    if (toUpdate == constituencyCache_.end())
        return false;
    auto row = static_cast<int>(toUpdate - constituencyCache_.begin());
    *toUpdate = move(constituencyManager_->constituency(id));
    emit dataChanged(index(row), index(row));
    return true;
}

void ConstituencyModel::loadConstituencyCache()
{
    constituencyCache_ = constituencyManager_->constituencies();
}
