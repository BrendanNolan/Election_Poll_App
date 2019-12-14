#include "PoliticianModel.h"

#include "IDatabaseManagerFactory.h"
#include "IPoliticianDatabaseManager.h"

#include "ListModelFunctions.h"

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

void PoliticianModel::setConstituency(int id)
{
    if (id == constituencyId_)
        return;
    beginResetModel();
    constituencyId_ = id;
    loadPoliticianCache();
    endResetModel();
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
