#ifndef IDATABASEMANAGERFACTORY_H
#define IDATABASEMANAGERFACTORY_H

#include <memory>

class IConstituencyDatabaseManager;
class IPollResultDatabaseManager;
class IPoliticianDatabaseManager;

class IDatabaseManagerFactory
{
public:
    virtual ~IDatabaseManagerFactory() = default;
    
    virtual std::shared_ptr<IConstituencyDatabaseManager> 
        createConstituencyDatabaseManager() const = 0;
    virtual std::shared_ptr<IPollResultDatabaseManager>
        createPollResultDatabaseManager() const = 0;
    virtual std::shared_ptr<IPoliticianDatabaseManager>
        createPoliticianDatabaseManager() const = 0;

    virtual IDatabaseManagerFactory* clone() const = 0;
};

#endif //IDATABASEMANAGERFACTORY_H
