#include "ConstituencyModel.h"

#include "IConstituencyDatabaseManager.h"
#include "IDatabaseManagerFactory.h"

#include <algorithm>

using namespace std;

ConstituencyModel::ConstituencyModel(
    const IDatabaseManagerFactory& factory,
    QObject* parent = nullptr)
    : QAbstractListModel(parent)
    , manager_(factory.createConstituencyDatabaseManager())
{
    manager_->init();
    loadConstituencies();
}

ConstituencyModel::~ConstituencyModel()
{}

int ConstituencyModel::rowCount() const
{
    return constituencies_.size();
}

QVariant ConstituencyModel::data(const QModelIndex &index, int role) const
{
    auto row = index.row();
    switch (role)
    {
        const auto& constituency = *(constituencies_[row]);
        case Qt::DisplayRole:
        {
            return constituency.pictoralRepresentation().fileName();
        }
        case LatitudeRole:
        {
            return constituency.latitude();
        }
        case LongitudeRole:
        {
            return constituency.longitude();
        }
        case NameRole:
        {
            return constituency.name();
        }
        case CurrentPartyRole:
        {
            return constituency.mp().party_;
        }
        case CurrentMPRole:
        {
            return constituency.mp().name_;
        }
        default:
        {
            return QVariant();
        }
    }
}

QModelIndex ConstituencyModel::addConstituency(const Constituency& constituency)
{
    auto row = rowCount();

    beginInsertRows(QModelIndex(), row, row);
    unique_ptr<Constituency> newConstituency(new Constituency(constituency));
    manager_->addConstituency(*newConstituency);
    constituencies_.push_back(move(newConstituency));
    endInsertRows();

    return index(row);
}

void ConstituencyModel::refreshConstituency(int id)
{
    auto toUpdate = find_if(
        constituencies_.begin(),
        constituencies_.end(),
        [id](const unique_ptr<Constituency>& c) { 
            return c->id() == id; 
        });
    if (toUpdate == constituencies_.end())
        return;
    auto row = static_cast<int>(toUpdate - constituencies_.begin());
    auto& ptr = *toUpdate;
    ptr = move(manager_->constituency(id));
    emit dataChanged(index(row), index(row));
}

void ConstituencyModel::loadConstituencies()
{
    beginResetModel();
    constituencies_ = manager_->constituencies();
    endResetModel();
}
