TEMPLATE = subdirs

SUBDIRS += \
    cpp_code/poll_zapp_gui \
    cpp_code/poll_zapp_core \
    cpp_code/utils_geometric

poll_zapp_gui.depends += \
    poll_zapp_core \
    utils_geometric
