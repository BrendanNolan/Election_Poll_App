#include "ConstituencyPixmapCreatingFunctor.h"

#include <QModelIndex>
#include <QPainter>

#include "ConstituencyModel.h"

namespace
{
QColor hashToColour(const QHash<QString, QVariant>& hash);
}

ConstituencyPixmapCreatingFunctor::ConstituencyPixmapCreatingFunctor(
    const ConstituencyModel* constituencyModel,
    const PoliticianModel& politicianModel)
    : constituencyModel_(constituencyModel)
    , politicianModel_(politicianModel)
{
    politicianModel_.setParent(nullptr);
    politicianModel_.setElectoralStatus(
        PoliticianModel::ElectoralStatus::SITTING);
}

QPixmap ConstituencyPixmapCreatingFunctor::operator()(
    const QModelIndex& index) const
{
    if (!constituencyModel_)
        return QPixmap();

    auto constituencyId =
        constituencyModel_->data(index, ConstituencyModel::IdRole).toInt();
    politicianModel_.setConstituency(constituencyId);
    QVector<QColor> colours;
    auto politicianCount = politicianModel_.rowCount();
    if (politicianCount == 0)
    {
        QPixmap blackPixmap(50, 50);
        blackPixmap.fill(Qt::black);
        return blackPixmap;
    }
    for (auto row = 0; row < politicianCount; ++row)
    {
        auto rgbHash = politicianModel_
                           .data(constituencyModel_->index(row, 0),
                               PoliticianModel::PartyColourRole)
                           .value<QHash<QString, QVariant>>();
        colours.push_back(hashToColour(rgbHash));
    }
    QPixmap pixmap(50, 50);
    auto sectionWidth = pixmap.width() / politicianCount;
    auto pixmapHeight = pixmap.height();
    QPainter painter(&pixmap);
    auto currentDrawXValue = 0.0;
    for (const auto& colour : colours)
    {
        QRectF rectToFill(currentDrawXValue, 0, sectionWidth, pixmapHeight);
        painter.fillRect(rectToFill, colour);
        currentDrawXValue += sectionWidth;
    }

    return pixmap;
}

namespace
{
QColor hashToColour(const QHash<QString, QVariant>& hash)
{
    auto red = hash["red"].toInt();
    auto green = hash["green"].toInt();
    auto blue = hash["blue"].toInt();
    return QColor(red, green, blue);
}
}// namespace
