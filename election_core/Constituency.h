#ifndef CONSTITUENCY_H
#define CONSTITUENCY_H

#include <QUrl>
#include <QString>

#include "election_core_global.h"

class ELECTIONCORESHARED_EXPORT Constituency
{
public:
    Constituency() = default;
    Constituency(
        const QString& name,
        int latitude,
        int longitude);

    int id() const;
    void setId(int id);
    QString name() const;
    void setName(const QString& name);
    int latitude() const;
    void setLatitude(int latitude);
    int longitude() const;
    void setLongitude(int longitude);

private:
    int id_ = -1;
    QString name_ = QString("");
    int latitude_ = -1;
    int longitude_ = -1;
};

#endif // CONSTITUENCY_H
