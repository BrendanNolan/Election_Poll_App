include($$top_srcdir/paths.pri)

QT += widgets

TARGET = qt_graphics_utils
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
    $$geometry_source_path
