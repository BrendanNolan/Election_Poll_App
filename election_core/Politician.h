#ifndef POLITICIAN_H
#define POLITICIAN_H

#include <QString>
#include <QUrl>

struct RGBValue
{
    RGBValue(int red = 0, int green = 0, int blue = 0)
        : red_(red)
        , green_(green)
        , blue_(blue)
    {}

    int red_;
    int green_;
    int blue_;
};

struct PartyDetails
{
    QString name_;
    RGBValue colour_;
};

class Politician
{
public:
    Politician() = default;
    Politician(const QString& name, const PartyDetails& partyDetails);

    int id() const;
    void setId(int id);
    int constituencyId() const;
    void setConstituencyId(int id);
    QString name() const;
    void setName(const QString& name);
    QUrl imageUrl() const;
    void setImageUrl(const QUrl& imageUrl);
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
