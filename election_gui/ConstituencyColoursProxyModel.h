#ifndef CONSTITUENCYCOLOURSPROXYMODEL_H
#define CONSTITUENCYCOLOURSPROXYMODEL_H

#include <QColor>
#include <QIdentityProxyModel>
#include <QMap>

class PoliticianModel;

class ConstituencyColoursProxyModel : public QIdentityProxyModel
{
public:
    // In this constructor, will probably need to connect politicianModel_ 
    // and sourceModel() signals to lambdas which just call
    // ConstituencyColoursProxyModel::loadConstituencyColourCache() and 
    // ConstituencyColoursProxyModel::reLoadConstituencyColourCache().
    ConstituencyColoursProxyModel(
        QObject* parent = nullptr,
        PoliticianModel* politicianModel = nullptr);
    
    void setPoliticianModel(PoliticianModel* politicianModel);
    
private:
    void loadConstituencyColourCache(const QModelIndex& startIndex, int count);
    void reLoadConstituencyColourCache();

private:
    PoliticianModel* politicianModel_ = nullptr;
    QMap<QModelIndex, QColor> constituencyColourCache_;
};

#endif // CONSTITUENCYCOLOURSPROXYMODEL_H
