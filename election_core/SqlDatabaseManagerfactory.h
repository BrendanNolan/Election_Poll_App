#ifndef SQLDATABASEMANAGERFACTORY_H
#define SQLDATABASEMANAGERFACTORY_H

#include <memory>

#include "IDatabaseManagerFactory.h"

class IConstituencyDatabaseManager;
class IPollResultDatabaseManager;
class IPoliticianDatabaseManager;

class QSqlDatabase;

class SqlDatabaseManagerFactory : public IDatabaseManagerFactory
{
public:
    std::shared_ptr<IConstituencyDatabaseManager>
        createConstituencyDatabaseManager() const override;
    std::shared_ptr<IPollResultDatabaseManager>
        createPollResultDatabaseManager() const override;
    std::shared_ptr<IPoliticianDatabaseManager>
        createPoliticianDatabaseManager() const override;

private:
    static std::shared_ptr<QSqlDatabase> database_;
};

#endif // SQLDATABASEMANAGERFACTORY_H
