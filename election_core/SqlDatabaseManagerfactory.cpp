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
    conditionallyCreateSqlDatabase(databaseFileInfo_);
}

shared_ptr<IConstituencyDatabaseManager> 
SqlDatabaseManagerFactory::createConstituencyDatabaseManager() const
{
    auto database = QSqlDatabase::database(
        databaseFileInfo_.absoluteFilePath());
    if (!database.isValid())
        return nullptr;
    auto manager = make_shared<SqlConstituencyDatabaseManager>(
        databaseFileInfo_);
    return manager;
}

shared_ptr<IPollResultDatabaseManager>
SqlDatabaseManagerFactory::createPollResultDatabaseManager() const
{
    auto database = QSqlDatabase::database(
        databaseFileInfo_.absoluteFilePath());
    if (!database.isValid())
        return nullptr;
    auto manager = make_shared<SqlPollResultDatabaseManager>(databaseFileInfo_);
    return manager;
}

shared_ptr<IPoliticianDatabaseManager>
SqlDatabaseManagerFactory::createPoliticianDatabaseManager() const
{
    auto database = QSqlDatabase::database(
        databaseFileInfo_.absoluteFilePath());
    if (!database.isValid())
        return nullptr;
    auto manager = make_shared<SqlPoliticianDatabaseManager>(databaseFileInfo_);
    return manager;
}

SqlDatabaseManagerFactory* SqlDatabaseManagerFactory::clone() const
{
    return new SqlDatabaseManagerFactory(*this);
}
