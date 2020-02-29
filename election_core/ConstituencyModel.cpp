#include "ConstituencyModel.h"

#include <QMap>
#include <QSqlDatabase>
#include <QString>

#include <algorithm>
#include <map>

#include "IConstituencyDatabaseManager.h"
#include "IDatabaseManagerFactory.h"
#include "SqlDatabaseManagerFactory.h"

#include "election_core_utils.h"

using namespace std;

ConstituencyModel::ConstituencyModel(
    const IDatabaseManagerFactory& factory, QObject* parent)
    : QAbstractListModel(parent)
    , manager_(factory.createConstituencyDatabaseManager())
{
    beginResetModel();
    reloadConstituencyCache();
    endResetModel();
}

int ConstituencyModel::rowCount(const QModelIndex& /*parent*/) const
{
    return constituencyCache_.size();
}

QVariant ConstituencyModel::data(const QModelIndex& index, int role) const
{
    if (!election_core_utils::isIndexValid(index, *this))
        return false;
    const auto& constituency = *(constituencyCache_[index.row()]);
    switch (role)
    {
    case LatitudeRole:
        return constituency.latitude();
    case LongitudeRole:
        return constituency.longitude();
    case Qt::DisplayRole:
    case NameRole:
        return constituency.name();
    case IdRole:
        return constituency.id();
    default:
        return QVariant();
    }
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
    manager_->addConstituency(*constituency);
    constituencyCache_.push_back(move(constituency));
    endInsertRows();

    return index(row);
}

void ConstituencyModel::reload()
{
    reloadConstituencyCache();
    emit dataChanged(index(0), index(rowCount()));
}

void ConstituencyModel::refreshDataSource()
{
    manager_->refreshDatabase();
    reload();
}

void ConstituencyModel::reloadConstituencyCache()
{
    constituencyCache_ = manager_->constituencies();
}
