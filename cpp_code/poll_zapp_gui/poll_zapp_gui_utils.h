#ifndef POLL_ZAPP_GUI_UTILS_H
#define POLL_ZAPP_GUI_UTILS_H

#include <QColor>
#include <QString>
#include <QVariant>

namespace qt_nonqt_conversion
{

QColor hashToColour(const QHash<QString, QVariant>& hash);

}// namespace qt_nonqt_conversion

#endif// POLL_ZAPP_GUI_UTILS_H
