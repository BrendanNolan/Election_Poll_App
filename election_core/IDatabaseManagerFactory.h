#ifndef IDATABASEMANAGERFACTORY_H
#define IDATABASEMANAGERFACTORY_H

#include "election_core_global.h"
#include <memory>

class IConstituencyDatabaseManager;
class IPollResultDatabaseManager;
class IImageDatabaseManager;

class ELECTIONCORESHARED_EXPORT IDatabaseManagerFactory
{
public:
    virtual std::shared_ptr<IConstituencyDatabaseManager> 
        createConstituencyDatabaseManager() const = 0;
    virtual std::shared_ptr<IPollResultDatabaseManager>
        createPollResultDatabaseManager() const = 0;
    virtual std::shared_ptr<IImageDatabaseManager>
        createImageDatabaseManager() const = 0;
};

#endif //IDATABASEMANAGERFACTORY_H
