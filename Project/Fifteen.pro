
SOURCES += \
    Board.cpp \
    Entry.cpp \
    GraphicBoard/ImageProvider.cpp \
    Options.cpp \
    GraphicBoard/GraphicBoard.cpp \
    Message.cpp \
    UndoMove.cpp \
    FileBoard/IOBoard.cpp \
    FileBoard/IOFile.cpp \
    MappedValues.cpp \
    Fifteen.cpp \
    GUIMain.cpp \
    GUIAbout.cpp \
    GUISetting.cpp

HEADERS += \
    Board.h \
    Types.h \
    GraphicBoard/ImageProvider.h \
    Options.h \
    GraphicBoard/GraphicBoard.h \
    Message.h \
    UndoMove.h \
    FileBoard/IOBoard.h \
    FileBoard/IOFile.h \
    MappedValues.h \
    Fifteen.h \
    GUIMain.h \
    GUIAbout.h \
    GUISetting.h

QMAKE_CFLAGS_DEBUG  = -g
QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
