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
    auto row = index.row();
    switch (role)
    {
        const auto& politician = *(politicianCache_[row]);
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

void PoliticianModel::setConstituency(int id)
{
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
