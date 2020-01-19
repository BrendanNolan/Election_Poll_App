#include "ElectionCoreFunctions.h"

#include <QAbstractListModel>
#include <QFileInfo>
#include <QModelIndex>

bool isIndexValid(const QModelIndex& index, const QAbstractListModel& model)
{
    auto row = index.row();
    if (row < 0 || row >= model.rowCount() || !index.isValid())
        return false;
    return true;
}

QSqlDatabase connectToSqlDatabase(const QFileInfo& databaseFileInfo)
{
    auto database = databaseFileInfo.exists() ?
        QSqlDatabase::database(databaseFileInfo.absoluteFilePath())
        : QSqlDatabase::database();
    
    if (database.isValid())
    {
        database.open();
        return database;
    }
    
    database = databaseFileInfo.exists() ?
        QSqlDatabase::addDatabase(
            "QSQLITE",
            databaseFileInfo.absoluteFilePath())
        : QSqlDatabase::addDatabase("QSQLITE");
    database.open();
    return database;
}
