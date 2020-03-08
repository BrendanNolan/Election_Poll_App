#include "IConstituencyDatabaseManager.h"

IConstituencyDatabaseManager::IConstituencyDatabaseManager(
    std::shared_ptr<DatabaseSignaller> databaseSignaller)
    : databaseSignaller_(std::move(databaseSignaller))
{
}

DatabaseSignaller* IConstituencyDatabaseManager::databaseSignaller() const
{
    return databaseSignaller_.get();
}
