#include "PollResultPixmapCreatingFunctor.h"

#include <QColor>
#include <QModelIndex>

#include <vector>

#include "PollResultModel.h"

PollResultPixmapCreatingFunctor::PollResultPixmapCreatingFunctor(
    const PollResultModel* pollResultModel)
    : pollResultModel_(pollResultModel)
{}

QPixmap PollResultPixmapCreatingFunctor::operator()(
    const QModelIndex& index) const
{
    if (!pollResultModel_)
        return QPixmap();

    auto histogram = pollResultModel_->data(
        index, PollResultModel::HistogramRole)
        .value<QHash<QString, QVariant>>();

    QPixmap ret;
    // PLACEHOLDER DUMMY IMPLEMENTATION
    {
        std::vector<int> pollPercentages;
        pollPercentages.reserve(histogram.size());
        for (auto s : histogram.values())
            pollPercentages.push_back(s.toInt());

        std::vector<int> rgb(3, 100);
        for (size_t i = 0; i < pollPercentages.size(); ++i)
        {
            rgb[i % 3] += pollPercentages[i];
            rgb[i % 3] %= 256;
        }

        ret.fill(QColor(rgb[0], rgb[1], rgb[2]));
    }

    return ret;
}
