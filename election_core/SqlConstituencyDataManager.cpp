#include "SqlConstituencyDataManager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <Qvariant>

#include "Constituency.h"

using namespace std;

SqlConstituencyDataManager::SqlConstituencyDataManager(
    shared_ptr<QSqlDatabase> database)
    : database_(move(database))
{}

void SqlConstituencyDataManager::init() const
{
    if (!database_ || database_->tables().contains("constituencies"))
        return;

    QSqlQuery query(*database_);
    query.exec("CREATE TABLE constituencies" 
        "(if INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
}

void SqlConstituencyDataManager::addConstituency(
    Constituency& constituency) const
{
    if (!database_)
        return;

    QSqlQuery query(*database_);
    query.prepare("INSERT INTO constituencies (name) VALUES (:name)");
    query.bindValue("name", constituency.name());
    query.exec();
    constituency.setId(query.lastInsertId().toInt());
}

void SqlConstituencyDataManager::
    updateConstituency(const Constituency& constituency) const
{
    if (!database_)
        return;

    QSqlQuery query(*database_);
    query.prepare("UPDATE constituencies SET name = (:name) WHERE id = (:id)");
    query.bindValue(":name", constituency.name());
    query.bindValue(":id", constituency.id());
    query.exec();
}

void SqlConstituencyDataManager::removeConstituency(int id) const
{
    if (!database_)
        return;

    QSqlQuery query(*database_);
    query.prepare("DELETE FROM albums WHERE id = (:id)");
    query.bindValue(":id", id);
    query.exec();
}

vector<unique_ptr<Constituency>> SqlConstituencyDataManager::
    constituencies() const
{
    vector<unique_ptr<Constituency>> ret;
    if (!database_)
        return ret;

    QSqlQuery query("SELECT * FROM constituencies", *database_);
    query.exec();
    while (query.next())
    {
        auto constituency = make_unique<Constituency>();
        if (!constituency)
            continue;
        constituency->setId(query.value("id").toInt());
        constituency->setName(query.value("name").toString());
        ret.push_back(move(constituency));
    }

    return ret;
}
