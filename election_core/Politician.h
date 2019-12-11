#ifndef POLITICIAN_H
#define POLITICIAN_H

// #include <QUrl>

enum class Colour
{
    Red,
    Green,
    Blue,
    Yellow
};

struct PartyDetails
{
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
    // QString fileUrl() const;
    // void setFileUrl(const QString& fileUrl);
    PartyDetails partyDetails() const;
    void setPartyDetails(const PartyDetails& party);

private:
    // QUrl fileurl_;
    QString name_;
    int id_;
    int constituencyId_;
    PartyDetails partyDetails_;
};

#endif // POLITICIAN_H
