include($$top_srcdir/paths.pri)

QT += widgets

TARGET = utils_qt_dep
TEMPLATE = lib
CONFIG += static

HEADERS += \
    point_utils.h \
    QtSceneCoordConverter.h \
    GraphicsItemLayoutEngine.h \
    GraphicsItemInflatingPositioningEngine.h
    
SOURCES += \
    point_utils.cpp \
    QtSceneCoordConverter.cpp \
    GraphicsItemInflatingPositioningEngine.cpp
    
INCLUDEPATH += \
    $$utils_geometric_source_path
