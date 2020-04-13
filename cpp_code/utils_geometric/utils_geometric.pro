QT -= \
    core \
    gui

TARGET = utils_geometric
TEMPLATE = lib
CONFIG += static

HEADERS += \
    geom_defs.h \
    Point.h \
    Polygon.h \
    geom_functions.h \
    GraphicsItemLayoutEngine.h \
    GraphicsItemInflatingPositioningEngine.h

SOURCES += \
    Point.cpp \
    Polygon.cpp \
    geom_functions.cpp \
    GraphicsItemInflatingPositioningEngine.cpp
