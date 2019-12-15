#include "PollResultModel.h"

#include "PollResult.h"

#include "IDatabaseManagerFactory.h"
#include "IPollResultDatabaseManager.h"
#include "PollResult.h"

PollResultModel::PollResultModel(
    const IDatabaseManagerFactory& factory,
    QObject* parent)
    : QAbstractListModel(parent)
    , manager_(factory.createPollResultDatabaseManager())
{
    manager_->init();
    loadPollResultCache();
}
