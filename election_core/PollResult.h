#ifndef POLLRESULT_H
#define POLLRESULT_H

#include <QDateTime>
#include <QHash>
#include <Qvariant>

class PollResult
{
public:
    PollResult() = default;
    PollResult(
        const QString& source, 
        const QHash<QString, QVariant>& results,
        const QDateTime& dateTime,
        int constituencyId);
    
    void append(const QString& name, int value);
    int value(const QString& name) const;
    
    QHash<QString, QVariant> histogram() const;
    void setHistogram(const QHash<QString, QVariant>& histogram);
    int id() const;
    void setId(int id);
    int constituencyId() const;
    void setConstituencyId(int constituencyId);
    QString source() const;
    QDateTime dateTime() const;

private:
    int constituencyId_ = -1;
    QHash<QString, QVariant> histogram_;
    QString source_ = "Unknown";
    QDateTime dateTime_ = QDateTime();
};

#endif // POLLRESULT_H
