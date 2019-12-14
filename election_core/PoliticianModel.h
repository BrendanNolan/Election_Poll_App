#ifndef POLITICIANMODEL_H
#define POLITICIANMODEL_H

#include <QAbstractListModel>

#include <memory>
#include <vector>

#include "Politician.h"

class IDatabaseManagerFactory;
class IPoliticianDatabaseManager;

class PoliticianModel : public QAbstractListModel
{
public:
    explicit PoliticianModel(
        const IDatabaseManagerFactory&,
        QObject *parent = nullptr);
    enum Role
    {
        ImageUrlRole = Qt::UserRole + 1,
        NameRole,
        ConstituencyIdRole,
        IdRole,
        PartyNameRole,
        PartyColourRole
    };

    int rowCount() const;
    QVariant data(
        const QModelIndex &index,
        int role = Qt::DisplayRole) const override;
    bool setData(
        const QModelIndex& index,
        const QVariant& value,
        int role) override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;
    QHash<int, QByteArray> roleNames() const override;

    QModelIndex addPolitician(const Politician& politician);

private:
    bool refreshCachedPolitician(int id); // O(rowCount()) complexity
    void loadPoliticianCache();

private:
    std::vector<std::shared_ptr<Politician>> politicianCache_;
    std::shared_ptr<IPoliticianDatabaseManager> manager_;
};

#endif // POLITICIANMODEL_H
