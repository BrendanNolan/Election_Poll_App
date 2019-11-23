#ifndef SQLCONSTITUENCYDATAMANAGER_H
#define SQLCONSTITUENCYDATAMANAGER_H

#include <memory>
#include <vector>

#include "ConstituencyDataManagerBase.h"

class Constituency;
class QSqlDatabase;

class SqlConstituencyDataManager : public ConstituencyDataManagerBase
{
public:
    explicit SqlConstituencyDataManager(std::shared_ptr<QSqlDatabase> database);
    
    void init() const override;
    void addConstituency(Constituency& constituency) const override;
    void updateConstituency(const Constituency& constituency) const override;
    void removeConstituency(int id) const override;
    std::vector<std::unique_ptr<Constituency>>
        constituencies() const override;

private:
    std::shared_ptr<QSqlDatabase> database_;
};

#endif // SQLCONSTITUENCYDATAMANAGER_H
