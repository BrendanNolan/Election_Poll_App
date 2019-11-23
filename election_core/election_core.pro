QT += sql
QT -= gui

TARGET = election_core
TEMPLATE = lib
CONFIG += shared

DEFINES += ELECTIONCORE_LIBRARY

SOURCES += \
    SqlConstituencyDataManager.cpp \
    Constituency.cpp

HEADERS += \
    election_core_global.h \
    ConstituencyDataManagerBase.h \
    SqlConstituencyDataManager.h \
    Constituency.h
