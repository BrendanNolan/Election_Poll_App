#ifndef PICTUREPROXYMODEL_H
#define PICTUREPROXYMODEL_H

#include <QMap>
#include <QIdentityProxyModel>

class PictureProxyModel : public QIdentityProxyModel
{
    Q_OBJECT

public:
    PictureProxyModel(QObject* parent = nullptr);

private:


private:
    QMap<QString, QPixmap> politicianPixmapCache_;
};

#endif // PICTUREPROXYMODEL_H
