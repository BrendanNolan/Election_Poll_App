#ifndef PIXMAPCREATINGFUNCTOR_H
#define PIXMAPCREATINGFUNCTOR_H

class QModelIndex;

class PixmapCreatingFunctor
{
public:
    virtual QPixmap operator()(const QModelIndex& index) const = 0;
};

#endif // PIXMAPCREATINGFUNCTOR_H
