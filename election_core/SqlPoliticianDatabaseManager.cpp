#include "SqlPoliticianDatabaseManager.h"

#include <QSqlQuery>
#include <QUrl>

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
        + "image_url TEXT)");
}

namespace 
{
    unique_ptr<Politician> sqlQueryToPolitician(const QSqlQuery& query)
    {
        PartyDetails details;
        {
            RGBValue rgb(
                query.value("rgb_red").toInt(),
                query.value("rgb_green").toInt(),
                query.value("rgb_blue").toInt());
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
