#ifndef DATAREFRESHSIGNALLER_H
#define DATAREFRESHSIGNALLER_H

#include <QObject>

class DatabaseSignaller : public QObject
{
    Q_OBJECT

signals:
    void databaseRefreshed();
};

#endif// DATAREFRESHSIGNALLER_H
