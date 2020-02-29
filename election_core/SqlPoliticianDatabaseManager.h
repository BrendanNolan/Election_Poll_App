#ifndef SQLPOLITICIANDATABASEMANAGER_H
#define SQLPOLITICIANDATABASEMANAGER_H

#include <QFileInfo>

#include <memory>
#include <vector>

#include "IPoliticianDatabaseManager.h"

class QSqlDatabase;

class SqlPoliticianDatabaseManager : public IPoliticianDatabaseManager
{
public:
    explicit SqlPoliticianDatabaseManager(
        const QFileInfo& databaseFileInfo = QFileInfo());
    SqlPoliticianDatabaseManager* clone() const override;

    std::vector<std::unique_ptr<Politician>> mpsForConstituency(
        int constituencyId) const override;
    std::vector<std::unique_ptr<Politician>> candidatesForConstituency(
        int constituencyId) const override;
    std::unique_ptr<Politician> politician(int id) const override;
    QUrl imageUrlForPolitician(int politicianId) const override;
    void addPoliticianToConstituency(
        Politician& politcian, int constituencyId) const override;
    void updatePolitician(const Politician& politician) const override;
    void removePolitician(int politicianId) const override;
    void clearPoliticiansFromConstituency(int constituencyId) const override;

    void refreshDatabase() const override;

private:
    QFileInfo databaseFileInfo_;
};

#endif// SQLPOLITICIANDATABASEMANAGER_H
