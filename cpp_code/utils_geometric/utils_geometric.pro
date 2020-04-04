QT -= \
    core \
    gui

TARGET = utils_geometric
TEMPLATE = lib
CONFIG += static

HEADERS += \
    Points.h \
    Rectangle.h \
    RectanglePositionCalculator.h

SOURCES += \
    Points.cpp \
    Rectangle.h \
    RectanglePositionCalculator.cpp
