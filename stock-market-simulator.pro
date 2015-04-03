QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = stock-market-simulator
TEMPLATE = app
CONFIG  += qt

INCLUDEPATH += ./src
INCLUDEPATH += ./include
INCLUDEPATH += ./gui
INCLUDEPATH += ./gui/include
INCLUDEPATH += ./gui/layout

SOURCES += src/main.cpp \
           #src/present_value.cpp \
           gui/src/main_window.cpp

HEADERS += include/present_value.hpp \
           gui/include/main_window.hpp

FORMS   += gui/layout/main_window.ui
