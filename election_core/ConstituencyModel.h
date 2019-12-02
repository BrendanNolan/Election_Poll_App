#ifndef CONSTITUENCYMODEL_H
#define CONSTITUENCYMODEL_H

#include <QAbstractTableModel>

#include <vector>

#include "Constituency.h"


class ConstituencyModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role
    {
        LatitudeRole = Qt::UserRole + 1,
        LongitudeRole,
        NameRole,
        CurrentPartyRole,
        CurrentMPRole
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

    void addConstituency();
    void refreshConstituency();
    void refreshConstituencies();

private:
    std::vector<Constituency> constituencies_;
};

#endif // CONSTITUENCYMODEL_H
