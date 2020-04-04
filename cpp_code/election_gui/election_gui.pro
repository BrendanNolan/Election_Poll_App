include($$top_srcdir/paths.pri)

QT += core gui widgets sql

TARGET = election_gui
TEMPLATE = app

HEADERS += \
    ConstituencyWidget.h \
    ConstituencyDrillDownWidget.h \
    ConstituencyExplorerWidget.h \
    MainWindow.h \
    ThinPixmapDelegate.h \
    RotatingItemsWidget.h \
    ConstituencyColoursProxyModel.h \
    PoliticianPictureProxyModel.h \
    PollResultPlotProxyModel.h \
    HistogramPainter.h \
    IPlotPainter.h \
    StartupHandler.h

SOURCES += \
    ConstituencyWidget.cpp \
    ConstituencyDrillDownWidget.cpp \
    ConstituencyExplorerWidget.cpp \
    main.cpp \
    MainWindow.cpp \
    ThinPixmapDelegate.cpp \
    RotatingItemsWidget.cpp \
    ConstituencyColoursProxyModel.cpp \
    PoliticianPictureProxyModel.cpp \
    PollResultPlotProxyModel.cpp \
    HistogramPainter.cpp \
    StartupHandler.cpp

FORMS += \
    ConstituencyDrillDownWidget.ui \
    ConstituencyExplorerWidget.ui

INCLUDEPATH += \
    $$election_core_source_path \
    $$utils_geometric_source_path \
    $$(PYTHON_38_STUFF)\include

win32:CONFIG(release, debug|release) {
    LIBS += \ 
        -L$$election_core_build_path/release/ \
        -L$$utils_geometric_build_path/release/ \
        -L$$(PYTHON_38_STUFF)/libs/ \
        -lelection_core \
        -lutils_geometric \
        -lpython38
}
else:win32:CONFIG(debug, debug|release) {
    LIBS += \ 
        -L$$election_core_build_path/debug/ \
        -L$$utils_geometric_build_path/debug/ \
        -L$$(PYTHON_38_STUFF)/libs/ \ 
        -lelection_core \
        -lutils_geometric \
        -lpython38_d
}
else:unix {
    LIBS += \
        -L$$election_core_build_path/ \
        -L$$utils_geometric_build_path/ \
        -lutils_geometric \
        -lelection_core
}

win32:CONFIG(release, debug|release) {
    QMAKE_POST_LINK += cp $$(PYTHON_38_STUFF)/python38.dll $$election_gui_build_path/release/
}
else:win32:CONFIG(debug, debug|release) {
    QMAKE_POST_LINK += cp $$(PYTHON_38_STUFF)/python38_d.dll $$election_gui_build_path/debug/
}
