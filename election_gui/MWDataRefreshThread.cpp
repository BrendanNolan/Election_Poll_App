#include "MWDataRefreshThread.h"

#include "MainWindow.h"

MWDataRefreshThread::MWDataRefreshThread(MainWindow& mainWindow)
    : QThread(&mainWindow)
    , mainWindow_(&mainWindow)
{}

void MWDataRefreshThread::run()
{
    if (mainWindow_)
        mainWindow_->refreshData();
    emit resultReady();
}
