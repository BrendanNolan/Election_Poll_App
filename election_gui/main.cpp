#include <Python.h>

#include <QApplication>
#include <QFileInfo>

#include <cstdlib>
#include <string>

#include "ElectionDefinitions.h"
#include "ElectionGuiFunctions.h"
#include "MainWindow.h"

int main(int argc, char* argv[])
{   
    // Setting up python interpreter
    auto c = argv[0];
    auto cSz = strlen(c);
    std::wstring wc(cSz + 1, L'#');
    std::mbstowcs(&wc[0], c, cSz);
    Py_SetProgramName(wc.c_str());

    election_gui_functions::runPythonScript(QFileInfo(paths::scraperScript));

    QApplication app(argc, argv);
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
