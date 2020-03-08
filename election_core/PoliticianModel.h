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
    Q_OBJECT

public:
    enum class ElectoralStatus
    {
        SITTING,
        CANDIDATE
    };

public:
    PoliticianModel(const IDatabaseManagerFactory& factory,
        QObject* parent = nullptr,
        ElectoralStatus status = ElectoralStatus::SITTING);
    PoliticianModel(const PoliticianModel& rhs);

    enum Role
    {
        NameRole = Qt::UserRole + 1,
        PartyNameRole,
        PartyColourRole,
        FilePathRole
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(
        const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(
        const QModelIndex& index, const QVariant& value, int role) override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;
    QHash<int, QByteArray> roleNames() const override;

    QModelIndex addPolitician(std::unique_ptr<Politician> politician);
    ElectoralStatus electoralStatus() const;

    bool refreshDataSource();

public slots:
    void reload();
    void setElectoralStatus(ElectoralStatus status);
    void setConstituency(int id);
    // int constituencyId() const;

private:
    // bool refreshCachedPolitician(int id); // O(rowCount()) complexity
    void reloadPoliticianCache();

private:
    std::vector<std::unique_ptr<Politician>> politicianCache_;
    std::shared_ptr<IPoliticianDatabaseManager> manager_ = nullptr;
    ElectoralStatus electoralStatus_ = ElectoralStatus::SITTING;
    int constituencyId_ = -1;
};

#endif// POLITICIANMODEL_H
