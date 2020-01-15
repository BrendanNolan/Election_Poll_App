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

QSqlDatabase getOrCreateDatabase(const QFileInfo& databaseFileInfo)
{
    auto database = QSqlDatabase::database(databaseFileInfo.absoluteFilePath());
    if (!database.isValid())
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName(databaseFileInfo.absoluteFilePath());
        database.open();
    }
    return database;
}
