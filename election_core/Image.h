#ifndef IMAGE_H
#define IMAGE_H

#include <QUrl>

class Image
{
    Image(const QString& filePath = "");
    Image(const QUrl& fileUrl);

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

#endif // IMAGE_H
