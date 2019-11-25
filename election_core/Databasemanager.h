#ifndef IDATABASEMANAGER_H
#define IDATABASEMANAGER_H

class IConstituencyDatabaseManager;
class IImageDatabaseManager;
class IPollResultsDatabaseManager;


class IDatabaseManager
{
public:
    virtual const IConstituencyDatabaseManager& 
        constituencyDatabaseManager() const = 0;
    virtual const IImageDatabaseManager& imageDatabaseManager() const = 0;
    virtual const IPollResultsDatabaseManager& 
        pollResultsDatabaseManager() const = 0;
};

#endif // IDATABASEMANAGER_H
