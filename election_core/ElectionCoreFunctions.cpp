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
    if (!databaseFileInfo.exists())
    {
        if (QSqlDatabase::database().isValid())
            return QSqlDatabase::database();
        QSqlDatabase::addDatabase("QSQLITE");
        return QSqlDatabase::database();
    }

    auto path = databaseFileInfo.absoluteFilePath();
    if (QSqlDatabase::database(path).isValid())
        return QSqlDatabase::database(path);
    QSqlDatabase::addDatabase("QSQLITE").setDatabaseName(path);
    return QSqlDatabase::database(path);
}
