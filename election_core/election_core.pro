QT += sql
QT -= gui

TARGET = election_core
TEMPLATE = lib
CONFIG += shared

DEFINES += ELECTIONCORE_LIBRARY

SOURCES += \
    SqlConstituencyDataManager.h

HEADERS += \
    election_core_global.h \
    ConstituencyDataManagerBase.h \
    SqlConstituencyDataManager.cpp
