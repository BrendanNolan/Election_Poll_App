#ifndef SQLPOLITICIANDATABASEMANAGER_H
#define SQLPOLITICIANDATABASEMANAGER_H

#include <memory>
#include <vector>

#include "IPoliticianDatabaseManager.h"

class QSqlDatabase;

class SqlPoliticianDatabaseManager : public IPoliticianDatabaseManager
{
public:
    explicit SqlPoliticianDatabaseManager(
        std::shared_ptr<QSqlDatabase> database);
    ~SqlPoliticianDatabaseManager() = default;

    void init() const override;

    std::vector<std::unique_ptr<Politician>> mpsForConstituency(
        int constituencyId) const override;
    std::vector<std::unique_ptr<Politician>> candidatesForConstituency(
        int constituencyId) const override;
    std::unique_ptr<Politician> politician(int id) const override;
    QUrl imageUrlForPolitician(int politicianId) const override;
    void addPoliticianToConstituency(
        Politician& politcian,
        int constituencyId) const override;
    void updatePolitician(const Politician& politician) const override;
    void removePolitician(int politicianId) const override;
    void clearPoliticiansFromConstituency(int constituencyId) const override;

private:
    std::shared_ptr<QSqlDatabase> database_;
};

#endif // SQLPOLITICIANDATABASEMANAGER_H
