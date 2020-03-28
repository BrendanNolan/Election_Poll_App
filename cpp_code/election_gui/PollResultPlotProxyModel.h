#ifndef POLLRESULTPLOTPROXYMODEL_H
#define POLLRESULTPLOTPROXYMODEL_H

#include <QIdentityProxyModel>
#include <QHash>
#include <QPair>
#include <QPixmap>
#include <QString>
#include <QVariant>
#include <QVector>

#include <memory>

#include "RollingKeyValueCache.h"

class IPlotPainter;
class PollResultModel;

// OBVIOUSLY FAR FROM COMPLETE
class PollResultPlotProxyModel : public QIdentityProxyModel
{
public:
    ~PollResultPlotProxyModel();

    PollResultPlotProxyModel(
        PollResultModel* pollResultModel = nullptr, QObject* parent = nullptr);
    QVariant data(
        const QModelIndex& index, int role = Qt::DecorationRole) const override;

    void setCacheCapacity(int capacity);
    void setPlotPainter(std::unique_ptr<IPlotPainter> plotPainter);
    PollResultModel* pollResultModel() const;

private:
    mutable RollingKeyValueCache<QHash<QString, int>, QPixmap> pixmapCache_;
    std::unique_ptr<IPlotPainter> plotPainter_;
    QPixmap blackPixmap_;
};

#endif// POLLRESULTPLOTPROXYMODEL_H
