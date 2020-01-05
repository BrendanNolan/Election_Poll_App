#include "PollResultModel.h"

#include "PollResult.h"

#include "IDatabaseManagerFactory.h"
#include "IPollResultDatabaseManager.h"
#include "ListModelFunctions.h"
#include "PollResult.h"
#include "SqlDatabaseManagerFactory.h"

using namespace std;

PollResultModel::PollResultModel(QObject* parent)
    : PollResultModel(SqlDatabaseManagerFactory(), parent)
{}

PollResultModel::PollResultModel(
    const IDatabaseManagerFactory& factory,
    QObject* parent)
    : QAbstractListModel(parent)
    , manager_(factory.createPollResultDatabaseManager())
{
    beginResetModel();
    loadPollResultCache();
    endResetModel();
}

int PollResultModel::rowCount() const
{
    return pollResultCache_.size();
}

QVariant PollResultModel::data(const QModelIndex & index, int role) const
{
    if (!isIndexValid(index, *this))
        return QVariant();
    if (role != Qt::DisplayRole && role != SourceRole && role != DateTimeRole)
        return QVariant();

    const auto& pollResult = *(pollResultCache_[index.row()]);
    switch (role)
    {
    case Qt::DisplayPropertyRole:
        return pollResult.histogram();
    case SourceRole:
        return pollResult.source();
    case DateTimeRole:
        return pollResult.dateTime();
    default:
        return QVariant();
    }
}

bool PollResultModel::setData(
    const QModelIndex& index, 
    const QVariant& value, 
    int role)
{
    if (!isIndexValid(index, *this) || role != Qt::DisplayRole)
        return false;

    pollResultCache_[index.row()]->setHistogram(
        value.value<QHash<QString, QVariant>>());
    emit dataChanged(index, index);
    return true;
}

bool PollResultModel::removeRows(
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
        const auto& pollResultToRemove =
            *(pollResultCache_[row + rowsLeftToRemove - 1]);
        manager_->removePollResult(pollResultToRemove);
    }
    pollResultCache_.erase(
        pollResultCache_.begin() + row,
        pollResultCache_.end() + row + count);
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

void PollResultModel::loadPollResultCache()
{
    if (constituencyId_ == -1)
        pollResultCache_.clear();
    pollResultCache_ = manager_->pollResultsForConstituency(constituencyId_);
}
