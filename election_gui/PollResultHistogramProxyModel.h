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
    
private:    
    PollResultModel* pollResultModel() const;

private:
    QHash<DataToMakeHistogram, QPixmap> pixmapCache_;
};

#endif // POLLRESULTHISTOGRAMPROXYMODEL_H
