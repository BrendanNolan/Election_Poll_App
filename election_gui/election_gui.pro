QT += core gui widgets sql

TARGET = election_gui
TEMPLATE = app

HEADERS += \
    ConstituencyWidget.h \
    PoliticianListWidget.h \
    ConstituencyExplorerWidget.h \
    RectanglePositionCalculator.h \
    MainWindow.h \
    PollGraphProxyModel.h \
    PoliticianPictureProxyModel.h \
    ConstituencyColoursProxyModel.h

SOURCES += \
    ConstituencyWidget.cpp \
    PoliticianListWidget.cpp \
    ConstituencyExplorerWidget.cpp \
    RectanglePositionCalculator.cpp \
    main.cpp \
    MainWindow.cpp \
    PollGraphProxyModel.cpp \
    PoliticianPictureProxyModel.cpp \
    ConstituencyColoursProxyModel.cpp

FORMS += \
    PoliticianListWidget.ui \
    ConstituencyExplorerWidget.ui

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
