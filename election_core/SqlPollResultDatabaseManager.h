#ifndef SQLPOLLRESULTDATABASEMANAGER_H
#define SQLPOLLRESULTDATABASEMANAGER_H

#include <memory>

#include "IPollResultDatabaseManager.h"

class QSqlDatabase;

class SqlPollResultDatabaseManager : public IPollResultDatabaseManager
{
    explicit SqlPollResultDatabaseManager(
        std::shared_ptr<QSqlDatabase> database_);
};

#endif // SQLPOLLRESULTDATABASEMANAGER_H
