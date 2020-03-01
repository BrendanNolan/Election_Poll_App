#include <Python.h>

#include "election_core_utils.h"

#include <QAbstractListModel>
#include <QByteArray>
#include <QDir>
#include <QFileInfo>
#include <QModelIndex>

#include <cstdio>

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

bool runPythonScript(const QFileInfo& script)
{
    auto scriptPathAsQString =
        QDir::toNativeSeparators(script.absoluteFilePath());
    auto byteArray = scriptPathAsQString.toLatin1();
    auto scriptPathAsCString = byteArray.data();

    auto scriptFilePtr = fopen(scriptPathAsCString, "r");
    if (!scriptFilePtr)
        return false;
    Py_Initialize();
    if (PyRun_SimpleFile(scriptFilePtr, scriptPathAsCString) != 0)
        return false;
    Py_Finalize();
    fclose(scriptFilePtr);
    return true;
}

}// namespace python_scripting
