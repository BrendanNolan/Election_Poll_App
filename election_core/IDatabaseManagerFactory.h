#ifndef IDATABASEMANAGERFACTORY_H
#define IDATABASEMANAGERFACTORY_H

#include <memory>

class IConstituencyDatabaseManager;
class IPollResultDatabaseManager;
class IImageDatabaseManager;

class IDatabaseManagerFactory
{
public:
    virtual std::shared_ptr<IConstituencyDatabaseManager> 
        createConstituencyDatabaseManager() = 0;
    virtual std::shared_ptr<IPollResultDatabaseManager>
        createPollResultDatabaseManager() = 0;
    virtual std::shared_ptr<IImageDatabaseManager>
        createImageDatabaseManager() = 0;
};

#endif //IDATABASEMANAGERFACTORY_H
