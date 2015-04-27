QT += core gui
@gcc* {
    message( "gcc detected" )
    QMAKE_CXXFLAGS += -std=c++1y -Wall
}@
@clang* {
    message( "clang detected" )
    QMAKE_CXXFLAGS += -std=c++1z -Wall
}@
win32:{
    DEFINES += _CRT_SECURE_NO_WARNINGS \
        _SCL_SECURE_NO_WARNINGS
}
win32-msvc* {
    system(cl|grep "Compiler Version 18.") {
        message( "msvc 2013 detected" )
        Release:QMAKE_CXXFLAGS += /MT
        Debug:QMAKE_CXXFLAGS += /MTd
    }
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PATH
TEMPLATE = app

INCLUDEPATH += "C:\H\M\boost"
INCLUDEPATH += "F:\P\thridparty\boost"

SOURCES += main.cpp\
    mainwindow.cpp \
    path.cpp

HEADERS  += mainwindow.h \
    path.h \
    stdafx.h

FORMS += mainwindow.ui
