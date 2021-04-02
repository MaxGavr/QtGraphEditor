#-------------------------------------------------
#
# Project created by QtCreator 2017-03-01T17:44:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtGraphEditor
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += src/

SOURCES += $$files("src/*.cpp", true)
HEADERS += $$files("src/*.h", true)

RESOURCES += \
    icons.qrc
