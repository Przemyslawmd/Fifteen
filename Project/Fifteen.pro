
SOURCES += \
    WindowSetting.cpp \
    MainWindow.cpp \
    Board.cpp \
    Entry.cpp \
    WindowAbout.cpp \
    GraphicBoard/ImageLoad.cpp \
    GraphicBoard/ImageProvider.cpp \
    Options.cpp \
    GraphicBoard/GraphicBoard.cpp \
    IOFile.cpp

HEADERS += \
    WindowSetting.h \
    MainWindow.h \
    Board.h \
    WindowAbout.h \
    Types.h \
    GraphicBoard/ImageLoad.h \
    GraphicBoard/ImageProvider.h \
    Options.h \
    GraphicBoard/GraphicBoard.h \
    IOFile.h

QMAKE_CFLAGS_DEBUG  = -g
QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
