#include "SqlDatabaseManagerFactory.h"

#include <QSqlDatabase>

#include "DatabaseSignaller.h"
#include "poll_zapp_core_utils.h"
#include "SqlConstituencyDatabaseManager.h"
#include "SqlPoliticianDatabaseManager.h"
#include "SqlPollResultDatabaseManager.h"

using namespace std;

SqlDatabaseManagerFactory::SqlDatabaseManagerFactory(
    const QFileInfo& databaseFileInfo)
    : databaseFileInfo_(databaseFileInfo)
    , constituencySignaller_(std::make_shared<DatabaseSignaller>())
    , politicianSignaller_(std::make_shared<DatabaseSignaller>())
    , pollResultSignaller_(std::make_shared<DatabaseSignaller>())
{
}

SqlDatabaseManagerFactory* SqlDatabaseManagerFactory::clone() const
{
    return new SqlDatabaseManagerFactory(*this);
}

shared_ptr<IConstituencyDatabaseManager> SqlDatabaseManagerFactory::
    createConstituencyDatabaseManager() const
{
    return make_shared<SqlConstituencyDatabaseManager>(
        databaseFileInfo_, constituencySignaller_);
}

shared_ptr<IPollResultDatabaseManager> SqlDatabaseManagerFactory::
    createPollResultDatabaseManager() const
{
    return make_shared<SqlPollResultDatabaseManager>(
        databaseFileInfo_, pollResultSignaller_);
}

shared_ptr<IPoliticianDatabaseManager> SqlDatabaseManagerFactory::
    createPoliticianDatabaseManager() const
{
    return make_shared<SqlPoliticianDatabaseManager>(
        databaseFileInfo_, politicianSignaller_);
}
