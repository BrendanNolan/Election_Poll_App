QT += core gui widgets sql

TARGET = election_gui
TEMPLATE = app

HEADERS += \
    ConstituencyWidget.h \
    ConstituencyDrillDownWidget.h \
    ConstituencyExplorerWidget.h \
    RectanglePositionCalculator.h \
    MainWindow.h \
    PoliticianPictureProxyModel.h \
    ConstituencyPixmapProxyModel.h \
    ThinPixmapDelegate.h \
    election_gui_utils.h \
    RotatingItemsWidget.h \
    PollResultHistogramProxyModel.h \
    PixmapCachingProxyModel.h \
    PixmapCreatingFunctor.h \
    PoliticianPixmapCreatingFunctor.h \
    ConstituencyPixmapCreatingFunctor.h \
    PollResultPixmapCreatingFunctor.h

SOURCES += \
    ConstituencyWidget.cpp \
    ConstituencyDrillDownWidget.cpp \
    ConstituencyExplorerWidget.cpp \
    RectanglePositionCalculator.cpp \
    main.cpp \
    MainWindow.cpp \
    PoliticianPictureProxyModel.cpp \
    ConstituencyPixmapProxyModel.cpp \
    ThinPixmapDelegate.cpp \
    election_gui_utils.cpp \
    RotatingItemsWidget.cpp \
    PollResultHistogramProxyModel.cpp \
    PixmapCachingProxyModel.cpp \
    PixmapCreatingFunctor.cpp \
    PoliticianPixmapCreatingFunctor.cpp \
    ConstituencyPixmapCreatingFunctor.cpp \
    PollResultPixmapCreatingFunctor.cpp

FORMS += \
    ConstituencyDrillDownWidget.ui \
    ConstituencyExplorerWidget.ui

INCLUDEPATH += \
    $$PWD/../election_core \
    $$(PYTHON_38_STUFF)\include

win32:CONFIG(release, debug|release) {
    LIBS += \ 
        -L$$OUT_PWD/../election_core/release/ \ 
        -L$$(PYTHON_38_STUFF)/libs/ \
        -lelection_core \
        -lpython38
}
else:win32:CONFIG(debug, debug|release) {
    LIBS += \ 
        -L$$OUT_PWD/../election_core/debug/ \
        -L$$(PYTHON_38_STUFF)/libs/ \ 
        -lelection_core \
        -lpython38_d
}
else:unix {
    LIBS += \
        -L$$OUT_PWD/../election_core/ \
        -lelection_core
}

win32:CONFIG(release, debug|release) {
    QMAKE_POST_LINK += cp $$(PYTHON_38_STUFF)/python38.dll $$OUT_PWD/../election_gui/release/
}
else:win32:CONFIG(debug, debug|release) {
    QMAKE_POST_LINK += cp $$(PYTHON_38_STUFF)/python38_d.dll $$OUT_PWD/../election_gui/debug/
}
