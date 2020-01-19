#ifndef CONSTITUENCYSCENE_H
#define CONSTITUENCYSCENE_H

#include <QGraphicsScene>

class ConstituencyScene : public QGraphicsScene
{
public:

signals:
    void activated(QGraphicsItem* item);
};

#endif // CONSTITUENCYSCENE_H
