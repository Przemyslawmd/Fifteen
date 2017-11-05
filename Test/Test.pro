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

SOURCES += TestFifteen.cpp \
    Data.cpp \
    TestVector.cpp \
    ../Project/Options.cpp \
    ../Project/GraphicBoard/GraphicBoard.cpp \
    ../Project/GraphicBoard/ImageProvider.cpp \

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    Data.h \
    TestVector.h \
    ../Project/Options.h \
    ../Project/GraphicBoard/GraphicBoard.h \
    ../Project/GraphicBoard/ImageProvider.h \
