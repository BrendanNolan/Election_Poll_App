QT += sql

TARGET = election_core
TEMPLATE = lib
CONFIG += shared

DEFINES += ELECTIONCORE_LIBRARY

SOURCES += \
    SqlConstituencyDatabaseManager.cpp \
    Constituency.cpp \
    ConstituencyModel.cpp \
    PoliticianModel.cpp \
    PollResultModel.cpp \
    SqlDatabaseManagerFactory.cpp \
    Politician.cpp \
    PollResult.cpp \
    SqlPollResultDatabaseManager.cpp \
    SqlPoliticianDatabaseManager.cpp

HEADERS += \
    election_core_global.h \
    IConstituencyDatabaseManager.h \
    SqlConstituencyDatabaseManager.h \
    Constituency.h \
    ConstituencyModel.h \
    PoliticianModel.h \
    PollResultModel.h \
    IPollResultDatabaseManager.h \
    IPoliticianDatabaseManager.h \
    IDatabaseManagerFactory.h \
    SqlDatabaseManagerFactory.h \
    Politician.h \
    PollResult.h \
    SqlPollResultDatabaseManager.h \
    SqlPoliticianDatabaseManager.h
