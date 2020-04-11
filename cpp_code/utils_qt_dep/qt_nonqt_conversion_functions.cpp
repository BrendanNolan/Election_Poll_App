#include "qt_nonqt_conversion_functions.h"

#include <QHash>

namespace qt_nonqt_conversions
{

QColor hashToColour(const QHash<QString, QVariant>& hash)
{
    auto red = hash["red"].toInt();
    auto green = hash["green"].toInt();
    auto blue = hash["blue"].toInt();
    return QColor(red, green, blue);
}

}// namespace qt_nonqt_conversions
