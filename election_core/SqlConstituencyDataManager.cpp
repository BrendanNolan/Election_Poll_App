#include "SqlConstituencyDataManager.h"

#include <QSqlDatabase>
#include <QSqlQuery>

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
