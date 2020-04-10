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

#include "IPlotPainter.h"
#include "PoliticianModel.h"
#include "RollingKeyValueCache.h"

class PollResultModel;

// OBVIOUSLY FAR FROM COMPLETE
class PollResultPlotProxyModel : public QIdentityProxyModel
{
public:
    ~PollResultPlotProxyModel();

    PollResultPlotProxyModel(
        PollResultModel& pollResultModel,
        const PoliticianModel& politicianModel,
        QObject* parent = nullptr);
    QVariant data(
        const QModelIndex& index, int role = Qt::DecorationRole) const override;

    void setCacheCapacity(int capacity);
    void setPlotPainter(std::unique_ptr<IPlotPainter> plotPainter);
    PollResultModel* pollResultModel() const;

private:
    mutable PoliticianModel politicianModel_;
    mutable RollingKeyValueCache<PlotData, QPixmap> pixmapCache_;
    std::unique_ptr<IPlotPainter> plotPainter_;
    QPixmap blackPixmap_;
};

#endif// POLLRESULTPLOTPROXYMODEL_H
