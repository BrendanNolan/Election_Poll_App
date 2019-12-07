#ifndef POLITICIAN_H
#define POLITICIAN_H

#include <QUrl>

class Politician
{
    Politician(const QString& filePath = "");
    Politician(const QUrl& fileUrl);

    int id() const;
    void setId(int id);
    int parentId() const;
    void setParentId(int id);
    QString fileUrl() const;
    void setFileUrl(const QString& fileUrl);

private:
    QUrl fileurl_;
    int id_;
    int parentId_;
};

#endif // POLITICIAN_H
