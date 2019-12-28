#ifndef IPOLLRESULTDATABASEMANAGER_H
#define IPOLLRESULTDATABASEMANAGER_H

#include <vector>

class PollResult;
class QString;

class IPollResultDatabaseManager
{
public:
    virtual ~IPollResultDatabaseManager() = default;

    virtual void addPollResultInConstituency(
        PollResult& result,
        int constituencyId) const = 0;
    virtual void updatePollResult(const PollResult& result) const = 0;
    virtual void removePollResult(
        const QString& source,
        int constituencyId) const = 0;
    virtual std::vector<std::unique_ptr<PollResult>>
        pollResultsForConstituency(int id) const = 0;
};

#endif // IPOLLRESULTDATABASEMANAGER_H
