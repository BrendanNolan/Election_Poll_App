#include <Python.h>

#include "election_gui_utils.h"

#include <QFileInfo>

#include <cstdio>

namespace python_script_running
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

}
