# Load this project with Qt creator
#################################################################
TEMPLATE = app
QT += opengl
CONFIG += debug
include($$PWD/../../framework/framework.pri)


INCLUDEPATH += $$PWD/src

################################################################
# Plugin configuration - modify these for your example
# MX_PLUGIN_HEADER: Header file containing the plugin class definition
# MX_PLUGIN_CLASS: Name of the plugin class to instantiate
################################################################

DEFINES += MX_PLUGIN_HEADER=\\\"starsmodule.h\\\" \
           MX_PLUGIN_CLASS=StarsModule

SOURCES += $$PWD/src/starsmodule.cpp \
           $$PWD/src/starsprogram.cpp

HEADERS += $$PWD/src/starsmodule.h \
           $$PWD/src/starsprogram.h





