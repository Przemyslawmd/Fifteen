#-------------------------------------------------
#
# Project created by QtCreator 2017-04-22T19:06:52
#
#-------------------------------------------------

QT       += testlib

#QT       -= gui

TARGET = testfifteen
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    Data.cpp \
    ../Project/Options.cpp \
    ../Project/GraphicBoard/GraphicBoard.cpp \
    ../Project/GraphicBoard/ImageProvider.cpp \
    ../Project/Message.cpp \
    Suites.cpp \
    Test.cpp \
    DataCommon.cpp \
    DataGraphic.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    Data.h \
    ../Project/Options.h \
    ../Project/GraphicBoard/GraphicBoard.h \
    ../Project/GraphicBoard/ImageProvider.h \
    ../Project/Message.h \
    Test.h \
    DataCommon.h \
    DataGraphic.h

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
