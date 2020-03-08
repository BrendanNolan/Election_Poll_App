#include "IPoliticianDatabaseManager.h"

DatabaseSignaller* IPoliticianDatabaseManager::databaseSignaller() const
{
    return databaseSignaller_.get();
}
