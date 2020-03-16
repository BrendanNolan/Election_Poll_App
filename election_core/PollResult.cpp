#include "PollResult.h"

PollResult::PollResult(
    const QString& source,
    const QDateTime& dateTime,
    int constituencyId,
    const QHash<QString, int>& histogram)
    : constituencyId_(constituencyId)
    , histogram_(histogram)
    , source_(source)
    , dateTime_(dateTime)
{
}

void PollResult::appendToHistogram(const QString& name, int value)
{
    histogram_[name] = value;
}

int PollResult::value(const QString& name) const
{
    return histogram_[name];
}

QHash<QString, int> PollResult::histogram() const
{
    return histogram_;
}

void PollResult::setHistogram(const QHash<QString, int>& histogram)
{
    histogram_ = histogram;
}

int PollResult::constituencyId() const
{
    return constituencyId_;
}

void PollResult::setConstituencyId(int constituencyId)
{
    constituencyId_ = constituencyId;
}

QString PollResult::source() const
{
    return source_;
}

QDateTime PollResult::dateTime() const
{
    return dateTime_;
}
