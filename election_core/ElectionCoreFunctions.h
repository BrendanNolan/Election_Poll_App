#ifndef ELECTIONCOREFUNCTIONS_H
#define ELECTIONCOREFUNCTIONS_H

#include <QFileInfo>
#include <QSqlDatabase>

class QAbstractListModel;
class QModelIndex;
class QString;

bool isIndexValid(const QModelIndex& index, const QAbstractListModel& model);

// If the database file exists, then this function returns an open connection
// to the database, first adding a database connection to the file if necessary.
// If the file does not exist, then this function simply returns the default 
// connection, which may ne invalid.
QSqlDatabase connectToSqlDatabase(
    const QFileInfo& databaseFileInfo = QFileInfo());

#endif // ELECTIONCOREFUNCTIONS_H
