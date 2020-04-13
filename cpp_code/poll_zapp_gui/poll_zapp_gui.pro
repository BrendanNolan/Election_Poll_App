include($$top_srcdir/paths.pri)

QT += widgets sql

TARGET = poll_zapp_gui
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
    StartupHandler.h \
    PlotData.h \
    poll_zapp_gui_utils.h

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
    StartupHandler.cpp \
    PlotData.cpp \
    poll_zapp_gui_utils.cpp

FORMS += \
    ConstituencyDrillDownWidget.ui \
    ConstituencyExplorerWidget.ui

INCLUDEPATH += \
    $$poll_zapp_core_source_path \
    $$utils_geometric_source_path \
    $$(PYTHON_38_STUFF)\include

win32:CONFIG(release, debug|release) {
    LIBS += \ 
        -L$$poll_zapp_core_build_path/release/ \
        -L$$utils_geometric_build_path/release/ \
        -L$$(PYTHON_38_STUFF)/libs/ \
        -lpoll_zapp_core \
        -lutils_geometric \
        -lpython38
}
else:win32:CONFIG(debug, debug|release) {
    LIBS += \ 
        -L$$poll_zapp_core_build_path/debug/ \
        -L$$utils_geometric_build_path/debug/ \
        -L$$(PYTHON_38_STUFF)/libs/ \ 
        -lpoll_zapp_core \
        -lutils_geometric \
        -lpython38_d
}
else:unix {
    LIBS += \
        -L$$poll_zapp_core_build_path/ \
        -L$$utils_geometric_build_path/ \
        -lpoll_zapp_core \
        -lutils_geometric
}

win32:CONFIG(release, debug|release) {
    QMAKE_POST_LINK += cp $$(PYTHON_38_STUFF)/python38.dll $$poll_zapp_gui_build_path/release/
}
else:win32:CONFIG(debug, debug|release) {
    QMAKE_POST_LINK += cp $$(PYTHON_38_STUFF)/python38_d.dll $$poll_zapp_gui_build_path/debug/
}
