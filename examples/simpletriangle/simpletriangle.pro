# Load this project with Qt creator
#################################################################
TEMPLATE = app
QT += opengl
CONFIG += debug
include($$PWD/../../framework/framework.pri)


INCLUDEPATH += $$PWD/src

################################################################
# Plugin configuration - modify these for your example
# MX_MODULE_HEADER: Header file containing the plugin class definition
# MX_MODULE_CLASS: Name of the plugin class to instantiate
################################################################

DEFINES += MX_MODULE_HEADER=\\\"simpletriangle.h\\\" \
           MX_MODULE_CLASS=SimpleTriangle

SOURCES += $$PWD/src/simpletriangle.cpp \
           $$PWD/src/triangleprogram.cpp

HEADERS += $$PWD/src/simpletriangle.h \
           $$PWD/src/triangleprogram.h





