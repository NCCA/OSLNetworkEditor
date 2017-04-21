TARGET=OSLNetworkEditor
CONFIG+=c++11
CONFIG-=app_bundle
SOURCES += $$PWD/src/ShaderParser.cpp \
           $$PWD/src/main.cpp \
           $$PWD/src/ShaderDataModel.cpp \
           $$PWD/src/MainWindow.cpp

HEADERS+= $$PWD/include/ShaderParser.h \
          $$PWD/include/ShaderDataModel.h \
          $$PWD/include/ShaderNodeData.h \
          $$PWD/include/MainWindow.h

QT+= core widgets gui

INCLUDEPATH+=$$PWD/include
INCLUDEPATH+=/usr/local/include
LIBS+= -L/usr/local/lib -lnodes
DEFINES+=NODE_EDITOR_STATIC
MOC_DIR=$$PWD/moc
OBJECTS_DIR=$$PWD/obj
