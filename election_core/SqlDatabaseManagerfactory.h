#ifndef SQLDATABASEMANAGERFACTORY_H
#define SQLDATABASEMANAGERFACTORY_H

#include <QString>

#include <memory>

#include "IDatabaseManagerFactory.h"

class IConstituencyDatabaseManager;
class IPollResultDatabaseManager;
class IPoliticianDatabaseManager;

class QSqlDatabase;

class SqlDatabaseManagerFactory : public IDatabaseManagerFactory
{
public:
    SqlDatabaseManagerFactory(
        std::shared_ptr<QSqlDatabase> database = nullptr,
        const QString& name = "election_database.db",
        const QString& type = "QSQLITE");

    std::shared_ptr<IConstituencyDatabaseManager>
        createConstituencyDatabaseManager() const override;
    std::shared_ptr<IPollResultDatabaseManager>
        createPollResultDatabaseManager() const override;
    std::shared_ptr<IPoliticianDatabaseManager>
        createPoliticianDatabaseManager() const override;

    SqlDatabaseManagerFactory* clone() const override;

private:
    std::shared_ptr<QSqlDatabase> database_;
};

#endif // SQLDATABASEMANAGERFACTORY_H
