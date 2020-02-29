#ifndef POLLRESULTPIXMAPCREATINGFUNCTOR_H
#define POLLRESULTPIXMAPCREATINGFUNCTOR_H

#include "PixmapCreatingFunctor.h"

#include <QPixmap>

class PollResultModel;
class QModelIndex;

class PollResultPixmapCreatingFunctor : public PixmapCreatingFunctor
{
public:
    PollResultPixmapCreatingFunctor(const PollResultModel* pollResultModel);

private:
    QPixmap operator()(const QModelIndex& index) const override;

private:
    const PollResultModel* pollResultModel_;
};

#endif// POLLRESULTPIXMAPCREATINGFUNCTOR_H
