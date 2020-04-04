QT -= \
    core \
    gui

TARGET = utils_geometric
TEMPLATE = lib
CONFIG += static

HEADERS += \
    geom_defs.h \
    Points.h \
    Polygon.h \
    IPolygonLayoutEngine.h \
    PolygonInflatingPositioningEngine.h

SOURCES += \
    Points.cpp \
    Polygon.cpp \
    PolygonInflatingPositioningEngine.cpp
