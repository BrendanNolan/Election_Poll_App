#ifndef QT_NONQT_CONVERSION_FUNCTIONS_H
#define QT_NONQT_CONVERSION_FUNCTIONS_H

#include <QColor>
#include <QString>
#include <QVariant>

namespace qt_nonqt_conversions
{

QColor hashToColour(const QHash<QString, QVariant>& hash);

}// namespace qt_nonqt_conversions

#endif// QT_NONQT_CONVERSION_FUNCTIONS_H
