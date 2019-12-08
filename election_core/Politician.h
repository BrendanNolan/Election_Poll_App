#ifndef POLITICIAN_H
#define POLITICIAN_H

#include <QUrl>

enum class Colour
{
    Red,
    Green,
    Blue,
    Yellow
};

struct Party
{
    QString name_;
    Colour colour_;
};

class Politician
{
public:
    Politician(const QString& filePath = "");
    Politician(const QUrl& fileUrl);

    int id() const;
    void setId(int id);
    int parentId() const;
    void setParentId(int id);
    QString fileUrl() const;
    void setFileUrl(const QString& fileUrl);
    const Party& party() const;
    void setParty(const Party& party);

private:
    QUrl fileurl_;
    int id_;
    int parentId_;
    Party party_;
};

#endif // POLITICIAN_H
