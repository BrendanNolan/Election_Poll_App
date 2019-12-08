#ifndef IPOLITICIANDATABASEMANAGER_H
#define IPOLITICIANDATABASEMANAGER_H

#include "Politician.h"

class IPoliticianDatabaseManager
{
public:
    virtual ~IPoliticianDatabaseManager() = default;

    virtual void init() const = 0;
    
    virtual std::vector<Politician> mpsForConstituency(
        int constituencyId) const = 0;
    virtual std::vector<Politician> candidatesForConstituency(
        int constituencyId) const = 0;
    virtual void addPoliticianToConstituency(int politicianId) const = 0;
    virtual void updatePolitician(int politicianId) const = 0;
    virtual void removePolitician(int politicianId) const = 0;
    virtual void clearPoliticiansFromConstituency(int constituencyId) const = 0;
};

#endif // IPOLITICIANDATABASEMANAGER_H
