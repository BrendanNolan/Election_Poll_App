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

void SqlPollResultDatabaseManager::addPollResult(const PollResult& result) const
{
    if (!database_)
        return;

    QSqlQuery query(*database_);
    query.prepare(
        "INSERT INTO poll_results "
        "("
        "constituency_id, source, date_time, politician_name, poll_value"
        ") "
        "VALUES "
        "("
        ":constituency_id, :source, :date_time, :politician_name, :poll_value"
        ")");
    auto histogram = result.histogram();
}

void SqlPollResultDatabaseManager::updatePollResult(
    const PollResult& result) const
{

}

void SqlPollResultDatabaseManager::removePollResult(
    const PollResult& result) const
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
