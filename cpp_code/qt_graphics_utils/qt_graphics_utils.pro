include($$top_srcdir/paths.pri)

QT += widgets

TARGET = qt_graphics_utils
TEMPLATE = lib
CONFIG += static

HEADERS += \
    QtSceneCoordConverter.h \
    GraphicsItemLayoutEngine.h \
    GraphicsItemInflatingPositioningEngine.h \
    qt_point_functions.h
    
SOURCES += \
    QtSceneCoordConverter.cpp \
    GraphicsItemInflatingPositioningEngine.cpp \
    qt_point_functions.cpp
    
INCLUDEPATH += \
    $$geometry_source_path
