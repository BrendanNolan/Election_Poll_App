#include "ConstituencyColoursProxyModel.h"

#include <QPainter>

#include <QtGlobal>

#include <algorithm>

#include "ConstituencyModel.h"

namespace
{
const auto PREFERRED_WIDTH = 50;
const auto PREFERRED_HEIGHT = 50;

QColor hashToColour(const QHash<QString, QVariant>& hash);
}

ConstituencyColoursProxyModel::ConstituencyColoursProxyModel(
    ConstituencyModel& constituencyModel,
    const PoliticianModel& politicianModel,
    QObject* parent)
    : politicianModel_(politicianModel)
    , QIdentityProxyModel(parent)
    , blackPixmap_(1, 1)
{
    setSourceModel(&constituencyModel);
    blackPixmap_.fill(Qt::black);
}

QVariant ConstituencyColoursProxyModel::data(
    const QModelIndex& index, int role) const
{
    auto sourceConstituencyModel = constituencyModel();
    if (!sourceConstituencyModel)
        return QVariant();
    if (role != Qt::DecorationRole)
        return sourceConstituencyModel->data(index, role);

    auto constituencyId =
        sourceConstituencyModel->data(index, ConstituencyModel::IdRole).toInt();
    politicianModel_.setConstituency(constituencyId);
    QVector<QColor> colours;
    auto politicianCount = politicianModel_.rowCount();
    if (politicianCount == 0)
        return blackPixmap_;

    for (auto row = 0; row < politicianCount; ++row)
    {
        auto rgbHash = politicianModel_
                           .data(
                               sourceConstituencyModel->index(row, 0),
                               PoliticianModel::PartyColourRole)
                           .value<QHash<QString, QVariant>>();
        colours.push_back(hashToColour(rgbHash));
    }
    std::sort(colours.begin(), colours.end(), [](QColor a, QColor b) {
        if (a.red() > b.red())
            return true;
        if (a.red() < b.red())
            return false;
        if (a.green() > b.green())
            return true;
        if (a.green() < b.green())
            return false;
        if (a.blue() > b.blue())
            return true;
        if (a.blue() < b.blue())
            return false;
        return false;
    });
    
    if (pixmapCache_.contains(colours))
        return pixmapCache_.value(colours);

    QPixmap pixmap(PREFERRED_WIDTH, PREFERRED_HEIGHT);
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
    pixmapCache_.insert(colours, pixmap);
    return pixmap;
}

void ConstituencyColoursProxyModel::setCacheCapacity(int capacity)
{
    pixmapCache_.setCapacity(capacity);
}

ConstituencyModel* ConstituencyColoursProxyModel::constituencyModel() const
{
    auto ret = qobject_cast<ConstituencyModel*>(sourceModel());
    Q_ASSERT(ret);
    return ret;
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
