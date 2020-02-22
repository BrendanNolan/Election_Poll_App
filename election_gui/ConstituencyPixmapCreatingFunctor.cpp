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
    politicianModel_.setElectoralStatus(
        PoliticianModel::ElectoralStatus::SITTING);
}

ConstituencyPixmapCreatingFunctor::~ConstituencyPixmapCreatingFunctor()
{}

QPixmap ConstituencyPixmapCreatingFunctor::operator()(
    const QModelIndex& index) const
{
    if (!constituencyModel_)
        return QPixmap();

    auto constituencyId = constituencyModel_->data(
        index, ConstituencyModel::IdRole).toInt();
    politicianModel_.setConstituency(constituencyId);
    QVector<QColor> colours;
    auto politicianCount = politicianModel_.rowCount();
    for (auto row = 0; row < politicianCount; ++row)
    {
        auto rgbHash = politicianModel_.data(
            constituencyModel_->index(row, 0), PoliticianModel::PartyColourRole)
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
}
