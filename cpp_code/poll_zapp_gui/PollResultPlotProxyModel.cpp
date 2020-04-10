#include "PollResultPlotProxyModel.h"

#include <QtGlobal>

#include "PollResultModel.h"
#include "poll_zapp_core_utils.h"

namespace
{
const auto PREFERRED_WIDTH = 100;
const auto PREFERRED_HEIGHT = 50;
}// namespace

PollResultPlotProxyModel::~PollResultPlotProxyModel()
{
}

PollResultPlotProxyModel::PollResultPlotProxyModel(
    PollResultModel* pollResultModel,
    const PoliticianModel& politicianModel,
    QObject* parent)
    : QIdentityProxyModel(parent)
    , politicianModel_(politicianModel)
    , blackPixmap_(1, 1)
{
    setSourceModel(pollResultModel);
    blackPixmap_.fill(Qt::black);
}

QVariant PollResultPlotProxyModel::data(// needs work
    const QModelIndex& index,
    int role) const
{
    auto sourcePollResultModel = pollResultModel();
    if (!sourcePollResultModel)
        return QVariant();
    if (role != Qt::DecorationRole)
        return sourcePollResultModel->data(index, role);

    auto stringVarHash =
        sourcePollResultModel->data(index, PollResultModel::PlotRole)
            .value<QHash<QString, QVariant>>();
    QHash<QString, int> namesAndPollingNumbers;
    for (const auto& key : stringVarHash.keys())
        namesAndPollingNumbers[key] = stringVarHash[key].toInt();
    PlotData plotData;
    for (const auto& name : namesAndPollingNumbers.keys())
    {
        auto index =
            poll_zapp_core_utils::nameToModelIndex(politicianModel_, name);
        auto colour =
            politicianModel_.data(index, PoliticianModel::PartyColourRole)
                .value<QColor>();
        plotData.push_back(
            PlotDataPoint(name, colour, namesAndPollingNumbers[name]));
    }

    if (pixmapCache_.contains(plotData))
        return pixmapCache_.value(plotData);

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

    plotPainter_->setPlotData(&plotData);
    plotPainter_->paint(&pixmap);
    pixmapCache_.insert(plotData, pixmap);
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
