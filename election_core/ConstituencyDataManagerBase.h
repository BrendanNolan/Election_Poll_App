#ifndef CONSTITUENCYDATAMANAGERBASE_H
#define CONSTITUENCYDATAMANAGERBASE_H

#include <memory>
#include <vector>

class Constituency;

class ConstituencyDataManagerBase
{
public:
    virtual void init() const = 0;
    virtual void addConstituency(Constituency& constituency) const = 0;
    virtual void updateConstituency(const Constituency& constituency) const = 0;
    virtual void removeConstituency(int id) const = 0;
    virtual std::vector<std::unique_ptr<Constituency>> 
        constituencies() const = 0;
};

#endif // CONSTITUENCYDATAMANAGERBASE_H
