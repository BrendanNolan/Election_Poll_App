#include "PoliticianModel.h"

#include "IDatabaseManagerFactory.h"
#include "IPoliticianDatabaseManager.h"

#include "ListModelFunctions.h"

using namespace std;

PoliticianModel::PoliticianModel(
    ElectoralStatus status,
    const IDatabaseManagerFactory& factory,
    QObject* parent)
    : electoralStatus_(status)
    , QAbstractListModel(parent)
    , manager_(factory.createPoliticianDatabaseManager())
{
    manager_->init();
    loadPoliticianCache();
}

int PoliticianModel::rowCount() const
{
    return politicianCache_.size();
}

QVariant PoliticianModel::data(
    const QModelIndex& index,
    int role = Qt::DisplayRole) const
{
    if (!isIndexValid(index, *this))
        return QVariant();
    switch (role)
    {
        const auto& politician = *(politicianCache_[index.row()]);
    case Qt::DisplayRole:
        return politician.imageUrl();
    case ConstituencyIdRole:
        return politician.constituencyId();
    case IdRole:
        return politician.id();
    case PartyNameRole:
        return politician.partyDetails().name_;
    /*case PartyColourRole:
        return;*/
    }
}

bool PoliticianModel::setData(
    const QModelIndex& index,
    const QVariant& value,
    int role)
{
    if (role != Qt::DisplayRole && role != PartyNameRole)
        return false;
    if (!isIndexValid(index, *this))
        return false;
    auto& politician = *(politicianCache_[index.row()]);
    switch (role)
    {
    case Qt::DisplayRole: 
        politician.setImageUrl(value.toString());
        break;
    case PartyNameRole:
        politician.setName(value.toString());
        break;
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
    const QModelIndex& parent)
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
    ret[ConstituencyIdRole] = "Constituency Id";
    ret[IdRole] = "Id";
    ret[PartyNameRole] = "Party Name";
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

void PoliticianModel::setElectoralStatus(ElectoralStatus status)
{
    beginResetModel();
    electoralStatus_ = status;
    loadPoliticianCache();
    endResetModel();
}

void PoliticianModel::setConstituency(int id)
{
    if (id == constituencyId_)
        return;
    beginResetModel();
    constituencyId_ = id;
    loadPoliticianCache();
    endResetModel();
}

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

void PoliticianModel::loadPoliticianCache()
{
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
