#include "SqlDatabaseManagerFactory.h"

#include <QSqlDatabase>

#include "election_core_utils.h"
#include "SqlConstituencyDatabaseManager.h"
#include "SqlPoliticianDatabaseManager.h"
#include "SqlPollResultDatabaseManager.h"

using namespace std;

SqlDatabaseManagerFactory::SqlDatabaseManagerFactory(
    const QFileInfo& databaseFileInfo)
    : databaseFileInfo_(databaseFileInfo)
{}

SqlDatabaseManagerFactory* SqlDatabaseManagerFactory::clone() const
{
    return new SqlDatabaseManagerFactory(*this);
}

shared_ptr<IConstituencyDatabaseManager> 
SqlDatabaseManagerFactory::createConstituencyDatabaseManager() const
{
    return make_shared<SqlConstituencyDatabaseManager>(databaseFileInfo_);
}

shared_ptr<IPollResultDatabaseManager>
SqlDatabaseManagerFactory::createPollResultDatabaseManager() const
{
    return make_shared<SqlPollResultDatabaseManager>(databaseFileInfo_);
}

shared_ptr<IPoliticianDatabaseManager>
SqlDatabaseManagerFactory::createPoliticianDatabaseManager() const
{
    return make_shared<SqlPoliticianDatabaseManager>(databaseFileInfo_);
}
