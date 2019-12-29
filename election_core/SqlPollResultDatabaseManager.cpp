#include "SqlPollResultDatabaseManager.h"

#include <QSqlDatabase>
#include <QSqlQuery>

#include "PollResult.h"

using namespace std;

namespace
{
    unique_ptr<PollResult> sqlQueryToPollResult(QSqlQuery& query);
}

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
    auto constituencyId = result.constituencyId();
    auto source = result.source();
    auto dateTime = result.dateTime();
    auto histogram = result.histogram();
    for (auto it = histogram.constBegin(); it != histogram.constEnd(); ++it)
    { // May need to move the above query preparation inside this loop.
        query.bindValue(":constituency_id", constituencyId);
        query.bindValue(":source", source);
        query.bindValue(":date_time", dateTime);
        query.bindValue(":politician_name", it.key());
        query.bindValue(":poll_value", it.value());
        query.exec();
    }
}

void SqlPollResultDatabaseManager::updatePollResult(
    const PollResult& result) const
{
    if (!database_)
        return;

    QSqlQuery query(*database_);
    query.prepare(
        "UPDATE poll_results SET "
        "poll_value = (:poll_value) "
        "WHERE "
        "("
        "constituency_id = (:constituency_id), "
        "source = (:source), "
        "date_time = (:date_time), "
        "politician_name = (:politician_name)"
        ")");
    auto constituencyId = result.constituencyId();
    auto source = result.source();
    auto dateTime = result.dateTime();
    auto histogram = result.histogram();
    for (auto it = histogram.constBegin(); it != histogram.constEnd(); ++it)
    { // May need to move the above query preparation inside this loop.
        query.bindValue(":constituency_id", constituencyId);
        query.bindValue(":source", source);
        query.bindValue(":date_time", dateTime);
        query.bindValue(":politician_name", it.key());
        query.bindValue(":poll_value", it.value());
        query.exec();
    }
}

void SqlPollResultDatabaseManager::removePollResult(
    const PollResult& result) const
{
    if (!database_)
        return;

    QSqlQuery query(*database_);
    query.prepare(
        "DELETE FROM poll_results WHERE "
        "("
        "constituency_id = (:constituency_id), "
        "source = (:source), "
        "date_time = (:date_time)"
        ")");
    query.bindValue(":constituency_id", result.constituencyId());
    query.bindValue(":source", result.source());
    query.bindValue(":date_time", result.dateTime());
    query.exec();
}

vector<unique_ptr<PollResult>> 
SqlPollResultDatabaseManager::pollResultsForConstituency(int id) const
{
    vector<unique_ptr<PollResult>> ret;
    if (!database_)
        return ret;

    QSqlQuery query(*database_);
    query.prepare(
        "SELECT (politician_name, poll_value) "
        "FROM poll_results "
        "WHERE constituency_id = (:constituency_id)"
        "GROUP BY (source, date_time)");
    query.bindValue(":constitucney_id", id);
    query.exec();
    while (query.next())
        ret.push_back(sqlQueryToPollResult(query));

    return ret;
}

namespace
{
    unique_ptr<PollResult> sqlQueryToPollResult(QSqlQuery& query)
    {
        unique_ptr<PollResult> ret(new PollResult(
            query.value("source").toString(),
            QHash<QString, QVariant>(),
            query.value("date_time").toDateTime(),
            query.value("constituency_id").toInt()));
        while (query.next())
            ret->appendToHistogram(
                query.value("politician_name").toString(),
                query.value("poll_value").toInt());
        return ret;
    }
}
