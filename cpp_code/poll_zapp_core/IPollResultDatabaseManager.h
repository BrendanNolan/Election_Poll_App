#ifndef IPOLLRESULTDATABASEMANAGER_H
#define IPOLLRESULTDATABASEMANAGER_H

#include <memory>
#include <vector>

class DatabaseSignaller;

class PollResult;
class QString;

class IPollResultDatabaseManager
{
public:
    virtual ~IPollResultDatabaseManager() = default;

    virtual void addPollResult(const PollResult& result) const = 0;
    virtual void updatePollResult(const PollResult& result) const = 0;
    virtual void removePollResult(const PollResult& result) const = 0;
    virtual std::vector<std::unique_ptr<PollResult>> pollResultsForConstituency(
        int id) const = 0;

    virtual bool refreshDatabase() const = 0;
    virtual DatabaseSignaller& databaseSignaller() const = 0;
};

#endif// IPOLLRESULTDATABASEMANAGER_H
