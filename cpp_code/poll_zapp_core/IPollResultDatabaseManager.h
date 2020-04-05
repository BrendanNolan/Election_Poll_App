#ifndef IPOLLRESULTDATABASEMANAGER_H
#define IPOLLRESULTDATABASEMANAGER_H

#include <memory>
#include <vector>

#include "DatabaseSignaller.h"

class PollResult;
class QString;

class IPollResultDatabaseManager
{
public:
    IPollResultDatabaseManager(
        std::shared_ptr<DatabaseSignaller> databaseSignaller);
    virtual ~IPollResultDatabaseManager() = default;
    virtual IPollResultDatabaseManager* clone() const = 0;

    virtual void addPollResult(const PollResult& result) const = 0;
    virtual void updatePollResult(const PollResult& result) const = 0;
    virtual void removePollResult(const PollResult& result) const = 0;
    virtual std::vector<std::unique_ptr<PollResult>> pollResultsForConstituency(
        int id) const = 0;

    virtual bool refreshDatabase() const = 0;
    DatabaseSignaller* databaseSignaller() const;

private:
    std::shared_ptr<DatabaseSignaller> databaseSignaller_;
};

#endif// IPOLLRESULTDATABASEMANAGER_H
