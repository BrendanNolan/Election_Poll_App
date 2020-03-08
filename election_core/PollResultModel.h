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
    PollResultModel(
        const IDatabaseManagerFactory& factory, QObject* parent = nullptr);

    enum Role
    {
        SourceRole = Qt::UserRole + 1,
        DateTimeRole,
        HistogramRole
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(
        const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(
        const QModelIndex& index, const QVariant& value, int role) override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;
    QHash<int, QByteArray> roleNames() const override;

    QModelIndex addPollresult(std::unique_ptr<PollResult> pollResult);

    bool refreshDataSource();

public slots:
    void setConstituency(int id);
    void reload();

private:
    void reloadPollResultCache();

private:
    std::vector<std::unique_ptr<PollResult>> pollResultCache_;
    std::shared_ptr<IPollResultDatabaseManager> manager_ = nullptr;
    int constituencyId_ = -1;
};

#endif// POLLRESULTMODEL_H
