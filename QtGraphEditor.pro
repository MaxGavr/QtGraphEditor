#-------------------------------------------------
#
# Project created by QtCreator 2017-03-01T17:44:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtGraphEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    workspace.cpp \
    node.cpp \
    edge.cpp

HEADERS  += mainwindow.h \
    workspace.h \
    node.h \
    edge.h
