
QT       += core gui

OBJECTS_DIR = out/obj
MOC_DIR = out/generated
UI_DIR = out/generated
RCC_DIR = out/generated

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(toolbar_editor/toolbar_editor.pri)

TARGET = ToolbarEditor
TEMPLATE = app


SOURCES += main.cpp\
        test_window.cpp

HEADERS  += test_window.hpp

FORMS    += test_window.ui
