#-------------------------------------------------
#
# Project created by QtCreator 2018-07-11T20:46:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Conver2UTF8
TEMPLATE = app
#LIBS += D:\ProgramFiles\Qt\Qt5.7.0\Tools\mingw530_32\i686-w64-mingw32\lib/libiconv.a

SOURCES += main.cpp\
        mainwindow.cpp \
    AboutDialog.cpp \
    ConvertFormat.cpp

HEADERS  += mainwindow.h \
    AboutDialog.h \
    ConvertFormat.h \
    IconvPair.h

FORMS    += mainwindow.ui \
    AboutDialog.ui

DISTFILES +=

RESOURCES += \
    resource.qrc
