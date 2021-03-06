#ifndef ICONSTITUENCYDATABASEMANAGER_H
#define ICONSTITUENCYDATABASEMANAGER_H

#include <memory>
#include <vector>

class Constituency;
class DatabaseSignaller;

class IConstituencyDatabaseManager
{
public:
    virtual ~IConstituencyDatabaseManager() = default;

    virtual void addConstituency(Constituency& constituency) const = 0;
    virtual void updateConstituency(const Constituency& constituency) const = 0;
    virtual void removeConstituency(int id) const = 0;
    virtual std::unique_ptr<Constituency> constituency(int id) const = 0;
    virtual std::vector<std::unique_ptr<Constituency>> constituencies()
        const = 0;

    virtual bool refreshDatabase() const = 0;
    virtual DatabaseSignaller& databaseSignaller() const = 0;
};

#endif// ICONSTITUENCYDATABASEMANAGER_H
