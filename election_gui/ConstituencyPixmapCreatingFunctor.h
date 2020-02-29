#ifndef CONSTITUENCYPIXMAPCREATINGFUNCTOR_H
#define CONSTITUENCYPIXMAPCREATINGFUNCTOR_H

#include "PixmapCreatingFunctor.h"
#include "PoliticianModel.h"

#include <QPixmap>

class ConstituencyModel;
class PoliticianModel;
class QModelIndex;

class ConstituencyPixmapCreatingFunctor : public PixmapCreatingFunctor
{
public:
    ConstituencyPixmapCreatingFunctor(
        const ConstituencyModel* constituencyModel,
        const PoliticianModel& politicianModel);

private:
    QPixmap operator()(const QModelIndex& index) const override;

private:
    const ConstituencyModel* constituencyModel_;
    mutable PoliticianModel politicianModel_;
};

#endif// CONSTITUENCYPIXMAPCREATINGFUNCTOR_H
