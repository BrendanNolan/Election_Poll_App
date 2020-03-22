#include "PollResultHistogramProxyModel.h"

#include <QtGlobal>

#include <QPainter>
#include <QPen>

#include "HistogramPainter.h"
#include "PollResultModel.h"

namespace
{
const auto PREFERRED_WIDTH = 100;
const auto PREFERRED_HEIGHT = 50;
}// namespace

PollResultHistogramProxyModel::~PollResultHistogramProxyModel()
{
}

PollResultHistogramProxyModel::PollResultHistogramProxyModel(
    PollResultModel* pollResultModel, QObject* parent)
    : QIdentityProxyModel(parent)
    , histogramPainter_(std::make_unique<HistogramPainter>())
    , blackPixmap_(1, 1)
{
    setSourceModel(pollResultModel);
    blackPixmap_.fill(Qt::black);
}

QVariant PollResultHistogramProxyModel::data(
    const QModelIndex& index, int role) const
{
    auto sourcePollResultModel = pollResultModel();
    if (!sourcePollResultModel)
        return QVariant();
    if (role != Qt::DecorationRole)
        return sourcePollResultModel->data(index, role);

    auto stringVarHash =
        sourcePollResultModel->data(index, PollResultModel::HistogramRole)
            .value<QHash<QString, QVariant>>();
    QHash<QString, int> histogram;
    for (const auto& key : stringVarHash.keys())
        histogram[key] = stringVarHash[key].toInt();

    if (pixmapCache_.contains(histogram))
        return pixmapCache_.value(histogram);

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
    
    histogramPainter_->setHistogram(&histogram);
    histogramPainter_->paint(&pixmap);
    pixmapCache_.insert(histogram, pixmap);
    return pixmap;
}

void PollResultHistogramProxyModel::setCacheCapacity(int capacity)
{
    pixmapCache_.setCapacity(capacity);
}

PollResultModel* PollResultHistogramProxyModel::pollResultModel() const
{
    auto prm = qobject_cast<PollResultModel*>(sourceModel());
    Q_ASSERT(prm);
    return prm;
}
