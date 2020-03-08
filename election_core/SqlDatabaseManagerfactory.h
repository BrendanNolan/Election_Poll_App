#ifndef SQLDATABASEMANAGERFACTORY_H
#define SQLDATABASEMANAGERFACTORY_H

#include <QFileInfo>

#include <memory>

#include "IDatabaseManagerFactory.h"

class DatabaseSignaller;
class IConstituencyDatabaseManager;
class IPollResultDatabaseManager;
class IPoliticianDatabaseManager;

class QSqlDatabase;
class QString;

class SqlDatabaseManagerFactory : public IDatabaseManagerFactory
{
public:
    explicit SqlDatabaseManagerFactory(
        const QFileInfo& databaseFileInfo = QFileInfo());
    SqlDatabaseManagerFactory* clone() const override;

    std::shared_ptr<IConstituencyDatabaseManager>
        createConstituencyDatabaseManager() const override;
    std::shared_ptr<IPollResultDatabaseManager>
        createPollResultDatabaseManager() const override;
    std::shared_ptr<IPoliticianDatabaseManager>
        createPoliticianDatabaseManager() const override;

private:
    QFileInfo databaseFileInfo_;
    std::shared_ptr<DatabaseSignaller> constituencySignaller_;
    std::shared_ptr<DatabaseSignaller> politicianSignaller_;
    std::shared_ptr<DatabaseSignaller> pollResultSignaller_;
};

#endif// SQLDATABASEMANAGERFACTORY_H
