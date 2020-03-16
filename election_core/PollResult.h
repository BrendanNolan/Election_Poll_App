#ifndef POLLRESULT_H
#define POLLRESULT_H

#include <QDateTime>
#include <QHash>

class PollResult
{
public:
    PollResult() = default;
    PollResult(
        const QString& source,
        const QDateTime& dateTime,
        int constituencyId,
        const QHash<QString, int>& histogram = QHash<QString, int>());

    void appendToHistogram(const QString& name, int value);
    int value(const QString& name) const;

    QHash<QString, int> histogram() const;
    void setHistogram(const QHash<QString, int>& histogram);
    int constituencyId() const;
    void setConstituencyId(int constituencyId);
    QString source() const;
    QDateTime dateTime() const;

private:
    int constituencyId_ = -1;
    QHash<QString, int> histogram_;
    QString source_ = "Unknown";
    QDateTime dateTime_ = QDateTime();
};

#endif// POLLRESULT_H
