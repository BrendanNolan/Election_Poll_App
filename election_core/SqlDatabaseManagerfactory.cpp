#include "SqlDatabaseManagerfactory.h"

#include "SqlConstituencyDatabaseManager.h"
#include "SqlImageDatabaseManager.h"
#include "SqlPollResultDatabaseManager.h"

std::shared_ptr<QSqlDatabase> SqlDatabaseManagerfactory::database_ 
= std::make_shared<QSqlDatabase>();

std::shared_ptr<IConstituencyDatabaseManager> 
SqlDatabaseManagerfactory::createConstituencyDatabaseManager() const
{
    return std::make_shared<SqlConstituencyDatabaseManager>(database_);
}

std::shared_ptr<IPollResultDatabaseManager>
SqlDatabaseManagerfactory::createPollResultDatabaseManager() const
{
    return std::make_shared<SqlPollResultDatabaseManager>(database_);
}

std::shared_ptr<IImageDatabaseManager>
SqlDatabaseManagerfactory::createImageDatabaseManager() const
{
    return std::make_shared<SqlImageDatabaseManager>(database_);
}
