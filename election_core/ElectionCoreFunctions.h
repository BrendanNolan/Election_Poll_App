#ifndef ELECTIONCOREFUNCTIONS_H
#define ELECTIONCOREFUNCTIONS_H

#include <QSqlDatabase>

class QAbstractListModel;
class QFileInfo;
class QModelIndex;
class QString;

bool isIndexValid(const QModelIndex& index, const QAbstractListModel& model);

// Creates a database of type `type` at the given file location if there is no
// database there. If there is a database at the given file location, this
// function does nothing.
void createSqlDatabase(
    const QFileInfo& databaseFileInfo, 
    const QString& type = "QSQLITE");

// Need to check if what you get when you call this function will still be open.
QSqlDatabase makeSqlDatabaseConnection(
    const QFileInfo& databaseFileInfo,
    const QString& type = "QSQLITE");

#endif // ELECTIONCOREFUNCTIONS_H
