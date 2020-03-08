#include "IPollResultDatabaseManager.h"

IPollResultDatabaseManager::IPollResultDatabaseManager(
    std::shared_ptr<DatabaseSignaller> databaseSignaller)
    : databaseSignaller_(std::move(databaseSignaller))
{
}

DatabaseSignaller* IPollResultDatabaseManager::databaseSignaller() const
{
    return databaseSignaller_.get();
}
