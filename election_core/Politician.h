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
    {
    }

    int red_;
    int green_;
    int blue_;
};

struct PartyDetails
{
    PartyDetails() = default;
    PartyDetails(const QString& name, const RGBValue& rgb)
        : name_(name)
        , colour_(rgb)
    {
    }

    QString name_;
    RGBValue colour_;
};

class Politician
{
public:
    Politician() = default;

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
    bool elected() const;
    void setElected(bool elected);
    bool candidate() const;
    void setCandidate(bool candidate);

private:
    QUrl imageUrl_;
    QString name_;
    int id_;
    int constituencyId_;
    PartyDetails partyDetails_;
    bool elected_;
    bool candidate_;
};

#endif// POLITICIAN_H
