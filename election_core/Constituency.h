#ifndef CONSTITUENCY_H
#define CONSTITUENCY_H

#include <QUrl>
#include <QString>

#include "election_core_global.h"

struct MemberOfParliament
{
    QString name_;
    QString party_;
    QUrl image_;
};

class ELECTIONCORESHARED_EXPORT Constituency
{
public:
    Constituency() = default;
    explicit Constituency(
        const QString& name,
        int latitude,
        int longitude,
        const QUrl& pictoralRepresentationUrl);

    int id() const;
    void setId(int id);
    QString name() const;
    void setName(const QString& name);
    QUrl pictoralRepresentation() const;
    void setPictoralRepresentation(const QUrl& pic);
    int latitude() const;
    void setLatitude(int latitude);
    int longitude() const;
    void setLongitude(int longitude);
    MemberOfParliament mp() const;
    void setMp(const MemberOfParliament& mp);
    bool isValid() const;

private:
    int id_ = -1;
    QString name_ = QString("");
    int latitude_ = -1;
    int longitude_ = -1;
    QUrl pictoralRepresentationUrl_;
    MemberOfParliament mp_;
};

#endif // CONSTITUENCY_H
