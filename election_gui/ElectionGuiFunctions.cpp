#include <Python.h>

#include "ElectionGuiFunctions.h"

#include <QFileInfo>

#include <cstdio>

void election_gui_functions::runPythonScript(const QFileInfo& script)
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
