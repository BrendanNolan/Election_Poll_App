#include "election_core_utils.h"

#include <QAbstractListModel>
#include <QDir>
#include <QFileInfo>
#include <QModelIndex>

#include <Python.h>

namespace election_core_utils
{

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

    auto database = QSqlDatabase::database("QSQLITE");
    if (!database.isValid())
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.open();
    }

    auto path = QDir::toNativeSeparators(databaseFileInfo.absoluteFilePath());
    if (database.databaseName() != path)
        database.setDatabaseName(path);

    if (!database.isValid())
        return QSqlDatabase();

    database.open();
    return database;
}

}// namespace election_core_utils

namespace python_scripting
{

void runPythonScript(const QFileInfo& script)
{
    const auto scriptPathAsStdString = script.absoluteFilePath().toStdString();
    auto scriptPathAsCString = scriptPathAsStdString.c_str();

    auto scriptFilePtr = fopen(scriptPathAsCString, "r");
    // Not yet asynchronous but needs to be
    Py_Initialize();
    PyRun_SimpleFile(scriptFilePtr, scriptPathAsCString);
    Py_Finalize();
    fclose(scriptFilePtr);
}

}// namespace python_scripting
