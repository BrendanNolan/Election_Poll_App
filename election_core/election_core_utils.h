#ifndef ELECTION_CORE_UTILS_H
#define ELECTION_CORE_UTILS_H

#include <QFileInfo>
#include <QModelIndex>
#include <QSqlDatabase>

class QAbstractListModel;
class QItemSelectionModel;
class QString;

namespace election_core_utils
{

template <class Model>
QModelIndex idToModelIndex(const Model& model, int id)
{
    auto numRows = model.rowCount();
    for (auto row = 0; row < numRows; ++row)
    {
        auto modelIndex = model.index(row, 0);
        if (model.data(modelIndex, Model::IdRole).toInt() == id)
            return modelIndex;
    }
    return QModelIndex();
}

bool isIndexValid(const QModelIndex& index, const QAbstractListModel& model);

// Returns a connection to the database file if the file exists, otherwise
// returns the default connection; in either case, the returned connection
// may be invalid, for example if the connection has not been added with
// QSqlDatabase::addDatabase().
QSqlDatabase connectToSqlDatabase(
    const QFileInfo& databaseFileInfo = QFileInfo());

}// namespace election_core_utils

namespace python_scripting
{

bool runPythonScript(const QFileInfo& script);

}// namespace python_scripting

#endif// ELECTION_CORE_UTILS_H
