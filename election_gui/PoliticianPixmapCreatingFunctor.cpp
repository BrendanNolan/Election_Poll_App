#include "PoliticianPixmapCreatingFunctor.h"

#include <QModelIndex>
#include <QString>

#include "PoliticianModel.h"

PoliticianPixmapCreatingFunctor::PoliticianPixmapCreatingFunctor(
    const PoliticianModel* politicianModel)
    : politicianModel_(politicianModel)
{}

QPixmap PoliticianPixmapCreatingFunctor::operator()(
    const QModelIndex & index) const
{
    if (!politicianModel_)
        return QPixmap();

    auto path = politicianModel_->data(
        index, PoliticianModel::FilePathRole).toString();
    return QPixmap(path);
}
