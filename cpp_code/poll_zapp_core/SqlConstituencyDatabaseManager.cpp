#include "SqlConstituencyDatabaseManager.h"

#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <Qvariant>

#include "Constituency.h"
#include "app_data_functions.h"
#include "poll_zapp_core_utils.h"
#include "Politician.h"

using namespace std;

namespace
{
unique_ptr<Constituency> sqlQueryToConstituency(const QSqlQuery& query);
}

SqlConstituencyDatabaseManager::SqlConstituencyDatabaseManager(
    const QFileInfo& databaseFileInfo)
    : databaseFileInfo_(databaseFileInfo)
{
    auto database =
        poll_zapp_core_utils::connectToSqlDatabase(databaseFileInfo_);
    if (!database.isValid() || database.tables().contains("constituencies"))
        return;

    QSqlQuery query(database);
    query.exec(
        "CREATE TABLE constituencies "
        "("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT, "
        "latitude FLOAT, "
        "longitude FLOAT, "
        "area_sq_km FLOAT"
        ")");
}

void SqlConstituencyDatabaseManager::addConstituency(
    Constituency& constituency) const
{
    auto database =
        poll_zapp_core_utils::connectToSqlDatabase(databaseFileInfo_);
    if (!database.isValid())
        return;

    QSqlQuery query(database);
    query.prepare(
        "INSERT INTO constituencies "
        "(name, latitude, longitude, area_sq_km) "
        "VALUES "
        "(:name, :latitude, :longitude, :area_sq_km)");
    query.bindValue(":name", constituency.name());
    query.bindValue(":latitude", constituency.latitude());
    query.bindValue(":longitude", constituency.longitude());
    query.bindValue(":area_sq_km", constituency.areaSqKm());
    query.exec();
    constituency.setId(query.lastInsertId().toInt());
}

void SqlConstituencyDatabaseManager::updateConstituency(
    const Constituency& constituency) const
{
    auto database =
        poll_zapp_core_utils::connectToSqlDatabase(databaseFileInfo_);
    if (!database.isValid())
        return;

    QSqlQuery query(database);
    query.prepare(
        "UPDATE constituencies SET "
        "name = (:name) "
        "latitude = (:latitude)"
        "longitude = (:longitude)"
        "area_sq_km = (:area_sq_km)"
        "WHERE "
        "id = (:id)");
    query.bindValue(":name", constituency.name());
    query.bindValue(":latitude", constituency.latitude());
    query.bindValue(":longitude", constituency.longitude());
    query.bindValue(":id", constituency.id());
    query.bindValue(":area_sq_km", constituency.areaSqKm());
    query.exec();
}

void SqlConstituencyDatabaseManager::removeConstituency(int id) const
{
    auto database =
        poll_zapp_core_utils::connectToSqlDatabase(databaseFileInfo_);
    if (!database.isValid())
        return;

    QSqlQuery query(database);
    query.exec("DELETE FROM comstituencies WHERE id = " + QString::number(id));
}

unique_ptr<Constituency> SqlConstituencyDatabaseManager::constituency(
    int id) const
{
    auto database =
        poll_zapp_core_utils::connectToSqlDatabase(databaseFileInfo_);
    if (!database.isValid())
        return nullptr;

    QSqlQuery query(database);
    query.exec(
        "SELECT * FROM comstituencies WHERE id = " + QString::number(id));
    return sqlQueryToConstituency(query);
}

vector<unique_ptr<Constituency>> SqlConstituencyDatabaseManager::
    constituencies() const
{
    auto database =
        poll_zapp_core_utils::connectToSqlDatabase(databaseFileInfo_);
    if (!database.isValid())
        return vector<unique_ptr<Constituency>>();

    vector<unique_ptr<Constituency>> ret;
    QSqlQuery query(database);
    if (!query.exec("SELECT * FROM constituencies"))
        return vector<unique_ptr<Constituency>>();
    while (query.next())
        ret.push_back(sqlQueryToConstituency(query));

    return ret;
}

bool SqlConstituencyDatabaseManager::refreshDatabase() const
{
    if (!python_scripting::runPythonScript(
            QFileInfo(paths::constituencyScrapingScript())))
    {
        return false;
    }
        
    emit databaseSignaller().databaseRefreshed();
    return true;
}

namespace
{
unique_ptr<Constituency> sqlQueryToConstituency(const QSqlQuery& query)
{
    unique_ptr<Constituency> constituency(new Constituency);
    constituency->setId(query.value("id").toInt());
    constituency->setName(query.value("name").toString());
    constituency->setLatitude(query.value("latitude").toFloat());
    constituency->setLongitude(query.value("longitude").toFloat());
    constituency->setAreaSqKm(query.value("area_sq_km").toFloat());
    return constituency;
}
}// namespace
