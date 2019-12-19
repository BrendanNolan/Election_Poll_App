#include "SqlDatabaseManagerfactory.h"

#include <QSqlDatabase>

#include "SqlConstituencyDatabaseManager.h"
#include "SqlPoliticianDatabaseManager.h"
#include "SqlPollResultDatabaseManager.h"

using namespace std;

shared_ptr<QSqlDatabase> SqlDatabaseManagerFactory::database_ = 
    make_shared<QSqlDatabase>(QSqlDatabase::addDatabase("QSQLITE"));

SqlDatabaseManagerFactory::SqlDatabaseManagerFactory(const QString& name)
{
    database_->setDatabaseName(name);
    database_->open();
}

shared_ptr<IConstituencyDatabaseManager> 
SqlDatabaseManagerFactory::createConstituencyDatabaseManager() const
{
    auto manager = make_shared<SqlConstituencyDatabaseManager>(database_);
    manager->init();
    return manager;
}

shared_ptr<IPollResultDatabaseManager>
SqlDatabaseManagerFactory::createPollResultDatabaseManager() const
{
    auto manager = make_shared<SqlPollResultDatabaseManager>(database_);
    manager->init();
    return manager;
}

shared_ptr<IPoliticianDatabaseManager>
SqlDatabaseManagerFactory::createPoliticianDatabaseManager() const
{
    auto manager = make_shared<SqlPoliticianDatabaseManager>(database_);
    manager->init();
    return manager;
}
