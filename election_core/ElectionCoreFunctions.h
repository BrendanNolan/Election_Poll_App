#ifndef ELECTIONCOREFUNCTIONS_H
#define ELECTIONCOREFUNCTIONS_H

#include <QSqlDatabase>

class QAbstractListModel;
class QFileInfo;
class QModelIndex;

bool isIndexValid(const QModelIndex& index, const QAbstractListModel& model);

// Need to check if what you get when you call this function will still be open.
QSqlDatabase getOrCreateDatabase(const QFileInfo& databaseFileInfo);

#endif // ELECTIONCOREFUNCTIONS_H
