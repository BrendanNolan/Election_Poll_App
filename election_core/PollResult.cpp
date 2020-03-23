#include "PollResult.h"

PollResult::PollResult(
    const QString& source,
    const QDateTime& dateTime,
    int constituencyId,
    const QHash<QString, int>& plot)
    : constituencyId_(constituencyId)
    , plot_(plot)
    , source_(source)
    , dateTime_(dateTime)
{
}

void PollResult::appendToPlot(const QString& name, int value)
{
    plot_[name] = value;
}

int PollResult::value(const QString& name) const
{
    return plot_[name];
}

QHash<QString, int> PollResult::plot() const
{
    return plot_;
}

void PollResult::setPlotData(const QHash<QString, int>& plot)
{
    plot_ = plot;
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
