#include "IPoliticianDatabaseManager.h"

IPoliticianDatabaseManager::IPoliticianDatabaseManager(
    std::shared_ptr<DatabaseSignaller> databaseSignaller)
    : databaseSignaller_(std::move(databaseSignaller))
{
}

DatabaseSignaller* IPoliticianDatabaseManager::databaseSignaller() const
{
    return databaseSignaller_.get();
}
