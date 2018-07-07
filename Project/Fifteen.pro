
SOURCES += \
    WindowSetting.cpp \
    MainWindow.cpp \
    Board.cpp \
    Entry.cpp \
    WindowAbout.cpp \
    GraphicBoard/ImageProvider.cpp \
    Options.cpp \
    GraphicBoard/GraphicBoard.cpp \
    Message.cpp \
    UndoMove.cpp \
    FileBoard/IOBoard.cpp \
    FileBoard/IOFile.cpp

HEADERS += \
    WindowSetting.h \
    MainWindow.h \
    Board.h \
    WindowAbout.h \
    Types.h \
    GraphicBoard/ImageProvider.h \
    Options.h \
    GraphicBoard/GraphicBoard.h \
    Message.h \
    UndoMove.h \
    FileBoard/IOBoard.h \
    FileBoard/IOFile.h

QMAKE_CFLAGS_DEBUG  = -g
QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
