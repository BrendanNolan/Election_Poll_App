#ifndef MP_H
#define MP_H

#include <QUrl>

class MP
{
    MP(const QString& filePath = "");
    MP(const QUrl& fileUrl);

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

#endif // MP_H
