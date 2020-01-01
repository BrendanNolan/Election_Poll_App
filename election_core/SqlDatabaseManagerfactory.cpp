#include "SqlDatabaseManagerfactory.h"

#include <QSqlDatabase>

#include "SqlConstituencyDatabaseManager.h"
#include "SqlPoliticianDatabaseManager.h"
#include "SqlPollResultDatabaseManager.h"

using namespace std;

SqlDatabaseManagerFactory::SqlDatabaseManagerFactory(
    shared_ptr<QSqlDatabase> database,
    const QString& name,
    const QString& sqlFlavour)
    : database_(move(database))
{
    if (!database_)
    {
        database_ = make_shared<QSqlDatabase>(QSqlDatabase::addDatabase(
            sqlFlavour));
    }
    database_->setDatabaseName(name);
    database_->open();
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
