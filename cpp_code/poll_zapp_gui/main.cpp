#include <Python.h>

#include <QApplication>
#include <QFileInfo>
#include <QMessageBox>

#include <cstdlib>
#include <exception>
#include <string>

#include "MainWindow.h"
#include "StartupHandler.h"

int main(int argc, char* argv[])
{
    // Setting up python interpreter
    auto c = argv[0];
    auto cSz = strlen(c);
    std::wstring wc(cSz + 1, L'#');
    std::mbstowcs(&wc[0], c, cSz);
    Py_SetProgramName(wc.c_str());

    StartupHandler startup;
    try
    {
        startup.performStartupTasks();
    }
    catch (const std::exception& /*exc*/)
    {
        QMessageBox failureWarning;
        failureWarning.setWindowTitle("Load Failure");
        failureWarning.setIcon(QMessageBox::Warning);
        failureWarning.setText("Data Loading Operation Failed");
        failureWarning.exec();
    }

    QApplication app(argc, argv);
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
