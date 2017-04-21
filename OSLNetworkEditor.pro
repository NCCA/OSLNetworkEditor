TARGET=OSLNetworkEditor
CONFIG+=c++11
CONFIG-=app_bundle
SOURCES += $$PWD/src/ShaderParser.cpp \
           $$PWD/src/main.cpp \
           $$PWD/src/ShaderDataModel.cpp \
           $$PWD/src/MainWindow.cpp \
           $$PWD/src/ShaderParams.cpp

HEADERS+= $$PWD/include/ShaderParser.h \
          $$PWD/include/ShaderDataModel.h \
          $$PWD/include/ShaderNodeData.h \
          $$PWD/include/MainWindow.h \
          $$PWD/include/ShaderParams.h

QT+= core widgets gui

INCLUDEPATH+=$$PWD/include
INCLUDEPATH+=/usr/local/include
LIBS+= -L/usr/local/lib -lnodes
DEFINES+=NODE_EDITOR_STATIC
MOC_DIR=$$PWD/moc
OBJECTS_DIR=$$PWD/obj
UI_HEADERS_DIR=$$PWD/include

FORMS += \
          $$PWD/ui/ShaderParams.ui
