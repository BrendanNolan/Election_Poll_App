#ifndef POLLRESULTHISTOGRAMPROXYMODEL_H
#define POLLRESULTHISTOGRAMPROXYMODEL_H

#include <QIdentityProxyModel>
#include <QHash>
#include <QPair>
#include <QPixmap>
#include <QString>
#include <QVariant>
#include <QVector>

#include <memory>

#include "RollingKeyValueCache.h"

class HistogramPainter;
class PollResultModel;

// OBVIOUSLY FAR FROM COMPLETE
class PollResultHistogramProxyModel : public QIdentityProxyModel
{
public:
    ~PollResultHistogramProxyModel();

    PollResultHistogramProxyModel(
        PollResultModel* pollResultModel = nullptr, QObject* parent = nullptr);
    QVariant data(
        const QModelIndex& index, int role = Qt::DecorationRole) const override;

    void setCacheCapacity(int capacity);
    PollResultModel* pollResultModel() const;

private:
    mutable RollingKeyValueCache<QHash<QString, int>, QPixmap> pixmapCache_;
    std::unique_ptr<HistogramPainter> histogramPainter_;
    QPixmap blackPixmap_;
};

#endif// POLLRESULTHISTOGRAMPROXYMODEL_H
