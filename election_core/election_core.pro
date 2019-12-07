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
    MPModel.cpp \
    PollResultModel.cpp \
    SqlDatabaseManagerFactory.cpp \
    MP.cpp \
    PollResult.cpp \
    SqlPollResultDatabaseManager.cpp \
    SqlMPDatabaseManager.cpp

HEADERS += \
    election_core_global.h \
    IConstituencyDatabaseManager.h \
    SqlConstituencyDatabaseManager.h \
    Constituency.h \
    ConstituencyModel.h \
    MPModel.h \
    PollResultModel.h \
    IPollResultDatabaseManager.h \
    IMPDatabaseManager.h \
    IDatabaseManagerFactory.h \
    SqlDatabaseManagerFactory.h \
    MP.h \
    PollResult.h \
    SqlPollResultDatabaseManager.h \
    SqlMPDatabaseManager.h
