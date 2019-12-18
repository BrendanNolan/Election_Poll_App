#ifndef POLLRESULTMODEL_H
#define POLLRESULTMODEL_H

#include <QAbstractListModel>

#include <memory>

class IDatabaseManagerFactory;
class IPollResultDatabaseManager;
class PollResult;

class PollResultModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role
    {
        SourceRole = Qt::UserRole + 1,
        DateTimeRole
    };

public:
    PollResultModel(
        const IDatabaseManagerFactory& factory,
        QObject* parent);

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

    QModelIndex addPollresult(std::unique_ptr<PollResult> pollResult);

private:
    void loadPollResultCache();

private:
    std::vector<std::unique_ptr<PollResult>> pollResultCache_;
    std::shared_ptr<IPollResultDatabaseManager> manager_;
    int constituencyId_;
};

#endif // POLLRESULTMODEL_H
