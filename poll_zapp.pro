TEMPLATE = subdirs

SUBDIRS += \
    cpp_code/poll_zapp_gui \
    cpp_code/poll_zapp_core \
    cpp_code/geometry \
    cpp_code/qt_graphics_utils

cpp_code/poll_zapp_gui.depends += \
    cpp_code/poll_zapp_core \
    cpp_code/geometry \
    cpp_code/qt_graphics_utils

cpp_code/qt_graphics_utils.depends += \
    cpp_code/geometry
