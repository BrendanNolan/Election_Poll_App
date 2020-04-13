include($$top_srcdir/paths.pri)

QT += widgets

TARGET = qt_graphics_utils
TEMPLATE = lib
CONFIG += static

HEADERS += \
    qt_point_functions.h \
    QtSceneCoordConverter.h \
    GraphicsItemLayoutEngine.h \
    GraphicsItemInflatingPositioningEngine.h
    
SOURCES += \
    qt_point_functions.cpp \
    QtSceneCoordConverter.cpp \
    GraphicsItemInflatingPositioningEngine.cpp
    
INCLUDEPATH += \
    $$geometry_source_path
