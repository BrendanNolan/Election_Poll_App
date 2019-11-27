#ifndef IPOLLRESULTDATABASEMANAGER_H
#define IPOLLRESULTDATABASEMANAGER_H

class PollResult;

class IPollResultDatabaseManager
{
public:
    virtual ~IPollResultDatabaseManager() = default;

    virtual void init() const = 0;
    virtual void addPollResultInConstituency(
        int constituencyId, PollResult& result) const = 0;
    virtual void updatePollResult(PollResult& result) const = 0;
    virtual void removePollResult(int id) const = 0;
    virtual std::vector<std::unique_ptr<PollResult>>
        pollResultsForConstituency(int id) const = 0;
};

#endif // IPOLLRESULTDATABASEMANAGER_H
