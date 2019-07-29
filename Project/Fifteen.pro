
SOURCES += \
    Board.cpp \
    Entry.cpp \
    FileBoard/IODataModel.cpp \
    GraphicBoard/ImageProvider.cpp \
    Options.cpp \
    GraphicBoard/GraphicBoard.cpp \
    Message.cpp \
    UndoMove.cpp \
    FileBoard/IOBoard.cpp \
    FileBoard/IOFile.cpp \
    MappedValues.cpp \
    Fifteen.cpp \
    GUI/GUIMain.cpp \
    GUI/GUIAbout.cpp \
    GUI/GUISetting.cpp

HEADERS += \
    Board.h \
    FileBoard/IODataModel.h \
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
    GUI/GUIMain.h \
    GUI/GUIAbout.h \
    GUI/GUISetting.h

QMAKE_CFLAGS_DEBUG  = -g
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS += -std=c++17
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
