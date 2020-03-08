#include "IPollResultDatabaseManager.h"

DatabaseSignaller* IPollResultDatabaseManager::databaseSignaller() const
{
    return databaseSignaller_.get();
}
