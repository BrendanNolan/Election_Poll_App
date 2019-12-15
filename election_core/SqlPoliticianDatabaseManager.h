#ifndef SQLPOLITICIANDATABASEMANAGER_H
#define SQLPOLITICIANDATABASEMANAGER_H

#include <memory>
#include <vector>

#include "IPoliticianDatabaseManager.h"

class QSqlDatabase;

class SqlPoliticianDatabaseManager : public IPoliticianDatabaseManager
{
public:
    explicit SqlPoliticianDatabaseManager(
        std::shared_ptr<QSqlDatabase> database);

private:
    std::shared_ptr<QSqlDatabase> database_;
};

#endif // SQLPOLITICIANDATABASEMANAGER_H
