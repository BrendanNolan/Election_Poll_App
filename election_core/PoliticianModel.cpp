#include "PoliticianModel.h"

#include <QDir>
#include <QFileInfo>

#include "IDatabaseManagerFactory.h"
#include "IPoliticianDatabaseManager.h"
#include "election_core_utils.h"
#include "SqlDatabaseManagerFactory.h"

using namespace std;

PoliticianModel::PoliticianModel(
    const IDatabaseManagerFactory& factory,
    QObject* parent,
    ElectoralStatus status)
    : QAbstractListModel(parent)
    , electoralStatus_(status)
    , manager_(factory.createPoliticianDatabaseManager())
{
    refresh();
}

PoliticianModel::PoliticianModel(const PoliticianModel& rhs)
    : manager_(rhs.manager_)
    , electoralStatus_(rhs.electoralStatus_)
    , constituencyId_(rhs.constituencyId_)
{
    politicianCache_.reserve(rhs.politicianCache_.size());
    for (const auto& uniquePtrConstRef : rhs.politicianCache_)
    {
        politicianCache_.push_back(
            unique_ptr<Politician>(new Politician(*uniquePtrConstRef)));
    }
}

int PoliticianModel::rowCount(const QModelIndex& /*parent*/) const
{
    return politicianCache_.size();
}

QVariant PoliticianModel::data(
    const QModelIndex& index,
    int role) const
{
    if (!election_core_utils::isIndexValid(index, *this))
        return QVariant();
    const auto& politician = *(politicianCache_[index.row()]);
    switch (role)
    {
    case Qt::DisplayRole:
        return politician.imageUrl();
    case NameRole:
        return politician.name();
    case PartyNameRole:
        return politician.partyDetails().name_;
    case PartyColourRole:
    {
        QHash<QString, QVariant> hash;
        auto rgb = politician.partyDetails().colour_;
        hash["red"] = rgb.red_;
        hash["green"] = rgb.green_;
        hash["blue"] = rgb.blue_;
        return hash;
    }
    case FilePathRole:
        return QDir::toNativeSeparators(
            QFileInfo(politician.imageUrl().path()).absoluteFilePath());
    default: 
        return QVariant();
    }
}

bool PoliticianModel::setData(
    const QModelIndex& index,
    const QVariant& value,
    int role)
{
    if (!election_core_utils::isIndexValid(index, *this))
        return false;
    auto& politician = *(politicianCache_[index.row()]);
    switch (role)
    {
    case Qt::DisplayRole: 
        politician.setImageUrl(value.toString());
        break;
    case NameRole:
        politician.setName(value.toString());
    case PartyNameRole:
        politician.setName(value.toString());
    case PartyColourRole:
    {
        auto hash = value.value<QHash<QString, QVariant>>();
        auto details = politician.partyDetails();
        details.colour_ = RGBValue(
            hash["rgb_red"].toInt(),
            hash["rgb_green"].toInt(),
            hash["rgb_blue"].toInt());
        politician.setPartyDetails(details);
        break;
    }
    default:
        return false;
    }
    manager_->updatePolitician(politician);
    emit dataChanged(index, index);
    return true;
}

bool PoliticianModel::removeRows(
    int row, 
    int count, 
    const QModelIndex& /*parent*/)
{
    if (row < 0 || count < 0 || row + count > rowCount())
        return false;
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    auto rowsLeftToRemove = count;
    while (rowsLeftToRemove > 0)
    {
        manager_->removePolitician(
            politicianCache_[row + rowsLeftToRemove - 1]->id());
        --rowsLeftToRemove;
    }
    politicianCache_.erase(
        politicianCache_.begin() + row,
        politicianCache_.begin() + row + count);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> PoliticianModel::roleNames() const
{
    QHash<int, QByteArray> ret;
    ret[NameRole] = "Name";
    ret[PartyNameRole] = "Party Name";
    ret[PartyColourRole] = "Party Colour";
    return ret;
}

QModelIndex PoliticianModel::addPolitician(unique_ptr<Politician> politician)
{
    auto row = rowCount();

    beginInsertRows(QModelIndex(), row, row);
    manager_->addPoliticianToConstituency(*politician, constituencyId_);
    politicianCache_.push_back(move(politician));
    endInsertRows();

    return index(row);
}

PoliticianModel::ElectoralStatus PoliticianModel::electoralStatus() const
{
    return electoralStatus_;
}

void PoliticianModel::refresh()
{
    beginResetModel();
    reloadPoliticianCache();
    endResetModel();
}

void PoliticianModel::setElectoralStatus(ElectoralStatus status)
{
    beginResetModel();
    electoralStatus_ = status;
    reloadPoliticianCache();
    endResetModel();
}

void PoliticianModel::setConstituency(int id)
{
    if (id == constituencyId_)
        return;
    beginResetModel();
    constituencyId_ = id;
    reloadPoliticianCache();
    endResetModel();
}

/*
bool PoliticianModel::refreshCachedPolitician(int id)
{
    auto toUpdate = find_if(
        politicianCache_.begin(),
        politicianCache_.end(),
        [id](const unique_ptr<Politician>& c) {
            return c->id() == id;
        });
    if (toUpdate == politicianCache_.end())
        return false;
    auto row = static_cast<int>(toUpdate - politicianCache_.begin());
    *toUpdate = move(manager_->politician(id));
    emit dataChanged(index(row), index(row));
    return true;
}
*/

void PoliticianModel::reloadPoliticianCache()
{
    if (constituencyId_ == -1)
        politicianCache_.clear();
    switch (electoralStatus_)
    {
    case ElectoralStatus::SITTING:
        politicianCache_ = manager_->mpsForConstituency(constituencyId_);
        return;
    case ElectoralStatus::CANDIDATE:
        politicianCache_ = manager_->candidatesForConstituency(constituencyId_);
        return;
    }
}
