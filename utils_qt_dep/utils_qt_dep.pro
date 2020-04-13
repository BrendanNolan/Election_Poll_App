include($$top_srcdir/paths.pri)

TARGET = utils_qt_dep
TEMPLATE = lib
CONFIG += static

HEADERS += \
    point_utils.h \
    QtSceneCoordConverter.h \
    qt_nonqt_conversion_functions.h

SOURCES += \
    point_utils.cpp \
    QtSceneCoordConverter.cpp \
    qt_nonqt_conversion_functions.cpp

INCLUDEPATH += \
    $$utils_geometric_source_path
