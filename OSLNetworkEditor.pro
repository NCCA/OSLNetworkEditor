TARGET=OSLNetworkEditor
CONFIG+=c++11
CONFIG-=app_bundle
SOURCES += $$PWD/src/ShaderParser.cpp \
           $$PWD/src/main.cpp

HEADERS+= $$PWD/include/ShaderParser.h

QT+= core widgets gui

INCLUDEPATH+=$$PWD/include
