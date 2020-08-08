#ifndef SQLPOLLRESULTDATABASEMANAGER_H
#define SQLPOLLRESULTDATABASEMANAGER_H

#include <QFileInfo>

#include <memory>
#include <mutex>

#include "DatabaseSignaller.h"
#include "IPollResultDatabaseManager.h"

class SqlPollResultDatabaseManager : public IPollResultDatabaseManager
{
public:
    explicit SqlPollResultDatabaseManager(
        const QFileInfo& databaseFileInfo = QFileInfo());

    void addPollResult(const PollResult& result) const override;
    void updatePollResult(const PollResult& result) const override;
    void removePollResult(const PollResult& result) const override;
    std::vector<std::unique_ptr<PollResult>> pollResultsForConstituency(
        int id) const override;

    bool refreshDatabase() const override;
    DatabaseSignaller& databaseSignaller() const override;

private:
    QFileInfo databaseFileInfo_;
    mutable DatabaseSignaller signaller_;
    mutable std::mutex mutex_;
};

#endif// SQLPOLLRESULTDATABASEMANAGER_H
