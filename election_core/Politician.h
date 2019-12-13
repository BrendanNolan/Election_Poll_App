#ifndef POLITICIAN_H
#define POLITICIAN_H

#include <QUrl>

struct PartyDetails
{
    enum Colour
    {
        Red,
        Green,
        Blue,
        Yellow
    };

    QString name_;
    Colour colour_;
};

class Politician
{
public:
    Politician(const QString& name, const PartyDetails& partyDetails);

    int id() const;
    void setId(int id);
    int constituencyId() const;
    void setConstituencyId(int id);
    QString name() const;
    void setName(const QString& name);
    QString imageUrl() const;
    void setImageUrl(const QString& imageUrl);
    PartyDetails partyDetails() const;
    void setPartyDetails(const PartyDetails& party);

private:
    QUrl imageUrl_;
    QString name_;
    int id_;
    int constituencyId_;
    PartyDetails partyDetails_;
};

#endif // POLITICIAN_H
