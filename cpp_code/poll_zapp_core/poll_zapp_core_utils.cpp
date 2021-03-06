#include <Python.h>

#include "poll_zapp_core_utils.h"

#include <QAbstractListModel>
#include <QDir>
#include <QFileInfo>
#include <QString>

#include <cstdio>
#include <string>

namespace poll_zapp_core_utils
{

bool isIndexValid(const QModelIndex& index, const QAbstractListModel& model)
{
    return (index.row() >= 0) && (index.row() < model.rowCount()) && index.isValid();
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

}// namespace poll_zapp_core_utils

namespace python_scripting
{

bool runPythonScript(const QFileInfo& script)
{
    auto scriptPathAsQString =
        QDir::toNativeSeparators(script.absoluteFilePath());
    auto scriptPathAsStdString = scriptPathAsQString.toStdString();
    auto scriptPathAsCString = scriptPathAsStdString.c_str();

    auto scriptFilePtr = fopen(scriptPathAsCString, "rb");
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
