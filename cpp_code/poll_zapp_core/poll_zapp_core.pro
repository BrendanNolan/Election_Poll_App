include($$top_srcdir/paths.pri)

QT += sql
QT -= gui

TARGET = poll_zapp_core
TEMPLATE = lib
CONFIG += static

SOURCES += \
    SqlConstituencyDatabaseManager.cpp \
    Constituency.cpp \
    ConstituencyModel.cpp \
    PoliticianModel.cpp \
    PollResultModel.cpp \
    IPollResultDatabaseManager.cpp \
    IPoliticianDatabaseManager.cpp \
    IConstituencyDatabaseManager.cpp \
    SqlDatabaseManagerFactory.cpp \
    Politician.cpp \
    PollResult.cpp \
    SqlPollResultDatabaseManager.cpp \
    SqlPoliticianDatabaseManager.cpp \
    app_data_functions.cpp \
    poll_zapp_core_utils.cpp

HEADERS += \
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
    SqlPoliticianDatabaseManager.h \
    UnaryPredicate.h \
    app_data_functions.h \
    DatabaseSignaller.h \
    RollingKeyValueCache.h \
    poll_zapp_core_utils.h

INCLUDEPATH += \
    $$(PYTHON_38_STUFF)\include
