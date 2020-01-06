QT += core gui widgets

TARGET = election_gui
TEMPLATE = app

HEADERS += \
    ConstituencyWidget.h \
    ConstituencyWidgetView.h

SOURCES += \
    ConstituencyWidget.cpp \
    ConstituencyWidgetView.cpp

FORMS += \
    ConstituencyWidget.ui
    