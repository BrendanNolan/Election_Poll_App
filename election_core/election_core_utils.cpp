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

const char* election_core_utils::qStringToCString(const QString& qString)
{
    // Do not try to contract the two lines below into a single line i.e. 
    // do not make the body of the function as follows:
    //   return qString.toLatin1().data();  
    auto byteArray = qString.toLatin1();
    return byteArray.data();
}

}// namespace election_core_utils

namespace python_scripting
{

bool runPythonScript(const QFileInfo& script)
{
    auto scriptPathAsQString =
        QDir::toNativeSeparators(script.absoluteFilePath());
    auto scriptPathAsCString =
        election_core_utils::qStringToCString(scriptPathAsQString);

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
