#include "poll_zapp_gui_utils.h"

#include <QHash>

namespace qt_nonqt_conversions
{

QColor hashToColour(const QHash<QString, QVariant>& hash)
{
    if (!hash.contains("red")
        || !hash.contains("green")
        || !hash.contains("blue"))
    {
        return QColor();
    }

    auto red = hash["red"].toInt();
    auto green = hash["green"].toInt();
    auto blue = hash["blue"].toInt();
    return QColor(red, green, blue);
}

}// namespace qt_nonqt_conversions
