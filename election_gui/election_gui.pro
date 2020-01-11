QT += core gui widgets

TARGET = election_gui
TEMPLATE = app

HEADERS += \
    ConstituencyWidget.h \
    MainWindow.h

SOURCES += \
    ConstituencyWidget.cpp \
    MainWindow.cpp

FORMS += \
    ConstituencyWidget.ui \
    MainWindow.ui

INCLUDEPATH += \
    $$PWD/../election_core

win32:CONFIG(release, debug|release) {
    LIBS += \ 
        -L$$OUT_PWD/../election_core/release/ \ 
        -lelection_core
}
else:win32:CONFIG(debug, debug|release) {
    LIBS += \ 
        -L$$OUT_PWD/../election_core/debug/ \ 
        -lelection_core
}
else:unix {
    LIBS += \
        -L$$OUT_PWD/../election_core/ \
        -lelection_core
}