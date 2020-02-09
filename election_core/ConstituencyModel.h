#ifndef CONSTITUENCYMODEL_H
#define CONSTITUENCYMODEL_H

#include <QAbstractTableModel>
#include <QModelIndex>

#include <memory>
#include <vector>

#include "Constituency.h"

class IConstituencyDatabaseManager;
class IDatabaseManagerFactory;

class ConstituencyModel : public QAbstractListModel
{
    Q_OBJECT

public:
    ConstituencyModel(
        const IDatabaseManagerFactory&,
        QObject* parent = nullptr);

    enum Role
    {
        LatitudeRole = Qt::UserRole + 1,
        LongitudeRole,
        NameRole,
        IdRole,
        AreaRole
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(
        const QModelIndex &index, 
        int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    QModelIndex addConstituency(std::unique_ptr<Constituency> constituency);

    // Does not emit QAbstractItemModel::modelReset(). The rationalse is that
    // constituencies don't come and go like politicians and poll results.
    // This is why I am not reimplementing QAbstractItemModel::removeRows()
    // or QAbstractItemModel::setData().
    void refresh(); 

private:
    void reloadConstituencyCache();

private:
    std::vector<std::unique_ptr<Constituency>> constituencyCache_;
    std::shared_ptr<IConstituencyDatabaseManager> constituencyManager_ = 
        nullptr;
};

#endif // CONSTITUENCYMODEL_H
