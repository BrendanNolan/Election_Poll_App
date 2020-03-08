#include "IConstituencyDatabaseManager.h"

IConstituencyDatabaseManager::IConstituencyDatabaseManager(
    std::shared_ptr<DatabaseSignaller> databaseSignaller)
    : databaseSignaller_(databaseSignaller)
{
}

DatabaseSignaller* IConstituencyDatabaseManager::databaseSignaller() const
{
    return databaseSignaller_.get();
}
