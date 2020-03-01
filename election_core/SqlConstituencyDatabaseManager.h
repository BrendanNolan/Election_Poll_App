#ifndef SQLCONSTITUENCYDATABASEMANAGER_H
#define SQLCONSTITUENCYDATABASEMANAGER_H

#include <QFileInfo>

#include <memory>
#include <vector>

#include "IConstituencyDatabaseManager.h"

class Constituency;
class QSqlDatabase;

class SqlConstituencyDatabaseManager : public IConstituencyDatabaseManager
{
public:
    explicit SqlConstituencyDatabaseManager(
        const QFileInfo& databaseFileInfo = QFileInfo());
    SqlConstituencyDatabaseManager* clone() const override;

    void addConstituency(Constituency& constituency) const override;
    void updateConstituency(const Constituency& constituency) const override;
    void removeConstituency(int id) const override;
    std::unique_ptr<Constituency> constituency(int id) const override;
    std::vector<std::unique_ptr<Constituency>> constituencies() const override;

    bool refreshDatabase() const override;

private:
    QFileInfo databaseFileInfo_;
};

#endif// SQLCONSTITUENCYDATABASEMANAGER_H
