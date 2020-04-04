TEMPLATE = subdirs

SUBDIRS += \
    cpp_code/election_gui \
    cpp_code/election_core \
    cpp_code/utils_geometric

election_gui.depends += \
    election_core \
    utils_geometric
