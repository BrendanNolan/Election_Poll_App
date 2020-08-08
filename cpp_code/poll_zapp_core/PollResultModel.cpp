#include "PollResultModel.h"

#include <QHash>
#include <QString>
#include <QVariant>

#include "DatabaseSignaller.h"
#include "IDatabaseManagerFactory.h"
#include "IPollResultDatabaseManager.h"
#include "poll_zapp_core_utils.h"
#include "PollResult.h"
#include "SqlDatabaseManagerFactory.h"

using namespace std;

PollResultModel::PollResultModel(
    const IDatabaseManagerFactory& factory, QObject* parent)
    : QAbstractListModel(parent)
    , manager_(factory.createPollResultDatabaseManager())
{
    connect(
        &(manager_->databaseSignaller()),
        &DatabaseSignaller::databaseRefreshed,
        this,
        &PollResultModel::reload);
}

int PollResultModel::rowCount(const QModelIndex& /*parent*/) const
{
    return pollResultCache_.size();
}

QVariant PollResultModel::data(const QModelIndex& index, int role) const
{
    if (!poll_zapp_core_utils::isIndexValid(index, *this))
        return QVariant();

    const auto& pollResult = *(pollResultCache_[index.row()]);
    switch (role)
    {
    case Qt::DisplayRole:
    case SourceRole:
        return pollResult.source();
    case PlotRole:
    {
        auto stringIntHash = pollResult.plot();
        QHash<QString, QVariant> stringVarHash;
        for (const auto& key : stringIntHash.keys())
            stringVarHash[key] = stringIntHash[key];
        return stringVarHash;
    }
    case DateTimeRole:
        return pollResult.dateTime();
    default:
        return QVariant();
    }
}

bool PollResultModel::setData(
    const QModelIndex& index, const QVariant& value, int role)
{
    if (!poll_zapp_core_utils::isIndexValid(index, *this))
        return false;
    if (role != PlotRole)
        return false;

    auto stringVarHash = value.value<QHash<QString, QVariant>>();
    auto stringIntHash = QHash<QString, int>();
    for (const auto& key : stringVarHash.keys())
        stringIntHash[key] = stringVarHash[key].toInt();
    pollResultCache_[index.row()]->setPlotData(stringIntHash);
    emit dataChanged(index, index);
    return true;
}

bool PollResultModel::removeRows(
    int row, int count, const QModelIndex& /*parent*/)
{
    if (row < 0 || count < 0 || row + count > rowCount())
        return false;

    beginRemoveRows(QModelIndex(), row, row + count - 1);
    auto rowsLeftToRemove = count;
    while (rowsLeftToRemove > 0)
    {
        const auto& pollResultToRemove =
            *(pollResultCache_[row + rowsLeftToRemove - 1]);
        manager_->removePollResult(pollResultToRemove);
    }
    pollResultCache_.erase(
        pollResultCache_.begin() + row, pollResultCache_.end() + row + count);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> PollResultModel::roleNames() const
{
    QHash<int, QByteArray> ret;
    ret[SourceRole] = "Source";
    ret[DateTimeRole] = "DateTime";
    return ret;
}

QModelIndex PollResultModel::addPollresult(unique_ptr<PollResult> pollResult)
{
    auto row = rowCount();

    beginInsertRows(QModelIndex(), row, row);
    manager_->addPollResult(*pollResult);
    pollResultCache_.push_back(move(pollResult));
    endInsertRows();

    return index(row);
}

int PollResultModel::constituencyId() const
{
    return constituencyId_;
}

void PollResultModel::reload()
{
    beginResetModel();
    reloadPollResultCache();
    endResetModel();
}

bool PollResultModel::refreshDataSource()
{
    if (manager_)
        return manager_->refreshDatabase();

    return false;
}

void PollResultModel::setConstituency(int id)
{
    if (id == constituencyId_)
        return;
    beginResetModel();
    constituencyId_ = id;
    reloadPollResultCache();
    endResetModel();
}

void PollResultModel::reloadPollResultCache()
{
    if (constituencyId_ == -1)
    {
        pollResultCache_.clear();
        return;
    }
    pollResultCache_ = manager_->pollResultsForConstituency(constituencyId_);
}
