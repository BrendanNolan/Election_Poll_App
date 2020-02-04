#include "ElectionCoreFunctions.h"

#include <QAbstractListModel>
#include <QDir>
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
    if (!databaseFileInfo.exists())
        return QSqlDatabase();

    auto database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QDir::toNativeSeparators(
        databaseFileInfo.absoluteFilePath()));

    if (!database.isValid())
        return QSqlDatabase();
    
    database.open();
    return database;
}
