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

    if (!isIndexValid(index, *this))
        return false;
    auto& politician = *(politicianCache_[index.row()]);
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
    // More required
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
