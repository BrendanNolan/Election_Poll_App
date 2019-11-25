QT += sql
QT -= gui

TARGET = election_core
TEMPLATE = lib
CONFIG += shared

DEFINES += ELECTIONCORE_LIBRARY

SOURCES += \
    SqlConstituencyDatabaseManager.cpp \
    Constituency.cpp \
    ConstituencyModel.cpp \
    ImageModel.cpp \
    PollResultsModel.cpp

HEADERS += \
    election_core_global.h \
    IConstituencyDatabaseManager.h \
    SqlConstituencyDatabaseManager.h \
    Constituency.h \
    ConstituencyModel.h \
    ImageModel.h \
    PollResultsModel.h \
    IPollResultsDatabaseManager.h \
    IImageDatabaseManager.h \
    DatabaseManager.h
