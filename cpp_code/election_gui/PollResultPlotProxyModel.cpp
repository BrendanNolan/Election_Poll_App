#include "PollResultPlotProxyModel.h"

#include <QtGlobal>

#include "IPlotPainter.h"
#include "PollResultModel.h"

namespace
{
const auto PREFERRED_WIDTH = 100;
const auto PREFERRED_HEIGHT = 50;
}// namespace

PollResultPlotProxyModel::~PollResultPlotProxyModel()
{
}

PollResultPlotProxyModel::PollResultPlotProxyModel(
    PollResultModel* pollResultModel, QObject* parent)
    : QIdentityProxyModel(parent)
    , blackPixmap_(1, 1)
{
    setSourceModel(pollResultModel);
    blackPixmap_.fill(Qt::black);
}

QVariant PollResultPlotProxyModel::data(
    const QModelIndex& index, int role) const
{
    auto sourcePollResultModel = pollResultModel();
    if (!sourcePollResultModel)
        return QVariant();
    if (role != Qt::DecorationRole)
        return sourcePollResultModel->data(index, role);

    auto stringVarHash =
        sourcePollResultModel->data(index, PollResultModel::PlotRole)
            .value<QHash<QString, QVariant>>();
    QHash<QString, int> plot;
    for (const auto& key : stringVarHash.keys())
        plot[key] = stringVarHash[key].toInt();

    if (pixmapCache_.contains(plot))
        return pixmapCache_.value(plot);

    if (!plotPainter_)
        return QPixmap();

    QPixmap pixmap(PREFERRED_WIDTH, PREFERRED_HEIGHT);
    auto pollSource = data(index, PollResultModel::SourceRole).toString();
    if (pollSource == "NYT")
        pixmap.fill(Qt::cyan);
    else if (pollSource == "WAPO")
        pixmap.fill(Qt::darkYellow);
    else if (pollSource == "HUFFPO")
        pixmap.fill(Qt::green);
    else
        pixmap.fill(Qt::magenta);
    
    plotPainter_->setPlotData(&plot);
    plotPainter_->paint(&pixmap);
    pixmapCache_.insert(plot, pixmap);
    return pixmap;
}

void PollResultPlotProxyModel::setCacheCapacity(int capacity)
{
    pixmapCache_.setCapacity(capacity);
}

void PollResultPlotProxyModel::setPlotPainter(
    std::unique_ptr<IPlotPainter> plotPainter)
{
    plotPainter_ = std::move(plotPainter);
}

PollResultModel* PollResultPlotProxyModel::pollResultModel() const
{
    auto prm = qobject_cast<PollResultModel*>(sourceModel());
    Q_ASSERT(prm);
    return prm;
}
