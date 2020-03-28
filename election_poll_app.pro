TEMPLATE = subdirs

SUBDIRS += \
    cpp_code/election_gui \
    cpp_code/election_core

election_gui.depends = election_core
