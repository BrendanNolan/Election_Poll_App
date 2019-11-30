#ifndef CONSTITUENCY_H
#define CONSTITUENCY_H

#include <QUrl>
#include <QString>

#include "election_core_global.h"

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
    bool isValid() const;

private:
    int id_ = -1;
    QString name_ = QString("");
    int latitude_ = -1;
    int longitude = -1;
    QUrl pictoralRepresentationUrl_;
    QUrl mpImage_;
    QString mpName_;
};

#endif // CONSTITUENCY_H
