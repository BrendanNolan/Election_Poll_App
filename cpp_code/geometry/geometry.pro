QT -= \
    core \
    gui

TARGET = geometry
TEMPLATE = lib
CONFIG += static

HEADERS += \
    geom_defs.h \
    Point.h \
    Polygon.h \
    geom_functions.h

SOURCES += \
    Point.cpp \
    Polygon.cpp \
    geom_functions.cpp
