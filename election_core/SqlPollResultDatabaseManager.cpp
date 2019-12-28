#include "SqlPollResultDatabaseManager.h"

#include <QSqlDatabase>
#include <QSqlQuery>

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
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "constituency_id INTEGER, "
        "image_url TEXT, "
        "name TEXT, "
        "elected INTEGER, " // 0 for false 1 for true
        "candidate INTEGER, " // 0 for false 1 for true
        "party_name TEXT, "
        "party_rgb_red TEXT, "
        "party_rgb_green TEXT, "
        "party_rgb_blue TEXT"
        ")");
}
