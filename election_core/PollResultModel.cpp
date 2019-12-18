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

QModelIndex PollResultModel::addPollresult(unique_ptr<PollResult> pollResult)
{
    auto row = rowCount();

    beginInsertRows(QModelIndex(), row, row);
    manager_->addPollResultInConstituency(*pollResult, constituencyId_);
    pollResultCache_.push_back(move(pollResult));
    endInsertRows();

    return index(row);
}
