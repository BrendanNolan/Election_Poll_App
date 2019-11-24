QT += sql
QT -= gui

TARGET = election_core
TEMPLATE = lib
CONFIG += shared

DEFINES += ELECTIONCORE_LIBRARY

SOURCES += \
    SqlConstituencyDataManager.cpp \
    Constituency.cpp \
    ConstituencyModel.cpp \
    ImageModel.cpp \
    PollResultsModel.cpp

HEADERS += \
    election_core_global.h \
    ConstituencyDataManagerBase.h \
    SqlConstituencyDataManager.h \
    Constituency.h \
    ConstituencyModel.h \
    ImageModel.h \
    PollResultsModel.h
