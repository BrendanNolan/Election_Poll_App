TEMPLATE = subdirs

SUBDIRS += \
    election_gui \
    election_core

election_gui.depends = election_core
