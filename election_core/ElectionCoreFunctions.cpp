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

void conditionallyCreateSqlDatabase(
    const QFileInfo& databaseFileInfo,
    const QString& type)
{
    auto database = QSqlDatabase::database(databaseFileInfo.absoluteFilePath());
    if (database.isValid())
        return;
    database = QSqlDatabase::addDatabase(type);
    database.setDatabaseName(databaseFileInfo.absoluteFilePath());
}

QSqlDatabase makeSqlDatabaseConnection(
    const QFileInfo& databaseFileInfo,
    const QString& type)
{
    conditionallyCreateSqlDatabase(databaseFileInfo, type);
    return QSqlDatabase::database(databaseFileInfo.absoluteFilePath());
}
