#include "SqlPollResultDatabaseManager.h"

#include <QSqlDatabase>
#include <QSqlQuery>

#include "PollResult.h"

using namespace std;

SqlPollResultDatabaseManager::SqlPollResultDatabaseManager(
    std::shared_ptr<QSqlDatabase> database)
    : database_(move(database))
{
    if (!database_ || database_->tables().contains("poll_results"))
        return;
    QSqlQuery query(*database_);
    query.exec(
        "CREATE TABLE poll_results "
        "("
        "constituency_id INTEGER, "
        "source TEXT, "
        "date_time DATETIME, "
        "politician_name TEXT, "
        "poll_value INT"
        ")");
}

void SqlPollResultDatabaseManager::addPollResultInConstituency(
    PollResult& result, 
    int constituencyId) const
{

}

void SqlPollResultDatabaseManager::updatePollResult(
    const PollResult& result) const
{

}

void SqlPollResultDatabaseManager::removePollResult(
    const QString& source, 
    int constituencyId) const
{

}

vector<unique_ptr<PollResult>> 
SqlPollResultDatabaseManager::pollResultsForConstituency(int id) const
{
    vector<unique_ptr<PollResult>> ret;
    if (!database_)
        return ret;


    return ret;
}
