#include "PollResultModel.h"

#include "PollResult.h"

#include "IDatabaseManagerFactory.h"
#include "IPollResultDatabaseManager.h"
#include "ListModelFunctions.h"
#include "PollResult.h"

using namespace std;

PollResultModel::PollResultModel(
    const IDatabaseManagerFactory& factory,
    QObject* parent)
    : QAbstractListModel(parent)
    , manager_(factory.createPollResultDatabaseManager())
{
    manager_->init();
    loadPollResultCache();
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

    switch (role)
    {
        const auto& pollResult = *(pollResultCache_[index.row()]);
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
    if (!isIndexValid(index, *this))
        return false;
    if (role != Qt::DisplayRole)
        return false;

    switch (role)
    {
        auto& pollData = *(pollResultCache_[index.row()]);
    case Qt::DisplayRole:
        pollData.setHistogram(value.value<QHash<QString, QVariant>>());
        return true;
    default:
        return false;
    }

    emit dataChanged(index, index);
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
        manager_->removePollResult(pollResultToRemove.id());
    }
    pollResultCache_.erase(
        pollResultCache_.begin() + row,
        pollResultCache_.end() + row + count);
    endRemoveRows();
    return true;
}

QModelIndex PollResultModel::addPollresult(unique_ptr<PollResult> pollResult)
{
    auto row = rowCount();

    beginInsertRows(QModelIndex(), row, row);
    manager_->addPollResultInConstituency(*pollResult, constituencyId_);
    pollResultCache_.push_back(move(pollResult));
    endInsertRows();

    return index(row);
}
