#ifndef POLLRESULT_H
#define POLLRESULT_H

#include <QHash>

class PollResult
{
public:
    PollResult() = default;
    explicit PollResult(const QHash<QString, int>& results);
    
    void append(const QString& name, int value);
    int value(const QString& name) const;
    void setResults(const QHash<QString, int>& results);
    QHash<QString, int> results() const;

private:
    int parentId_;
    int id_;
    QHash<QString, int> histogram_;
    QString source_;
};

#endif // POLLRESULT_H
