include($$top_srcdir/paths.pri)

TARGET = utils_qt_dep
TEMPLATE = lib
CONFIG += static

HEADERS += \
    point_utils.h

SOURCES += \
    point_utils.cpp

INCLUDEPATH += \
    $$utils_geometric_source_path
