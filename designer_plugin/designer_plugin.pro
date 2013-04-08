 

CONFIG += plugin
QT += designer
TARGET = toolbar_editor
TEMPLATE = lib
OBJECTS_DIR = ../out/obj
MOC_DIR = ../out/generated
UI_DIR = ../out/generated
RCC_DIR = ../out/generated


HEADERS += \
    toolbar_editor_plugin.hpp \
    config_widget_plugin_collection.hpp

SOURCES += \
    toolbar_editor_plugin.cpp \
    config_widget_plugin_collection.cpp

include(../toolbar_editor.pri)



build_all:!build_pass {
 CONFIG -= build_all
 CONFIG += release
}

# install
target.path += $$[QT_INSTALL_PLUGINS]/designer

unix{
    LIB_TARGET = lib$${TARGET}.so
}
win32 {
    LIB_TARGET = lib$${TARGET}.dll
}
creator.files =$$LIB_TARGET
creator.path = $$[QT_INSTALL_PREFIX]/../../Tools/QtCreator/bin/designer
INSTALLS += target creator
