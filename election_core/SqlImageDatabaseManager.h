#ifndef SQLIMAGEDATABASEMANAGER_H
#define SQLIMAGEDATABASEMANAGER_H

#include <memory>
#include <vector>

#include "IImageDatabaseManager.h"

class QSqlDatabase;

class SqlImageDatabaseManager : public IImageDatabaseManager
{
public:
    explicit SqlImageDatabaseManager(std::shared_ptr<QSqlDatabase> database);

private:
    std::shared_ptr<QSqlDatabase> database_;
};

#endif // SQLIMAGEDATABASEMANAGER_H
