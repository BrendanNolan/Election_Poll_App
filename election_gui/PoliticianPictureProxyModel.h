#ifndef POLITICIANPICTUREPROXYMODEL_H
#define POLITICIANPICTUREPROXYMODEL_H

#include <QIdentityProxyModel>
#include <QPixmap>
#include <QString>
#include <QPair>
#include <QVector>

class PoliticianModel;

class PoliticianPictureProxyModel : public QIdentityProxyModel
{
public:
    PoliticianPictureProxyModel(
        PoliticianModel* politicianModel = nullptr, QObject* parent = nullptr);
    QVariant data(
        const QModelIndex& index, int role = Qt::DecorationRole) const override;
    
    void setMaxCacheCapacity(int capacity);
    PoliticianModel* politicianModel() const;

private:
    void insertIntoCacheWhileRespectingCapacity(
        const QString& filePath, const QPixmap& pixmap) const;

private:
    mutable QVector<QPair<QString, QPixmap>> pixmapCache_;
    int maxCacheCapacity_ = 50;
    QPixmap blackPixmap_;
};

#endif// POLITICIANPICTUREPROXYMODEL_H
