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
    graph/graph.cpp \
    graph/graphedge.cpp \
    graph/graphnode.cpp \
    graphics/graphicsedgeitem.cpp \
    graphics/graphicsnodeitem.cpp \
    workspace/mainwindow.cpp \
    workspace/workspace.cpp

HEADERS  += graph/graph.h \
    graph/graphedge.h \
    graph/graphnode.h \
    graphics/graphicsedgeitem.h \
    graphics/graphicsnodeitem.h \
    workspace/mainwindow.h \
    workspace/workspace.h \
    graph/exceptions.h
