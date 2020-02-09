#ifndef MWDATAREFRESHTHREAD_H
#define MWDATAREFRESHTHREAD_H

#include <QThread>

class MWDataRefreshThread : public QThread
{
    Q_OBJECT

public:
    MWDataRefreshThread(MainWindow& mainWindow);

signals:
    void resultReady();

private:
    void run() override;

private:
    MainWindow* mainWindow_;
};

#endif // MWDATAREFRESHTHREAD_H
