#ifndef ROLLINGKEYVALUECACHE_H
#define ROLLINGKEYVALUECACHE_H

#include <QtGlobal>

#include <QColor>
#include <QHash>
#include <QQueue>

template<class Key, class Value> class RollingKeyValueCache
{
public:
    Value& operator[](const Key& key)
    {
        if (!hash_.contains(key))
            keyQueue_.enqueue(key);

        auto& value = hash_[key];

        if (hash_.size() > capacity_)
            hash_.remove(keyQueue_.dequeue());

        return value;
    }

    Value operator[](const Key& key) const { return hash_[key]; }

    bool contains(const Key& key) const { return hash_.contains(key); }

    void setCapacity(int capacity)
    {
        while (hash_.size() > capacity_)
        {
            auto dequeuedVal = keyQueue_.dequeue();
            auto numItemsRemoved = hash_.remove(dequeuedVal);
            Q_ASSERT(numItemsRemoved == 1);
        }

        capacity_ = capacity;
    }

private:
    QHash<Key, Value> hash_;
    QQueue<Key> keyQueue_;
    int capacity_ = 50;
};

#endif// ROLLINGKEYVALUECACHE_H
