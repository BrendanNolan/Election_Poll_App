#ifndef IDATABASEMANAGERFACTORY_H
#define IDATABASEMANAGERFACTORY_H

#include "election_core_global.h"
#include <memory>

class IConstituencyDatabaseManager;
class IPollResultDatabaseManager;
class IPoliticianDatabaseManager;

class ELECTIONCORESHARED_EXPORT IDatabaseManagerFactory
{
public:
    virtual ~IDatabaseManagerFactory() = default;

    virtual std::shared_ptr<IConstituencyDatabaseManager> 
        createConstituencyDatabaseManager() const = 0;
    virtual std::shared_ptr<IPollResultDatabaseManager>
        createPollResultDatabaseManager() const = 0;
    virtual std::shared_ptr<IPoliticianDatabaseManager>
        createPoliticianDatabaseManager() const = 0;
};

#endif //IDATABASEMANAGERFACTORY_H
