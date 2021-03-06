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

PROJECT_ROOT = ../

INCLUDEPATH += $${PROJECT_ROOT}/src/

SOURCES += $$files("$${PROJECT_ROOT}/src/*.cpp", true)
HEADERS += $$files("$${PROJECT_ROOT}/src/*.h", true)

RESOURCES += \
    $${PROJECT_ROOT}/resources/icons.qrc
