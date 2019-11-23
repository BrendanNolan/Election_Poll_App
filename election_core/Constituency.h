#ifndef CONSTITUENCY_H
#define CONSTITUENCY_H

#include <QString>

#include "election_core_global.h"

class ELECTIONCORESHARED_EXPORT Constituency
{
public:
    Constituency() = default;
    explicit Constituency(const QString& name);

    int id() const;
    void setId(int id);
    QString name() const;
    void setName(const QString& name);

private:
    int id_ = -1;
    QString name_ = QString("");
};

#endif // CONSTITUENCY_H
