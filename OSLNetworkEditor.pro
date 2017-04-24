TARGET=OSLNetworkEditor
CONFIG+=c++11
CONFIG-=app_bundle
SOURCES += $$PWD/src/ShaderParser.cpp \
           $$PWD/src/main.cpp \
           $$PWD/src/ShaderDataModel.cpp \
           $$PWD/src/MainWindow.cpp \
           $$PWD/src/ShaderParams.cpp \
           $$PWD/nodes/*.cpp

HEADERS+= $$PWD/include/ShaderParser.h \
          $$PWD/include/ShaderDataModel.h \
          $$PWD/include/ShaderNodeData.h \
          $$PWD/include/MainWindow.h \
          $$PWD/include/ShaderParams.h \
          $$PWD/nodes/*.hpp
OTHER_FILES+=$$PWD/tests/*.rib
QT+= core widgets gui opengl

INCLUDEPATH+=$$PWD/include
INCLUDEPATH+=$$PWD/nodes

DEFINES+=NODE_EDITOR_STATIC
MOC_DIR=$$PWD/moc
OBJECTS_DIR=$$PWD/obj
UI_HEADERS_DIR=$$PWD/include

FORMS+=$$PWD/ui/ShaderParams.ui \
    ui/MainWindow.ui

RESOURCES+= $$PWD/nodes/resources/resources.qrc
