#ifndef POLITICIANPICTUREPROXYMODEL_H
#define POLITICIANPICTUREPROXYMODEL_H

#include <QIdentityProxyModel>

class PoliticianModel;

class PoliticianPictureProxyModel : public QIdentityProxyModel
{
public:
    PoliticianPictureProxyModel(
        QObject* parent = nullptr, PoliticianModel* politicianModel = nullptr);
};

#endif // POLITICIANPICTUREPROXYMODEL_H
