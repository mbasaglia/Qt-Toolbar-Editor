#-------------------------------------------------
#
# Project created by QtCreator 2013-04-07T20:08:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(toolbar_editor/toolbar_editor.pri)

TARGET = ToolbarEditor
TEMPLATE = app


SOURCES += main.cpp\
        test_window.cpp

HEADERS  += test_window.hpp

FORMS    += test_window.ui
