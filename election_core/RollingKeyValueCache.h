#ifndef ROLLINGKEYVALUECACHE_H
#define ROLLINGKEYVALUECACHE_H

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <vector>

template<class Key, class Value> class RollingKeyValueCache
{
public:
    void insert(const Key& key, const Value& value)
    {
        auto found = find(key);
        if (found == cache_.end())
        {
            cache_.emplace_back(key, value);
            reduceToCapacity();
            return;
        }

        found->second = value;
    }

    bool contains(const Key& key) const { return find(key) != cache_.end(); }

    /*
        Throws std::out_of_range exception if \param key not present in cache.
    */
    Value& value(const Key& key)
    {
        auto found = find(key);
        if (found == cache_.end())
            throw std::out_of_range("Attempt to find value of missing key.");
        return found->second;
    }

    void setCapacity(int capacity)
    {
        capacity_ = capacity;
        reduceToCapacity();
    }

private:
    void reduceToCapacity()
    {
        while (cache_.size() > static_cast<size_t>(capacity_))
            cache_.erase(cache_.begin());
    }

    typename std::vector<std::pair<Key, Value>>::iterator find(const Key& key)
    {
        auto found = std::find_if(
            cache_.begin(),
            cache_.end(),
            [&key](const std::pair<Key, Value>& pair) {
                return pair.first == key;
            });
        return found;
    }

    typename std::vector<std::pair<Key, Value>>::const_iterator find(
        const Key& key) const
    {
        auto found = std::find_if(
            cache_.cbegin(),
            cache_.cend(),
            [&key](const std::pair<Key, Value>& pair) {
                return pair.first == key;
            });
        return found;
    }

private:
    std::vector<std::pair<Key, Value>> cache_;
    int capacity_ = 50;
};

#endif// ROLLINGKEYVALUECACHE_H
