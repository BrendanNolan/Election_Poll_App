TEMPLATE = subdirs

SUBDIRS += \
    cpp_code/poll_zapp_gui \
    cpp_code/poll_zapp_core \
    cpp_code/utils_geometric \
    cpp_code/utils_qt_dep

cpp_code/poll_zapp_gui.depends += \
    cpp_code/poll_zapp_core \
    cpp_code/utils_geometric \
    cpp_code/utils_qt_dep

cpp_code/utils_qt_dep.depends += \
    cpp_code/utils_geometric
