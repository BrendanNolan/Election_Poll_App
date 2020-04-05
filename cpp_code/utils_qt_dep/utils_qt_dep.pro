include($$top_srcdir/paths.pri)

QT -= \
    gui

TARGET = utils_qt_dep
TEMPLATE = lib
CONFIG += static

HEADERS += \
    point_utils.h \
    QtSceneCoordConverter.h

SOURCES += \
    point_utils.cpp \
    QtSceneCoordConverter.cpp

INCLUDEPATH += \
    $$utils_geometric_source_path
