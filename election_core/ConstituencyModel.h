#ifndef CONSTITUENCYMODEL_H
#define CONSTITUENCYMODEL_H

#include <QAbstractTableModel>
#include <QModelIndex>

#include <memory>
#include <vector>

#include "Constituency.h"

class IConstituencyDatabaseManager;
class IPoliticianDatabaseManager;
class IDatabaseManagerFactory;

class ConstituencyModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ConstituencyModel(
        const IDatabaseManagerFactory&,
        QObject *parent = nullptr);
    enum Role
    {
        NameRole = Qt::UserRole + 1,
        LatitudeRole,
        LongitudeRole,
        IDRole, 
        DisplayRole
    };

    int rowCount() const;
    QVariant data(
        const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(
        const QModelIndex& index,
        const QVariant& value,
        int role) override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;
    QHash<int, QByteArray> roleNames() const override;

    QModelIndex addConstituency(const Constituency& constituency);

private:
    void refreshConstituency(int id);
    void loadConstituencies();

private:
    std::vector<std::unique_ptr<Constituency>> constituencies_;
    std::shared_ptr<IConstituencyDatabaseManager> constituencyManager_;
    std::shared_ptr<IPoliticianDatabaseManager> politicianManager_;
};

#endif // CONSTITUENCYMODEL_H
