#include "SqlPollResultDatabaseManager.h"

#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "app_data_functions.h"
#include "poll_zapp_core_utils.h"
#include "PollResult.h"

using namespace std;

SqlPollResultDatabaseManager::SqlPollResultDatabaseManager(
    const QFileInfo& databaseFileInfo,
    std::shared_ptr<DatabaseSignaller> databaseSignaller)
    : IPollResultDatabaseManager(databaseSignaller)
    , databaseFileInfo_(databaseFileInfo)
{
    auto database =
        poll_zapp_core_utils::connectToSqlDatabase(databaseFileInfo_);
    if (!database.isValid() || database.tables().contains("poll_results"))
        return;

    QSqlQuery query(database);
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
    auto database =
        poll_zapp_core_utils::connectToSqlDatabase(databaseFileInfo_);
    if (!database.isValid())
        return;

    QSqlQuery query(database);
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
    auto plot = result.plot();
    for (auto it = plot.constBegin(); it != plot.constEnd(); ++it)
    {// May need to move the above query preparation inside this loop.
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
    auto database =
        poll_zapp_core_utils::connectToSqlDatabase(databaseFileInfo_);
    if (!database.isValid())
        return;

    QSqlQuery query(database);
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
    auto plot = result.plot();
    for (auto it = plot.constBegin(); it != plot.constEnd(); ++it)
    {// May need to move the above query preparation inside this loop.
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
    auto database =
        poll_zapp_core_utils::connectToSqlDatabase(databaseFileInfo_);
    if (!database.isValid())
        return;

    QSqlQuery query(database);
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

vector<unique_ptr<PollResult>> SqlPollResultDatabaseManager::
    pollResultsForConstituency(int id) const
{
    auto database =
        poll_zapp_core_utils::connectToSqlDatabase(databaseFileInfo_);
    if (!database.isValid())
        return vector<unique_ptr<PollResult>>();

    vector<unique_ptr<PollResult>> ret;
    QSqlQuery query(database);
    query.prepare(
        "SELECT * FROM poll_results "
        "WHERE constituency_id = (:constituency_id) "
        "ORDER BY date_time,source");
    query.bindValue(":constituency_id", id);
    if (!query.exec() || !query.next())
        return vector<unique_ptr<PollResult>>();
    auto source = query.value("source").toString();
    auto dateTime = query.value("date_time").toDateTime();
    unique_ptr<PollResult> pollResult(new PollResult(source, dateTime, id));
    query.previous();
    while (query.next())
    {
        auto nextSource = query.value("source").toString();
        auto nextDateTime = query.value("date_time").toDateTime();
        if (nextSource != source || nextDateTime != dateTime)
        {
            ret.push_back(move(pollResult));

            pollResult = unique_ptr<PollResult>(
                new PollResult(nextSource, nextDateTime, id));
            source = nextSource;
            dateTime = nextDateTime;
        }
        else
        {
            pollResult->appendToPlot(
                query.value("politician_name").toString(),
                query.value("poll_value").toInt());
        }
    }
    ret.push_back(move(pollResult));

    return ret;
}

bool SqlPollResultDatabaseManager::refreshDatabase() const
{
    if (python_scripting::runPythonScript(
            QFileInfo(paths::pollResultScrapingScript())))
    {
        if (auto signaller = databaseSignaller())
            emit signaller->databaseRefreshed();
        return true;
    }

    return false;
}
