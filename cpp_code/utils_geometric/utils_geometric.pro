QT -= \
    core \
    gui

TARGET = utils_geometric
TEMPLATE = lib
CONFIG += static

HEADERS += \
    geom_defs.h \
    Points.h \
    Rectangle.h \
    RectanglePositionCalculator.h

SOURCES += \
    Points.cpp \
    Rectangle.cpp \
    RectanglePositionCalculator.cpp
