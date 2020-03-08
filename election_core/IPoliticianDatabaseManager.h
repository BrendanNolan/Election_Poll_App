#ifndef IPOLITICIANDATABASEMANAGER_H
#define IPOLITICIANDATABASEMANAGER_H

#include <Qurl>

#include <memory>
#include <vector>

#include "DatabaseSignaller.h"
#include "Politician.h"

class IPoliticianDatabaseManager
{
public:
    virtual ~IPoliticianDatabaseManager() = default;
    virtual IPoliticianDatabaseManager* clone() const = 0;

    virtual std::vector<std::unique_ptr<Politician>> mpsForConstituency(
        int constituencyId) const = 0;
    virtual std::vector<std::unique_ptr<Politician>> candidatesForConstituency(
        int constituencyId) const = 0;
    virtual std::unique_ptr<Politician> politician(int id) const = 0;
    virtual QUrl imageUrlForPolitician(int politicianId) const = 0;
    virtual void addPoliticianToConstituency(
        Politician& politcian, int constituencyId) const = 0;
    virtual void updatePolitician(const Politician& politician) const = 0;
    virtual void removePolitician(int politicianId) const = 0;
    virtual void clearPoliticiansFromConstituency(int constituencyId) const = 0;

    virtual bool refreshDatabase() const = 0;
    DatabaseSignaller* databaseSignaller() const;

private:
    std::shared_ptr<DatabaseSignaller> databaseSignaller_;
};

#endif// IPOLITICIANDATABASEMANAGER_H
