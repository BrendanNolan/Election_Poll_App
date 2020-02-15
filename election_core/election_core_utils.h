#ifndef ELECTION_CORE_UTILS_H
#define ELECTION_CORE_UTILS_H

#include <QFileInfo>
#include <QSqlDatabase>

class QAbstractListModel;
class QModelIndex;
class QString;

bool isIndexValid(const QModelIndex& index, const QAbstractListModel& model);

// Returns a connection to the database file if the file exists, otherwise
// returns the default connection; in either case, the returned connection 
// may be invalid, for example if the connection has not been added with
// QSqlDatabase::addDatabase().
QSqlDatabase connectToSqlDatabase(
    const QFileInfo& databaseFileInfo = QFileInfo());

#endif // ELECTION_CORE_UTILS_H