#include "SqlPoliticianDatabaseManager.h"

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QUrl>
#include <QVariant>

#include "Politician.h"

using namespace std;

namespace
{
    unique_ptr<Politician> sqlQueryToPolitician(const QSqlQuery& query);
}

SqlPoliticianDatabaseManager::SqlPoliticianDatabaseManager(
    shared_ptr<QSqlDatabase> database)
    : database_(move(database))
{}

void SqlPoliticianDatabaseManager::init() const
{
    if (database_->tables().contains("politicians"))
        return;
    QSqlQuery query(*database_);
    query.exec(QString("CREATE TABLE politicians")
        + " (id INTEGER PRIMARY KEY AUTOINCREMENT, "
        + "constituency_id INTEGER, "
        + "image_url TEXT,"
        + "name TEXT,"
        + "elected BOOL,"
        + "candidate BOOL,"
        + "party_name TEXT,"
        + "party_rgb_red TEXT,"
        + "party_rgb_green TEXT,"
        + "party_rgb_blue TEXT)");
}

vector<unique_ptr<Politician>> SqlPoliticianDatabaseManager::mpsForConstituency(
    int constituencyId) const
{
    QSqlQuery query(*database_);
    query.prepare(
        "SELECT * FROM politicians WHERE constituency_id = (:constituency_id)"
        "WHERE elected = (:elected)");
    query.bindValue(":constituency_id", constituencyId);
    query.bindValue(":elected", true);
    query.exec();
    vector<unique_ptr<Politician>> ret;
    while (query.next())
        ret.push_back(sqlQueryToPolitician(query));
    return ret;
}

namespace 
{
    unique_ptr<Politician> sqlQueryToPolitician(const QSqlQuery& query)
    {
        PartyDetails details;
        {
            RGBValue rgb(
                query.value("party_rgb_red").toInt(),
                query.value("party_rgb_green").toInt(),
                query.value("party_rgb_blue").toInt());
            details.name_ = query.value("party_name").toString();
            details.colour_ = rgb;
        }
        unique_ptr<Politician> politician(new Politician);
        politician->setImageUrl(QUrl(query.value("image_url").toString()));
        politician->setName(query.value("name").toString());
        politician->setId(query.value("id").toInt());
        politician->setConstituencyId(query.value("constituency_id").toInt());
        politician->setPartyDetails(details);
        return politician;
    }
}
