#ifndef SQLPOLLRESULTDATABASEMANAGER_H
#define SQLPOLLRESULTDATABASEMANAGER_H

#include <QFileInfo>

#include "IPollResultDatabaseManager.h"

class SqlPollResultDatabaseManager : public IPollResultDatabaseManager
{
public:
    explicit SqlPollResultDatabaseManager(
        const QFileInfo& databaseFileInfo = QFileInfo());
    SqlPollResultDatabaseManager* clone() const override;

    void addPollResult(const PollResult& result) const override;
    void updatePollResult(const PollResult& result) const override;
    void removePollResult(const PollResult& result) const override;
    std::vector<std::unique_ptr<PollResult>> pollResultsForConstituency(
        int id) const override;

    void refreshDatabase() const override;

private:
    QFileInfo databaseFileInfo_;
};

#endif// SQLPOLLRESULTDATABASEMANAGER_H
