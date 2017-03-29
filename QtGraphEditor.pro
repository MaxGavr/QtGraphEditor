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

SOURCES += main.cpp\
        mainwindow.cpp \
    workspace.cpp \
    graphnode.cpp \
    graphedge.cpp \
    graph.cpp \
    graphicsnodeitem.cpp \
    graphicsedgeitem.cpp

HEADERS  += mainwindow.h \
    workspace.h \
    graphicsedgeitem.h \
    graphicsnodeitem.h \
    graphnode.h \
    graphedge.h \
    graph.h
