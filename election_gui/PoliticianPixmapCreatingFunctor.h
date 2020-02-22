#ifndef POLITICIANPIXMAPCREATINGFUNCTOR_H
#define POLITICIANPIXMAPCREATINGFUNCTOR_H

#include "PixmapCreatingFunctor.h"

#include <QPixmap>

class PoliticianModel;
class QModelIndex;

class PoliticianPixmapCreatingFunctor : public PixmapCreatingFunctor
{
public:
    PoliticianPixmapCreatingFunctor(const PoliticianModel* politicianModel);

private:
    QPixmap operator()(const QModelIndex& index) const override;

private:
    const PoliticianModel* politicianModel_;
};

#endif // POLITICIANPIXMAPCREATINGFUNCTOR_H
