#ifndef SQLPOLLRESULTDATABASEMANAGER_H
#define SQLPOLLRESULTDATABASEMANAGER_H

#include <memory>

#include "IPollResultDatabaseManager.h"

class QSqlDatabase;

class SqlPollResultDatabaseManager : public IPollResultDatabaseManager
{
public:
    explicit SqlPollResultDatabaseManager(
        std::shared_ptr<QSqlDatabase> database);

    void addPollResultInConstituency(
        PollResult& result,
        int constituencyId) const override;
    void updatePollResult(const PollResult& result) const override;
    void removePollResult(int id) const override;
    std::vector<std::unique_ptr<PollResult>>
        pollResultsForConstituency(int id) const override;

private:
    std::shared_ptr<QSqlDatabase> database_;
};

#endif // SQLPOLLRESULTDATABASEMANAGER_H
