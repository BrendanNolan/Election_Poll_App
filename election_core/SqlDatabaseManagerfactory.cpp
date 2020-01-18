#include "SqlDatabaseManagerFactory.h"

#include <QSqlDatabase>

#include "ElectionCoreFunctions.h"
#include "SqlConstituencyDatabaseManager.h"
#include "SqlPoliticianDatabaseManager.h"
#include "SqlPollResultDatabaseManager.h"

using namespace std;

SqlDatabaseManagerFactory::SqlDatabaseManagerFactory(
    const QFileInfo& databaseFileInfo)
    : databaseFileInfo_(databaseFileInfo)
{
    conditionallyCreateSqlDatabase(databaseFileInfo_.absoluteFilePath());
}

shared_ptr<IConstituencyDatabaseManager> 
SqlDatabaseManagerFactory::createConstituencyDatabaseManager() const
{
    auto manager = make_shared<SqlConstituencyDatabaseManager>(database_);
    return manager;
}

shared_ptr<IPollResultDatabaseManager>
SqlDatabaseManagerFactory::createPollResultDatabaseManager() const
{
    auto manager = make_shared<SqlPollResultDatabaseManager>(database_);
    return manager;
}

shared_ptr<IPoliticianDatabaseManager>
SqlDatabaseManagerFactory::createPoliticianDatabaseManager() const
{
    auto manager = make_shared<SqlPoliticianDatabaseManager>(database_);
    return manager;
}

SqlDatabaseManagerFactory* SqlDatabaseManagerFactory::clone() const
{
    return new SqlDatabaseManagerFactory(*this);
}
