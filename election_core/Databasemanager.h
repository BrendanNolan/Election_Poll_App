#ifndef IDATABASEMANAGER_H
#define IDATABASEMANAGER_H

#include <memory>
#include <vector>

class Constituency;
class PollResult;
class Image;

class IDatabaseManager
{
public:
    virtual void init() const = 0;
    
    virtual void addConstituency(Constituency& constituency) const = 0;
    virtual void updateConstituency(const Constituency& constituency) const = 0;
    virtual void removeConstituency(int id) const = 0;
    virtual std::vector<std::unique_ptr<Constituency>>
        constituencies() const = 0;

    virtual void addImageForConstituency(
        int constituencyId, Image& image) const = 0;
    virtual void removeImage(int id) const = 0;
    virtual void removeImagesForConstituency(int constituencyId) const = 0;
    virtual std::vector<std::unique_ptr<Image>> picturesForConstituency(
        int constituencyId) const = 0;

    virtual void addPollResultForConstituency(
        int constituencyId, PollResult& pollResult) const = 0;
    virtual void removePollResult(int id) const = 0;
    virtual void removePollResultsForConstituency(int constituencyId) const = 0;
    virtual std::vector<std::unique_ptr<PollResult>> pollResultForConstituency(
        int constituencyId) const = 0;
};

#endif // IDATABASEMANAGER_H
