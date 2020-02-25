#ifndef PIXMAPCREATINGFUNCTOR_H
#define PIXMAPCREATINGFUNCTOR_H

#include <QPixmap>

class QModelIndex;

class PixmapCreatingFunctor
{
public:
    virtual ~PixmapCreatingFunctor() {}
    virtual QPixmap operator()(const QModelIndex& index) const = 0;
};

#endif // PIXMAPCREATINGFUNCTOR_H
