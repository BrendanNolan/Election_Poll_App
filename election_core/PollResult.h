#ifndef POLLRESULT_H
#define POLLRESULT_H

#include <QDateTime>
#include <QHash>

class PollResult
{
public:
    PollResult() = default;
    explicit PollResult(
        const QString& source, 
        const QHash<QString, int>& results,
        const QDateTime& dateTime,
        int constituencyId);
    
    void append(const QString& name, int value);
    int value(const QString& name) const;
    
    QHash<QString, int> histogram() const;
    void setHistogram(const QHash<QString, int>& histogram);
    int id() const;
    void setId(int id);
    int constituencyId() const;
    void setConstituencyId(int constituencyId);
    QString source() const;
    QDateTime dateTime() const;

private:
    int constituencyId_ = -1;
    int id_ = -1;
    QHash<QString, int> histogram_;
    QString source_ = "Unknown";
    QDateTime dateTime_ = QDateTime();
};

#endif // POLLRESULT_H
