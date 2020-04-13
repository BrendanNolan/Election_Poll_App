TARGET = utils_geometric
TEMPLATE = lib
CONFIG += static

HEADERS += \
    geom_defs.h \
    Point.h \
    Polygon.h \
    geom_functions.h \
    point_utils.h \
    QtSceneCoordConverter.h \
    GraphicsItemLayoutEngine.h \
    GraphicsItemInflatingPositioningEngine.h

SOURCES += \
    Point.cpp \
    Polygon.cpp \
    geom_functions.cpp \
    point_utils.cpp \
    QtSceneCoordConverter.cpp \
    GraphicsItemInflatingPositioningEngine.cpp
