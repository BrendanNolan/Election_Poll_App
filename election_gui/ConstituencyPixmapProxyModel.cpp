#include "ConstituencyPixmapProxyModel.h"

#include <QtGlobal>

#include <QColor>
#include <QHash>
#include <QPainter>
#include <QRectF>
#include <QString>
#include <QVariant>
#include <QVector>

#include "ConstituencyModel.h"
#include "PoliticianModel.h"

namespace
{
    QColor hashToColour(const QHash<QString, QVariant>& hash);
}

ConstituencyPixmapProxyModel::ConstituencyPixmapProxyModel(
    QObject* parent, 
    ConstituencyModel* sourceModel = nullptr,
    PoliticianModel* politicianModel)
    : QIdentityProxyModel(parent)
    , politicianModel_(politicianModel)
{
    setSourceModel(sourceModel);
}

QVariant ConstituencyPixmapProxyModel::data(
    const QModelIndex& proxyIndex, 
    int role) const
{
    if (role != Qt::DisplayRole)
        return QIdentityProxyModel::data(proxyIndex, role);
    return constituencyPixmapCache_[proxyIndex];
}

void ConstituencyPixmapProxyModel::setSourceModel(
    QAbstractItemModel* sourceMod)
{
    Q_ASSERT(qobject_cast<ConstituencyModel*>(sourceMod));

    QIdentityProxyModel::setSourceModel(sourceMod);
    refreshConstituencyPixmapCache();
    if (!sourceMod)
        return;
    
    connect(sourceMod, &QAbstractItemModel::modelReset,
        this, &ConstituencyPixmapProxyModel::refreshConstituencyPixmapCache);
    connect(sourceMod, &QAbstractItemModel::rowsInserted,
        [this](const QModelIndex& /*parent*/, int first, int last) {
        partiallyRefreshPixmapCache(index(first, 0), last - first + 1);
    });
    connect(sourceMod, &QAbstractItemModel::dataChanged,
        [this](const QModelIndex& topLeft, const QModelIndex& bottomRight) {
        auto count = bottomRight.row() - topLeft.row();
        if (count <= 0)
            return;
        partiallyRefreshPixmapCache(topLeft, count);
    });
}

void ConstituencyPixmapProxyModel::setPoliticianModel(
    PoliticianModel* politicianModel)
{
    politicianModel_ = politicianModel;
}

//ConstituencyModel* ConstituencyPixmapProxyModel::constituencyModel() const
//{
//    return qobject_cast<ConstituencyModel*>(sourceModel());
//}

void ConstituencyPixmapProxyModel::partiallyRefreshPixmapCache(
    const QModelIndex& startIndex, 
    int count)
{
    auto sourceMod = sourceModel();
    Q_ASSERT(qobject_cast<ConstituencyModel*>(sourceMod));
    if (count <= 0 || !sourceModel() || !politicianModel_)
        return;
    politicianModel_->setElectoralStatus(
        PoliticianModel::ElectoralStatus::SITTING);
    auto startRow = startIndex.row();
    for (auto i = 0; i < count; ++i)
    {
        auto pixmapUpdateIndex = index(startRow + i, 0);
        auto constituencyId = sourceMod->data(
            pixmapUpdateIndex, ConstituencyModel::IdRole).toInt();
        politicianModel_->setConstituency(constituencyId);
        QMap<QColor, int> colourCounts;
        auto politicianCount = politicianModel_->rowCount();
        for (auto row = 0; row < politicianCount; ++row)
        {
            auto rgbHash = politicianModel_->data(
                index(row, 0), PoliticianModel::PartyColourRole).
                    value<QHash<QString, QVariant>>();
            colourCounts[hashToColour(rgbHash)]++;
        }
        QPixmap pixmap(50, 50);
        auto pixmapWidth = pixmap.width();
        auto pixmapHeight = pixmap.height();
        QPainter painter(&pixmap);
        qreal currentDrawXValue = 0;
        for (auto it = colourCounts.keyValueBegin(); 
            it != colourCounts.keyValueEnd();
            ++it)
        {
            auto colour = (*it).first;
            auto sectionWidth = 
                ((*it).second > 0) ? pixmapWidth / (*it).second : 0;
            QRectF rectToFill(currentDrawXValue, 0, sectionWidth, pixmapHeight);
            painter.fillRect(rectToFill, colour);
            currentDrawXValue += sectionWidth;
        }

        constituencyPixmapCache_[pixmapUpdateIndex] = pixmap;
    }
}

void ConstituencyPixmapProxyModel::refreshConstituencyPixmapCache()
{
    constituencyPixmapCache_.clear();
    if (!sourceModel() || !politicianModel_)
        return;
    partiallyRefreshPixmapCache(index(0, 0), rowCount());
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
