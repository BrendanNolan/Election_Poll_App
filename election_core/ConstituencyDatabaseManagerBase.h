#ifndef CONSTITUENCYDATABASEMANAGERBASE_H
#define CONSTITUENCYDATABASEMANAGERBASE_H

#include <memory>
#include <vector>

class Constituency;

class ConstituencyDatabaseManagerBase
{
public:
    virtual ~ConstituencyDatabaseManagerBase() = default;
    virtual void init() const = 0;
    virtual void addConstituency(Constituency& constituency) const = 0;
    virtual void updateConstituency(const Constituency& constituency) const = 0;
    virtual void removeConstituency(int id) const = 0;
    virtual std::vector<std::unique_ptr<Constituency>> 
        constituencies() const = 0;
};

#endif // CONSTITUENCYDATABASEMANAGERBASE_H
