
QT       += testlib

TARGET = testfifteen
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    ../Project/Options.cpp \
    ../Project/GraphicBoard/GraphicBoard.cpp \
    ../Project/GraphicBoard/ImageProvider.cpp \
    ../Project/Message.cpp \
    Suites.cpp \
    Test.cpp \
    DataGraphic.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../Project/Options.h \
    ../Project/GraphicBoard/GraphicBoard.h \
    ../Project/GraphicBoard/ImageProvider.h \
    ../Project/Message.h \
    Test.h \
    DataGraphic.h

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS += -std=c++17
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
