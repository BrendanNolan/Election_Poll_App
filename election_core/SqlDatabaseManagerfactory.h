#ifndef SQLDATABASEMANAGERFACTORY_H
#define SQLDATABASEMANAGERFACTORY_H

#include <QFileInfo>

#include <memory>

#include "IDatabaseManagerFactory.h"

class IConstituencyDatabaseManager;
class IPollResultDatabaseManager;
class IPoliticianDatabaseManager;

class QSqlDatabase;
class QString;

class SqlDatabaseManagerFactory : public IDatabaseManagerFactory
{
public:
    SqlDatabaseManagerFactory(const QFileInfo& databaseFileInfo);

    std::shared_ptr<IConstituencyDatabaseManager>
        createConstituencyDatabaseManager() const override;
    std::shared_ptr<IPollResultDatabaseManager>
        createPollResultDatabaseManager() const override;
    std::shared_ptr<IPoliticianDatabaseManager>
        createPoliticianDatabaseManager() const override;

    SqlDatabaseManagerFactory* clone() const override;

private:
    QFileInfo databaseFileInfo_;
};

#endif // SQLDATABASEMANAGERFACTORY_H
