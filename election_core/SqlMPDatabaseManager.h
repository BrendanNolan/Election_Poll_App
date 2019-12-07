#ifndef SQLIMAGEDATABASEMANAGER_H
#define SQLIMAGEDATABASEMANAGER_H

#include <memory>
#include <vector>

#include "IMPDatabaseManager.h"

class QSqlDatabase;

class SqlMPDatabaseManager : public IMPDatabaseManager
{
public:
    explicit SqlMPDatabaseManager(std::shared_ptr<QSqlDatabase> database);

private:
    std::shared_ptr<QSqlDatabase> database_;
};

#endif // SQLIMAGEDATABASEMANAGER_H
