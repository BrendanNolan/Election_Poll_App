#ifndef POLLRESULTHISTOGRAMPROXYMODEL_H
#define POLLRESULTHISTOGRAMPROXYMODEL_H

#include <QIdentityProxyModel>

class PollResultModel;

class PollResultHistogramProxyModel : public QIdentityProxyModel
{
public:
    PollResultHistogramProxyModel(
        QObject* parent = nullptr, PollResultModel* pollResultModel = nullptr);

    QVariant data(
        const QModelIndex& index, int role = Qt::DecorationRole) const override;
    void setSourceModel(QAbstractItemModel* source) override;
    PollResultModel* pollResultModel() const;

private:
    void partiallyReloadCache(const QModelIndex& startIndex, int count);
    void reloadCache();

private:
    QHash<QString, QPixmap> pixmapCache_;
};
};

#endif // POLLRESULTHISTOGRAMPROXYMODEL_H
