#-------------------------------------------------
#
# Project created by QtCreator 2014-12-07T17:49:24
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra -pedantic #c++1z

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PATH
TEMPLATE = app

INCLUDEPATH += "C:\H\M\boost"
#LIBS += "C:\H\M\boost\stage\lib"

SOURCES += main.cpp\
        mainwindow.cpp \
    path.cpp

HEADERS  += mainwindow.h \
    path.h \
    stdafx.h

FORMS    += mainwindow.ui
