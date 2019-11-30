#ifndef CONSTITUENCYMODEL_H
#define CONSTITUENCYMODEL_H

#include <QAbstractTableModel>

#include <vector>

#include "Constituency.h"


class ConstituencyModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum class Role
    {
        LatitudeRole = Qt::UserRole + 1,
        NameRole,
        CurrentPartyRole,
        CurrentMPRole
    };

    QVariant data(
        const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount() const;

private:
    std::vector<Constituency> constituencies_;
};

#endif // CONSTITUENCYMODEL_H
