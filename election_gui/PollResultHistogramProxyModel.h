#ifndef POLLRESULTHISTOGRAMPROXYMODEL_H
#define POLLRESULTHISTOGRAMPROXYMODEL_H

#include <QIdentityProxyModel>
#include <QHash>
#include <QPair>
#include <QPixmap>
#include <QString>
#include <QVariant>
#include <QVector>

class PollResultModel;

// OBVIOUSLY FAR FROM COMPLETE
class PollResultHistogramProxyModel : public QIdentityProxyModel
{
public:
    PollResultHistogramProxyModel(
        PollResultModel* pollResultModel = nullptr, QObject* parent = nullptr);
    QVariant data(
        const QModelIndex& index, int role = Qt::DecorationRole) const override;

    void setMaxCacheCapacity(int capacity);
    PollResultModel* pollResultModel() const;

private:
    void insertToCacheWhileRespectingCapacity(
        const QPair<QHash<QString, QVariant>, QPixmap>& pair) const;

private:
    mutable QVector<QPair<QHash<QString, int>, QPixmap>> pixmapCache_;
    int maxCacheCapacity_ = 50;
    QPixmap blackPixmap_;
};

#endif// POLLRESULTHISTOGRAMPROXYMODEL_H
