#ifndef POLLGRAPHPROXYMODEL_H
#define POLLGRAPHPROXYMODEL_H

#include <QIdentityProxyModel>

class PollGraphProxyModel : public QIdentityProxyModel
{
    Q_OBJECT
        
public:
    PollGraphProxyModel(QObject* parent = nullptr);

private:

};

#endif // POLLGRAPHPROXYMODEL_H
